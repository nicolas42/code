#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

// there's no reason for the custom memory allocator.  just a bit of fun.
#define MEMORY_ALLOCATED 10000000
float memory[MEMORY_ALLOCATED] = {0};
int memory_length = 0;

void* allocate(int bytes)
{
    int old_memory_offset = memory_length;
    memory_length += bytes;
    if(memory_length > MEMORY_ALLOCATED) { printf("error: no memory left\n"); exit(-1); }
    return memory + old_memory_offset;
}

float* allocate_multivector()
{
    return (float*)allocate(8*sizeof(float));
}

float* multiply_multivectors(float* a, float* b)
{
    float *c = allocate_multivector();
    // A 3D multivector has 8 elements
    // a scalar, a three dimensional vector, a three dimensional bivector, and a trivector
    // [ s x y z xy yz zx xyz ]
    // [ e0 e1 e2 e3 e12 e23 e31 e123 ]

    // multivector product in R3
    // c.e0     =   +a.e0*b.e0  +a.e1*b.e1  +a.e2*b.e2  +a.e3*b.e3  -a.e12*b.e12 -a.e23*b.e23 -a.e31*b.e31 -a.e123*b.e123;
    // c.e1     =   +a.e0*b.e1  +a.e1*b.e0  -a.e2*b.e12  +a.e3*b.e31  +a.e12*b.e2 -a.e23*b.e123 -a.e31*b.e3 -a.e123*b.e23;
    // c.e2     =   +a.e0*b.e2  +a.e1*b.e12  +a.e2*b.e0  -a.e3*b.e23  -a.e12*b.e1 +a.e23*b.e3 -a.e31*b.e123 -a.e123*b.e31;
    // c.e3     =   +a.e0*b.e3  -a.e1*b.e31  +a.e2*b.e23  +a.e3*b.e0  -a.e12*b.e123 -a.e23*b.e2 +a.e31*b.e1 -a.e123*b.e12;
    // c.e12    =   +a.e0*b.e12  +a.e1*b.e2  -a.e2*b.e1  +a.e3*b.e123  +a.e12*b.e0 -a.e23*b.e31 +a.e31*b.e23 +a.e123*b.e3;
    // c.e23    =   +a.e0*b.e23  +a.e1*b.e123  +a.e2*b.e3  -a.e3*b.e2  +a.e12*b.e31 +a.e23*b.e0 -a.e31*b.e12 +a.e123*b.e1;
    // c.e31    =   +a.e0*b.e31  -a.e1*b.e3  +a.e2*b.e123  +a.e3*b.e1  -a.e12*b.e23 +a.e23*b.e12 +a.e31*b.e0 +a.e123*b.e2;
    // c.e123   =   +a.e0*b.e123  +a.e1*b.e23  +a.e2*b.e31  +a.e3*b.e12  +a.e12*b.e3 +a.e23*b.e1 +a.e31*b.e2 +a.e123*b.e0;    

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

float* make_vector_spherical_coordinates(float r, float theta, float phi)
{
    // Spherical coordinates
    // x = cos(theta)*sin(phi); y = cos(theta-90)*sin(phi); z = cos(phi); 
    float *c = allocate_multivector();

    c[1] = r*cos(theta)*sin(phi);
    c[2] = r*sin(theta)*sin(phi);
    c[3] = r*cos(phi);

    return c;
}


char* stringify_multivector(float *c)
{
    char *str = (char*)allocate(200); 
    // 25 bytes per number * 8 = 200;
    int i = 0;
    
    i += snprintf(str+i, 200-i, "[");

    if ( c[0] != 0 ) { i += snprintf(str+i, 200-i, " %+.2f", c[0] ); }
    if ( c[1] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fx", c[1] ); }
    if ( c[2] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fy", c[2] ); }
    if ( c[3] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fz", c[3] ); }
    if ( c[4] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fxy", c[4] ); }
    if ( c[5] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fyz", c[5] ); }
    if ( c[6] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fzx", c[6] ); }
    if ( c[7] != 0 ) { i += snprintf(str+i, 200-i, " %+.2fxyz", c[7] ); }
    i += snprintf(str+i, 200-i, " ]");

    // printf("%d", i);
    return str;
    // printf("[ %.1f + (%.1fx + %.1fy + %.1fz) + (%.1fxy + %.1fyz + %.1fzx) + %.1fxyz ]", c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7] );
}

void print_multivector(float* a)
{
    printf("%s\n", stringify_multivector(a));
}

int main()
{

    const float TWOPI = 6.28318530718;

    float* (*mul)(float* a, float* b) = multiply_multivectors;
    float* (*sph)(float r, float theta, float phi) = make_vector_spherical_coordinates;
    void (*p)(float* c) = print_multivector;
    float* (*alloc)() = allocate_multivector;

    // 30 degrees, 45 degrees
    float *c,*d,*e,*f;

    float a[8] = {0, sqrt(3.)/2., 1./2., };
    float b[8] = {0, sqrt(2.)/2., sqrt(2.)/2., };
    c = mul(a,b);

    p(c);



}


// struct multivector {
//     float[8] d;
// }


// struct multivector_library {
//     float* (*mul)(float* a, float* b);
//     void (*p)(float *c);
//     float data[8];
// };

// struct multivector_library m = {
//     .mul = multiply_multivectors,
//     .p = stringify_multivector,
//     .data = {0,0,0,0,0,0,0,0}
// };



// float* multivector_rotate(float* v, float* a, float* b)
// {
//     // Rotate v by twice the angle between a and b;
//     // return multivector_mul(5, b,a,v,a,b);
// }




// int demo1() // int argc, char **argv)
// {
//     #define TWOPI 6.28318530718

//     float x[8] = { 0, 1,0,0 };
//     float y[8] = { 0, 0,1,0 };
//     float xy[8];
//     float temp[8];

//     // To multiply multiv
//     multiply_multivectors(x,y,xy);
//     stringify_multivector(xy);
    

//     mul(x,y,xy);
//     mul(x,xy,temp);
//     mul(y,xy,temp);
//     mul(xy,xy,temp);


//     float a[8] = { 0, 2,3,8,  4,8,15, 1};
//     float b[8] = { 0, 2,3,8,  4,8,15, 1};
//     mul(a,b,temp);

//     // float c[8],d[8];
//     // make_vector_spherical_coordinates(1,TWOPI/8,TWOPI/8, c);
//     // MUL(x,c,d)

//     return 0;

// }

