#include <stdio.h>
#include <string.h>
// #include <ctype.h>
#include <stdlib.h>


typedef struct string {
	size_t length;
	size_t allocated;
	char* data;
} string;

string make_string();
void free_string(string f);
string copy_string(string a);

string read_file(char *filename);

string make_string()
{
	string f;
	f.length = 0;
	f.allocated = 10;
	f.data = (char*)malloc(10);
	return f;
}

void free_string(string f)
{
	free(f.data);
}


string copy_string(string a)
{
	string b;
	b.length = a.length;
	b.allocated = a.allocated;
	b.data = (char*)malloc(b.allocated*sizeof(char));
	strcpy(b.data, a.data);
	return b;
}



string read_file (char *filename)
{
	string f = make_string();

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

		// maybe grow
        if (f.length == f.allocated){
            f.allocated *= 2;
            f.data = (char*)realloc(f.data, f.allocated*sizeof(char));
        }

	}
	fclose(fp);

	return f;
}










typedef struct int_array {
	size_t length;
	size_t allocated;
	int* data;
} int_array;

int_array make_int_array();
void free_int_array(int_array f);

int_array make_int_array()
{
	int_array a;
	a.length = 0;
	a.allocated = 10;
	a.data = (int*)malloc(a.allocated * sizeof(int));
	return a;
}

void free_int_array(int_array a)
{
	free(a.data);
}

int_array int_array_add (int_array a, int b)
{
	a.data[a.length] = b;
	a.length += 1;

	// maybe grow
	if (a.length == a.allocated){
		a.allocated *= 2;
		a.data = (int*)realloc(a.data, a.allocated*sizeof(int));
	}
	return a;
}


int_array get_offsets_of_string(string a, char separator)
{
	int_array o = make_int_array();

	o = int_array_add(o, 0);
	for (int i=0; i<a.length; i+=1){
		if (a.data[i] == separator) {
			o = int_array_add(o, i);
		}
	}
	o = int_array_add(o, a.length-1);

	return o;
}



int_array get_offsets_of_string(string a, char separator)
{
	int_array o = make_int_array();

	o = int_array_add(o, 0);
	for (int i=0; i<a.length; i+=1){
		if (a.data[i] == separator) {
			o = int_array_add(o, i);
		}
	}
	o = int_array_add(o, a.length-1);

	return o;
}



int main(int argc, char **argv)
{
	string s = read_file("show_images.cpp");
	// printf("%s", s.data);





	int_array offsets = get_offsets_of_string(s, '\n');

	for (int i=0; i<offsets.length; i+=1) printf("%d ", offsets.data[i]);


	for (int i=0; i<offsets.length; i+=2) {
		putchar('{');
		for (int j=offsets.data[i+0]; j<offsets.data[i+1]; j+=1) {
			putchar(s.data[j]);
		}
		putchar('}');
	}
	// int_array a = make_int_array();
	// for (int i=0; i<100; i+=1) a = int_array_add(a,i);
	// for (int i=0; i<a.length; i+=1) printf("%d ", a.data[i]);






	return 0;
}
