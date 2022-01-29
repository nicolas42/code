#ifndef DEFINE_ARRAY_HEADER_GUARD
#define DEFINE_ARRAY_HEADER_GUARD


#include <stdint.h>
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


// // expanding array 
// // usage:  type_array_add( &arr, val );

#define DEFINE_ARRAY(TYPENAME)\
\
struct TYPENAME ## _array { \
    TYPENAME* data; \
    int length; \
    int allocated; \
}; \
typedef struct TYPENAME ## _array TYPENAME ## _array;\
\
TYPENAME ## _array TYPENAME ## _array_make()\
{\
    TYPENAME ## _array arr;\
    arr.length = 0;\
    arr.allocated = 1000;\
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );\
    return arr;\
}\
\
void TYPENAME ## _array_add(TYPENAME ## _array *arr, TYPENAME item)\
{\
    if ( arr->length == arr->allocated ) {\
      arr->allocated *= 2;\
      arr->data = (TYPENAME*)realloc( arr->data, arr->allocated * sizeof(TYPENAME) );\
    }\
    arr->data[arr->length] = item;\
    arr->length += 1;\
}\



// // expanding array with copy semantics
// // usage:  arr = type_array_add(arr, val);


// #define DEFINE_ARRAY2(TYPENAME)\
// \
// typedef struct {\
//   TYPENAME* data;\
//   int length;\
//   int allocated;\
// } TYPENAME ## _array;\
// \
// TYPENAME ## _array TYPENAME ## _array_make()\
// {\
//     TYPENAME ## _array arr;\
//     arr.length = 0;\
//     arr.allocated = 16;\
//     arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );\
//     return arr;\
// }\
// \
// TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)\
// {\
//     if ( arr.length == arr.allocated ) {\
//       arr.allocated *= 2;\
//       arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );\
//     }\
//     arr.data[arr.length] = item;\
//     arr.length += 1;\
//     return arr;\
// }\


#endif // DEFINE_ARRAY_HEADER_GUARD