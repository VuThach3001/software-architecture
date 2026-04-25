/**
 * @file       Spi.c
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-04
 * @author     Thach Nguyen Ba Vu
 * @brief      Declare APIs for SPI handler/driver
 * @note       None
 */
/* Includes ----------------------------------------------------------- */
#include "Spi.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */

/**
 * @brief Store the state of SPI initialization.
 * @details This variable is pre-initialized to false (by allocation in cleared RAM) and set to True in Spi_Init().
 * In other functions it is checked if this module is already initialized.
 */
static boolean s_spi_isInitialized = 0;

static Spi_SeqResultType s_spi_seq_result[SPI_MAX_SEQUENCES];


/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void Spi_Init(const Spi_ConfigType *ConfigPtr){
    Spi_SeqResultType idxSeq_uo;
    Spi_JobType idxJob_io;
    Spi_HWUnitType idxHwUnit_u8;
#if((SPI_LEVEL_DELIVERED == 1u) || (SPI_LEVEL_DELIVERED == 2u))
    uint8 idxPrio_u8;
#endif
    if(s_spi_isInitialized){
        return;
    }

    // Make sure that the pointer to the PB variant is not a NULL pointer
    if(ConfigPtr == NULL_PTR){
        return;
    }

    // Make sure that the PB variant is in range
    if(*ConfigPtr >= Spi_Cfg_nrPbCfg_e){
        return;
    }



}

/* End of file -------------------------------------------------------- */
