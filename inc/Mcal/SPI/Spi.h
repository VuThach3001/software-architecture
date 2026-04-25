/**
 * @file       Spi.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-04
 * @author     Thach Nguyen Ba Vu
 * @brief      Place to store the handler/driver APIs for SPI
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SPI_H
#define __SPI_H

/* Includes ----------------------------------------------------------- */
#include "Spi_Types.h"
#include "Std_Types.h"
/* Public defines ----------------------------------------------------- */
#define SPI_MAX_SEQUENCES
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Service for SPI initialization.
 * @details TRACE[SWS_Spi_00175]: Definition of API function Spi_Init
 * @param ConfigPtr Pointer to configuration set 
 */
void Spi_Init(const Spi_ConfigType *ConfigPtr);

/* -------------------------------------------------------------------- */
#endif /* __SPI_H */

/* End of file -------------------------------------------------------- */
