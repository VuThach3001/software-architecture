/**
 * @file I2c_Types.h
 * @author Thach Nguyen Ba Vu (https://github.com/VuThach3001)
 * @brief Base data types for I2C driver.
 * @version 0.1
 * @date 2026-03-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef I2C_TYPES_H
#define I2C_TYPES_H

/* Data type describes the possible driver states */
typedef enum
{
  I2C_UNINIT, /* I2C driver is not initialized */
  I2C_IDLE,   /* I2C driver is idle */
  I2C_BUSY,   /* At least one transfer is in progress. */
} I2c_StatusType_ten;

/* This data type describes the possible sequence results */
typedef enum
{
    I2C_SEQ_OK,             // Sequence transfer complete.
    I2C_SEQ_PENDING,        // Sequence transfer pending.
    I2C_SEQ_FAILED          // Sequence transfer has failed.
} I2c_SeqResultType_ten;

// this data type describes the possible asynchronous modes
typedef enum
{
    I2C_POLLING_MODE,       // Asynchronous transfer is ensured by polling.
    I2C_INTERRUPT_MODE      // Asynchronous transfer is ensured by interrupts.
} I2c_AsyncModeType_ten;

#endif /* I2C_TYPES_H */