#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <float.h>
#define PI 3.1415926535897932384626433832795028841971693993751058f // Parte dos 300 digitos de PI na Wikipedia.
#define _2PI 2*PI
#define GS "GS"
#define SOR "SOR"

enum error_t{ NARGC_ERROR = -1, NX_ERROR = -2, NX_LETRA = -3, NY_ERROR = -4, NY_LETRA = -5, NI_ERROR = -6, NI_LETRA = -7, M_ERROR = -8, M_TYPE_ERROR = -9, O_ERROR = -10, ARQ_ERROR = -11 };

double timestamp(void);

void init_inc(double *pts, int ult_pt_bord_dir, int tam_inc, double delta_x);

void imprime_inc(double *inc, int tam_x, int tam_y);

void gauss_seidel_ssor(int nx, int ny, int ni, char mod, FILE *arq);
