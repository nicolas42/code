// g++ myprintf.c -Iinclude && ./a.out


#include "libc.h"








#include <stdio.h>

int snprintf_demo()
{

    printf("\n\n");
    printf("snprintf_demo\n");
    printf("-----------------------\n");

  char buffer [100];
  int cx;

  cx = snprintf ( buffer, 100, "The half of %d is %d", 60, 60/2 );

  if (cx>=0 && cx<100)      // check returned value

    snprintf ( buffer+cx, 100-cx, ", and the half of that is %d.", 60/2/2 );

  puts (buffer);

  return 0;
}





void sprint_float3(char* str, float arg)
{

    // sprint a float to 3 decimal places
    // To change the number of decimal places change 1000 and %03d
    // from https://stackoverflow.com/questions/905928/using-floats-with-sprintf-in-embedded-c

    char *sign;
    float val;
    int integer_part, fraction_part;

    if (arg < 0) { sign=(char*)"-"; val = -arg; } else { sign=(char*)""; val = arg; }

    integer_part = trunc(val);
    fraction_part = trunc((val - integer_part) * 1000);  // Get fraction then turn into integer (123).

    if (fraction_part == 0){
        sprintf (str, "%s%d", sign, integer_part);
    } else {
        sprintf (str, "%s%d.%03d", sign, integer_part, fraction_part);  
    }

}


int sprint_float3_main()
{

    printf("\n\n");
    printf("sprint_float3_main\n");
    printf("-----------------------\n");

    char str[100];

    sprint_float3(str, 0.01234);
    puts(str);
    sprint_float3(str, -3.1415926535);
    puts(str);
    sprint_float3(str, 3234);
    puts(str);

  return 0;
}


char *myprintf_convert(unsigned int num, int base)
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do { 
        *--ptr = Representation[num%base]; 
        num /= base; 
        
    } while(num != 0); 

    return(ptr); 
}


void myprintf(const char* format,...)
{ 

    const char *traverse; 
    int i; 
    char *s; 

    double float_value;
    int float_decimal_places  = 6;
    int float_fraction_scaler = 1000000;
    
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        // print regular
        if( *traverse != '%' && *traverse != '\\' ) { 
            putchar(*traverse);
        } 
        // print escape chars
        if( *traverse == '\\' ) {
            traverse += 1;

            if      ( *traverse == 'n' ) { putchar('\n'); }
            else if ( *traverse == 't' ) { putchar('\t'); }
            else if ( *traverse == 'r' ) { putchar('\r'); }
            else {
                printf("ERROR %s %d Unknown escape character\n", __FILE__, __LINE__ );
                putchar('\\');
                putchar( *traverse );
            }
        }
        // print numbers in various formats
        if( *traverse == '%' ) {
            traverse++;
            switch (*traverse) { 

            case 'c' : i = va_arg(arg, int);
                        putchar(i);
                        break; 

            case 'd' : i = va_arg(arg, int);
                        if(i<0){ 
                            i = -i;
                            putchar('-'); 
                        } 
                        fputs(myprintf_convert(i, 10), stdout);
                        break; 

            case 'o': i = va_arg(arg, unsigned int);
                        fputs(myprintf_convert(i, 8), stdout);
                        break; 

            case 's': s = va_arg(arg, char *);
                        fputs(s, stdout);
                        break; 

            case 'x': i = va_arg(arg, unsigned int);
                        fputs(myprintf_convert(i, 16), stdout);
                        break; 

            case 'f': 
                        float_value = va_arg(arg, double);

                        char sign = '\0';
                        if (float_value < 0) { sign='-'; float_value = -float_value; } 
                        int integer_part = trunc(float_value);
                        int fraction_part = trunc((float_value - integer_part) * float_fraction_scaler);


                        if (sign) fputc(sign, stdout);
                        fputs(myprintf_convert(integer_part, 10), stdout);

                        if (fraction_part != 0){
                            char *fraction_string = myprintf_convert(fraction_part, 10);
                            fputc('.', stdout);
                            for(int i=0; i < ( float_decimal_places - strlen(fraction_string) ); i+=1 ) fputc('0', stdout);
                            fputs(fraction_string, stdout);
                        }
                        break;
            }

        }
    } 


    va_end(arg); 
} 


void myprintf_demo()
{
    
    printf("\n\n");
    printf("myprintf_demo\n");
    printf("-----------------------\n");

    myprintf("char \t %c\ninteger \t %d\noctal \t %o\nstring \t {%s}\nhex \t %x\nfloat \t %f\n", 'c', 999, 999, "omg", 999, 999.4323423423234 );

}




int main()
{
    // snprintf_demo();
    // sprint_float3_main();
    myprintf_demo();
    return 0;
}



