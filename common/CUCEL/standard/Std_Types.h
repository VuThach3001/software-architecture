/**
 * @file       Std_Types.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      standard data types
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __STD_TYPES_H
#define __STD_TYPES_H

/* Includes ----------------------------------------------------------- */
#include "Platform_Types.h"

/* Public defines ----------------------------------------------------- */
#define E_NOT_OK   0x01u /* An error occurs            */

/* TRACE[SWS_Std_00007]: STD_HIGH and STD_Low */
#define STD_HIGH   0x01u /* Physical state 5V or 3.3V  */
#define STD_LOW    0x00u /* Physical state 0V          */

/*TRACE[SWS_Std_00013]: STD_ACTIVE and STD_IDLE */
#define STD_ACTIVE 0x01u /* Logical state active       */
#define STD_IDLE   0x00u /* Logical state idle         */

/*TRACE[SWS_Std_00010]: STD_On and STD_OFF */
#define STD_ON     0x01u /* On state                   */
#define STD_OFF    0x00u /* Off state                  */

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */

/*TRACE[SWS_Std_00031]: Definition of NULL pointer                     */
#ifdef __cplusplus
#define NULL_PTR (0)
#else
#define NULL_PTR ((void *) 0)
#endif
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------- */
#endif /* __STD_TYPES_H */

/* End of file -------------------------------------------------------- */
