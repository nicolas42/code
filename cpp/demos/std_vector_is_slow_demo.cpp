// g++ std_vector_is_slow_demo.cpp && ./a.out

// g++ std_vector_is_slow_demo.cpp -Ofast && ./a.out

// std::vector is almost 3 times slower than this simple expanding array implementation

#include <vector>


#include <stdint.h>
typedef uint64_t u64;

struct u64_array { u64* data; int length; int allocated; }; 
typedef struct u64_array u64_array;

u64_array u64_array_make()
{
    u64_array arr;
    arr.length = 0;
    arr.allocated = 16;
    arr.data = (u64*)malloc( arr.allocated * sizeof(u64) );
    return arr;
}

void u64_array_add(u64_array *arr, u64 item)
{
    if ( arr->length == arr->allocated ) {
      arr->allocated *= 2;
      arr->data = (u64*)realloc( arr->data, arr->allocated * sizeof(u64) );
    }
    arr->data[arr->length] = item;
    arr->length += 1;
}


u64_array u64_array_add2(u64_array arr, u64 item)
{
    if ( arr.length == arr.allocated ) {
      arr.allocated *= 2;
      arr.data = (u64*)realloc( arr.data, arr.allocated * sizeof(u64) );
    }
    arr.data[arr.length] = item;
    arr.length += 1;
    return arr;
}


int main()
{
    int i;
    time_t t0 = clock();

    std::vector<u64> std_vector;
    for(i=0;i<100*1000*1000;i+=1) std_vector.push_back(i);
    time_t t1 = clock();
    
    u64_array arr = u64_array_make();
    for(i=0;i<100*1000*1000;i+=1) u64_array_add( &arr, i );
    time_t t2 = clock();

    u64_array arr2 = u64_array_make();
    for(i=0;i<100*1000*1000;i+=1) arr2 = u64_array_add2( arr2, i );
    time_t t3 = clock();

    printf("\n\n");
    printf("std_vector\n");
    printf("duration: %f\n", ((double)( t1 - t0 )) / (double)CLOCKS_PER_SEC );
    printf("my expanding array\n");
    printf("duration: %f\n", ((double)( t2 - t1 )) / (double)CLOCKS_PER_SEC );
    printf("my expanding array with copies\n");
    printf("duration: %f\n", ((double)( t3 - t2 )) / (double)CLOCKS_PER_SEC );

    return 0;
}



