#ifndef ROOTS_H
#define ROOTS_H

typedef struct Complex {
    float real;
    float imag;
} Complex;

void find_roots(float a1, float a2, Complex *root1, Complex *root2);

#endif // ROOTS_H
