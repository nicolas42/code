#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Parse words by noting down the starting positions of words 
// and changing spaces to null characters

int tokenize(int* offsets, int* length_offsets_ptr, char* a, int(*fn)(int));
int isnewline(int a);

#endif
