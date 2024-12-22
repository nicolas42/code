// clang -Weverything -Wno-missing-prototypes allocator.c && ./a.out

#include "lib.h"

static u8 memory[1000000000];
static u64 memory_count = 0;

u8* allocate(u64 n){
    u64 saved_memory_count = memory_count;
    memory_count += n;
    return memory + saved_memory_count;
}

int main() {


    int* a = (int*)allocate(1000000);
    int* b = (int*)allocate(1000000);

    int i=0;
    int N=100;
    for(i=0;i<N;++i){ a[i] = i; } 
    for(i=0;i<N;++i){ printf("%d ", a[i]); }
    printf("\n");

    for(i=0;i<N;++i){ b[i] = N-i; } 
    for(i=0;i<N;++i){ printf("%d ", b[i]); }

    return 0;

}
