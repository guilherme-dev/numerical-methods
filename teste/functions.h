#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define M_PI 3.14159265358979323846


void generate_equation( int N, double *line );
double f (double x);

void create_linear_system (double **A, double *b, int n);