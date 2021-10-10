#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
typedef uint8_t     u8;
typedef int8_t      s8;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint64_t    u64;
typedef int64_t     s64;
typedef float       f32;
typedef double      f64;

#define PI 3.14159265358979323846
#define TAU 6.28318530718
#define DEBUG 

// 3d multivector
struct multivector {
    double e0;
    double e1;
    double e2;
    double e3;
    double e12;
    double e23;
    double e13;
    double e123;
};

typedef struct multivector Multivector;

// // custom memory allocator
// #define MEMORY_ALLOCATED 10000000
// double memory[MEMORY_ALLOCATED];
// int memory_length = 0;


// void* allocate(int bytes)
// {
//     int old_memory_offset = memory_length;
//     memory_length += bytes;
//     if(memory_length > MEMORY_ALLOCATED) { printf("error: no memory left\n"); exit(-1); }
//     return memory + old_memory_offset;
// }

Multivector *multivector_allocate()
{
    return (Multivector *)calloc(0, sizeof(Multivector));
}

Multivector multivector_multiply(Multivector a, Multivector b)
{
    Multivector c;
    // A 3D multivector has 8 elements
    // a scalar e0, a three dimensional vector e1,e2,e3, a three dimensional bivector e12 e13 e23, and a trivector e123

    // self._base = ["1", "e1", "e2", "e3", "e12", "e13", "e23", "e123"]

    c.e0=b.e0*a.e0+b.e1*a.e1+b.e2*a.e2+b.e3*a.e3-b.e12*a.e12-b.e13*a.e13-b.e23*a.e23-b.e123*a.e123;
    c.e1=b.e1*a.e0+b.e0*a.e1-b.e12*a.e2-b.e13*a.e3+b.e2*a.e12+b.e3*a.e13-b.e123*a.e23-b.e23*a.e123;
    c.e2=b.e2*a.e0+b.e12*a.e1+b.e0*a.e2-b.e23*a.e3-b.e1*a.e12+b.e123*a.e13+b.e3*a.e23+b.e13*a.e123;
    c.e3=b.e3*a.e0+b.e13*a.e1+b.e23*a.e2+b.e0*a.e3-b.e123*a.e12-b.e1*a.e13-b.e2*a.e23-b.e12*a.e123;
    c.e12=b.e12*a.e0+b.e2*a.e1-b.e1*a.e2+b.e123*a.e3+b.e0*a.e12-b.e23*a.e13+b.e13*a.e23+b.e3*a.e123;
    c.e13=b.e13*a.e0+b.e3*a.e1-b.e123*a.e2-b.e1*a.e3+b.e23*a.e12+b.e0*a.e13-b.e12*a.e23-b.e2*a.e123;
    c.e23=b.e23*a.e0+b.e123*a.e1+b.e3*a.e2-b.e2*a.e3-b.e13*a.e12+b.e12*a.e13+b.e0*a.e23+b.e1*a.e123;
    c.e123=b.e123*a.e0+b.e23*a.e1-b.e13*a.e2+b.e12*a.e3+b.e3*a.e12-b.e2*a.e13+b.e1*a.e23+b.e0*a.e123;

    return c;
}


// Multivector multiply_n_multivectors(int n, Multivector *m)
// {
//     Multivector out = m[0];
//     for (int i=1; i<n; i+=1){
//         out = multivector_multiply(out, m[i]);
//     }
//     return out;
// }


bool feq(float a, float b)
{
  return fabs(a - b) < 1e-10;
}

char* stringify_multivector(Multivector c)
{
    char *str = (char*)calloc(200,sizeof(char)); 
    // 25 bytes per number * 8 = 200;
    int i = 0;
    
    i += snprintf(str+i, 200-i, "[");

    if ( !feq(c.e0,0) ) { i += snprintf(str+i, 200-i, " %+.2f", c.e0 ); }
    if ( !feq(c.e1,0) ) { i += snprintf(str+i, 200-i, " %+.2fx", c.e1 ); }
    if ( !feq(c.e2,0) ) { i += snprintf(str+i, 200-i, " %+.2fy", c.e2 ); }
    if ( !feq(c.e3,0) ) { i += snprintf(str+i, 200-i, " %+.2fz", c.e3 ); }
    if ( !feq(c.e12,0) ) { i += snprintf(str+i, 200-i, " %+.2fxy", c.e12 ); }
    if ( !feq(c.e23,0) ) { i += snprintf(str+i, 200-i, " %+.2fyz", c.e23 ); }
    if ( !feq(c.e13,0) ) { i += snprintf(str+i, 200-i, " %+.2fzx", c.e13 ); }
    if ( !feq(c.e123,0) ) { i += snprintf(str+i, 200-i, " %+.2fxyz", c.e123 ); }
    i += snprintf(str+i, 200-i, " ]");

    // printf("%d", i);
    return str;
    // printf(".d[ %.1f + (%.1fx + %.1fy + %.1fz) + (%.1fxy + %.1fyz + %.1fzx) + %.1fxyz ]", c.e0,c.e1,c.e2,c.e3,c.e12,c.e23,c.e13,c.e123 );
}

void multivector_print(Multivector a)
{
    printf("%s\n", stringify_multivector(a));
}

Multivector multivector_copy(Multivector a)
{
    Multivector b;

    b.e0 = a.e0;
    b.e1 = a.e1;
    b.e2 = a.e2;
    b.e3 = a.e3;
    b.e12 = a.e12;
    b.e23 = a.e23;
    b.e13 = a.e13;
    b.e123 = a.e123;
    return b;
}

Multivector make_conjugate(Multivector a)
{
    Multivector b = multivector_copy(a);
    b.e12 = -a.e12;
    b.e23 = -a.e23;
    b.e13 = -a.e13;
    return b;
}


Multivector multivector_multiply_n(int num_args, Multivector...) {
   int val = 0;
   va_list args;
   int i;

   va_start(args, num_args);
    Multivector out = va_arg(args, Multivector);
   for(i = 1; i < num_args; i++) {
       out = multivector_multiply(out, va_arg(args, Multivector));
   }
   va_end(args);
 
   return out;
}

Multivector multivector_rotate(Multivector arg, double xy_angle, double xz_angle, double yz_angle )
{
    Multivector v = multivector_copy(arg);

    Multivector a;
    a.e0 = cos(xy_angle/2.);
    a.e12 = sin(xy_angle/2.);
    Multivector aconj = make_conjugate(a);

    Multivector b;
    b.e0 = cos(yz_angle/2.);
    b.e23 = sin(yz_angle/2.);
    Multivector bconj = make_conjugate(b);

    Multivector c;
    c.e0 = cos(xz_angle/2.);
    c.e13 = sin(xz_angle/2.);
    Multivector cconj = make_conjugate(c);

#ifdef DEBUG
    Multivector v2 = multivector_multiply_n(3,aconj,v,a);
    multivector_print(v2);
    Multivector v3 = multivector_multiply_n(3,bconj,v2,b);
    multivector_print(v3);
    Multivector v4 = multivector_multiply_n(3,cconj,v3,c);
    multivector_print(v4);
#endif 

    v = multivector_multiply_n(7,cconj, bconj, aconj,v,a,b,c);

    return v;

}


Multivector make_quaternion_from_axis_and_angle(Multivector axis, double angle) // remember to divide angle by 2
{
    // apparently a quaternion can be made like this
    // cos(theta) + sin(theta)*(unit bivector oriented plane)

    multivector_print(axis);
    Multivector pseudoscalar;
    pseudoscalar.e123 = 1.;
    // multivector_print(pseudoscalar);
    Multivector quaternion = multivector_multiply(axis,pseudoscalar);
    // multivector_print(quaternion);

    // double angle = 90./2.*PI/180.; // remember to divide angle by 2
    quaternion.e0 = cos(angle);
    quaternion.e12 *= sin(angle);
    quaternion.e13 *= sin(angle);
    quaternion.e23 *= sin(angle);
    multivector_print(quaternion);

    return quaternion;

}

int main()
{
    void (*p)(Multivector c) = multivector_print;
    // Multivector (*mul)(Multivector a, Multivector b) = multivector_multiply;
    // Multivector (*muln)(int num_args, Multivector...) = multivector_multiply_n;
    // Multivector (*multivector_multiply_n)(int n, Multivector *m ) = multiply_n_multivectors;


    {
        printf("Multiply x unit vector around xy,yz, and xz planes by TAU/8 TAU/8 0 \n");
        Multivector v;
        v.e1 = 1;
        Multivector vdash = multivector_rotate(v,TAU/8., 0, TAU/8.);
        multivector_print(vdash);
    }


    {
        printf("Rotate x unit vector 180 degrees around plane with normal x-y \n");
        printf("That is towards the third quadrant.\n");

        Multivector v;
        v.e1 = 1;

        Multivector axis;
        axis.e1 = 1./sqrt(2.);
        axis.e2 = -1./sqrt(2.);
        multivector_print(axis);

        double angle = 180./2.*PI/180.;
        Multivector q = make_quaternion_from_axis_and_angle(axis, angle);
        Multivector vdash = multivector_multiply_n(3, make_conjugate(q), v, q);
        multivector_print(vdash);
        
    }

}
