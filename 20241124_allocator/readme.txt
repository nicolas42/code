# literals

123      // Decimal integer
0123     // Octal integer (83 in decimal)
0x123    // Hexadecimal integer
0b101    // Binary integer (GCC-specific extension)

123U     // Unsigned integer
123L     // Long integer
123UL    // Unsigned long integer
123LL    // Long long integer
123ULL   // Unsigned long long integer



# static for globals

stops external linking of globals

When used at the global level (outside functions), static limits the visibility of the variable or function to the file in which it is declared. This is called internal linkage.

Without static, global variables and functions have external linkage, meaning they can be accessed from other files if declared using extern.


# Pointer arithmetic

In c you can just add an integer to a pointer and it'll return a pointer
