#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Parse words by noting down the starting positions of words 
// and changing spaces to null characters

int tokenize(int* offsets, int* length_offsets_ptr, char* a, int(*fn)(int)){

	int la = strlen(a);
	int length_offsets = *length_offsets_ptr;

	for (int i = 0; i < la - 1; i++){
		if (i == 0 && !fn(a[i]))
		{
			offsets[length_offsets++] = i;
		}
		else if (fn(a[i]) && !fn(a[i+1])) 
		{
			offsets[length_offsets++] = i+1;
		}
	}

	/* Convert spaces to null */
	for (int i = 0; i < la; i++){
		if (fn(a[i])){
			a[i] = '\0';
		}
	}

	*length_offsets_ptr = length_offsets;

	return 0;
}

int isnewline(int a){
	return (a == '\n' || a == '\r');
}

// int main()
// {

// 	int max_size = 1000000; /* 1mb */
// 	char a[max_size];
	
// 	FILE *fp;
// 	fp = fopen("main.c", "r");
//     fread(a, max_size, 1, fp);
// 	fclose(fp);

// 	// char ca[max_size];
// 	// strcpy(ca, a);

// 	// // ======TOKENIZE +=========

// 	int t[1000];
// 	int lt = 0;

// 	tokenize(t, &lt, a, isspace);

// 	for (int i = 0; i < lt; i++){
// 		printf("[%s]\n", a + t[i]);
// 	}
// 	puts("\n");

// 	// printf("%s", ca);

// 	return 0;
// }
