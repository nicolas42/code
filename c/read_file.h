#include <stdio.h>
// #include <ctype.h>
#include <stdlib.h>




void read_file (char *filename, char **ret_data, int *ret_length)
{
	// string
    char *data = (char*)malloc(1000);
	int allocated = 1000;
	int length = 0;
	
    // open file for reading
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		char err[200];
		snprintf(err, 200, "Error in opening file %s", filename);
		perror(err);
		return;
	}

	while (1) {
        int character;

		character = fgetc(f);
		if (feof(f)) { 
			data[length] = '\0'; // null byte
			length += 1;
			break; 
		}
		data[length] = (char)character;
		length += 1;

        // maybe grow string
        if (length == allocated){
            allocated *= 2;
            data = (char*)realloc(data, allocated);
            printf("ALLOCATED %d\n", allocated);
        }

	}
	fclose(f);
    *ret_data = data;
    *ret_length = length;
}

int demo_read_file(int argc, char **argv)
{
    char *data = NULL; 
	int data_length = -1;
    read_file( "read_file.h", &data, &data_length );
    printf("%s", data);
    printf("%d\n", data_length);
	free(data);
	
    return 0;
}
