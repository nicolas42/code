
#include "read_file.h"

int main(int argc, char **argv)
{
    char *data = NULL; 
	int data_length = -1;
    read_file( "read_file.h", &data, &data_length );
    printf("%s", data);
    printf("%d\n", data_length);
	free(data);
	
    return 0;
}
