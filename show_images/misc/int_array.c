
#include <stdio.h>
#include <stdlib.h>

typedef struct int_array {
	size_t length;
	size_t allocated;
	int* data;
} int_array;

int_array make_int_array();
void free_int_array(int_array f);

int_array make_int_array()
{
	int_array f;
	f.length = 0;
	f.allocated = 10;
	f.data = (int*)malloc(10);
	return f;
}

void free_int_array(int_array f)
{
	free(f.data);
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

// struct slice {
// 	int start;
// 	int end;
// };

int_array get_offsets_of_string(string a, char separator)
{
	int_array output = make_int_array();

	int_array_add(output, 0);
	for (int i=0; i<a.length; i+=1){
		if (a.data[i] == separator) {
			int_array_add(output, i);
		}
	}
	int_array_add(output, a.length-1);

	return output;
}

int mystring_main(int argc, char **argv)
{
	string s = read_file("show_images.cpp");
	printf("%s", s.data);

	int_array offsets = get_offsets_of_string(s, '\n');

	for (int i=0; i<offsets.length; i+=1) printf("%d ", offsets.data[i]);

	return 0;
}
