#include <stdio.h>

// Functions to be pointed to
void add(int a, int b) {
    printf("Sum: %d\n", a + b);
}

void subtract(int a, int b) {
    printf("Difference: %d\n", a - b);
}

// Function pointer declaration
void (*operation)(int, int);

int main() {
    // Assign function pointers to the functions
    operation = add;
    printf("Calling add via function pointer:\n");
    operation(5, 3);

    operation = subtract;
    printf("Calling subtract via function pointer:\n");
    operation(5, 3);

    return 0;
}
