/**
 * @file       soc_caps.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      System On Chip - Capabilities of the ESP32-S3 chip
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SOC_CAPS_H
#define __SOC_CAPS_H

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */

/*-------------------------- I2C CAPS ----------------------------------*/
// ESP32-S3 has 2 I2C
#define SOC_I2C_NUM                 (2U)
#define SOC_HP_I2C_NUM              (2U)

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */


#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
#endif /* __SOC_CAPS_H */

/* End of file -------------------------------------------------------- */
