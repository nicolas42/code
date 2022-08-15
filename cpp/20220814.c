// gcc 20220814.c -Weverything -Wno-missing-prototypes -Wno-strict-prototypes -Wno-unused-parameter && ./a.out


// libc
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// small types
typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;

// fprintf( stderr, "ERROR %s %d %s\n", __FILE__, __LINE__, msg );



int read_whole_file ( const char *filename, char **ret_str, size_t *ret_length);
void read_whole_file_demo();
int parse_csv(char *str, int w, int h, char*** table_arg);
int main();

// extra crap
int parse_into_slices_non_destructive();
int main3();
int main2(int argc, char **argv);



// extern int errno;

// return 0 if it's okay or a non-zero integer if there's an error
int read_whole_file ( const char *filename, char **ret_str, size_t *ret_length)
{	
	FILE *file = fopen(filename, "r");
    if (!file) { 
        printf( "ERROR %s:%d %s\n", __FILE__,__LINE__, strerror(errno) ); 
        fclose(file); // closing this before accessing errno causes an error.
        *ret_length = 0;
        return 1;
    }

	size_t allocated = 1000;
	size_t length = 0;
    char *str = (char*)malloc(allocated);

	while (1) {
		int character = fgetc(file);
		if (feof(file)) { 
			str[length++] = '\0'; 
			break; 
		}
        if (length == allocated){
            allocated *= 2;
            str = (char*)realloc(str, allocated);
        }
		str[length++] = (char)character;

	}
	fclose(file);
	
    *ret_str = str;
    *ret_length = length;
    return 0;
}



void read_whole_file_demo()
{
    printf("\n\n");
    printf("read_whole_file_demo\n");
    printf("-----------------------\n");

    const char *filename = __FILE__;
    char *str;
    size_t len = 0;
    int err = read_whole_file(filename, &str, &len);
    if (err) exit(1);

    printf("{");
    for(int i=0;i<100;i+=1) putc( str[i], stdout );
    printf("...}\n");
}







// parse_into_c_strings
int parse_csv(char *str, int w, int h, char*** table_arg)
{
    char **table = *table_arg;

    int x = 0;
    int y = 0;
    assert(str[0] != '\0');

    table[y*w+x] = &(str[0]);

    int add_next = 0;
    for( int i=0; str[i] != '\0'; i+=1 ) {

        if (str[i]==',') { x+=1; add_next = 1; str[i] = '\0'; }
        else if (str[i]=='\n') { y+=1; x = 0; add_next = 1; str[i] = '\0'; }
        else if (add_next) {
            table[y*w+x] = &(str[i]);
            add_next = 0;
        }
    }

    return 0;
}


// int demo_parse_csv()
int main()
{

    char str[] = "\
nicolas schmidt,0459 986 668,some address\n\
single female lawyer,3325 7778,another address\n\
omgomgomg,0459654987,omg it's like everyone has an address\n\
omgomgomg,0459654987,omg it's like everyone has an address\n\
";

    // const char *filename = "20220814.csv";
    // char *str;
    // size_t len = 0;
    // int err = read_whole_file(filename, &str, &len);
    // if (err) exit(1);



    int w=3;
    int h=4;
    char** table = (char**)calloc( (u64)(w*h), sizeof(char*) );

    parse_csv(str, w, h, &table);

    int x,y;
    for(y=0;y<h;y++) { for(x=0;x<w;x++) { printf("%s, ", table[y*w+x]); } printf("\n"); }

}


















// parse into slices - non-destructive.
int parse_into_slices_non_destructive()
{
    struct slice {
        int low;
        int high;
    };

    // delimiters are , and \n

    const char str[208] = "nicolas schmidt, 0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\nomgomgomg,0459654987,omg it's like everyone has an address\n";

    int w=3;
    int h=4;
    struct slice* table = (struct slice*)calloc( (u64)(w*h), sizeof(int) );
    int x = 0;
    int y = 0;
    assert(str[0] != '\0');

    int low = 0;
    for( int i=0; str[i] != '\0'; i+=1 ) {
        if (str[i]==',') { 
            table[y*w+x].low = low; table[y*w+x].high = i; low = i+1; 
            x+=1; 
        } else if (str[i]=='\n') { 
            table[y*w+x].low = low; table[y*w+x].high = i; low = i+1; 
            y+=1; x=0; 
        }
    }


    for(y=0;y<h;y++) {
        for(x=0;x<w;x++) {
            printf("str[%d:%d] ", table[y*w+x].low, table[y*w+x].high);
            // print slice
            printf("{");
            for( int i=table[y*w+x].low; i<table[y*w+x].high; i++) printf("%c", str[i]); 
            printf("}");
            printf("\n"); 
        }
        printf("\n"); 
    }
    printf("\n");

   return 0;
}



// parse_into_c_strings
int main3()
{
    // delimiters are , and \n

    char str[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\nomgomgomg,0459654987,omg it's like everyone has an address\n";
    int w=3;
    int h=5;
    char** table = (char**)calloc( (u64)(w*h), sizeof(char*) );



    int x = 0;
    int y = 0;
    assert(str[0] != '\0');

    table[y*w+x] = &(str[0]);

    int add_next = 0;
    for( int i=0; str[i] != '\0'; i+=1 ) {

        if (str[i]==',') { x+=1; add_next = 1; str[i] = '\0'; }
        else if (str[i]=='\n') { y+=1; x = 0; add_next = 1; str[i] = '\0'; }
        else if (add_next) {
            table[y*w+x] = &(str[i]);
            add_next = 0;
        }
    }

    // for(int i=0;i<w*h;i++) printf("%s\n", table[i]);
    for(y=0;y<h;y++) { for(x=0;x<w;x++) { printf("%s, ", table[y*w+x]); } printf("\n"); }

   return 0;
}






#include <string.h>
#include <stdio.h>

int main1 () {
    char str[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\n";
    const char s[] = ",\n";
    char *token;
    char *tokens[1000];
    int tokens_count=0;

    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while( token != NULL ) {
        tokens[tokens_count++] = token;
        // printf( "%s\n", token );
        token = strtok(NULL, s);

    }

    for(int i=0;i<tokens_count;i++) printf("%s\n", tokens[i]);


    return 0;
}




// g++ 20220814.cpp -Wfatal-errors -Wall -Wpedantic -fPIC -Ofast && ./a.out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// #define PRINT_AND_EXIT(msg) { fprintf(stderr, "ERROR %s %d %s\n", __FILE__,__LINE__,msg); exit(1); }


// parse_into_c_strings
int main2(int argc, char **argv)
{
    // delimiters are , and \n

    char input_string[] = "nicolas schmidt,0459 986 668,some address\nsingle female lawyer,3325 7778,another address\nomgomgomg,0459654987,omg it's like everyone has an address\n";
    int input_string_length = (int)strlen(input_string);
    assert(input_string_length >= 2);

    // nullify delimiters
    for(int i=0; i<input_string_length; i+=1) if ( strchr(",\n", input_string[i]) ) { input_string[i] = '\0'; }

    // note down positions after delimiters
    char* output_strings[1000];
    int output_strings_length=0;

    // corner case: save the first position if it's not a null character.
    if ( input_string[0] != '\0' ) { output_strings[output_strings_length++] = &(input_string[0]); } 

    for(int i=1; i<input_string_length;i++){
        if ( input_string[i-1] == '\0' && input_string[i] != '\0' ) { output_strings[output_strings_length++] = &(input_string[i]); } 
    }


    printf("%d\n", output_strings_length);
    for(int i=0;i<output_strings_length;i++) printf("%s\n", output_strings[i]);

   return 0;
}
