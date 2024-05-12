#include <stdio.h>
#include <string.h>
#include <stdint.h>

unsigned long hashcode = 0x21DD09EC;
unsigned long check_password(const char* p){
  int* ip = (int*)p;
  int i;
  int res=0;
  for(i=0; i<5; i++){
    // printf("0x%x\n",ip[i]);
    res += ip[i];
  }
  // printf("0x%x\n", res);
  return res;
}


int main(int argc, char* argv[]){

  0x1dd905e801010101010101010101010101010101
  printf("%lu\n", strlen(argv));
  for(int i=0;i<20;++i) printf("0x%x,", argv[1][i]);


  // 0x1dd905e801010101010101010101010101010101

  printf("\n");

  return 0;
}

// '\x1d\xd9\x05\xe8\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01'

// I literally just need 5 numbers that add to
// 0x21DD09EC (568134124)
// The numbers are each 4 characters long.

// 568134124 = 5x - 2^32
// x = ( 568134124 + 2**32 ) / 5 = 972620284
// >>> hex(972620284 * 5) == '0x121dd09ec
// that's okay, except for the 
//>>> hex(972620284) == '0x39f901fc'

// x86 is little endian 
// 0xfc01f939
    


// pass_hex=$(echo -n "00000000000000000000" | xxd -p);  echo -n $pass_hex | xxd -r -p | xargs ./col

// hex_string="fc01f939fc01f939fc01f939fc01f939fc01f939"; echo -n $hex_string | xxd -r -p | xargs ./col

// 0x39f901fc
// 0xfc01f939


int main3(){

  // Trying dividing the bytes individually :(
  unsigned long hashcode = 0x21DD09EC;  
  uint32_t a = 0xFF + 0x21, b = 0xFF + 0xdd, c = 0xFF + 0x09, d = 0x100 + 0xec;

  printf("0x%x 0x%x 0x%x 0x%x\n", a/5, b/5, c/5, d/5);
  printf("0x%x 0x%x 0x%x 0x%x\n", a%5, b%5, c%5, d%5);

  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62  
  // 0x3 0x1 0x4 0x2

  uint8_t e[4] = {0x39, 0x5f, 0x34, 0x62};
  uint32_t f = *((uint32_t*)e);
  uint8_t g[4] = { 0x3, 0x1, 0x4, 0x2};
  uint32_t h = *((uint32_t*)g);
  
  printf("0x%x\n",f*5+h);
  printf("0x%lx\n",hashcode);
  return 0;

}



int main1(int argc, char* argv[]){

  // 0x21DD09EC + 0xFFFFFFFF + 0x1
  printf("0x%x r 0x%x\n", 0x21DD09EC / 5, 0x21DD09EC % 5);
  printf("0x%x r 0x%x\n", 0xFFFFFFFF / 5, 0xFFFFFFFF % 5);
  // 0x6c5cec8 r 0x4
  // 0x33333333 r 0x0
  // each value should be about 0x33333333 + 0x6c5cec8
  printf("0x%x\n", 0x33333333 + 0x6c5cec8);
  // 0x39f901fb
  printf("0x%x\n", 0x39f901fb * 5);
  printf("0x%lx <-goal\n", hashcode);

  printf("%c%c%c%c\n", 0x39,0xf9, 0x01, 0xfb);  
  
  return 0;
}



int demo1(){
  uint32_t a[5] = {0,0,0,0,0};
  for(uint32_t i=0;i<4294967295;++i){
    for(uint32_t j=0;i<4294967295;++j){
      for(uint32_t k=0;i<4294967295;++k){
	for(uint32_t l=0;i<4294967295;++l){
	  for(uint32_t m=0;i<4294967295;++m){
	    a[0]=i;
	    a[1]=j;
	    a[2]=k;
	    a[3]=l;
	    a[4]=m;
    
	    char *b = (char*)a;
	    if(hashcode == check_password( b )){
	      for(int n=0;n<20;++n){ printf("%c", b[n]); } // 0x5abd1ae0
	    }
	  }
	}
      }
    }
  }
  
  return 0;
}


/*
  // 0x30 .. 0x7E
  // 32 bit integer represents 2^32 values
  // overflow means you add

  //  uint8_t a1 = 0xFF;
  //  uint8_t b1 = 0x21;
  //  printf("0x%x\n", (uint8_t)(a1+b1 + 0x01));
   

  unsigned long hashcode = 0x21DD09EC;  
  uint32_t a = 0xFF + 0x21, b = 0xFF + 0xdd, c = 0xFF + 0x09, d = 0x100 + 0xec;

  printf("0x%x 0x%x 0x%x 0x%x\n", a/5, b/5, c/5, d/5);
  printf("0x%x 0x%x 0x%x 0x%x\n", a%5, b%5, c%5, d%5);

  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62
  // 0x39 0x5f 0x34 0x62  
  // 0x3 0x1 0x4 0x2
  
  char test[][4] = {
    {0x39, 0x5f, 0x34, 0x62},
    {0x39, 0x5f, 0x34, 0x62},
    {0x39, 0x5f, 0x34, 0x62},
    {0x39, 0x5f, 0x34, 0x62},
    {0x42, 0x60, 0x38, 0x64},
  // 0x3 0x1 0x4 0x2    
  };
  printf("test: ");
  for(int i=0;i<5;++i){
    for(int j=0;j<4;++j){ printf("%c",  test[i][j]); }
  }
  printf("\n");

  char argv1[20] = {
    0x39, 0x5f, 0x34, 0x62,
    0x39, 0x5f, 0x34, 0x62,
    0x39, 0x5f, 0x34, 0x62,
    0x39, 0x5f, 0x34, 0x62,
    0x42, 0x60, 0x38, 0x64
  };
  
  check_password(argv1);
  return 0;
  // remainder <`8d
    
  // x86 uses little endian  
  // 9_4b
  // <`8d



  

  uint32_t e = (a/5 << 24) + (b/5 << 16) + (c/5 << 8) + d/5;
  uint32_t f = (a%5 << 24) + (b%5 << 16) + (c%5 << 8) + d%5;  
  printf("5e+f: 0x%x 5e: 0x%x\n", e*5+f, 5*e);
  printf("goal: 0x%lx\n", hashcode);

  uint8_t *g = (int*)&e; // b4_9
  printf("%c%c%c%c\n", g[0],g[1],g[2],g[3]);

  return 0;


  //  0x39 0x5f 0x34 0x62
  //  0x3 0x1 0x4 0x2

  uint8_t *g = (uint8_t*)&e;
  uint8_t *h = (uint8_t*)&f;
  for(int i=0;i<4;++i) printf("0x%x ", g[i]);
  for(int i=0;i<4;++i) printf("0x%x ", h[i]);


  printf("%c%c%c%c\n", g[3],g[2],g[1],g[0]);
  printf("%c%c%c%c\n", g[3]+h[3],g[2]+h[2],g[1]+h[1],g[0]+h[0]);


  char test[][4] = {
    {0x40, 0x5f, 0x34, 0x62},
    {0x40, 0x5f, 0x34, 0x62},
    {0x40, 0x5f, 0x34, 0x62},
    {0x39, 0x50, 0x34, 0x62},
    {0x39, 0x6f, 0x38, 0x64},
  };
  for(int i=0;i<5;++i){
    for(int j=0;j<4;++j){ printf("%c",  test[i][j]); }
  }
  printf("\n");


  printf("hashcode: 0x%lx\n", hashcode);
  check_password("9_4b9_4b9_4b9_4b9_4b");
  */

  /*

  uint32_t l = *(uint32_t*)g;
  uint32_t m = *(uint32_t*)h;
  printf("0x%x\n", 5*l+m);

  // x86 uses little endian  
  // 9_4b
  // <`8d

  // b4_9
  // d8`<
  

  char test[][4] = {
    {0x40, 0x5f, 0x34, 0x62},
    {0x40, 0x5f, 0x34, 0x62},
    {0x40, 0x5f, 0x34, 0x62},
    {0x39, 0x50, 0x34, 0x62},
    {0x39, 0x6f, 0x38, 0x64},
  };

  for(int i=0;i<5;++i){
    for(int j=0;j<4;++j){ printf("%c",  test[i][j]); }
  }
  printf("\n");

    char test[][] = {
    {0x39, 0x5f, 0x34, 0x62},
    {0x39, 0x5f, 0x34, 0x62},
    {0x39, 0x5f, 0x34, 0x62},
    {0x39, 0x50, 0x34, 0x62},
    {0x3c, 0x6f, 0x38, 0x64},
    }  
  // char h[] = {0x3, 0x1, 0x4, 0x2}; // remainder

// can't have 0x60 cause it's `
  */
  


  
  /*  
  int a[5];
  a[0] = (0x3A << 24) + (0x3A << 16) + (0x3A << 8) + (0x3A << 0);
  a[1] = (0x3A << 24) + (0x3A << 16) + (0x3A << 8) + (0x3A << 0);
  a[2] = (0x3A << 24) + (0x3A << 16) + (0x3A << 8) + (0x3A << 0);
  a[3] = (0x3A << 24) + (0x3A << 16) + (0x3A << 8) + (0x3A << 0);
  a[4] = (0x39 << 24) + (0x00 << 16) + (0x00 << 8) + (0x00 << 0);  
  int s = a[0]+a[1]+a[2]+a[3]+a[4];

  printf("result: 0x%x\n", s);
  printf("goal: 0x%x\n", (int)hashcode);

  int difference = s - hashcode;
  printf("difference: %d\n", difference);

  printf("difference: 0x%x\n",difference);
  */  

  //  return 0;
    


/*

  
  if(argc<2){
    printf("usage : %s [passcode]\n", argv[0]);
    return 0;
  }

  printf("characters: ");
  for (int i=0;i<20;i+=1) printf("%c ",argv[1][i]);
  printf("\n");
  printf("bytes: ");  
  for (int i=0;i<20;i+=1) printf("%d ",argv[1][i]);
  printf("\n");
  
  int *a = (int*)(argv[1]);
  int s = 0;
  printf("integers: ");
  for (int i=0;i<5;i+=1) {
    s += a[i];
    printf("%d ",a[i]);
  }
  printf("\n");
  
  printf("sum: %d\n", s);

  int goal = 568134124;
  printf("goal: %d\n", goal);
  printf("difference %d\n", goal - s);
  
  
  return 0;

  
  if(strlen(argv[1]) != 20){
    printf("passcode length should be 20 bytes\n");
    return 0;
  }

  if(hashcode == check_password( argv[1] )){
    system("/bin/cat flag");
    return 0;
  }
  else
    printf("wrong passcode.\n");
  return 0;
}

*/
