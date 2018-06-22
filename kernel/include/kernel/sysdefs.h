#ifndef __SYS_DEFS_H__
#define __SYS_DEFS_H__ 1

#include <stdint.h>

typedef int16_t KAOS_ERR;

#define KAOS_ERR_NO_ERROR              0
#define KAOS_ERR_DIVISION_BY_ZERO      1
#define KAOS_ERR_OVERFLOW              2
#define KAOS_ERR_NO_FS_DETECTED        3




typedef uint8_t BOOL;

#define TRUE    1
#define FALSE   0



#ifdef KAOS_DEBUG_MODE
#define UNUSED(x) (void)(x)
#else
#define UNUSED(x)
#endif



#endif