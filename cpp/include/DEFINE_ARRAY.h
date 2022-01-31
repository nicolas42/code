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


// expanding array 
// usage:  
// <type>_array arr = <type>_array_make();
// <type>_array_add( &arr, val );
// free ( arr.data );

#define DEFINE_ARRAY(TYPE)\
\
struct TYPE ## _array { \
    TYPE* data; \
    int length; \
    int allocated; \
}; \
typedef struct TYPE ## _array TYPE ## _array;\
\
TYPE ## _array TYPE ## _array_make()\
{\
    TYPE ## _array arr;\
    arr.length = 0;\
    arr.allocated = 1000;\
    arr.data = (TYPE*)malloc( arr.allocated * sizeof(TYPE) );\
    return arr;\
}\
\
void TYPE ## _array_add(TYPE ## _array *arr, TYPE item)\
{\
    if ( arr->length == arr->allocated ) {\
      arr->allocated *= 2;\
      arr->data = (TYPE*)realloc( arr->data, arr->allocated * sizeof(TYPE) );\
    }\
    arr->data[arr->length] = item;\
    arr->length += 1;\
}\








// #include <stdio.h>
// #include <stdlib.h>

// DEFINE_ARRAY(f64)
// DEFINE_ARRAY(char)
// typedef struct { int x; int y; } arbitrary_type;
// DEFINE_ARRAY(arbitrary_type)
// typedef void* voidptr;
// DEFINE_ARRAY(voidptr)


// int main()
// {
//     f64_array arr = f64_array_make();
//     int i;
//     for(i=0;i<100;++i) f64_array_add(&arr, i);
//     printf("[ ");
//     for(i=0;i<100;++i) printf("%f ", arr.data[i]);
//     printf("]\n\n");

//     char_array arr2 = char_array_make();
//     char c;
//     for(c=0;c<100;++c) char_array_add(&arr2, c+65);
//     printf("[ ");
//     for(i=0;i<100;++i) printf("%c ", arr2.data[i] );
//     printf("]\n\n");


//     arbitrary_type_array arr3 = arbitrary_type_array_make();
//     for(i=0;i<100;++i) { 
//         arbitrary_type a;
//         a.x = i;
//         a.y = 2*i;
//         arbitrary_type_array_add(&arr3, a);
//     }
//     printf("[ ");
//     for(i=0;i<100;++i) printf("[%d %d] ", arr3.data[i].x, arr3.data[i].y);
//     printf("]\n\n");


//     voidptr_array arr4 = voidptr_array_make();
//     for(s64 i=0;i<100;++i) voidptr_array_add(&arr4, (voidptr)i);
//     printf("[ ");
//     for(i=0;i<100;++i) printf("%lld ", (s64)arr4.data[i] );
//     printf("]\n\n");

//     return 0;
// }





#endif // DEFINE_ARRAY_HEADER_GUARD
