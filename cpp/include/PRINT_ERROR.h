#ifndef PRINT_ERROR_HEADER_GUARD
#define PRINT_ERROR_HEADER_GUARD


#define PRINT_ERROR(msg) fprintf( stderr, "ERROR %s:%d %s\n", __FILE__, __LINE__, msg );

#define PRINT_ERROR_EXIT(msg) { fprintf( stderr, "ERROR %s:%d %s\n", __FILE__, __LINE__, msg ); exit(1); } 



// #include <stdio.h>
// #include <stdlib.h>

// int main()
// {
//     int a = 0;
//     if (!a) PRINT_ERROR("omg!\n");

//     int b = 23;
//     if (b == 23) PRINT_ERROR_EXIT("omg you!\n")

//     PRINT_ERROR("You shouldn't see this\n");

//     return 0;
// }


#endif // PRINT_ERROR_HEADER_GUARD
