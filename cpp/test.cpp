// cl /Zi test.cpp /link  "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS

#include <stdint.h>
#include <stdio.h>



int main()
{
  int candidate = 887;
  
  int is_prime = 1;
    for (int i=2; i<candidate; i++){
      if ( candidate % i == 0 ) { is_prime = 0; break; }
    }
    printf("%d\n\r", is_prime);

    
  return 0;
}

