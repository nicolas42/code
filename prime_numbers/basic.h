#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>
#include <time.h>


typedef struct string {
	size_t length;
	size_t allocated;
	char* data;
} string;

typedef struct string_array {
	size_t length;
	size_t allocated;
	char** data;
} string_array;

int file_exists(const char * filename);
double get_time_elapsed(void);
string read_file(char *filename);
string copy_string(string a);
void string_array_add(string_array* f, char* a);
string_array split_string(char* a, char* characters_to_split_on);


double get_time_elapsed(void)
{
	return clock()/(double)CLOCKS_PER_SEC;
}

string copy_string(string a)
{
	string b;
	b.length = a.length;
	b.allocated = a.allocated;
	b.data = (char*)malloc(b.allocated*sizeof(char*));
	strcpy(b.data, a.data);
	return b;
}


int file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    file = fopen(filename, "r");
    if (file){
        fclose(file);
        return 1;
    }
    return 0;
}

string read_file (char *filename)
{
	string f;
	f.length = 0;
	f.allocated = 1000;
	f.data = (char*)malloc(1000);

	FILE *fp;
	int c;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return f;
	}

	while (1) {
		c = fgetc(fp);
		if (feof(fp)) { 
			f.data[f.length] = '\0';
			f.length += 1;
			break; 
		}
		f.data[f.length] = (char)c;
		f.length += 1;
		
		if (f.length == f.allocated){
			f.allocated *= 2;
			f.data = (char*)realloc(f.data, f.allocated);
		}
	}
	fclose(fp);

	return f;
}



void string_array_add(string_array* s, char* string_to_add)
{
	if (s->length == s->allocated){
		s->allocated *= 2;
		s->data = (char**)realloc(s->data, s->allocated*sizeof(char**));
		printf("GROW!!!\n");
	}
	s->data[s->length] = string_to_add;
	s->length += 1;
}

string_array split_string(char* s, char* split_chars)
{
	// this modifies the original string
	// first it changes all of the split characters to null
	// then it notes down all positions where there's a null non-null pattern
	// (as well as the first position if it's not null)

	string_array sa;
	sa.length = 0;
	sa.allocated = 100;
	sa.data = (char**)malloc(100*sizeof(char**));

	size_t strlen_a = strlen(s); 
	for (size_t i = 1; i < strlen_a; i++){

		for (size_t j = 0; j < strlen(split_chars); j++)
		{
			if ( s[i] == split_chars[j] ){ 
				s[i] = '\0'; 
				break; 
			}
		}
	}

	if (s[0] != '\0') {
		string_array_add(&sa, &(s[0]));
	}
	for (size_t i = 1; i < strlen_a; i++) {
		if (s[i-1] == '\0' && s[i] != '\0') {
			string_array_add(&sa, &(s[i]));
		}
	}

	return sa;
}






// double min(double a, double b)
// {
// 	if (a < b ){
// 		return a;
// 	}
// 	return b;
// }

// void demo_split_destructive(void)
// {
// 	string f = read_file("basic.h");
// 	string_array tokens = split_string(f.data, "\n\r\t ");

// 	for (size_t i = 0; i < min(10, tokens.length); i++){
// 		printf("{%s} ", tokens.data[i]);
// 	}
// }

// int split_main(int argc, char** argv)
// {
// 	// ./a.out split "Halsdkjf asldfk jasfdkl askjfd kalsfkj" "\n"

// 	if (argc != 4){
// 		printf("usage: ./a.out split string-to-split chars-to-split-on\n");
// 		return -1;
// 	}

// 	char* data = argv[2];
// 	char* characters_to_split_on = argv[3];
// 	string_array tokens = split_string(data, characters_to_split_on);

// 	for (size_t i = 0; i < min(10, tokens.length); i++){
// 		printf("%s\n", tokens.data[i]);
// 	}
// 	return 0;
// }

