#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double* data;
	int length;
	int capacity;
	int index;
} ARRAY;

ARRAY* array_init(ARRAY* a){
	a->length = 0;
	a->capacity = 2;
	a->data = malloc(a->capacity * sizeof(double));
	return a;
}

ARRAY* array_add(ARRAY* a, double b){
	
	// reallocate if full
	if (a->length == a->capacity){
		a->capacity = 2 * a->capacity;
		a->data = realloc(a->data, a->capacity * sizeof(double));
		puts("Realloc! ");
	}
	a->data[a->length] = b;
	a->length++;
	return a;
}

ARRAY* array_clear(ARRAY* a){
	for (int i = 0; i < a->length; i++){
		a->data[i] = 0;
		/* Zero is represented with an exponent field of zero and a mantissa field of zero. Depending on the sign bit, it can be a positive zero or a negative zero. Thus, -0 and +0 are distinct values, though they are treated as equal. (https://blogs.msdn.microsoft.com/premk/2006/02/25/ieee-754-floating-point-special-values-and-ranges/)*/
	}
	a->length = 0;
	return a;
}

ARRAY* array_print(ARRAY* a){
	for (int i = 0; i < a->length; i++){
		printf("%.3f ", a->data[i]);
	}
	return a;
}

ARRAY* array_printf(ARRAY* a, char* format){
	for (int i = 0; i < a->length; i++){
		printf(format, a->data[i]);
	}
	return a;
}

// int main(int argc, char** argv){

// 	ARRAY a;
// 	array_init(&a);

// 	for (int i = 0; i < 10; i++) { array_add(&a, (char)48+i); }
// 	puts("\r\n\r\nChars");
// 	for (int i = 0; i < 10; i++) { printf("%c", (char)a.data[i]); }
// 	array_clear(&a);

// 	for (int i = 0; i < 10; i++) { array_add(&a, (double)(1.0/i)); }
// 	puts("\r\n\r\nFloats");
// 	for (int i = 0; i < 10; i++) { printf("%f ", (double)a.data[i]); }
// 	array_clear(&a);

// 	for (int i = 0; i < 10; i++) { array_add(&a, (int)987*i); }
// 	puts("\r\n\r\nInts");
// 	for (int i = 0; i < 10; i++) { printf("%d ", (int)a.data[i]); }
// 	array_clear(&a);

// 	for (int i = 0; i < 10; i++) { array_add(&a, (int8_t)1000*i); }
// 	puts("\r\n\r\nLittle Ints :)");
// 	for (int i = 0; i < 10; i++) { printf("%d ", (int8_t)a.data[i]); }
// 	array_clear(&a);


// 	return 0;
// }
