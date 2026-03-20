/**
 * @file       Port_Types.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      Port data type
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __PORT_TYPES_H
#define __PORT_TYPES_H

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ----------------------------------------------------------- */
#include "Platform_Types.h"

    /* Public defines ----------------------------------------------------- */
    /* Public enumerate/structure ----------------------------------------- */

    /**
     * @brief Data type for the symbolic name of a port pin.
     * @note  Shall cover all available port pins. The type should be chosen for the specific MCU platform
     * (best performance).
     *
     * @param
     */
    typedef uint16 Port_PinType;
    /* Public macros ------------------------------------------------------ */
    /* Public variables --------------------------------------------------- */
    /* Public function prototypes ----------------------------------------- */

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
#endif /* __PORT_TYPES_H */

/* End of file -------------------------------------------------------- */
