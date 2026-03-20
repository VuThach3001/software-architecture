/**
 * @file       port.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      Port driver. This file contains the ROM functions which were already implemented in the ROM,
 * and can be called by the Port driver.
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __PORT_H
#define __PORT_H

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ----------------------------------------------------------- */
#include "Platform_Types.h"
#include "Port_Types.h"
    /* Public defines ----------------------------------------------------- */
    /* Public enumerate/structure ----------------------------------------- */
    /* Public macros ------------------------------------------------------ */
    /* Public variables --------------------------------------------------- */
    /* Public function prototypes ----------------------------------------- */

    /**
     * @brief Configure IO Pad as General Purpose IO,
     *        so that it can be connected to internal Matrix,
     *        then combined with one or more peripheral signals.
     *
     * @param iopad_num IO Pad number
     */
    void esp_rom_gpio_pad_select_gpio(uint32 iopad_num);

    /**
     * @brief Enable internal pull up, and disable internal pull down.
     *
     * @param iopad_num IO Pad number
     */
    void esp_rom_gpio_pad_pullup_only(uint32 iopad_num);

    /**
     * @brief Unhold the IO Pad.
     * @note When the Pad is set to hold, the state is latched at that moment and won't get changed.
     *
     * @param iopad_num IP Pad number
     */
    void esp_rom_gpio_pad_unhold(uint32 gpio_num);

    /**
     * @brief Set IO Pad current drive capability.
     *
     * @param iopad_num IO Pad number
     * @param drv Numeric to indicate the capability of current drive
     *      - 0: 5mA
     *      - 1: 10mA
     *      - 2: 20mA
     *      - 3: 40mA
     */
    void esp_rom_gpio_pad_set_drv(uint32 iopad_num, uint32 drv);

    /**
     * @brief Combine a GPIO input with a peripheral signal, which tagged as input attribute.
     *
     * @note There's no limitation on the number of signals that a GPIO can combine with.
     *
     * @param gpio_num GPIO number, especially, `GPIO_MATRIX_CONST_ZERO_INPUT` means connect logic 0 to signal
     *                                          `GPIO_MATRIX_CONST_ONE_INPUT` means connect logic 1 to signal
     * @param signal_idx Peripheral signal index (tagged as input attribute)
     * @param inv  Whether the GPIO input to be inverted or not
     */
    void esp_rom_gpio_connect_in_signal(uint32 gpio_num, uint32 signal_idx, bool inv);

    /**
     * @brief Combine a peripheral signal which tagged as output attribute with a GPIO.
     *
     * @note There's no limitation on the number of signals that a GPIO can combine with.
     * @note Internally, the signal will be connected first, then output will be enabled on the pad.
     *
     * @param gpio_num GPIO number
     * @param signal_idx Peripheral signal index (tagged as output attribute). Particularly,
     * `SIG_GPIO_OUT_IDX` means disconnect GPIO and other peripherals. Only the GPIO driver can control the
     * output level.
     * @param out_inv Whether to signal to be inverted or not
     * @param oen_inv Whether the output enable control is inverted or not
     */
    void esp_rom_gpio_connect_out_signal(uint32 gpio_num, uint32 signal_idx, bool out_inv, bool oen_inv);

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
#endif /* __PORT_H */

/* End of file -------------------------------------------------------- */
