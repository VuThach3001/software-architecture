/**
 * @file       weth.c
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-04
 * @author     Thach Nguyen Ba Vu
 * @brief      Specifies the functionality, API and the configuration inspired from the AUTOSAR Basic Software module Wireless Ethernet driver
 * @note       None
 */

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "weth.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void WEth_Init(const WEth_ConfigType* ConfigPtr)
{
#if (CPUVENDOR_SC == CPUVENDOR_SC_ESP32) && (WETH_ENA == WETH_SUPPORTED)
esp_err_t esp_wifi_init(const WEth_ConfigType* ConfigPtr);
#endif
    return;
}


#ifdef __cplusplus
}
#endif

/* End of file -------------------------------------------------------- */
