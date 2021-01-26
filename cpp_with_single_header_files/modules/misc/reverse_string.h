#include <stdio.h>
#include <string.h>

namespace misc {

char* reverse_string(char *s)
{
  int l = strlen(s);
  
  for (int i=0; i<l/2; ++i){
    char tmp = s[l-1-i];
    s[l-1-i] = s[0+i];
    s[0+i] = tmp;
  }
  return s;
}

}
