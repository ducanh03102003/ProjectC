#include <math.h>
#include <complex.h>
#include "roots.h"

void find_roots(float a1, float a2, double complex *root1, double complex *root2) {
    float discriminant = a1 * a1 - 4 * a2;

    if (discriminant > 0) {
        *root1 = (-a1 + sqrt(discriminant)) / 2;
        *root2 = (-a1 - sqrt(discriminant)) / 2;
    } else if (discriminant == 0) {
        *root1 = *root2 = -a1 / 2;
    } else {
        float real = -a1 / 2;
        float imag = sqrt(-discriminant) / 2;
        *root1 = real + imag * I;
        *root2 = real - imag * I;
    }
}
