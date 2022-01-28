// demo endianness o_o

#include <stdio.h>
#include <stdint.h>

int main( int argc, char* args[] )
{

    {
        uint32_t a[2] = {0x01020304, 0x01020304 };
        uint8_t *b = (uint8_t*)a;
        int i;
        // printf("The pointer points to the first byte in the array, independent of the data, apparently. address = %u, %u", a,b);

        printf("The two integers ");
        for(i=0;i<2;++i){ printf("%08x ", a[i]); }
        printf("\n");

        printf("are represented in memory as ");
        for(i=0;i<2*4;++i){ printf("%02x ", b[i]); }
        printf("\n");

        printf("\nIn x86 systems, multi-byte data is flipped around as it goes from memory to the processor\n");
    }




    // let's do the same thing again why not?
    if(0){
        uint8_t bytes[8] = {0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04 };
        uint32_t* integers = (uint32_t*)bytes;
        int i;

        printf("Put some bytes in memory\n");
        for(i=0;i<2*4;++i){ printf("%02x ", bytes[i]); }
        printf("\n");

        printf("Retype them as integers and print the array again\n");
        for(i=0;i<2;++i){ printf("%08x ", integers[i]); }
        printf("\n");


        // why not do it again with laborious bitwise operations
        printf("Do it again with laborious bitwise operations\n");
        for(i=0;i<2;++i){ 
            printf("%02x %02x %02x %02x ", 
                (uint8_t)((integers[i] & 0xff000000)>>24), 
                (uint8_t)((integers[i] & 0x00ff0000)>>16),
                (uint8_t)((integers[i] & 0x0000ff00)>>8), 
                (uint8_t)((integers[i] & 0x000000ff)>>0) 
            ); 
        }
        printf("\n");
    }


    return 0;
}
