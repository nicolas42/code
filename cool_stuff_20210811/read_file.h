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



// /* 
// https://www.reddit.com/r/Cprog/comments/kaapdr/prints_itself/
// */
// #include <stdio.h>
// #include <unistd.h>
// #include <stdint.h>

// namespace misc {

// int prints_itself(void)
// {
//     FILE *file = fopen("./"__FILE__, "r");
//     uint16_t tick = UINT16_MAX;

//     for (;;) {
//         while (!feof(file)) {
//             usleep(tick -= ftell(file));
//             fputc(fgetc(file), stderr);
//         }
//         rewind(file);
//     }
// }

// }

static void print_char(unsigned char theChar) {

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
	char *filename = __FILE__; // the filename of this file

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
