// gcc basic_test.c -Wfatal-errors && ./a.out

#define BASIC_IMPLEMENTATION
#include "basic.h"


// DEFINE_ARRAY(TYPENAME) Demo

DEFINE_ARRAY(f64)
DEFINE_ARRAY(char)
typedef struct { int x; int y; } arbitrary_type;
DEFINE_ARRAY(arbitrary_type)
typedef void* voidptr;
DEFINE_ARRAY(voidptr)

void define_array_demo()
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


    arbitrary_type_array arr3 = arbitrary_type_array_make();
    for(i=0;i<100;++i) { 
        arbitrary_type a;
        a.x = i;
        a.y = 2*i;
        arr3 = arbitrary_type_array_add(arr3, a);
    }
    for(i=0;i<100;++i) printf("[%d %d] ", arr3.data[i].x, arr3.data[i].y);
    printf("\n");


    voidptr_array arr4 = voidptr_array_make();
    for(s64 i=0;i<100;++i) arr4 = voidptr_array_add(arr4, (voidptr)i);
    for(i=0;i<100;++i) printf("%d ", (int)arr4.data[i]);
    printf("\n");

}






void split_string_demo()
{

    char string[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\n";
    struct list list;
    list = split_string(string,",\n");
    for(int i=0;i<list.length;i+=1) printf("%s\n", (char*)list.data[i]);

}


int main(int argc, char **argv)
{
    define_array_demo();
    split_string_demo();

    return 0;
}
