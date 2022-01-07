/*
Use -E to see the outputs of macros
gcc -E define_array_macro.c

## joins strings in a macro
str1 ## str2 becomes str1str2


*/

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
#include <stdio.h>
#include <stdlib.h>


#define DEFINE_ARRAY(TYPENAME)                                                                  \
                                                                                                \
typedef struct {                                                                                \
  TYPENAME* data;                                                                               \
  int length;                                                                                   \
  int allocated;                                                                                \
} TYPENAME ## _array;                                                                           \
                                                                                                \
TYPENAME ## _array TYPENAME ## _array_make()                                                    \
{                                                                                               \
    TYPENAME ## _array arr;                                                                     \
    arr.length = 0;                                                                             \
    arr.allocated = 10;                                                                         \
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );                           \
    return arr;                                                                                 \
}                                                                                               \
                                                                                                \
TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)                \
{                                                                                               \
    arr.data[arr.length] = item;                                                                \
    arr.length += 1;                                                                            \
    if ( arr.length == arr.allocated ) {                                                        \
      arr.allocated *= 2;                                                                       \
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );              \
    }                                                                                           \
    return arr;                                                                                 \
}                                                                                               \



DEFINE_ARRAY(f64)
DEFINE_ARRAY(char)
typedef struct { int x; int y; } another_type;
DEFINE_ARRAY(another_type)
typedef void* voidptr;
DEFINE_ARRAY(voidptr)

int main()
{
    // int a;
    // a = sqr(64);
    // printf("%d\n", a);

    f64_array arr = f64_array_make();
    int i;
    for(i=0;i<100;++i) arr = f64_array_add(arr, i);
    for(i=0;i<100;++i) printf("%f ", arr.data[i]);
    printf("\n");

    char_array arr2 = char_array_make();
    char c;
    for(c=0;c<100;++c) arr2 = char_array_add(arr2, c+65);
    for(i=0;i<100;++i) printf("%c ", (int)arr2.data[i]);
    printf("\n");


    another_type_array arr3 = another_type_array_make();
    for(i=0;i<100;++i) { 
        another_type a;
        a.x = i;
        a.y = 2*i;
        arr3 = another_type_array_add(arr3, a);
    }
    for(i=0;i<100;++i) printf("[%d %d] ", arr3.data[i].x, arr3.data[i].y);
    printf("\n");


    voidptr_array arr4 = voidptr_array_make();
    for(s64 i=0;i<100;++i) arr4 = voidptr_array_add(arr4, (voidptr)i);
    for(i=0;i<100;++i) printf("%d ", (int)arr4.data[i]);
    printf("\n");




    return 0;
}

