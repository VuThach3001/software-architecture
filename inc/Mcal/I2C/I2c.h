/**
 * @file       I2c.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      Contain definition of I2C functions
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __I2C_H
#define __I2C_H

/* Includes ----------------------------------------------------------- */
#include "I2c_Types.h"
#include "Std_Types.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/**
 * @brief This service initializes the I2C Driver.
 * @details TRACE[CP_SWS_I2C_00820]: Definition of API function I2C_Init
 * @param ConfigPtr Pointer to I2C Driver configuration set.
 */
void I2C_Init(const I2C_ConfigType *ConfigPtr);

/**
 * @brief This service de-initializes the I2C Driver.
 * @details TRACE[CP_SWS_I2C_00821]: Definition of API function I2C_DeInit
 * @param void
 */
void I2C_DeInit(void);

/**
 * @brief TRACE[CP_SWS_I2C_00822] Definition of API function I2C_SetupEB
 * @details Service to setup the buffers and the length of data for the EB I2C Driver Job specified
 * @param JobId Job identifier for the I2C transmission.
 * @param SlaveAddr Address of the I2C slave device to be accessed.
 * @param TxDataBufferPtr Pointer to the transmit data buffer.
 * @param RxDataBufferPtr Pointer to the receive data buffer.
 * @param Length Number of data elements to be transmitted/received.
 * @return Std_ReturnType Returns E_OK if the setup of the I2C job was successful, E_NOT_OK otherwise.
 */
Std_ReturnType I2C_SetupEB(I2C_JobType           JobId,
                           I2C_AddressType       SlaveAddr,
                           I2C_DataConstPtrType *TxDataBufferPtr,
                           I2C_DataPtrType      *RxDataBufferPtr,
                           I2C_NumberOfDataType  Length);

/**
 * @brief TRACE[CP_SWS_I2C_00823] Definition of API function I2C_AsyncTransmit
 * @details The service conducts an asynchronous data transmission according to the parameters
 * provided to the I2c_SetupEB() service. The callback I2c_SeqEndNotification() is called, when
 * the asynchronous operation has finished.
 * @return Std_ReturnType Returns E_OK if the data exchange is successful, E_NOT_OK if the request is
 * rejected.
 */
Std_ReturnType I2C_AsyncTransmit(I2C_SequenceType SequenceId);

/**
 * @brief TRACE[CP_SWS_I2C_00824] Definition of API function I2C_SyncTransmit
 * @details This service sends or receives data using a blocking mechanism according to the parameters
 * provided to the I2c_SetupEB() service.
 * @return Std_ReturnType Returns E_OK if the data exchange is successful, E_NOT_OK if the request is
 * rejected.
 */
Std_ReturnType I2C_SyncTransmit(I2C_SequenceType SequenceId);

/* -------------------------------------------------------------------- */
#endif /* __I2C_H */

/* End of file -------------------------------------------------------- */
