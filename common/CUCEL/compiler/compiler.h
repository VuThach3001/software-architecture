/**
 * @file       compiler.h
 * @copyright  Copyright (C) 2026 ESP32-TYH5HC. All rights reserved.
 * @license    This project is released under the ESP32-TYH5HC License.
 * @version    1.0.0
 * @date       2026-03
 * @author     Thach Nguyen Ba Vu
 * @brief      compiler abstraction layer
 * @note       None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __COMPILER_H
#define __COMPILER_H

/* Includes ----------------------------------------------------------- */
/* Public defines ----------------------------------------------------- */

/* TRACE[SWS_COMPILER_00057]:  Inline keyword                             */
#define INLINE inline

/* TRACE[SWS_COMPILER_00060]: Local inline keyword       */
#ifdef SIL_BUILD_ENABLED
#define LOCAL_INLINE static
#else
#define LOCAL_INLINE static inline __attribute__((always_inline))
#endif

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */

/*
 **********************************************************************************************************************
 * TRACE[SWS_COMPILER_00001]: Macro for declaration and definition of functions.
 *
 * \param in     rettype:  Return type of the function
 * \param in     memclass: Classification of the function itself
 * \return       None
 * \note        SWS_COMPILER_00058: No nesting of Compiler Abstraction macros in parameter list.
 *              Instead, use a previously defined type as return type or use FUNC_P2CONST/FUNC_P2VAR.
 **********************************************************************************************************************
 */
#define FUNC(rettype, memclass)                   rettype

/*
 **********************************************************************************************************************
 * TRACE[SWS_COMPILER_00061]: Macro for declaration and definition of functions returning a pointer to a
 * constant.
 *
 * \param       rettype:   Return type of the function
 * \param       ptrclass:  Defines the classification of the pointer's distance
 * \param       memclass:  Classification of the function itself
 * \return      None
 * \note        SWS_COMPILER_00062: No nesting of Compiler Abstraction macros in this parameter list.
 **********************************************************************************************************************
 */
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *

/*
 **********************************************************************************************************************
 * TRACE[SWS_COMPILER_00063]:  Macro for declaration and definition of functions returning a pointer to a
 * variable.
 *
 * \param       rettype:   Return type of the function
 * \param       ptrclass:  Defines the classification of the pointer's distance
 * \param       memclass:  Classification of the function itself
 * \return      None
 * \note        SWS_COMPILER_00064: No nesting of Compiler Abstraction macros in this parameter list.
 **********************************************************************************************************************
 */
#define FUNC_P2VAR(rettype, ptrclass, memclass)   rettype *
/*
 **********************************************************************************************************************
 * Macros for Pointers
 **********************************************************************************************************************
 */

/*
 *********************************************************************************************************************
 * TRACE[SWS_COMPILER_00006]:  Macro for Declaration and definition of pointers in RAM, pointing to Variables.
 *
 * \param       ptrtype:  Type of the referenced variable
 * \param       memclass: Classification of the pointer's variable itself
 * \param       ptrclass: Defines the classification of the pointer's distance
 * \return      None
 **********************************************************************************************************************
 */
#define P2VAR(ptrtype, memclass, ptrclass)        ptrtype *

/*
 *********************************************************************************************************************
 * TRACE[SWS_COMPILER_00013]:  Macro for Declaration and definition of pointers in RAM, pointing to Constants.
 *
 * \param       ptrtype:  Type of the referenced constant
 * \param       memclass: Classification of the pointer's variable itself
 * \param       ptrclass: Defines the classification of the pointer's distance
 * \return      None
 **********************************************************************************************************************
 */
#define P2CONST(ptrtype, memclass, ptrclass)      const ptrtype *

/*
 *********************************************************************************************************************
 * TRACE[SWS_COMPILER_00031]:  Macro for Declaration and definition of constant pointers accessing variables.
 *
 * \param       ptrtype:  Type of the referenced variable
 * \param       memclass: Classification of the pointer's constant itself
 * \param       ptrclass: Defines the classification of the pointer's distance
 * \return      None
 *********************************************************************************************************************
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass)   ptrtype *const

/*
 *********************************************************************************************************************
 * TRACE[SWS_COMPILER_00032]:  Macro for Declaration and definition of constant pointers accessing constants.
 *
 * \param       ptrtype:  Type of the referenced variable
 * \param       memclass: Classification of the pointer's constant itself
 * \param       ptrclass: Defines the classification of the pointer's distance
 * \return      None
 ********************************************************************************************************************
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype *const

/*
 *******************************************************************************************************************
 * TRACE[SWS_COMPILER_00039]:  Macro for type definition of pointers to function.
 *
 * \param       rettype:  Return type of the function
 * \param       ptrclass: Defines the classification of the pointer's distance
 * \param       fctname:  Function name respectively name of the defined type
 * \return      None
 **********************************************************************************************************************
 */
#define P2FUNC(rettype, ptrclass, fctname)        rettype(*fctname)

/*
 **********************************************************************************************************************
 * SWS_COMPILER_00065:  Macro for type definition of constant pointers to function.
 *
 * \param       rettype:  Return type of the function
 * \param       ptrclass: Defines the classification of the pointer's distance
 * \param       fctname:  Function name respectively name of the defined type
 * \return      None
 **********************************************************************************************************************
 */
#define CONSTP2FUNC(rettype, ptrclass, fctname)   rettype(*const fctname)

/*
 **********************************************************************************************************************
 * Keywords for constants
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * TRACE[SWS_COMPILER_00023]:  Macro for declaration and definition of constants.
 *
 * \param       consttype: Type of the constant
 * \param       memclass:  Classification of the constant itself
 * \return      None
 **********************************************************************************************************************
 */
#ifndef CONST
#define CONST(type, memclass) const type
#endif

/*
 **********************************************************************************************************************
 * Keywords for variables
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * SWS_COMPILER_00026:  Macro for declaration and definition of variables.
 *
 * \param       vartype:   Type of the variable
 * \param       memclass:  Classification of the variable itself
 * \return      None
 **********************************************************************************************************************
 */
#define VAR(type, memclass) type

/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/* -------------------------------------------------------------------- */
#endif /* __COMPILER_H */

/* End of file -------------------------------------------------------- */
