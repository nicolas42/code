#ifndef BASIC_HEADER_GUARD
#define BASIC_HEADER_GUARD

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <math.h>

// #define PRINT_ERROR(msg) printf("ERROR %s %d %s\n",__FILE__,__LINE__,msg);


typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;



#define DEFINE_ARRAY(TYPENAME)\
\
typedef struct {\
  TYPENAME* data;\
  int length;\
  int allocated;\
} TYPENAME ## _array;\
\
TYPENAME ## _array TYPENAME ## _array_make()\
{\
    TYPENAME ## _array arr;\
    arr.length = 0;\
    arr.allocated = 16;\
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );\
    return arr;\
}\
\
TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)\
{\
    if ( arr.length == arr.allocated ) {\
      arr.allocated *= 2;\
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );\
    }\
    arr.data[arr.length] = item;\
    arr.length += 1;\
    return arr;\
}\



#endif // BASIC_HEADER_GUARD
