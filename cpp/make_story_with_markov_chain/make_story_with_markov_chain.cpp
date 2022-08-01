
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


// DEFINE_ARRAY(type) macro
#define DEFINE_ARRAY(TYPENAME)\
\
typedef struct {\
  TYPENAME* data;\
  int length;\
  int allocated;\
} TYPENAME ## _array;\
\
TYPENAME ## _array TYPENAME ## _array_make()\
{\
    TYPENAME ## _array arr;\
    arr.length = 0;\
    arr.allocated = 16;\
    arr.data = (TYPENAME*)malloc( arr.allocated * sizeof(TYPENAME) );\
    return arr;\
}\
\
TYPENAME ## _array TYPENAME ## _array_add(TYPENAME ## _array arr, TYPENAME item)\
{\
    if ( arr.length == arr.allocated ) {\
      arr.allocated *= 2;\
      arr.data = (TYPENAME*)realloc( arr.data, arr.allocated * sizeof(TYPENAME) );\
    }\
    arr.data[arr.length] = item;\
    arr.length += 1;\
    return arr;\
}\



// struct string_array { string* data; int length; int allocated; }; typedef struct string_array string_array;
// string_array string_array_make(){ string_array arr; arr.length = 0; arr.allocated = 1000; arr.data = (string*)malloc( arr.allocated * sizeof(string) ); return arr;}
// void string_array_add(string_array *arr, string item){ if ( arr->length == arr->allocated ) { arr->allocated *= 2; arr->data = (string*)realloc( arr->data, arr->allocated * sizeof(string) ); } arr->data[arr->length] = item; arr->length += 1;};


typedef char* string;
DEFINE_ARRAY(string);

// destructively split a string by converting delimiters into null bytes
// and noting down the positions after them.
string_array split_string(char *str, const char *delim)
{
    size_t string_length = strlen(str);

    // convert delimiters to null bytes
    for (int i = 0; i < string_length; i++ ) {
        for ( int j = 0; delim[j] != '\0'; j += 1 ) {
            if (str[i]==delim[j]) { 
                str[i] = '\0'; 
                break; 
            }
        }
    }

    string_array l = string_array_make();

    // add pointer to first element if it's not null
    if ( str[0] != '\0' ) l = string_array_add(l, str);
    for ( int i = 1; i < string_length; i++ ) {
        // add locations which are directly after null bytes
        if ( str[i-1] == '\0' && str[i] != '\0' ) l = string_array_add(l, str+i);
    }
    return l;
}

void print_char( char the_char)
{

    switch (the_char) {

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
            if ((the_char < 0x20) || (the_char > 0x7f)) {
                printf("\\%03o", (unsigned char)the_char);
            } else {
                printf("%c", the_char);
            }
        break;
   }
}


int main()
{
    char filename[] = "2701-0.txt";
    FILE *file = fopen(filename, "r");
    char *str;
    int str_length;
    if (file){
        fseek(file, 0, SEEK_END); // seek to end of file
        str_length = ftell(file);   // get current file pointer
        fseek(file, 0, SEEK_SET); // seek back to beginning of file
        str = (char*)malloc(str_length * sizeof(char));
        fread(str, str_length, 1, file);
        fclose(file);
        str[str_length] = 0;
    }

    // for(int i=0; i<str_length; i++) printf("%c", str[i]);


    string_array lines = split_string(str," \r\t\n.,:;");
    for(uint32_t i=0;i<lines.length; i++) {
        printf("{");
        for(int j=0; lines.data[i][j] != 0;j++) print_char(lines.data[i][j]);
        printf("}\n");
    }
    
    // std::map<char, SDL_Texture*>
    
    // int words_allocated = 1000;
    // char **words = (char**)malloc(words_allocated*sizeof(char*));
    // int words_length = 0;

    // // strtok uses a static for the string after it's initialized
    // char delim[] = " \t\n,";
    // for (char *p = strtok(str,delim); p != NULL; p = strtok(NULL,delim)){
    //     // printf("{ %s}\n", p);
    //     if ( words_length == words_allocated ) {
    //         words_allocated *= 2;
    //         words = (char**)malloc( words_allocated *sizeof(char*));
    //     }
    //     words[words_length++] = p;

    // }

    // for (int i=0; i<words_length; i+=1) printf("{ %s}\n", words[i]);

    // int position = 24158; // position = random.randint(0, len(data)-3) # 24158 

    // output.append(data[position])
    // output.append(data[position+1])

    // for j in range(100):
    //     # print(j)
    //     locations_of_matches = []
    //     for i,_ in enumerate(data):
    //         if data[i].lower() == output[-2].lower() and data[i+1].lower() == output[-1].lower():
    //             # print(i)
    //             locations_of_matches.append(i)

    //     # print(locations_of_matches)        
    //     # for l in locations_of_matches:
    //     #     print(data[l], data[l+1], data[l+2])
    //     random_match_location = random.choice(locations_of_matches)
    //     new_word = data[random_match_location+2]
    //     output.append(new_word)
    //     print(new_word, end=' ', flush=True)

    // print()
    // # joined_result = ' '.join(output)
    // # print(joined_result)

    return 0;
}
