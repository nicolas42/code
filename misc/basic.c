// #include "basic.h"

#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>
#include <time.h>

double get_time(void);

typedef struct string_t {
	size_t length;
	size_t allocated;
	char* data;
} string_t;

string_t make_string(size_t n);
void free_string(string_t f);
void maybe_grow_string(string_t* f);
string_t copy_string(string_t a);

string_t read_file(char *filename);

typedef struct strings_t {
	size_t length;
	size_t allocated;
	char** data;
	string_t string;
} strings_t;

strings_t make_strings(size_t length);
void free_strings(strings_t f);
void maybe_grow_strings(strings_t* f);
void strings_add(strings_t* f, char* a);

strings_t split_string(char* a, char* split_chars);
void demo_split(void);
double min(double a, double b);
int split_main(int argc, char** argv);

#endif




double get_time(void)
{
	return clock()/(double)CLOCKS_PER_SEC;
}

string_t make_string(size_t n)
{
	string_t f;
	f.length = 0;
	f.allocated = n;
	f.data = (char*)malloc(n);
	return f;
}

string_t copy_string(string_t a)
{
	string_t b;
	b.length = a.length;
	b.allocated = a.allocated;
	b.data = (char*)malloc(b.allocated*sizeof(char*));
	strcpy(b.data, a.data);
	return b;
}

void free_string(string_t f)
{
	free(f.data);
}

void maybe_grow_string(string_t* f)
{
	if (f->length == f->allocated){
		f->allocated *= 2;
		f->data = (char*)realloc(f->data, f->allocated);
	}
}

string_t read_file(char *filename)
{
	string_t s = make_string(10000); // 10 kilobytes

	FILE *f;
	int c;

	f = fopen(filename, "r");
	if (f == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return s;
	}

	while (1) {
		c = fgetc(f);
		if (feof(f)) { 
			s.data[s.length] = '\0';
			s.length += 1;
			break; 
		}
		s.data[s.length] = (char)c;
		s.length += 1;
		maybe_grow_string(&s);
	}
	fclose(f);

	return s;
}





strings_t make_strings(size_t n)
{
	strings_t f;
	f.length = 0;
	f.allocated = n;
	f.data = (char**)malloc(n*sizeof(char**));
	return f;
}

void free_strings(strings_t f)
{
	free(f.data);
}

void maybe_grow_strings(strings_t* f)
{
	if (f->length == f->allocated){
		f->allocated *= 2;
		f->data = (char**)realloc(f->data, f->allocated*sizeof(char**));
		// printf("GROW!!!\n");
	}
}

void strings_add(strings_t* f, char* a)
{
	maybe_grow_strings(f);
	f->data[f->length] = a;
	f->length += 1;
}


double min(double a, double b)
{
	if (a < b ){
		return a;
	}
	return b;
}

// split a string_t by replacing characters (split_chars)
strings_t split_string(char* a, char* split_chars)
{
	strings_t lines = make_strings(10);

	strings_add(&lines, &(a[0]));

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
			strings_add(&lines, &(a[i]));
		}
	}

	return lines;
}


void demo_split(void)
{
	string_t f = read_file("basic.h");
	strings_t tokens = split_string(f.data, "\n\r\t ");

	for (size_t i = 0; i < min(10, tokens.length); i++){
		printf("{%s} ", tokens.data[i]);
	}
}

int split_main(int argc, char** argv)
{
	// ./a.out split "Halsdkjf asldfk jasfdkl askjfd kalsfkj" "\n"

	if (argc != 4){
		printf("usage: ./a.out split string_t-to-split chars-to-split-on\n");
		return -1;
	}

	char* data = argv[2];
	char* split_chars = argv[3];
	strings_t tokens = split_string(data, split_chars);

	for (size_t i = 0; i < min(10, tokens.length); i++){
		printf("%s\n", tokens.data[i]);
	}
	return 0;
}

strings_t read_lines(char *filename)
{
	string_t f = read_file(filename);
	strings_t lines = split_string(f.data, "\n\r");

	return lines;
}

int main(int argc, char **argv)
{
	strings_t lines = read_lines("basic.c");
	for (size_t i = 0; i < min(20, lines.length); i++){
		printf("{%s}\n", lines.data[i]);
	}
	return 0;
}

