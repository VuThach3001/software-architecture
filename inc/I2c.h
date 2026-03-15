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

/* -------------------------------------------------------------------- */
#endif /* __I2C_H */

/* End of file -------------------------------------------------------- */
