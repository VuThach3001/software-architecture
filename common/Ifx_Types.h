/**
 * @file Ifx_Types.h
 * @author Thach Nguyen Ba Vu (https://github.com/VuThach3001)
 * @brief Base data types for Fixed-point interpolation routines.
 * @version 0.1
 * @date 2026-03-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */

/*
 **********************************************************************************************************************
 *
 * COPYRIGHT (c) ETAS GmbH 2012, all rights reserved
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 **********************************************************************************************************************
*/


#ifndef IFX_TYPES_H
#define IFX_TYPES_H


/*
 **********************************************************************************************************************
 * Specific data types
 **********************************************************************************************************************
 */


/* 64 bit integer data types */
typedef signed long long   Ifx_sint64;
typedef unsigned long long   Ifx_uint64;


/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */

/* Structure used for data point search for index and ratio */
/* 4 byte alignment is required to guarantee atomicity on multicore systems */
#ifdef __TASKING__
#pragma align 4
typedef struct
{
    uint16 Index;            /* Data point index */
    uint16 Ratio;            /* Data point ratio */
} Ifx_DPResultU16_Type;
#pragma align 0
#else
/* This attribute is tested only in hightec compiler. Compatibility is not verified for other compilers*/
typedef struct
{
    uint16 Index;            /* Data point index */
    uint16 Ratio;            /* Data point ratio */
} Ifx_DPResultU16_Type __attribute__ ((aligned (4)));
#endif




typedef union
{
    uint32 Tmp_u32;
    Ifx_DPResultU16_Type Tmp_st;
}  Ifx_DPResultVarU16_Type_U;

/*********************************************************************************************************************/

/* ASAM versions used */

#define IFX_ASAM_VERSION_1_6        1
#define IFX_ASAM_VERSION_1_7        0

/* IFX_TYPES_H */
#endif
