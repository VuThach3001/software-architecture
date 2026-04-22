/**
 * @file       I2c.c
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      Define the functions for I2C driver based on AUTOSAR
 * @note       None
 */

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ----------------------------------------------------------- */
#include "I2c.h"

#include "gconf_sy_dat.h"
#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
#include "driver/i2c_master.h"
#include "driver/i2c_slave.h"
#include "esp_err.h"
#include "esp_log.h"
#elif CPUVENDOR_SC == CPUVENDOR_SC_STM32
#include "stm32f4xx_hal.h"
#endif

    /* Private defines ---------------------------------------------------- */

    /** @brief Maximum number of Jobs supported */
#define I2C_MAX_JOBS        8u

    /** @brief Maximum number of Sequences supported */
#define I2C_MAX_SEQUENCES   4u

    /** @brief FIFO queue depth for queued async Sequences [CP_SWS_I2C_82304] */
#define I2C_QUEUE_SIZE      I2C_MAX_SEQUENCES

    /** @brief Slave TX/RX ring-buffer depth in bytes */
#define I2C_SLAVE_BUF_DEPTH 256u

    /** @brief ESP-IDF master transaction queue depth for async callbacks */
#define I2C_MASTER_QUEUE_DEPTH 8u

    /** @brief Default transfer timeout in ms (-1 = wait forever) */
#define I2C_XFER_TIMEOUT_MS (-1)

    /* Private enumerate/structure ---------------------------------------- */

    /**
     * @brief External Buffer configuration per Job (AUTOSAR EB concept)
     */
    typedef struct
    {
        I2C_AddressType       nodeAddress;
        I2C_DataConstPtrType *txDataBufferPtr;
        I2C_DataPtrType      *rxDataBufferPtr;
        I2C_NumberOfDataType  length;
        boolean               isConfigured;
    } I2C_JobEBConfigType;

    /* Private macros ----------------------------------------------------- */
    /* Public variables --------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00832] Sequence-end notification callback.
     * @details Single definition here; declared extern in I2c.h.
     *          Caller sets this to their callback before using the driver.
     */
    void (*I2C_SeqEndNotification)(I2C_SequenceType SequenceId, I2C_SequenceResultType Result) = NULL_PTR;

    /* Private variables -------------------------------------------------- */
#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
    static const char *TAG = "I2C_DRV";

    /** @brief I2C master bus handle (CONTROLLER mode) */
    static i2c_master_bus_handle_t s_i2c_bus_handle = NULL;

    /** @brief I2C device handles per Job */
    static i2c_master_dev_handle_t s_i2c_dev_handles[I2C_MAX_JOBS] = { NULL };

    /** @brief I2C slave device handle (TARGET mode) */
    static i2c_slave_dev_handle_t s_i2c_slave_handle = NULL;
#endif /* CPUVENDOR_SC == CPUVENDOR_SC_ESP32 */

    /** @brief Pointer to configuration provided at I2C_Init */
    static const I2C_ConfigType *s_i2c_config = NULL_PTR;

    /** @brief External Buffer config per Job */
    static I2C_JobEBConfigType s_i2c_job_eb[I2C_MAX_JOBS];

    /** @brief Current driver bus status */
    static I2C_StatusType s_i2c_status = I2C_UNINIT;

    /** @brief Per-sequence result [CP_SWS_I2C_80701] */
    static I2C_SequenceResultType s_i2c_seq_result[I2C_MAX_SEQUENCES];

    /* -------------------------------------------------------------------- */
    /* Async FIFO queue  [CP_SWS_I2C_82304]                                 */
    /* -------------------------------------------------------------------- */
    static I2C_SequenceType s_async_queue[I2C_QUEUE_SIZE];
    static uint8            s_async_queue_head  = 0u;
    static uint8            s_async_queue_tail  = 0u;
    static uint8            s_async_queue_count = 0u;

    /* -------------------------------------------------------------------- */
    /* Polling-mode deferred completion state                               */
    /* -------------------------------------------------------------------- */
    static volatile boolean                s_polling_done[I2C_MAX_SEQUENCES];
    static volatile I2C_SequenceResultType s_polling_result[I2C_MAX_SEQUENCES];

    /** @brief Set by INTERRUPT-mode ISR; cleared by I2C_MainFunction */
    static volatile boolean s_drain_queue_requested = FALSE;

    /* -------------------------------------------------------------------- */
    /* TARGET mode listening state                                          */
    /* -------------------------------------------------------------------- */
    static I2C_SequenceType s_listening_seq_id = 0u;
    static boolean          s_listening_active = FALSE;

    static volatile boolean                s_slave_rx_done   = FALSE;
    static volatile boolean                s_slave_tx_done   = FALSE;
    static volatile I2C_SequenceResultType s_slave_rx_result = I2C_SEQ_OK;

    /* Private function prototypes ---------------------------------------- */
    static void I2C_Prv_NotifySeqEnd(I2C_SequenceType SequenceId, I2C_SequenceResultType Result);
    static void I2C_Prv_DrainQueue(void);

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
    static Std_ReturnType I2C_Prv_AddDevice(I2C_JobType JobId, I2C_AddressType NodeAddress);
    static Std_ReturnType I2C_Prv_ExecuteJob(I2C_JobType JobId);

    static boolean I2C_Prv_AsyncDoneCallback(i2c_master_dev_handle_t        i2c_dev,
                                             const i2c_master_event_data_t *evt_data,
                                             void                          *arg);
    static boolean I2C_Prv_SlaveReceiveCb(i2c_slave_dev_handle_t                i2c_slave,
                                          const i2c_slave_rx_done_event_data_t *evt_data,
                                          void                                 *arg);
    static boolean I2C_Prv_SlaveRequestCb(i2c_slave_dev_handle_t                i2c_slave,
                                          const i2c_slave_request_event_data_t *evt_data,
                                          void                                 *arg);
#endif /* CPUVENDOR_SC == CPUVENDOR_SC_ESP32 */

    /* Function definitions ----------------------------------------------- */
    /**
     * @brief [CP_SWS_I2C_82002] I2C_Init
     * @details Initialises hardware and resets all sequence results to
     *          I2C_SEQ_OK. For TARGET mode creates the slave device and, when
     *          I2cTargetListening == TRUE, pre-registers slave event callbacks
     *          for permanent listening [CP_SWS_I2C_80901].
     */
    void I2C_Init(const I2C_ConfigType *ConfigPtr)
    {
        if (ConfigPtr == NULL_PTR)
        {
            return;
        }

        /* [CP_SWS_I2C_82002] Reset all sequence results */
        for (uint8 idx = 0u; idx < I2C_MAX_SEQUENCES; idx++)
        {
            s_i2c_seq_result[idx] = I2C_SEQ_OK;
            s_polling_done[idx]   = FALSE;
            s_polling_result[idx] = I2C_SEQ_OK;
        }
        for (uint8 idx = 0u; idx < I2C_MAX_JOBS; idx++)
        {
            s_i2c_job_eb[idx].isConfigured = FALSE;
        }

        s_async_queue_head      = 0u;
        s_async_queue_tail      = 0u;
        s_async_queue_count     = 0u;
        s_drain_queue_requested = FALSE;
        s_listening_active      = FALSE;
        s_slave_rx_done         = FALSE;
        s_slave_tx_done         = FALSE;

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        if (ConfigPtr->hwUnitMode == I2C_HW_UNIT_MODE_CONTROLLER)
        {
            /* CONTROLLER (Master) mode */
            i2c_master_bus_config_t bus_cfg = {
                .clk_source                   = I2C_CLK_SRC_DEFAULT,
                .glitch_ignore_cnt            = 7u,
                .i2c_port                     = ConfigPtr->i2c_port,
                .sda_io_num                   = ConfigPtr->sda_pin,
                .scl_io_num                   = ConfigPtr->scl_pin,
                .trans_queue_depth            = I2C_MASTER_QUEUE_DEPTH,
                .flags.enable_internal_pullup = true,
            };
            ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &s_i2c_bus_handle));
        }
        else
        {
            /* TARGET (Slave) mode */
            i2c_slave_config_t slave_cfg = {
                .i2c_port                     = ConfigPtr->i2c_port,
                .sda_io_num                   = ConfigPtr->sda_pin,
                .scl_io_num                   = ConfigPtr->scl_pin,
                .clk_source                   = I2C_CLK_SRC_DEFAULT,
                .slave_addr                   = (uint16) ConfigPtr->deviceAddress,
                .send_buf_depth               = I2C_SLAVE_BUF_DEPTH,
                .receive_buf_depth            = I2C_SLAVE_BUF_DEPTH,
                .flags.enable_internal_pullup = true,
            };
            ESP_ERROR_CHECK(i2c_new_slave_device(&slave_cfg, &s_i2c_slave_handle));

            /* [CP_SWS_I2C_80901] Permanent listening: register callbacks now */
            if (ConfigPtr->targetListening == TRUE)
            {
                i2c_slave_event_callbacks_t cbs = {
                    .on_receive = I2C_Prv_SlaveReceiveCb,
                    .on_request = I2C_Prv_SlaveRequestCb,
                };
                /* Sequence 0 is the default for always-listening mode */
                ESP_ERROR_CHECK(
                  i2c_slave_register_event_callbacks(s_i2c_slave_handle, &cbs, (void *) (uintptr_t) 0u));
                s_listening_seq_id = 0u;
                s_listening_active = TRUE;
            }
        }
#elif CPUVENDOR_SC == CPUVENDOR_SC_STM32
    /* STM32 I2C initialisation via HAL */
#endif /* CPUVENDOR_SC */

        s_i2c_config = ConfigPtr;
        s_i2c_status = I2C_IDLE;
    }

    /* -------------------------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00821] I2C_DeInit
     */
    void I2C_DeInit(void)
    {
#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        for (uint8 idx = 0u; idx < I2C_MAX_JOBS; idx++)
        {
            if (s_i2c_dev_handles[idx] != NULL)
            {
                (void) i2c_master_bus_rm_device(s_i2c_dev_handles[idx]);
                s_i2c_dev_handles[idx] = NULL;
            }
            s_i2c_job_eb[idx].isConfigured = FALSE;
        }

        if (s_i2c_bus_handle != NULL)
        {
            (void) i2c_del_master_bus(s_i2c_bus_handle);
            s_i2c_bus_handle = NULL;
        }

        if (s_i2c_slave_handle != NULL)
        {
            (void) i2c_del_slave_device(s_i2c_slave_handle);
            s_i2c_slave_handle = NULL;
        }
#elif CPUVENDOR_SC == CPUVENDOR_SC_STM32
    /* STM32 de-initialisation via HAL */
#endif /* CPUVENDOR_SC */

        s_i2c_config            = NULL_PTR;
        s_i2c_status            = I2C_UNINIT;
        s_listening_active      = FALSE;
        s_async_queue_head      = 0u;
        s_async_queue_tail      = 0u;
        s_async_queue_count     = 0u;
        s_drain_queue_requested = FALSE;
    }

    /* -------------------------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00822] I2C_SetupEB
     * @details Valid buffer combinations per [CP_SWS_I2C_00104]:
     *   - TxDataBufferPtr only  -> CONTROLLER write  / TARGET TX-response
     *   - RxDataBufferPtr only  -> CONTROLLER read   / TARGET RX-receive
     *   - Both non-NULL         -> CONTROLLER write-then-read
     * [CP_SWS_I2C_00103] NodeAddress == 0 -> use I2cDeviceAddress from config.
     */
    Std_ReturnType I2C_SetupEB(I2C_JobType           JobId,
                               I2C_AddressType       NodeAddress,
                               I2C_DataConstPtrType *TxDataBufferPtr,
                               I2C_DataPtrType      *RxDataBufferPtr,
                               I2C_NumberOfDataType  Length)
    {
        if (s_i2c_status == I2C_UNINIT)
        {
            return E_NOT_OK;
        }

        if (JobId >= I2C_MAX_JOBS)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_00104] At least one buffer must be provided */
        if ((TxDataBufferPtr == NULL_PTR) && (RxDataBufferPtr == NULL_PTR))
        {
            return E_NOT_OK;
        }

        if (Length == 0u)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_00103] NodeAddress == 0 -> fall back to configured address */
        I2C_AddressType resolvedAddr =
          (NodeAddress != 0u) ? NodeAddress : ((s_i2c_config != NULL_PTR) ? s_i2c_config->deviceAddress : 0u);

        s_i2c_job_eb[JobId].nodeAddress     = resolvedAddr;
        s_i2c_job_eb[JobId].txDataBufferPtr = TxDataBufferPtr;
        s_i2c_job_eb[JobId].rxDataBufferPtr = RxDataBufferPtr;
        s_i2c_job_eb[JobId].length          = Length;
        s_i2c_job_eb[JobId].isConfigured    = TRUE;

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        if ((s_i2c_config != NULL_PTR) && (s_i2c_config->hwUnitMode == I2C_HW_UNIT_MODE_CONTROLLER))
        {
            if (I2C_Prv_AddDevice(JobId, resolvedAddr) != E_OK)
            {
                s_i2c_job_eb[JobId].isConfigured = FALSE;
                return E_NOT_OK;
            }
        }
#endif /* CPUVENDOR_SC */

        return E_OK;
    }

    /* -------------------------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00823] I2C_AsyncTransmit
     * @details [CP_SWS_I2C_82303] No transfer ongoing  -> start, PENDING,  E_OK
     *          [CP_SWS_I2C_82304] Other Seq PENDING     -> FIFO enqueue,   E_OK
     *          [CP_SWS_I2C_82305] Same Seq PENDING      -> reject,         E_NOT_OK
     */
    Std_ReturnType I2C_AsyncTransmit(I2C_SequenceType SequenceId)
    {
        if (s_i2c_status == I2C_UNINIT)
        {
            return E_NOT_OK;
        }

        if (SequenceId >= I2C_MAX_SEQUENCES)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_82305] Same sequence already in flight */
        if (s_i2c_seq_result[SequenceId] == I2C_SEQ_PENDING)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_82304] Another sequence is busy -> enqueue */
        if (s_i2c_status == I2C_BUSY)
        {
            if (s_async_queue_count >= I2C_QUEUE_SIZE)
            {
                return E_NOT_OK; /* Queue full */
            }
            s_async_queue[s_async_queue_tail] = SequenceId;
            s_async_queue_tail                = (uint8) ((s_async_queue_tail + 1u) % I2C_QUEUE_SIZE);
            s_async_queue_count++;
            s_i2c_seq_result[SequenceId] = I2C_SEQ_QUEUED;
            return E_OK;
        }

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        I2C_JobType jobId = (I2C_JobType) SequenceId;

        if ((jobId >= I2C_MAX_JOBS) || (s_i2c_job_eb[jobId].isConfigured != TRUE)
            || (s_i2c_dev_handles[jobId] == NULL))
        {
            return E_NOT_OK;
        }

        i2c_master_event_callbacks_t cbs = {
            .on_trans_done = I2C_Prv_AsyncDoneCallback,
        };
        esp_err_t err = i2c_master_register_event_callbacks(s_i2c_dev_handles[jobId], &cbs,
                                                            (void *) (uintptr_t) SequenceId);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "AsyncTransmit: callback register failed Seq %u (0x%x)", SequenceId, err);
            return E_NOT_OK;
        }

        s_i2c_status                 = I2C_BUSY;
        s_i2c_seq_result[SequenceId] = I2C_SEQ_PENDING;

        Std_ReturnType ret = I2C_Prv_ExecuteJob(jobId);
        if (ret != E_OK)
        {
            s_i2c_status                          = I2C_IDLE;
            s_i2c_seq_result[SequenceId]          = I2C_SEQ_FAILED;
            i2c_master_event_callbacks_t cbs_null = { .on_trans_done = NULL };
            (void) i2c_master_register_event_callbacks(s_i2c_dev_handles[jobId], &cbs_null, NULL);
            return E_NOT_OK;
        }
#elif CPUVENDOR_SC == CPUVENDOR_SC_STM32
    /* STM32: HAL_I2C_Master_Transmit_IT / HAL_I2C_Master_Receive_IT */
#endif /* CPUVENDOR_SC */

        return E_OK;
    }

    /* -------------------------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00824] I2C_SyncTransmit
     * @details Blocking call. Calls I2C_SeqEndNotification on completion.
     */
    Std_ReturnType I2C_SyncTransmit(I2C_SequenceType SequenceId)
    {
        if (s_i2c_status == I2C_UNINIT)
        {
            return E_NOT_OK;
        }

        if (SequenceId >= I2C_MAX_SEQUENCES)
        {
            return E_NOT_OK;
        }

        if (s_i2c_status == I2C_BUSY)
        {
            return E_NOT_OK;
        }

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        I2C_JobType jobId = (I2C_JobType) SequenceId;

        if ((jobId >= I2C_MAX_JOBS) || (s_i2c_job_eb[jobId].isConfigured != TRUE)
            || (s_i2c_dev_handles[jobId] == NULL))
        {
            return E_NOT_OK;
        }

        s_i2c_status                 = I2C_BUSY;
        s_i2c_seq_result[SequenceId] = I2C_SEQ_PENDING;

        Std_ReturnType ret = I2C_Prv_ExecuteJob(jobId);

        s_i2c_status = I2C_IDLE;
        I2C_Prv_NotifySeqEnd(SequenceId, (ret == E_OK) ? I2C_SEQ_OK : I2C_SEQ_FAILED);

        return ret;
#elif CPUVENDOR_SC == CPUVENDOR_SC_STM32
    return E_NOT_OK;
#else
    return E_NOT_OK;
#endif /* CPUVENDOR_SC */
    }

    /* -------------------------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00835] I2C_StartListening
     * @details Puts the TARGET channel into on-demand listening mode.
     *          Only valid when I2cHwUnitMode == TARGET and
     *          I2cTargetListening == FALSE.
     *
     *  [CP_SWS_I2C_80801] Not yet listening  -> register slave callbacks,
     *                                            pre-load TX FIFO (if TX buf set),
     *                                            seq = PENDING, return E_OK
     *  [CP_SWS_I2C_80802] Already listening  -> return E_NOT_OK
     *  [CP_SWS_I2C_80804] NOT in TARGET mode -> return E_NOT_OK
     *  [CP_SWS_I2C_80805] targetListening==TRUE (always-listen active) -> E_NOT_OK
     *  [CP_SWS_I2C_82806] SetupEB not called -> return E_NOT_OK
     */
    Std_ReturnType I2C_StartListening(I2C_SequenceType SequenceId)
    {
        if (s_i2c_status == I2C_UNINIT)
        {
            return E_NOT_OK;
        }

        if (SequenceId >= I2C_MAX_SEQUENCES)
        {
            return E_NOT_OK;
        }

        if (s_i2c_config == NULL_PTR)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_80804] Must be in TARGET mode */
        if (s_i2c_config->hwUnitMode != I2C_HW_UNIT_MODE_TARGET)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_80805] Permanent listening active — StartListening forbidden */
        if (s_i2c_config->targetListening == TRUE)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_82806] SetupEB must have been called for this job */
        I2C_JobType jobId = (I2C_JobType) SequenceId;
        if ((jobId >= I2C_MAX_JOBS) || (s_i2c_job_eb[jobId].isConfigured != TRUE))
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_80802] Already listening on this channel */
        if ((s_listening_active == TRUE) && (s_i2c_seq_result[SequenceId] == I2C_SEQ_PENDING))
        {
            return E_NOT_OK;
        }

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        if (s_i2c_slave_handle == NULL)
        {
            return E_NOT_OK;
        }

        /* [CP_SWS_I2C_80801] Register slave event callbacks for this sequence */
        i2c_slave_event_callbacks_t cbs = {
            .on_receive = I2C_Prv_SlaveReceiveCb,
            .on_request = I2C_Prv_SlaveRequestCb,
        };
        esp_err_t err =
          i2c_slave_register_event_callbacks(s_i2c_slave_handle, &cbs, (void *) (uintptr_t) SequenceId);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "StartListening: slave callback register failed (0x%x)", err);
            return E_NOT_OK;
        }

        /*
         * [CP_SWS_I2C_80806] Pre-load TX buffer into slave FIFO so data is
         * ready before the master issues a read request.
         * TxDataBufferPtr != NULL means "provide this data when master reads us".
         */
        if (s_i2c_job_eb[jobId].txDataBufferPtr != NULL_PTR)
        {
            uint32_t write_len = 0u;
            (void) i2c_slave_write(s_i2c_slave_handle, (const uint8_t *) *s_i2c_job_eb[jobId].txDataBufferPtr,
                                   (uint32_t) s_i2c_job_eb[jobId].length, &write_len,
                                   0); /* Non-blocking: copy to ring buffer */
        }
#elif CPUVENDOR_SC == CPUVENDOR_SC_STM32
    /* STM32: enable slave address-match interrupt */
#endif /* CPUVENDOR_SC */

        /* [CP_SWS_I2C_80801] Mark driver as listening */
        s_listening_seq_id           = SequenceId;
        s_listening_active           = TRUE;
        s_i2c_seq_result[SequenceId] = I2C_SEQ_PENDING;
        s_i2c_status                 = I2C_BUSY;

        return E_OK;
    }

    /* -------------------------------------------------------------------- */

    /**
     * @brief [CP_SWS_I2C_00834] I2C_MainFunction — scheduled function.
     * @details Called periodically by the OS task. Handles three roles:
     *
     *  1. TARGET permanent listening [CP_SWS_I2C_80901]:
     *     POLLING mode  — slave callbacks set s_slave_rx/tx_done flags;
     *                     MainFunction calls I2C_SeqEndNotification and
     *                     re-arms the TX FIFO for the next master read.
     *     INTERRUPT mode — callbacks handle everything; nothing to do here.
     *
     *  2. TARGET on-demand listening (I2C_StartListening, POLLING mode):
     *     Same flag-based mechanism, but listening is deactivated after
     *     each completed exchange.
     *
     *  3. CONTROLLER POLLING mode [CP_SWS_I2C_82303 .. 82308]:
     *     ISR callback defers result in s_polling_done[]; MainFunction
     *     calls I2C_SeqEndNotification and drains the FIFO queue.
     *     INTERRUPT mode — ISR calls SeqEndNotification directly; MainFunction
     *     drains the queue at task level via s_drain_queue_requested flag.
     */
    void I2C_MainFunction(void)
    {
        if ((s_i2c_status == I2C_UNINIT) || (s_i2c_config == NULL_PTR))
        {
            return;
        }

        /* ================================================================
         * Section 1 & 2 — TARGET mode
         * ================================================================ */
        if (s_i2c_config->hwUnitMode == I2C_HW_UNIT_MODE_TARGET)
        {
            if (s_i2c_config->asyncMode == I2C_POLLING_MODE)
            {
                /* RX event: master wrote data to us */
                if (s_slave_rx_done == TRUE)
                {
                    s_slave_rx_done            = FALSE;
                    I2C_SequenceResultType res = s_slave_rx_result;

                    if (s_i2c_config->targetListening == FALSE)
                    {
                        /* On-demand: deactivate after this reception */
                        s_listening_active = FALSE;
                        s_i2c_status       = I2C_IDLE;
                    }
                    else
                    {
                        /* Permanent: re-arm TX FIFO for next master read */
#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
                        I2C_JobType jobId = (I2C_JobType) s_listening_seq_id;
                        if ((jobId < I2C_MAX_JOBS) && (s_i2c_job_eb[jobId].txDataBufferPtr != NULL_PTR))
                        {
                            uint32_t wlen = 0u;
                            (void) i2c_slave_write(s_i2c_slave_handle,
                                                   (const uint8_t *) *s_i2c_job_eb[jobId].txDataBufferPtr,
                                                   (uint32_t) s_i2c_job_eb[jobId].length, &wlen, 0);
                        }
#endif /* CPUVENDOR_SC */
                    }
                    /* [CP_SWS_I2C_80803] / [CP_SWS_I2C_80901] Invoke notification */
                    I2C_Prv_NotifySeqEnd(s_listening_seq_id, res);
                }

                /* TX event: master read data from us */
                if (s_slave_tx_done == TRUE)
                {
                    s_slave_tx_done = FALSE;

                    if (s_i2c_config->targetListening == FALSE)
                    {
                        s_listening_active = FALSE;
                        s_i2c_status       = I2C_IDLE;
                    }
                    I2C_Prv_NotifySeqEnd(s_listening_seq_id, I2C_SEQ_OK);
                }
            }
            /* INTERRUPT mode: all handled by ISR callbacks — nothing to do */
            return;
        }

        /* ================================================================
         * Section 3 — CONTROLLER mode
         * ================================================================ */
        if (s_i2c_config->asyncMode == I2C_POLLING_MODE)
        {
            /*
             * Scan for a completed async sequence. The ISR callback defers
             * the notification by setting s_polling_done[seqId] = TRUE.
             */
            for (uint8 i = 0u; i < I2C_MAX_SEQUENCES; i++)
            {
                if (s_polling_done[i] == TRUE)
                {
                    s_polling_done[i]          = FALSE;
                    I2C_SequenceResultType res = s_polling_result[i];
                    s_i2c_status               = I2C_IDLE;
                    I2C_Prv_NotifySeqEnd((I2C_SequenceType) i, res);
                    /* [CP_SWS_I2C_82308] Start next queued sequence */
                    I2C_Prv_DrainQueue();
                    break; /* One completion per MainFunction period */
                }
            }
        }
        else /* I2C_INTERRUPT_MODE */
        {
            /*
             * ISR called SeqEndNotification directly.
             * DrainQueue (calls i2c_master_transmit) is not ISR-safe, so
             * the ISR sets s_drain_queue_requested and we drain here at
             * task level.
             */
            if (s_drain_queue_requested == TRUE)
            {
                s_drain_queue_requested = FALSE;
                I2C_Prv_DrainQueue();
            }
        }
    }

    /* ====================================================================
     * Private function definitions
     * ==================================================================== */

    /**
     * @brief Update sequence result and call I2C_SeqEndNotification if set.
     */
    static void I2C_Prv_NotifySeqEnd(I2C_SequenceType SequenceId, I2C_SequenceResultType Result)
    {
        if (SequenceId < I2C_MAX_SEQUENCES)
        {
            s_i2c_seq_result[SequenceId] = Result;
        }
        if (I2C_SeqEndNotification != NULL_PTR)
        {
            I2C_SeqEndNotification(SequenceId, Result);
        }
    }

    /**
     * @brief [CP_SWS_I2C_82308] Dequeue the next pending sequence and start it.
     * @note  Must be called at task level — NOT from ISR context.
     */
    static void I2C_Prv_DrainQueue(void)
    {
        if (s_async_queue_count == 0u)
        {
            return;
        }

        I2C_SequenceType nextSeq = s_async_queue[s_async_queue_head];
        s_async_queue_head       = (uint8) ((s_async_queue_head + 1u) % I2C_QUEUE_SIZE);
        s_async_queue_count--;

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32
        I2C_JobType jobId = (I2C_JobType) nextSeq;

        if ((jobId >= I2C_MAX_JOBS) || (s_i2c_job_eb[jobId].isConfigured != TRUE)
            || (s_i2c_dev_handles[jobId] == NULL))
        {
            I2C_Prv_NotifySeqEnd(nextSeq, I2C_SEQ_FAILED);
            return;
        }

        i2c_master_event_callbacks_t cbs = {
            .on_trans_done = I2C_Prv_AsyncDoneCallback,
        };
        (void) i2c_master_register_event_callbacks(s_i2c_dev_handles[jobId], &cbs,
                                                   (void *) (uintptr_t) nextSeq);

        s_i2c_status              = I2C_BUSY;
        s_i2c_seq_result[nextSeq] = I2C_SEQ_PENDING;

        Std_ReturnType ret = I2C_Prv_ExecuteJob(jobId);
        if (ret != E_OK)
        {
            s_i2c_status                          = I2C_IDLE;
            i2c_master_event_callbacks_t cbs_null = { .on_trans_done = NULL };
            (void) i2c_master_register_event_callbacks(s_i2c_dev_handles[jobId], &cbs_null, NULL);
            I2C_Prv_NotifySeqEnd(nextSeq, I2C_SEQ_FAILED);
        }
#endif /* CPUVENDOR_SC == CPUVENDOR_SC_ESP32 */
    }

#if CPUVENDOR_SC == CPUVENDOR_SC_ESP32

    /**
     * @brief Add or refresh an ESP-IDF I2C master device handle for a Job.
     */
    static Std_ReturnType I2C_Prv_AddDevice(I2C_JobType JobId, I2C_AddressType NodeAddress)
    {
        if (s_i2c_bus_handle == NULL)
        {
            return E_NOT_OK;
        }

        if (s_i2c_dev_handles[JobId] != NULL)
        {
            (void) i2c_master_bus_rm_device(s_i2c_dev_handles[JobId]);
            s_i2c_dev_handles[JobId] = NULL;
        }

        i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address  = (uint16_t) NodeAddress,
            .scl_speed_hz    = (s_i2c_config != NULL_PTR) ? s_i2c_config->baudRate : 100000u,
        };

        esp_err_t err = i2c_master_bus_add_device(s_i2c_bus_handle, &dev_cfg, &s_i2c_dev_handles[JobId]);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "AddDevice: 0x%04X Job %u failed (0x%x)", NodeAddress, JobId, err);
            return E_NOT_OK;
        }

        return E_OK;
    }

    /**
     * @brief Execute the ESP-IDF I2C transfer for the given Job.
     * @details TX only -> write; RX only -> read; both -> write-then-read.
     */
    static Std_ReturnType I2C_Prv_ExecuteJob(I2C_JobType JobId)
    {
        const I2C_JobEBConfigType *job    = &s_i2c_job_eb[JobId];
        i2c_master_dev_handle_t    devHdl = s_i2c_dev_handles[JobId];
        esp_err_t                  err    = ESP_FAIL;

        boolean hasTx = (job->txDataBufferPtr != NULL_PTR) ? TRUE : FALSE;
        boolean hasRx = (job->rxDataBufferPtr != NULL_PTR) ? TRUE : FALSE;

        if ((hasTx == TRUE) && (hasRx == TRUE))
        {
            err = i2c_master_transmit_receive(devHdl, (const uint8_t *) *job->txDataBufferPtr,
                                              (size_t) job->length, (uint8_t *) *job->rxDataBufferPtr,
                                              (size_t) job->length, I2C_XFER_TIMEOUT_MS);
        }
        else if (hasTx == TRUE)
        {
            err = i2c_master_transmit(devHdl, (const uint8_t *) *job->txDataBufferPtr, (size_t) job->length,
                                      I2C_XFER_TIMEOUT_MS);
        }
        else if (hasRx == TRUE)
        {
            err = i2c_master_receive(devHdl, (uint8_t *) *job->rxDataBufferPtr, (size_t) job->length,
                                     I2C_XFER_TIMEOUT_MS);
        }
        else
        {
            return E_NOT_OK;
        }

        return (err == ESP_OK) ? E_OK : E_NOT_OK;
    }

    /**
     * @brief ISR callback: async master transfer complete [CP_SWS_I2C_82307].
     * @details INTERRUPT mode: calls SeqEndNotification from ISR, sets drain flag.
     *          POLLING mode:   sets s_polling_done[] flag; MainFunction notifies.
     */
    static boolean I2C_Prv_AsyncDoneCallback(i2c_master_dev_handle_t        i2c_dev,
                                             const i2c_master_event_data_t *evt_data,
                                             void                          *arg)
    {
        I2C_SequenceType seqId = (I2C_SequenceType) (uint32_t) (uintptr_t) arg;

        I2C_SequenceResultType result;
        if (evt_data->event == I2C_EVENT_DONE)
        {
            result = I2C_SEQ_OK;
        }
        else if (evt_data->event == I2C_EVENT_NACK)
        {
            result = I2C_SEQ_NACK;
        }
        else
        {
            result = I2C_SEQ_FAILED;
        }

        /* Deregister callback — device reverts to synchronous default */
        i2c_master_event_callbacks_t cbs_null = { .on_trans_done = NULL };
        (void) i2c_master_register_event_callbacks(i2c_dev, &cbs_null, NULL);

        if ((s_i2c_config != NULL_PTR) && (s_i2c_config->asyncMode == I2C_POLLING_MODE))
        {
            /* POLLING mode: defer to I2C_MainFunction */
            if (seqId < I2C_MAX_SEQUENCES)
            {
                s_polling_result[seqId] = result;
                s_polling_done[seqId]   = TRUE;
            }
            /* MainFunction will reset s_i2c_status and call DrainQueue */
        }
        else
        {
            /* INTERRUPT mode: notify immediately [CP_SWS_I2C_82307] */
            s_i2c_status = I2C_IDLE;
            if (seqId < I2C_MAX_SEQUENCES)
            {
                s_i2c_seq_result[seqId] = result;
            }
            if (I2C_SeqEndNotification != NULL_PTR)
            {
                I2C_SeqEndNotification(seqId, result);
            }
            /* Drain queue at task level via MainFunction */
            s_drain_queue_requested = TRUE;
        }

        return FALSE; /* No high-priority task woken */
    }

    /**
     * @brief ISR callback: master wrote data to this target [CP_SWS_I2C_80806].
     * @details Copies received bytes to RxDataBufferPtr.
     *          INTERRUPT mode: calls SeqEndNotification from ISR.
     *          POLLING mode:   sets s_slave_rx_done flag.
     */
    static boolean I2C_Prv_SlaveReceiveCb(i2c_slave_dev_handle_t                i2c_slave,
                                          const i2c_slave_rx_done_event_data_t *evt_data,
                                          void                                 *arg)
    {
        (void) i2c_slave;

        I2C_SequenceType seqId = (I2C_SequenceType) (uint32_t) (uintptr_t) arg;
        I2C_JobType      jobId = (I2C_JobType) seqId;

        /* [CP_SWS_I2C_80806] Copy received bytes into application RX buffer */
        if ((jobId < I2C_MAX_JOBS) && (s_i2c_job_eb[jobId].rxDataBufferPtr != NULL_PTR)
            && (evt_data != NULL_PTR) && (evt_data->buffer != NULL_PTR))
        {
            uint32_t copyLen = ((uint32_t) evt_data->length < (uint32_t) s_i2c_job_eb[jobId].length)
                                 ? (uint32_t) evt_data->length
                                 : (uint32_t) s_i2c_job_eb[jobId].length;
            uint8_t *dst     = (uint8_t *) *s_i2c_job_eb[jobId].rxDataBufferPtr;
            for (uint32_t k = 0u; k < copyLen; k++)
            {
                dst[k] = evt_data->buffer[k];
            }
        }

        if ((s_i2c_config != NULL_PTR) && (s_i2c_config->asyncMode == I2C_POLLING_MODE))
        {
            /* Defer to I2C_MainFunction */
            s_slave_rx_result = I2C_SEQ_OK;
            s_slave_rx_done   = TRUE;
        }
        else
        {
            /* INTERRUPT mode: notify immediately [CP_SWS_I2C_80803] */
            if ((s_i2c_config != NULL_PTR) && (s_i2c_config->targetListening == FALSE))
            {
                s_listening_active = FALSE;
                s_i2c_status       = I2C_IDLE;
            }
            if (seqId < I2C_MAX_SEQUENCES)
            {
                s_i2c_seq_result[seqId] = I2C_SEQ_OK;
            }
            if (I2C_SeqEndNotification != NULL_PTR)
            {
                I2C_SeqEndNotification(seqId, I2C_SEQ_OK);
            }
        }

        return FALSE;
    }

    /**
     * @brief ISR callback: master requested (read) data from this target.
     * @details TX data was pre-loaded into slave FIFO in I2C_StartListening
     *          or by I2C_MainFunction re-arm. This callback signals completion.
     *          INTERRUPT mode: calls SeqEndNotification from ISR.
     *          POLLING mode:   sets s_slave_tx_done flag.
     */
    static boolean I2C_Prv_SlaveRequestCb(i2c_slave_dev_handle_t                i2c_slave,
                                          const i2c_slave_request_event_data_t *evt_data,
                                          void                                 *arg)
    {
        (void) i2c_slave;
        (void) evt_data;

        I2C_SequenceType seqId = (I2C_SequenceType) (uint32_t) (uintptr_t) arg;

        if ((s_i2c_config != NULL_PTR) && (s_i2c_config->asyncMode == I2C_POLLING_MODE))
        {
            /* Defer to I2C_MainFunction */
            s_slave_tx_done = TRUE;
        }
        else
        {
            /* INTERRUPT mode: notify immediately [CP_SWS_I2C_80803] */
            if ((s_i2c_config != NULL_PTR) && (s_i2c_config->targetListening == FALSE))
            {
                s_listening_active = FALSE;
                s_i2c_status       = I2C_IDLE;
            }
            if (seqId < I2C_MAX_SEQUENCES)
            {
                s_i2c_seq_result[seqId] = I2C_SEQ_OK;
            }
            if (I2C_SeqEndNotification != NULL_PTR)
            {
                I2C_SeqEndNotification(seqId, I2C_SEQ_OK);
            }
        }

        return FALSE;
    }

#endif /* CPUVENDOR_SC == CPUVENDOR_SC_ESP32 */

#ifdef __cplusplus
}
#endif

/* End of file -------------------------------------------------------- */
