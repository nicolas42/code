#include <unistd.h>
#include <stdint.h>

int main() {
    // Define the binary data
  // 0x21DD09EC - 0x04040404 == 0x1dd905e8
  uint8_t binary_data[] = {0xe8, 0x05, 0xd9, 0x1d, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
    write(1, binary_data, 20);

    return 0;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Define the binary data
    unsigned char binary_data[] = {0x1D, 0xD9, 0x05, 0xE8, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

    // Calculate the length of the binary data
    size_t data_length = sizeof(binary_data) / sizeof(binary_data[0]);

    write(1, binary_data, data_length);
    
    // Write the binary data to stdout
    // fwrite(binary_data, 1, data_length, stdout);

    return 0;
}

*/
