/**
 * @file       I2c.c
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      Define the functions for I2C driver based on AUTOSAR
 * @note       None
 */

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ----------------------------------------------------------- */
#include "I2c.h"
#include "driver/i2c_master.h" // Why I removed the driver/ then the I2C_CLK_SRC_DEFAULT is found? instead i keep it, it can not detect?
#include "esp_err.h"

    /* Private defines ---------------------------------------------------- */
    /* Private enumerate/structure ---------------------------------------- */
    /* Private macros ----------------------------------------------------- */
    /* Public variables --------------------------------------------------- */

    /* Private variables -------------------------------------------------- */
    /* Private function prototypes ---------------------------------------- */
    /* Function definitions ----------------------------------------------- */

    void I2C_Init(const I2C_ConfigType *ConfigPtr)
    {
        i2c_master_bus_handle_t i2c_bus_handle = NULL;
        i2c_master_bus_config_t i2c_bus_config = {
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .i2c_port = ConfigPtr->i2c_port,
            .sda_io_num = ConfigPtr->sda_pin,
            .scl_io_num = ConfigPtr->scl_pin,
            .flags.enable_internal_pullup = true,
        };
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, &i2c_bus_handle));
    }

#ifdef __cplusplus
}
#endif

/* End of file -------------------------------------------------------- */
