/**
 * @file       I2c_Types.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     TYH5HC
 * @brief      Base datatypes for I2C driver
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __I2C_TYPES_H
#define __I2C_TYPES_H

/* Includes ----------------------------------------------------------- */
#include "Port_Types.h"
#include "Std_Types.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */

typedef Port_PinType I2C_PortNumType;

/**
 * @brief TRACE[CP_SWS_I2C_00810] Definition of datatype I2C_SequenceType
 * @details This is the type for a Sequence identifier
 */
typedef uint8 I2C_SequenceType;

/**
 * @brief TRACE[CP_SWS_I2C_00808]: Definition of datatype I2C_HwUnitType
 * @details Specifies the identification (ID) for a I2C Hardware micro-controller peripheral (unit).
 */
typedef uint8 I2C_HwUnitType;

/**
 * @brief TRACE[CP_SWS_I2C_00811]: Definition of datatype I2C_NumberOfDataType
 * @details Type to define the number of data elements to be sent and / or received during a transmission.
 */
typedef uint8 I2C_NumberOfDataType;

/**
 * @brief TRACE[CP_SWS_I2C_00809]: Definition of datatype I2C_JobType
 * @details This is the type for a Job identifier.
 */
typedef uint8 I2C_JobType;

/**
 * @brief TRACE[CP_SWS_I2C_00803] Definition of datatype I2C_AddressType
 * @details This type defines the address type for the I2C Driver. The type should be chosen for the specific
 * MCU platform (best performance).
 */
typedef uint16 I2C_AddressType;

/**
 * @brief TRACE[CP_SWS_I2C_00804] Definition of datatype I2C_DataType
 * @details This type defines the data to be transmitted using the I2C Driver.
 */
typedef uint8 I2C_DataType;

/**
 * @brief TRACE[CP_SWS_I2C_00805]: Definition of datatype I2C_DataPtrType
 * @details Definition for the pointer type for general buffer handling.
 *
 */
typedef uint8 *I2C_DataPtrType;

/**
 * @brief TRACE[CP_SWS_I2C_00806] Definition of datatype I2C_DataConstPtrType
 * @details Definition for the pointer type for TX buffer handling
 *
 */
typedef const uint8 *I2C_DataConstPtrType;

typedef enum
{
    I2C_UNINIT, /* I2C driver is not initialized */
    I2C_IDLE,   /* I2C driver is idle */
    I2C_BUSY,   /* At least one transfer is in progress. */
} I2C_StatusType;

/**
 * @brief TRACE[CP_SWS_I2C_00807]: Definition of datatype I2C_SequenceResultType
 * @details This type defines a range of specific Sequences status for the I2C Driver.
 */
typedef enum
{
    I2C_SEQ_OK,       // 0x00: The last transmission of the Sequence has been finished successfully.
    I2C_SEQ_PENDING,  // 0x01: The I2C Driver is performing an I2C Sequence. The meaning of this status is
                      // equal to I2C_BUSY.
    I2C_SEQ_QUEUED,   // 0x02: An I2C Sequence is queued and waiting to be transmitted.
    I2C_SEQ_FAILED,   // 0x03: An I2C Sequence encountered a NACK signal.
    I2C_SEQ_NACK      // 0x04: The last transmission of the Sequence has failed.
} I2C_SequenceResultType;

// this data type describes the possible asynchronous modes
typedef enum
{
    I2C_POLLING_MODE,   // Asynchronous transfer is ensured by polling.
    I2C_INTERRUPT_MODE  // Asynchronous transfer is ensured by interrupts.
} I2C_AsyncModeType;

/**
 * @brief TRACE[CP_SWS_I2C_00801]: This type of external data structure shall contain the initialization data
 * for the I2C Driver
 * @details The contents of the initialization data structure are I2C specific
 */
typedef struct
{
    I2C_HwUnitType    hwUnit;     // I2C hardware unit identifier for the specific micro-controller
    uint32            baudRate;   // I2C communication speed in bits per second
    I2C_AsyncModeType asyncMode;  // Asynchronous mode (polling or interrupt)
    I2C_PortNumType   i2c_port;   // I2C port number, `-1` for auto-detection based on the hardware unit
    Port_PinType      scl_pin;    // GPIO pin number for SCL line
    Port_PinType      sda_pin;    // GPIO pin number for SDA line
} I2C_ConfigType;

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------- */
#endif /* __I2C_TYPES_H */

/* End of file -------------------------------------------------------- */
