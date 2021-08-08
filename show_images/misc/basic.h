#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>
#include <time.h>

namespace basic {

// Parse words by noting down the starting positions of words 
// and changing spaces to null characters

double get_time(void);

typedef struct string {
	size_t length;
	size_t allocated;
	char* data;
} string;

string make_string(size_t n);
void free_string(string f);
void maybe_grow_string(string* f);
string copy_string(string a);

string read_file(char *filename);

typedef struct strings {
	size_t length;
	size_t allocated;
	char** data;
} strings;

strings init_string_array(void);
strings make_string_array(size_t length);
void free_string_array(strings f);
void maybe_grow_string_array(strings* f);
void string_array_add(strings* f, char* a);

// strings string_split_destructive(char* a char* split_chars);
strings string_split_destructive(char* a, char* split_chars);
void demo_split_destructive(void);
double min(double a, double b);
int split_main(int argc, char** argv);


double get_time(void)
{
	return clock()/(double)CLOCKS_PER_SEC;
}

string make_string(size_t n)
{
	string f;
	f.length = 0;
	f.allocated = n;
	f.data = (char*)malloc(n);
	return f;
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

void free_string(string f)
{
	free(f.data);
}

void maybe_grow_string(string* f)
{
	if (f->length == f->allocated){
		f->allocated *= 2;
		f->data = (char*)realloc(f->data, f->allocated);
	}
}

string read_file (char *filename)
{
	string f = make_string(1000);

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
		maybe_grow_string(&f);
	}
	fclose(fp);

	return f;
}

strings init_string_array(void)
{
	strings f;
	f.length = 0;
	f.allocated = 1000;
	f.data = (char**)malloc(1000*sizeof(char**));
	return f;
}

strings make_string_array(size_t n)
{
	strings f;
	f.length = 0;
	f.allocated = n;
	f.data = (char**)malloc(n*sizeof(char**));
	return f;
}

void free_string_array(strings f)
{
	free(f.data);
}

void maybe_grow_string_array(strings* f)
{
	if (f->length == f->allocated){
		f->allocated *= 2;
		f->data = (char**)realloc(f->data, f->allocated*sizeof(char**));
		printf("GROW!!!\n");
	}
}

void string_array_add(strings* f, char* a)
{
	maybe_grow_string_array(f);
	f->data[f->length] = a;
	f->length += 1;
}

// strings split_lines_destructive(char* a)
// {
// 	strings lines = make_string_array(10000);

// 	string_array_add(&lines, &(a[0]));

// 	size_t strlen_a = strlen(a);
// 	printf("strlen(a) %lu\n", strlen(a));

// 	for (size_t i = 1; i < strlen_a; i++){

// 		if ( a[i] == '\n' || a[i] == '\r' ) {
// 			a[i] = '\0';		
// 		}
// 	}

// 	for (size_t i = 1; i < strlen_a; i++) {

// 		if (a[i-1] == '\0' && a[i] != '\0') {
// 			string_array_add(&lines, &(a[i]));
// 		}
// 	}

// 	return lines;
// }


double min(double a, double b)
{
	if (a < b ){
		return a;
	}
	return b;
}

strings string_split_destructive(char* a, char* split_chars)
{
	strings lines = make_string_array(10000);

	string_array_add(&lines, &(a[0]));

	size_t strlen_a = strlen(a);
	// printf("strlen(a) %lu\n", strlen(a));

	for (size_t i = 1; i < strlen_a; i++){

		for (size_t j = 0; j < strlen(split_chars); j++)
		{
			if ( a[i] == split_chars[j] ){ a[i] = '\0'; break; }
		}
	}

	for (size_t i = 1; i < strlen_a; i++) {

		if (a[i-1] == '\0' && a[i] != '\0') {
			string_array_add(&lines, &(a[i]));
		}
	}

	return lines;
}


void demo_split_destructive(void)
{
	string f = read_file("basic.h");
	strings tokens = string_split_destructive(f.data, "\n\r\t ");

	for (size_t i = 0; i < min(10, tokens.length); i++){
		printf("{%s} ", tokens.data[i]);
	}
}

int split_main(int argc, char** argv)
{
	// ./a.out split "Halsdkjf asldfk jasfdkl askjfd kalsfkj" "\n"

	if (argc != 4){
		printf("usage: ./a.out split string-to-split chars-to-split-on\n");
		return -1;
	}

	char* data = argv[2];
	char* split_chars = argv[3];
	strings tokens = string_split_destructive(data, split_chars);

	for (size_t i = 0; i < min(10, tokens.length); i++){
		printf("%s\n", tokens.data[i]);
	}
	return 0;
}

// typedef struct slice { int offset ; int length; } slice;

// typedef struct slices {
// 	size_t length;
// 	size_t allocated;
// 	slice* data;
// } slices;

}

#endif