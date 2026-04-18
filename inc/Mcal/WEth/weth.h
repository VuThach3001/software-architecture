/**
 * @file       weth.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-04
 * @author     Thach Nguyen Ba VU
 * @brief      Specifies the functionality, API and the configuration inspired from the AUTOSAR Basic Software module Wireless Ethernet driver
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __WETH_H
#define __WETH_H

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "Std_Types.h"
#if (CPUVENDOR_SC == CPUVENDOR_SC_ESP32) && (WETH_ENA == WETH_SUPPORTED)
#include "esp_wifi.h"
#endif
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
#if (CPUVENDOR_SC == CPUVENDOR_SC_ESP32) && (WETH_ENA == WETH_SUPPORTED)
typedef wifi_init_config_t WEth_ConfigType;
#endif
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the Wireless Ethernet Driver.
 * @details TRACE[CP_SWS_I2C_00820]: Definition of API function I2C_Init
 * @param ConfigPtr Pointer to I2C Driver configuration set.
 */
void WEth_Init(const WEth_ConfigType* ConfigPtr);

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
#endif /* __WETH_H */

/* End of file -------------------------------------------------------- */
