#include <math.h>
#include "roots.h"

typedef struct Complex {
    float real;
    float imag;
} Complex;

void find_roots(float a1, float a2, Complex *root1, Complex *root2) {
    float discriminant = a1 * a1 - 4 * a2;

    if (discriminant > 0) {
        root1->real = (-a1 + sqrt(discriminant)) / 2;
        root2->real = (-a1 - sqrt(discriminant)) / 2;
        root1->imag = 0;
        root2->imag = 0;
    } else if (discriminant == 0) {
        root1->real = root2->real = -a1 / 2;
        root1->imag = root2->imag = 0;
    } else {
        root1->real = root2->real = -a1 / 2;
        float imag = sqrt(-discriminant) / 2;
        root1->imag = imag;
        root2->imag = -imag;
    }
}

