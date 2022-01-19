#define BASIC_IMPLEMENTATION
#include "basic.h"



char* caesar_cipher(char* text, int shift)
{
    char* code = (char*)calloc(strlen(text)+1, sizeof(char));
    int i;

    shift %= 26;

    for (i = 0; i < strlen(text); i++) {

        if (text[i] >= 'a' && text[i] <= 'z') {

            if (text[i]+shift >= 128) {
                shift -= 26;
            }

            code[i] = (char)(text[i]+shift);

            if (code[i] < 'a') {
                code[i] += 26;
            } else if (code[i] > 'z') {
                code[i] -= 26;
            }

        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            code[i] = (char)(text[i]+shift);

            if (code[i] < 'A') {
                code[i] += 26;
            } else if (code[i] > 'Z') {
                code[i] -= 26;
            }

        } else {
            code[i] = text[i];
        }
    }

    return code;
}

int caesar_cipher_main()
{
    printf(
        "\n\ncaesar_cipher_main\n"
        "--------------------------\n"
    );

    char text[] = "The quick brown fox jumps over the lazy dog.";
    int shift = 13;

    printf("\"%s\"\n", text );
    printf("\"%s\"\n",caesar_cipher(text, shift));
    return 0;
}



#include <stdio.h>
#include <string.h>

void demo_strtok(void)
{

    printf(
        "\n\nSTRTOK DEMO\n"
        "--------------------------\n"
    );

    char str[] = 
    "Return Value\n"
    "This function returns a pointer to the first token found in the string. \n"
    "A null pointer is returned if there are no tokens left to retrieve.\n"
    "\n"
    "Example\n"
    "The following example shows the usage of strtok() function.\n"
    "\n";


    // strtok uses a static for the string after it's initialized
    for (char *p = strtok(str,"\n"); p != NULL; p = strtok(NULL, "\n")){
        printf("{%s}\n", p);
    }

}


#include <stdarg.h>
// https://www.tutorialspoint.com/c_standard_library/c_macro_va_start.htm

int variadic_sum(int num_args, ...)
{
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}

int demo_variadic_sum(void)
{
   printf("Sum of 10, 20 and 30 = %d\n",  variadic_sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  variadic_sum(4, 4, 20, 25, 30) );

   return 0;
}


#include <stdio.h>
#include <stdio.h>
#include <math.h>

// float f_dash(float x, float y, float *dx, float *dy) { return y; }

int eulers_method_main()
{
    // Euler's Method for solving a differential equation
    // ---------------------------------------------------
    // start at a point.  calculate the slope
    // follow the slope to the next point
    // repeat

    // y1 = dydx(x0,y0) * delta_x + y0;
    // x1 = x0 + delta_x;

    // khan https://www.youtube.com/watch?v=q87L9R9v274



    if (0) {
        // Example: Draw the line y = e^x from its vector field 
        // dy_dx = y, y(0) = 1

        float x = 0;
        float y = 1;
        float slope = y; 
        float delta_x = 0.0001;

        for (int i = 0; i < 1.0/delta_x; i += 1)
        {

            slope = y;
            y = y + slope * delta_x;
            x = x + delta_x;
            printf("x, y, slope: [ %f %f %f ]\n", x, y, slope);
        }
        // output 
        // x, y, slope: [ 1.0000 2.7181 2.7179 ]
        // yahoo!!
    }



    {   
        // Example: Draw a circle using the vector field < -y, x >

        float x = 1;
        float y = 0;
        float dx = -y;
        float dy = x;
        float step = 0.0001;
        #define TWOPI 6.28318530718

        printf("\n\n");
        printf("Euler's Method for solving differential equations and vector fields\n");
        printf("---------------------------------------------------------------------\n");
        printf("Drawing a circle using the vector field < -y, x >\n");
        printf("Starting point\n");
        printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);

        for (int i = 0; i < TWOPI/step; i += 1)
        {
            dx = -y;
            dy = x;

            y = y + dy * step;
            x = x + dx * step;
            // printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);
        }
        printf("End point\n");
        printf("x, y, dx, dy: [ %f %f %f %f %f ]\n", x, y, dx, dy, step);

        // output 
        // using float
        // x, y, dx, dy: [ 1.000314 0.000015 0.000085 1.000314 0.000100 ]
        // using double
        // x, y, dx, dy: [ 1.000316 0.000015 0.000085 1.000316 0.000100 ]


    }




    // Conservative Vector Fields
    // -----------------------------------------

    // A conservative vector field is one that has an associated scalar field.
    // that can be found by integrating all of the partial derivative equations

    // Here's a scalar field
    // f(x,y) = 1/4 x4y4 + 1/2 x2 + 1/2 y2 ) + c

    // The associated vector field is the gradient of f 
    // grad f(x,y) = dfdx(x,y) i  + dfdy(x,y) j 

    // let fx be dfdx and fy be dfdy

    // fx = x3y4 + x
    // fy = x4y3 + y


    // A vector field is conservative if you can integrate all of the gradient
    // components into the same scalar field
    // of if you take several derivatives with respect to the different variables
    // in all the different orders and they're all the same.



    return 0;
}


// int main()
// {
//     eulers_method_main();
// }





int newtons_method_main()
{

    // Newton's Method for solving an equation of one variable
    // ---------------------------------------

    // x1 = x0 - f(x0)/f'(x0)

    // This can solve any equation of the form f(x) = some_number.
    // You do need to give it a good initial x position, specially if it's a higher
    // order equation.

    // Simply 
    // 1. Put the equation into homogenous form f(x) = 0
    // 2. set the initial x value
    // 3. Run the algorithm for a certain number of iterations

    // The technique is to calculate the height and derivative at the current x value
    // and follow them down to the next x value at the x-axis.
    
    // The way that polynomials curve means that this technique should bring you 
    // closer and closer to one of the closest roots of the equation.


    // set x to some value, say 0.
    // x = x - ( f(x) / f'(x) )
    float x = 0;
    for (int i=0; i<10; ++i) {
        x = x - ( (x*x + 5*x -20) / (2*x + 5) );
    }
    printf("newton's method x: %f\n", x);
    
    return 0;
}



#include <stdio.h>
#include <unistd.h>

void demo_print_stuff_on_one_line()
{
    int i;
    printf("\n\n");
    printf("OMG Carriage Return without newline prints to one line omg\n");
    printf("-----------------------------------\n");
    for (i=0;i<100;++i) { fprintf(stdout, "\romg I'm printing stuff on one line [%d%%]", i ); fflush(stdout); usleep(1e4); } 
    printf("\n");
}






char *myprintf_convert(unsigned int num, int base)
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}


void myprintf(char* format,...)
{ 

    char *traverse; 
    int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while( *traverse != '%' ) 
        { 
            putchar(*traverse);
            traverse++; 
        } 

        traverse++; 

        //Module 2: Fetching and executing arguments
        switch(*traverse) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        putchar(i);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            putchar('-'); 
                        } 
                        puts(myprintf_convert(i,10));
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        puts(myprintf_convert(i,8));
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
                        puts(s); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        puts(myprintf_convert(i,16));
                        break; 
        }   
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 




#include <stdio.h>
// #include <ctype.h>
#include <stdlib.h>


void read_file (char *filename, char **ret_char_array, int *ret_char_length)
{
	// string
    char *char_array = (char*)malloc(1000);
	int chars_allocated = 1000;
	int char_length = 0;
	
    // open file for reading
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return;
	}

	while (1) {
		// read character
		int character = fgetc(f);
		// at the end of the file add a null byte to work with c-string functions
		if (feof(f)) { 
			char_array[char_length] = '\0'; 
			char_length += 1;
			break; 
		}
		char_array[char_length] = (char)character;
		char_length += 1;

        // maybe grow string
        if (char_length == chars_allocated){
            chars_allocated *= 2;
            char_array = (char*)realloc(char_array, chars_allocated);
            // printf("chars_allocated %d\n", chars_allocated);
        }

	}
	fclose(f);
	
    *ret_char_array = char_array;
    *ret_char_length = char_length;
}

static void print_char(unsigned char theChar)
{

    switch (theChar) {

        case '\n':
            printf("\\n");
            break;
        case '\r':
            printf("\\r");
            break;
        case '\t':
            printf("\\t");
            break;
        default:
            if ((theChar < 0x20) || (theChar > 0x7f)) {
                printf("\\%03o", (unsigned char)theChar);
            } else {
                printf("%c", theChar);
            }
        break;
   }
}


int read_file_main()
{
	// __FILE__ appears to be the filename of this file
	// putting two string immediately next to each other concatenates them in c
	// "./"__FILE__
	// or "alskjdf""alksjdflka" => "alskjdfalksjdflka"

    char *data = NULL; 
	int length = -1;
	char *filename = (char*)__FILE__; // the filename of this file

	printf("reading %s\n", filename);


    read_file( filename , &data, &length );

	// print slice
	int start = 0;
	int end   = 100;

	fputs("\n{", stdout);
	for (int i=start; i<end; ++i) print_char(data[i]);
	fputs("}", stdout);
	printf("\n");



	free(data);
    return 0;
}



/*
Use this if you can't print floats - in an embedded system for example.
*/

#include <stdio.h>
#include <math.h>

void sprint_float3(char* str, float arg)
{

  // sprint float to 3 decimal places
  // to change decimal places change 1000 and %03d
  // from https://stackoverflow.com/questions/905928/using-floats-with-sprintf-in-embedded-c

  char *sign;
  float val;
  int a;
  int b;

  // arg = 678.0123;

    if (arg<0) { sign=(char*)"-"; } else { sign=(char*)""; }
//   sign = (arg < 0) ? "-" : "";
  val = (arg < 0) ? -arg : arg;

  a = val;                  // Get the integer (678).
  b = trunc((val - a) * 1000);  // Get fraction then turn into integer (123).

  // Print as parts, note that you need 0-padding for fractional bit.

  if (b == 0){
    sprintf (str, "%s%d", sign, a);
  } else {
    sprintf (str, "%s%d.%03d", sign, a, b);  
  }
  // puts(str);

}


int sprint_float3_main()
{

  char str[100];

  sprint_float3(str, 0.01234);
  puts(str);
  sprint_float3(str, 3.1415926535);
  puts(str);
  sprint_float3(str, 3234);
  puts(str);

  return 0;
}




// Operating on the same data using different threads
//
// The intended behaviour of this program is to add 1 to a global variable 
// until it's 1000.  When several threads are used to achieve this there is
// unintended behaviour.  If two threads read the global at the same time
// then the final value of the global will be less than 1000.

// If this code is made mutually exclusive, i.e. it can only be run by 
// one thread at any given time, then this is fixed.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int thread_race_global = 0;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* add1_to_global(void* arg)
{
	// pthread_mutex_lock(&mutex);
	thread_race_global += 1; // read and then write back it+1 to the same location
	// pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

void thread_race_main()
{
    printf("\n\n");
	printf("1000 threads adding 1 to a global. Who will win the race?\n");

	for (int i = 0; i < 1e6; i++){
		
		printf("Race %d: ", i);

		thread_race_global = 0;
		// Launch threads
		pthread_t tids[1000];
		for (int i = 0; i < 1000; i++) {
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_create(&tids[i], &attr, add1_to_global, NULL);
		}

		// Wait for threads
		for (int i = 0; i < 1000; i++) {
			pthread_join(tids[i], NULL);
		}

		printf("Result is %d\n", thread_race_global);
		if (thread_race_global != 1000){ break; }
	}

}




// Unions Demo
// ---------------------


int unions_demo( )
{

    typedef enum shape_type_t { CIRCLE, RECTANGLE } shape_type_t;

    typedef struct shape_t { 
        shape_type_t type;
        union { double radius; double width; };
        double height;
    } shape_t;

    typedef struct rectangle_t { shape_type_t type; double width; double height; } rectangle_t;

    #define shapes_length 2
    shape_t shapes[shapes_length] = { 
        { .type = RECTANGLE, .width = 2, .height = 3 },
        { .type = CIRCLE, .radius = 3 }
    };

    for (size_t i = 0; i < shapes_length; i++)
    {
        double r,w,h;

        switch (shapes[i].type)
        {
        case CIRCLE:
            r = shapes[i].radius;
            printf("circle :). radius: %f, area: %f\n", r, 3.14159*r*r);
            break;
        case RECTANGLE:
            w = shapes[i].width; h = shapes[i].height;
            printf("rectangle :). width: %f, height: %f, area: %f\n", w, h, w*h);
            break;        
        default:
            break;
        }
    }
        

   return 0;
}


#include <iostream>
#include <vector>
#include <string>
 
int demo_cpp_vectors()
{
    using namespace std;

    // integers
	vector<int> integers;
    integers.push_back(1);
    integers.push_back(2);
    integers.push_back(4);
    integers.push_back(8);
    integers.push_back(16);
 
    integers.push_back(25);
    integers.push_back(13);
 
    cout << "integers" << endl;
    for(int i=0;i<integers.size();++i) { cout << integers[i] << '\n'; }

    cout << "\nStrings\n";
	vector<string> fruits;
    fruits.push_back("orange");
    fruits.push_back("apple");
    fruits.push_back("raspberry");

    for(int i=0;i<fruits.size();++i) { cout << fruits[i] << '\n'; }

    cout << "\ndemo for loop, count, other things like this\n";
    cout << "size " << fruits.size() << endl;


    return 0;
}




int split_string_demo()
{

    char string[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg everyone has an address\n";
    char *string_copy = (char*)malloc(sizeof(string));
    memcpy(string_copy, string, strlen(string));

    List list;
    list = split_string(string,",\n");

    printf("\n\n");
    printf("split_string_demo\n");
    printf("-----------------------\n");

    printf("{%s}\n", string_copy);
    for(int i=0;i<list.length;i+=1) printf("{%s}, ", (char*)list.data[i]);
    printf("\n\n");

    return 0;
}




// https://www.reddit.com/r/Cprog/comments/kaapdr/prints_itself/
int print_this_file()
{
    FILE *file = fopen(__FILE__, "r");
    for (;;) {
        while (!feof(file)) {
            usleep(10*1000);
            fputc(fgetc(file), stderr);
        }
        rewind(file);
    }
}




// C89 allows two types of compilers: hosted and freestanding. The basic difference is that a 
// hosted compiler provides all of the C89 library, while a freestanding compiler need only 
// provide <float.h>, <limits.h>, <stdarg.h>, and <stddef.h>. If you limit yourself to these headers, 
// your code will be portable to any C89 compiler.


#include <stdio.h>
#include <float.h>

void float_header_demo ()
{
    // https://www.tutorialspoint.com/c_standard_library/float_h.htm
    
    printf("\n\n");
    printf("float.h demo\n");
    printf("-----------------------\n");

   printf("The maximum value of float = %.23e\n", FLT_MAX);
   printf("The minimum value of float = %.10e\n", FLT_MIN);
   printf("The number of digits in the number = %d\n", FLT_MANT_DIG);

   printf("The maximum value of double = %.10e\n", DBL_MAX);
   printf("The minimum value of double = %.10e\n", DBL_MIN);
   printf("The number of digits in the number = %d\n", DBL_MANT_DIG);

}


#include<limits.h>
#include<stdio.h>

int limits_header_demo()
{

    printf("\n\n");
    printf("limits.h demo\n");
    printf("-----------------------\n");


   printf("The number of bits in a byte %d\n", CHAR_BIT);

   printf("The minimum value of SIGNED CHAR = %d\n", SCHAR_MIN);
   printf("The maximum value of SIGNED CHAR = %d\n", SCHAR_MAX);
   printf("The maximum value of UNSIGNED CHAR = %d\n", UCHAR_MAX);

   printf("The minimum value of SHORT INT = %d\n", SHRT_MIN);
   printf("The maximum value of SHORT INT = %d\n", SHRT_MAX); 

   printf("The minimum value of INT = %d\n", INT_MIN);
   printf("The maximum value of INT = %d\n", INT_MAX);

   printf("The minimum value of CHAR = %d\n", CHAR_MIN);
   printf("The maximum value of CHAR = %d\n", CHAR_MAX);

   printf("The minimum value of LONG = %ld\n", LONG_MIN);
   printf("The maximum value of LONG = %ld\n", LONG_MAX);
  
   return(0);
}


#include<stdarg.h>
#include<stdio.h>


int sum(int num_args, ...)
{
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
      val += va_arg(ap, int);
   }
   va_end(ap);
 
   return val;
}


void stdarg_header_demo()
{

    printf("\n\n");
    printf("stdarg.h demo\n");
    printf("-----------------------\n");

   printf("Sum of 10, 20 and 30 = %d\n",  sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  sum(4, 4, 20, 25, 30) );

}



#include <stddef.h>
#include <stdio.h>

// Offsetof 
// -----------------------------------
// offsetof returns the address of a field relative to the start address of a struct.
// offsetof(struct, name)

void stddef_header_demo ()
{

    struct address {
        char name[50];
        char street[50];
        int phone;
    };
    

    printf("name offset = %lu byte in address structure.\n", offsetof(struct address, name));

    printf("street offset = %lu byte in address structure.\n", offsetof(struct address, street));

    printf("phone offset = %lu byte in address structure.\n", offsetof(struct address, phone));

} 



#include <stdio.h>

void demo_2d_arrays(void)
{
    printf("\n\n");
    printf("2D array demo\n");
    printf("-----------------------\n");


    int row, col;

    int a[2][5] = {      // Initialize a 2D array
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8, 9}
    };

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            printf("(%d,%d) = %d\n", row, col, a[row][col]);
        }
    }
}



// 1	void *memchr(const void *str, int c, size_t n)
// Searches for the first occurrence of the character c (an unsigned char) 
// in the first n bytes of the string pointed to, by the argument str.

// 2	int memcmp(const void *str1, const void *str2, size_t n)
// Compares the first n bytes of str1 and str2.

// 3	void *memcpy(void *dest, const void *src, size_t n)
// Copies n characters from src to dest.

// 4	void *memmove(void *dest, const void *src, size_t n)
// Another function to copy n characters from str2 to str1.

// 5	void *memset(void *str, int c, size_t n)
// Copies the character c (an unsigned char) to the first n characters 
// of the string pointed to, by the argument str.




int main()
{
    caesar_cipher_main();
    demo_strtok();
    demo_variadic_sum();
    eulers_method_main();
    newtons_method_main();
    // demo_print_stuff_on_one_line();
    read_file_main();
    sprint_float3_main();
    thread_race_main();
    demo_cpp_vectors();
    split_string_demo();
    unions_demo();
    // print_this_file();

    float_header_demo();  // print float limits
    limits_header_demo(); // print integral limits
    stdarg_header_demo(); // va_arg
    stddef_header_demo(); // offsetof

    demo_2d_arrays();


    return 0;
}



