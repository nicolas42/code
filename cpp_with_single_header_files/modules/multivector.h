#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H
/*
clang -Weverything multivector.h ; ./a.out

implements the multivector functions
init scalar vector bivector trivector vector_spherical 
geometric_product mul rotate rot 
print print_scalar print_vector print_bivector print_trivector 
allocate_memory allocate_multivector recycle_memory free_memory memory arena_length arena_capacity 

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
// #include "short_type.h"
// #include "type_aliases.h"


namespace multivector {

#define length 8
typedef double f64;
static unsigned int size = 8 * sizeof(f64);

f64* init(void);
f64* scalar(f64 arg);
f64* vector(f64 a, f64 b, f64 c);
f64* bivector(f64 a, f64 b, f64 c);
f64* trivector(f64 arg);
f64* vector_spherical(f64 r, f64 theta, f64 phi);

f64* geometric_product(f64* a, f64* b);
f64* mul(int num, ...);

f64* rotate(f64* v, f64* a, f64* b);
f64* rot(f64* a, f64* b);

void print(f64* a);
void print_scalar(f64* a);
void print_vector(f64* a);
void print_bivector(f64* a);
void print_trivector(f64* a);

void allocate_memory(size_t cap);
f64* allocate_multivector(void);
void recycle_memory(void);
void free_memory(void);
int main(void);

static f64* memory;
static size_t memory_size;
static size_t memory_allocated;


// === Arena Allocator =============

void allocate_memory(size_t n)
{
    memory_size = 0;
    memory_allocated = n * size;
    memory = (f64*)malloc(memory_allocated * size);
}

f64* allocate_multivector(void)
{
    f64* offset = memory + memory_size * size;

    // realloc on overflow
    if (memory_size + size > memory_allocated){
        memory_allocated *= 2;
        memory = (f64*)realloc(memory, memory_allocated * size);
    }

    memory_size += size;
    return offset;
}

void recycle_memory(void)
{
    memory_size = 0;
}

void free_memory(void)
{
    free(memory);
}

// ===================================

f64* init(void)
{
    f64* a = allocate_multivector();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    return a;
}


f64* scalar(f64 arg)
{
    f64* a = allocate_multivector();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    a[0] = arg;
    return a;
}

f64* vector(f64 a, f64 b, f64 c)
{
    f64* arr = allocate_multivector();
    for (size_t i = 0; i < length; i++) { arr[i] = 0; }
    arr[1] = a;
    arr[2] = b;
    arr[3] = c;
    return arr;
}

f64* bivector(f64 a, f64 b, f64 c)
{
    f64* arr = allocate_multivector();
    for (size_t i = 0; i < length; i++) { arr[i] = 0; }
    arr[4] = a;
    arr[5] = b;
    arr[6] = c;
    return arr;
}

f64* trivector(f64 arg)
{
    f64* a = allocate_multivector();
    for (size_t i = 0; i < length; i++) { a[i] = 0; }
    a[7] = arg;
    return a;
}


f64* geometric_product(f64* a, f64* b)
{

    // multivector product in R3
    // c.e0     =   +a.e0*b.e0  +a.e1*b.e1  +a.e2*b.e2  +a.e3*b.e3  -a.e12*b.e12 -a.e23*b.e23 -a.e31*b.e31 -a.e123*b.e123;
    // c.e1     =   +a.e0*b.e1  +a.e1*b.e0  -a.e2*b.e12  +a.e3*b.e31  +a.e12*b.e2 -a.e23*b.e123 -a.e31*b.e3 -a.e123*b.e23;
    // c.e2     =   +a.e0*b.e2  +a.e1*b.e12  +a.e2*b.e0  -a.e3*b.e23  -a.e12*b.e1 +a.e23*b.e3 -a.e31*b.e123 -a.e123*b.e31;
    // c.e3     =   +a.e0*b.e3  -a.e1*b.e31  +a.e2*b.e23  +a.e3*b.e0  -a.e12*b.e123 -a.e23*b.e2 +a.e31*b.e1 -a.e123*b.e12;
    // c.e12    =   +a.e0*b.e12  +a.e1*b.e2  -a.e2*b.e1  +a.e3*b.e123  +a.e12*b.e0 -a.e23*b.e31 +a.e31*b.e23 +a.e123*b.e3;
    // c.e23    =   +a.e0*b.e23  +a.e1*b.e123  +a.e2*b.e3  -a.e3*b.e2  +a.e12*b.e31 +a.e23*b.e0 -a.e31*b.e12 +a.e123*b.e1;
    // c.e31    =   +a.e0*b.e31  -a.e1*b.e3  +a.e2*b.e123  +a.e3*b.e1  -a.e12*b.e23 +a.e23*b.e12 +a.e31*b.e0 +a.e123*b.e2;
    // c.e123   =   +a.e0*b.e123  +a.e1*b.e23  +a.e2*b.e31  +a.e3*b.e12  +a.e12*b.e3 +a.e23*b.e1 +a.e31*b.e2 +a.e123*b.e0;    

    // "All the pieces matter" - Lester Freamon

    f64* c = allocate_multivector();
    for (size_t i = 0; i < length; i++)
    {
        c[i] = 0;
    }
    c[0]   =   +a[0]*b[0]  +a[1]*b[1]  +a[2]*b[2]  +a[3]*b[3]  -a[4]*b[4] -a[5]*b[5] -a[6]*b[6] -a[7]*b[7];
    c[1]   =   +a[0]*b[1]  +a[1]*b[0]  -a[2]*b[4]  +a[3]*b[6]  +a[4]*b[2] -a[5]*b[7] -a[6]*b[3] -a[7]*b[5];
    c[2]   =   +a[0]*b[2]  +a[1]*b[4]  +a[2]*b[0]  -a[3]*b[5]  -a[4]*b[1] +a[5]*b[3] -a[6]*b[7] -a[7]*b[6];
    c[3]   =   +a[0]*b[3]  -a[1]*b[6]  +a[2]*b[5]  +a[3]*b[0]  -a[4]*b[7] -a[5]*b[2] +a[6]*b[1] -a[7]*b[4];
    c[4]   =   +a[0]*b[4]  +a[1]*b[2]  -a[2]*b[1]  +a[3]*b[7]  +a[4]*b[0] -a[5]*b[6] +a[6]*b[5] +a[7]*b[3];
    c[5]   =   +a[0]*b[5]  +a[1]*b[7]  +a[2]*b[3]  -a[3]*b[2]  +a[4]*b[6] +a[5]*b[0] -a[6]*b[4] +a[7]*b[1];
    c[6]   =   +a[0]*b[6]  -a[1]*b[3]  +a[2]*b[7]  +a[3]*b[1]  -a[4]*b[5] +a[5]*b[4] +a[6]*b[0] +a[7]*b[2];
    c[7]   =   +a[0]*b[7]  +a[1]*b[5]  +a[2]*b[6]  +a[3]*b[4]  +a[4]*b[3] +a[5]*b[1] +a[6]*b[2] +a[7]*b[0];    
    return c;
}

f64* mul(int num, ...)
{

   va_list valist;
   f64* result = scalar(1);
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      result = geometric_product(result, va_arg(valist, f64*));
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   return result;
}

f64* rotate(f64* v, f64* a, f64* b)
{
    // Rotate v by twice the angle between a and b;
    return mul(5, b,a,v,a,b);
}

f64* rot(f64* a, f64* b)
{
    // rotate a by twice the angle between itself and b
    return mul(5,b,a,a,a,b);
}

f64* vector_spherical(f64 r, f64 theta, f64 phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    return vector(
        r*cos(theta)*sin(phi), 
        r*sin(theta)*sin(phi), 
        r*cos(phi)
    );
}

void print(f64* a)
{

    printf("multivector( ");
    for (size_t i = 0; i < length; i++)
    {
        printf("%.3f ", a[i]);
    }
    printf(")\n");
}

void print_scalar(f64* a)
{
    printf( "scalar( %.3f )\n", a[0] );
}

void print_vector(f64* a)
{
    printf( "vector( %.3f %.3f %.3f )\n", a[1],a[2],a[3]);
}

void print_bivector(f64* a)
{
    printf( "bivector( %.3f %.3f %.3f )\n", a[4],a[5],a[6]);
}

void print_trivector(f64* a)
{
    printf( "trivector( %.3f )\n", a[7]);
}

#undef length


int main(void)
{
    #define TAU 6.28318530718

    // #include "multiline_string_literal.h"
    // printf("%s", multiline_string_literal);

    allocate_memory(1000);

    f64* v = vector(1,0,0);
    f64* a = vector(1,0,0);
    f64* b = vector(1/sqrt(2),1/sqrt(2),0);
    // f64* c;
    f64* r;
    f64* spinor;
    f64* spinor1;
    f64* spinor2;

    puts("\
    length\n\
    multiplying two vectors which have the same direction is equivalent to dotting them together\n\
    It gives the length squared\n");

    puts("r = mul(2, vector(1,1,0), vector(1,1,0));");
    r = mul(2, vector(1,1,0), vector(1,1,0));
    print_scalar(r);
    puts(""); 
    
    //getchar();


    puts("\
    In spherical coordinates (r,theta,phi) where TAU = 2*Pi\n");

    puts("r = mul(2, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, TAU/8, TAU/4));");    
    r = mul(2, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, TAU/8, TAU/4));
    print_scalar(r);
    puts(""); 
    
    //getchar(); 
    
    puts("\
    Area\n\
    Multiplying two vectors which are orthogonal to each other will give the area of the rectangle\n");

    puts("r = mul(2, vector(1,0,0), vector(0,1,0));");    
    r = mul(2, vector(1,0,0), vector(0,1,0));
    print_bivector(r);
    puts(""); 
    
    //getchar();
    
    puts("\
    Here we have two vectors in spherical coordinates.\n\
    Multiplying them gives the dot product and the wedge product (similar to the cross product.\n");

    puts("r = mul(2, vector_spherical(1, TAU/8, TAU/8), vector_spherical(1, TAU/4, TAU/4));");
    r = mul(2, vector_spherical(1, TAU/8, TAU/8), vector_spherical(1, TAU/4, TAU/4));
    print(r);
    puts(""); 
    
    //getchar();

    puts("\
    volume\n\
    Volume works great but you get a trivector\n");

    puts("r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));");    
    r = mul(3, vector(1,0,0), vector(0,1,0), vector(0,0,1));
    print_trivector(r);
    puts(""); 
    
    //getchar();

    puts("\n");
    
    puts("r = mul(3, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, 3*TAU/8, TAU/4), vector(0,0,1));");
    r = mul(3, vector_spherical(1, TAU/8, TAU/4), vector_spherical(1, 3*TAU/8, TAU/4), vector(0,0,1));
    print_trivector(r);
    puts(""); 
    
    //getchar();

    puts("A trivector is also known as a pseudoscalar since it's a single number\n");
    puts("but it squares to give a negative scalar\n");
    puts("\n");
    puts("\n");
    puts("2D rotation (complex numbers)\n");
    puts("A vector can be rotated by multiplying it by a bivector\n");
    puts("A bivector works like a complex number\n");
    
    puts("r = mul(2, vector(1,0,0), bivector(1,0,0)); \n");
    r = mul(2, vector(1,0,0), bivector(1,0,0)); 
    print_vector(r);
    puts(""); 
    
    //getchar();

    puts("\n");
    
    puts("spinor = mul(2, vector(1,0,0), vector_spherical(1, TAU/12, TAU/4));");
    puts("r = mul(2, vector(1,0,0), spinor);");
    spinor = mul(2, vector(1,0,0), vector_spherical(1, TAU/12, TAU/4));
    r = mul(2, vector(1,0,0), spinor);
    print_vector(r);

    puts("\n");
    puts("\n");
    puts("3D rotation work in this way apparently\n");
    puts("To rotate a vector 'v' in the arc from vector 'a' to vector 'b'\n");
    puts("multiply(b,a,v,a,b);\n");
    puts("This will rotate v by twice the angle between a and b\n");
    puts("v = vector(1,0,0);\n");
    puts("a = vector_spherical(1, TAU/8, TAU/4);\n");
    puts("b = vector_spherical(1, TAU/8, TAU/8);\n");
    puts("r = mul(5, b,a,v,a,b);\n");

    v = vector(1,0,0);
    a = vector_spherical(1, TAU/8, TAU/4);
    b = vector_spherical(1, TAU/8, TAU/8);
    r = mul(5, b,a,v,a,b);

    print_vector(r);
    puts("\n");
    puts("Does it work just multiplying on one side? Not generally I think.\n");
    puts("spinor1 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4))\n");
    puts("spinor2 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4))\n");
    puts("mul(3, vector(1,0,0), spinor1, spinor2);\n");

    spinor1 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4));
    spinor2 = mul(2, vector(1,0,0), vector_spherical(1,TAU/8,TAU/4));
    mul(3, vector(1,0,0), spinor1, spinor2);

    puts("\n");
    puts("chirality???\n");
    puts("r = mul(2, trivector(3), trivector(4));\n");
    r = mul(2, trivector(3), trivector(4));
    print(r);
    
    free_memory();

    return 0;

    #undef TAU

}

}

#endif
