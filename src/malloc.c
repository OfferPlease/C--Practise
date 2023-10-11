#include <stdio.h>
#include <stdlib.h>
/* practise malloc with struct in C */
/* The difference between struc in C and C++*/
/**/
struct Vector{
    float x;
    float y;
    double *z;
};

int main()
{
    // Just allocate space for all variables in Vector
    // including pointer z itself, but not the memory it pointing to
    struct Vector *v = malloc(sizeof(struct Vector));
    // allocate memory for z's own space
    v->z = malloc(10 * sizeof(float));
    v->x = 1.0;
    v->y = 1.0;
    // calloc
    float* f_arr = calloc(10, sizeof(float));

    printf("%.2f",v->x);
    free(v->z);
    free(v);
    free(f_arr);
    return 0;
}