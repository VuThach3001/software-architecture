/* TRACE[SWS_Std_00014]: protected against multiple inclusion. */
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"


#define E_OK       0x00u   /* No error occurs            */
#define E_NOT_OK   0x01u   /* An error occurs            */

/* TRACE[SWS_Std_00007]: STD_HIGH and STD_Low */
#define STD_HIGH   0x01u   /* Physical state 5V or 3.3V  */
#define STD_LOW    0x00u   /* Physical state 0V          */

/*TRACE[SWS_Std_00013]: STD_ACTIVE and STD_IDLE */
#define STD_ACTIVE 0x01u   /* Logical state active       */
#define STD_IDLE   0x00u   /* Logical state idle         */

/*TRACE[SWS_Std_00010]: STD_On and STD_OFF */
#define STD_ON     0x01u   /* On state                   */
#define STD_OFF    0x00u   /* Off state                  */

#endif /* STD_TYPES_H */