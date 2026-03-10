/* TRACE[SWS_Std_00014]: protected against multiple inclusion. */
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*-------Standard Integer Data Types--------*/
/*TRACE[SWS_Platform_00016]:This standard AUTOSAR type shall be of 8 bit signed. */
 /* Range : -128 .. +127 */
/*           0x80..0x7F */
typedef signed char     sint8;

/* TRACE[SWS_Platform_00013]: This standard AUTOSAR type shall be of 8 bit unsigned.*/
 /* Range : 0 .. 255     */
 /*         0x00 .. 0xFF */
typedef unsigned char   uint8;

/* TRACE[SWS_Platform_00017]: This standard AUTOSAR type shall be of 16 bit signed. */
/* Range : -32768 .. +32767 */
/*          0x8000..0x7FFF  */
typedef signed short    sint16;

/*TRACE[SWS_Platform_00014]: This standard AUTOSAR type shall be of 16 bit unsigned. */
/* Range : 0 .. 65535      */
/*         0x0000..0xFFFF  */
typedef unsigned short  uint16;

/*TRACE[SWS_Platform_00018]:This standard AUTOSAR type shall be 32 bit signed. */
/*Range : -2147483648 .. +2147483647   */
/*         0x80000000..0x7FFFFFFF      */
typedef signed long     sint32;

/*TRACE[SWS_Platform_00067]: This standard AUTOSAR type shall be 64 bit signed. */
/*Range: -9223372036854775808..+9223372036854775807*/
/*        0x8000000000000000..0x7FFFFFFFFFFFFFFF   */
typedef signed long long sint64;

/*TRACE[SWS_Platform_00015]:This standard AUTOSAR type shall be 32 bit unsigned. */
/* Range:  0 .. 4294967295           */
/*         0x00000000..0xFFFFFFFF    */
typedef unsigned long   uint32;

/*TRACE[SWS_Platform_00066]: This standard AUTOSAR type shall be 64 bit unsigned.*/
/* Range :   0 ..18446744073709551615              */
/*           0x0000000000000000..0xFFFFFFFFFFFFFFFF*/
typedef unsigned long long   uint64;

/* Standard Float Data Types */
/* ------------------------- */
/* TRACE[SWS_Platform_00041]: This standard AUTOSAR type shall follow the 32-bit binary interchange format
  according to IEEE 754-2008 with encoding parameters specified in chapter 3.6, table 3.5, column "binary32".*/
typedef float   float32;
/*TRACE[SWS_Platform_00042]:This standard AUTOSAR type shall follow the 64-bit binary interchange format according
            to IEEE 754-2008 with encoding parameters specified in chapter 3.6, table 3.5, column "binary64". */
typedef double  float64;

/* Optimized Integer Data Types */
/* ---------------------------- */
/* TRACE[SWS_Platform_00023]:This optimized AUTOSAR type shall be at least 8 bit signed. */
 /* At least -128..+127 */
/*   0x80..0x7F  */
typedef signed long     sint8_least;

/* TRACE[SWS_Platform_00020]:This optimized AUTOSAR type shall be at least 8 bit unsigned. */
typedef unsigned long   uint8_least;    /* At least 0..255  */

/* TRACE[SWS_Platform_00024]:This optimized AUTOSAR type shall be at least 16 bit signed. */
   /*At least -32768..+32767*/
   /* 0x8000..0x7FFF */
typedef signed long     sint16_least;

/* TRACE[SWS_Platform_00021]:This optimized AUTOSAR type shall be at least 16 bit unsigned. */
   /*At least 0..65535 */
  /*0x0000..0xFFFF   */
typedef unsigned long   uint16_least;

/* TRACE[SWS_Platform_00025]:This optimized AUTOSAR type shall be at least 32 bit signed.*/
/* At least -2147483648..+2147483647*/
/*0x80000000..0x7FFFFFFF*/
typedef signed long sint32_least;

/* SWS_Platform_00022:This optimized AUTOSAR type shall be at least 32 bit unsigned. */
/* At least 0..4294967295*/
/* 0x00000000..0xFFFFFFFF */
typedef unsigned long   uint32_least;

/* SWS_Platform_91001:This standard AUTOSAR type shall be a void pointer. 
Note: This type shall be used for buffers that contain data returned to the caller */
typedef void* VoidPtr;

/* SWS_Platform_91002:This standard AUTOSAR type shall be a void pointer to const. 
Note: This type shall be used for buffers that are passed to the callee.*/
typedef const void* ConstVoidPtr;

#endif /* PLATFORM_TYPES_H */