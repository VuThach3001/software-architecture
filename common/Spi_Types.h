/**
 * @file       Spi_Types.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-04
 * @author     Thach Nguyen Ba Vu
 * @brief      Place to store the data types for SPI handler/driver
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SPI_TYPES_H
#define __SPI_TYPES_H

/* Includes ----------------------------------------------------------- */
#include "Std_Types.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */

/**
 * @brief TRACE[SWS_Spi_00373] Spi_StatusType
 * @details This type defines a range of specific status for SPI Handler/Driver.
 */
typedef enum
{
    SPI_UNINIT,  // The SPI Handler/Driver is not initialized or not usable.
    SPI_IDLE,    // The SPI Handler/Driver is not currently transmitting any Job.
    SPI_BUSY     // The SPI Handler/Driver is performing a SPI Job (transmit).
} Spi_StatusType;

/**
 * @brief TRACE[SWS_Spi_00374] Spi_JobResultType
 * @details This type defines a range of specific Jobs status for SPI Handler/Driver.
 */
typedef enum
{
    SPI_JOB_OK,       // The last transmission of the Job has been finished successfully.
    SPI_JOB_PENDING,  // The SPI Handler/Driver is performing a SPI Job. The meaning of this status is equal
                      // to SPI_BUSY.
    SPI_JOB_FAILED,   // The last transmission of the Job has failed.
    SPI_JOB_QUEUED  // An asynchronous transmit Job has been accepted, while actual transmission for this Job
                    // has not yet started.
} Spi_JobResultType;

/**
 * @brief TRACE[SWS_Spi_00375] Spi_SeqResultType
 * @details This type defines a range of specific Sequences status for SPI Handler/Driver.
 */
typedef enum
{
    SPI_SEQ_OK,        // The last transmission of the Sequence has been finished successfully.
    SPI_SEQ_PENDING,   // The SPI Handler/Driver is performing a SPI Sequence. The meaning of this status is
                       // equal to SPI_BUSY.
    SPI_SEQ_FAILED,    // The last transmission of the Sequence has failed.
    SPI_SEQ_CANCELLED  // The last transmission of the Sequence has been canceled by
                       // user
} Spi_SeqResultType;

/**
 * @brief TRACE[SWS_Spi_00382] Spi_AsyncModeType
 * @details Specifies the asynchronous mechanism mode for SPI busses handled
            asynchronously in LEVEL 2.
 */
typedef enum
{
    SPI_POLLING_MODE,   // The asynchronous mechanism is ensured by polling, so interrupts related to SPI
                        // busses handled asynchronously are
                        //  disabled.
    SPI_INTERRUPT_MODE  // The asynchronous mechanism is ensured by interrupts, so interrupts related to SPI
                        // busses handled asynchronously are enabled.
} Spi_AsyncModeType;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */

/**
 * @brief TRACE[SWS_Spi_00376] Spi_DataBufferType
 * @details Type of application data buffer elements.
 */
typedef uint8 Spi_DataBufferType;

/**
 * @brief TRACE[SWS_Spi_00381] Spi_HWUnitType
 * @details Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
 */
typedef uint8 Spi_HWUnitType;

/**
 * @brief TRACE[SWS_Spi_00377] Spi_NumberOfDataType
 * @details Type for defining the number of data elements of the type Spi_DataBufferType to
            send and / or receive by Channel
 */
typedef uint16 Spi_NumberOfDataType;

/**
 * @brief TRACE[SWS_Spi_00378] Spi_ChannelType
 * @details Specifies the identification (ID) for a Channel.
 */
typedef uint8 Spi_ChannelType;

/**
 * @brief TRACE[SWS_Spi_00380] Spi_HWUnitType
 * @details Specifies the identification (ID) for a sequence of jobs.
 */
typedef uint8 Spi_SequenceType;

/**
 * @brief TRACE[SWS_Spi_00379] Spi_JobType
 * @details Specifies the identification (ID) for a SPI Job.
 */
typedef uint16 Spi_JobType;

/**
 * @brief TRACE[SWS_Spi_00372] Spi_ConfigType
 * @details This type of the external data structure shall contain the initialization data for the SPI 
            Handler/Driver.
 */
typedef enum{
    Spi_Cfg_e,
    Spi_Cfg_nrPbCfg_e
} Spi_ConfigType;
/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------- */
#endif /* __SPI_TYPES_H */

/* End of file -------------------------------------------------------- */
