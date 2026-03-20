/**
 * @file       Port_nums.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      Place to store the port num
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __PORT_NUMS_H
#define __PORT_NUMS_H

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    /* Includes ----------------------------------------------------------- */
    /* Public defines ----------------------------------------------------- */
    /* Public enumerate/structure ----------------------------------------- */

    /**
     * @brief Port number
     */
    typedef enum
    {
        PORT_NUM_NC = -1, /*!< Use to signal not connected to S/W */
        PORT_NUM_0  = 0,  /*!< PORT0, input and output */
        PORT_NUM_1  = 1,  /*!< PORT1, input and output */
        PORT_NUM_2  = 2,  /*!< PORT2, input and output */
        PORT_NUM_3  = 3,  /*!< PORT3, input and output */
        PORT_NUM_4  = 4,  /*!< PORT4, input and output */
        PORT_NUM_5  = 5,  /*!< PORT5, input and output */
        PORT_NUM_6  = 6,  /*!< PORT6, input and output */
        PORT_NUM_7  = 7,  /*!< PORT7, input and output */
        PORT_NUM_8  = 8,  /*!< PORT8, input and output */
        PORT_NUM_9  = 9,  /*!< PORT9, input and output */
        PORT_NUM_10 = 10, /*!< PORT10, input and output */
        PORT_NUM_11 = 11, /*!< PORT11, input and output */
        PORT_NUM_12 = 12, /*!< PORT12, input and output */
        PORT_NUM_13 = 13, /*!< PORT13, input and output */
        PORT_NUM_14 = 14, /*!< PORT14, input and output */
        PORT_NUM_15 = 15, /*!< PORT15, input and output */
        PORT_NUM_16 = 16, /*!< PORT16, input and output */
        PORT_NUM_17 = 17, /*!< PORT17, input and output */
        PORT_NUM_18 = 18, /*!< PORT18, input and output */
        PORT_NUM_19 = 19, /*!< PORT19, input and output */
        PORT_NUM_20 = 20, /*!< PORT20, input and output */
        PORT_NUM_21 = 21, /*!< PORT21, input and output */
        PORT_NUM_22 = 22, /*!< PORT22, input and output */
        PORT_NUM_23 = 23, /*!< PORT23, input and output */
        PORT_NUM_25 = 25, /*!< PORT25, input and output */
        PORT_NUM_26 = 26, /*!< PORT26, input and output */
        PORT_NUM_27 = 27, /*!< PORT27, input and output */
        PORT_NUM_28 = 28, /*!< PORT28, input and output */
        PORT_NUM_29 = 29, /*!< PORT29, input and output */
        PORT_NUM_30 = 30, /*!< PORT30, input and output */
        PORT_NUM_31 = 31, /*!< PORT31, input and output */
        PORT_NUM_32 = 32, /*!< PORT32, input and output */
        PORT_NUM_33 = 33, /*!< PORT33, input and output */
        PORT_NUM_34 = 34, /*!< PORT34, input mode only */
        PORT_NUM_35 = 35, /*!< PORT35, input mode only */
        PORT_NUM_36 = 36, /*!< PORT36, input mode only */
        PORT_NUM_37 = 37, /*!< PORT37, input mode only */
        PORT_NUM_38 = 38, /*!< PORT38, input mode only */
        PORT_NUM_39 = 39, /*!< PORT39, input mode only */
        PORT_NUM_MAX,
    } port_num_t;
    /* Public macros ------------------------------------------------------ */
    /* Public variables --------------------------------------------------- */
    /* Public function prototypes ----------------------------------------- */

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
#endif /* __PORT_NUMS_H */

/* End of file -------------------------------------------------------- */
