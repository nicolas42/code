/*
An embarassingly large amount of other stuff was tried before doing this.

./col $(python -c "print('\xe8\x05\xd9\x1d' + 16*'\x01')")

./col $(python3 -c "import sys; sys.stdout.buffer.write(b'\xe8\x05\xd9\x1d' + 16 * b'\x01')")


I need 5 numbers that add to
0x21DD09EC (568134124)
They must each be 4 characters long.

568134124 = 5x - 2^32
x = ( 568134124 + 2**32 ) / 5
x = 972620284
>>> hex(972620284 * 5) == '0x121dd09ec
x86 is little endian so we reverse the bytes
0xfc01f939

Use xargs to avoid unprintable characters
hex_string="fc01f939fc01f939fc01f939fc01f939fc01f939"; echo -n $hex_string | xxd -r -p | xargs ./col

daddy! I just managed to create a hash collision :)



Without adding 2^23
------------------------------

>>> hex(0x21dd09ec // 5), hex(0x21dd09ec % 5)
('0x6c5cec8', '0x4')

>>> hex(0x6c5cec8 + 0x4) 
'0x6c5cecc'

4 * '0x6c5cec8' + '0x6c5cecc' should do it.

0x6c5cec80x6c5cec80x6c5cec80x6c5cec80x6c5cecc

convert to little endian 
c8cec506c8cec506c8cec506c8cec506cccec506

hex_string="c8cec506c8cec506c8cec506c8cec506cccec506"; echo -n $hex_string | xxd -r -p | xargs ./col


Python
------------------------
hex(0x21DD09EC - (4*0x01010101))
0x1dd905e801010101010101010101010101010101


*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p){
	int* ip = (int*)p;
	int i;
	int res=0;
	for(i=0; i<5; i++){
	  printf("0x%x\n", ip[i]);
		res += ip[i];
	}

	printf("0x%lx\n", hashcode);
	printf("0x%x\n",  res);
	return res;
}

int main(int argc, char* argv[]){
  
  /*
  // print bytes
  printf("%lu\n", strlen(argv[1]));
  for(int i=0;i<20;++i) printf("0x%X ", (uint8_t)argv[1][i]);
  printf("\n");
  return 0;
  */

  // check input.  use incantation below to output bytes and read them again
  // gcc col.c && ./a.out $(python3 -c "import sys; sys.stdout.buffer.write(b'\xe8\x05\xd9\x1d\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01')")
  /*
  uint32_t s = 0;
  for(int i=0;i<20;i+=4) {
    uint32_t ti = 0;
    uint8_t *b = &(argv[1][i]);
    // [1, 256, 65536, 16777216]
    ti += b[0] * 1;
    ti += b[1] * 256;
    ti += b[2] * 65536;
    ti += b[3] * 16777216;
    s += ti;
    printf("%x %x %x %x, ", b[0],b[1],b[2],b[3]);
    
  }
  printf("%X\n", s);
  */

  if(argc<2){
    printf("usage : %s [passcode]\n", argv[0]);
    return 0;
  }
  if(strlen(argv[1]) != 20){
    printf("passcode length should be 20 bytes\n");
    return 0;
  }

  check_password( argv[1] ); // omg
    
  if(hashcode == check_password( argv[1] )){
    system("/bin/cat flag");
    return 0;
  }
  else
    printf("wrong passcode.\n");
  return 0;
}
