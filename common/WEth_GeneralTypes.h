/**
 * @file       WEth_GeneralTypes.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-04
 * @author     Thach Nguyen Ba Vu
 * @brief      Store the general types for Wireless Ethernet Driver
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __WETH_GENERALTYPES_H
#define __WETH_GENERALTYPES_H

/* Cross-language compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Wireless radio parameters for a packet that has been received.
 */
enum WEth_BufWRxParamIdType
{
    WETH_BUFWRXPID_RSSI = 0x00,   /**< Parameter Idf or RSSIvalue */
    WETH_BUFWRXPID_CHANNEL_ID = 0x01,         /**< ParameterIdforChannel Id. Channel Id values are specified within IEEE802.11-2012 AnnexE.*/
    WETH_BUFWRXPID_FREQ = 0x02,          /**<  Frequency on the channel with that the packet has been received */
    WETH_BUFWRXPID_TRANSACTION_ID_32 = 0x03, /**< Uniqueidofaframethathasbeenreceived */
    WETH_BUFWRXPID_ANTENNA_ID = 0x04, /**< Indexoftheusedantenna */
};
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */


#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------- */
#endif /* __WETH_GENERALTYPES_H */

/* End of file -------------------------------------------------------- */
