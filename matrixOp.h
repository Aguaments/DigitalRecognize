#include "utils.h"
#include <math.h>

double ** ImgToMatrix(char * name);

double * Reshape(double ** m);

double ** getMatrixC1();
double ** getMatrixC2();

double * getMatrixE1();
double * getMatrixE2();

double* matrixAddDE1(const double * m1, const double * m2);
double* matrixAddHE2(const double * m1, const double * m2);

double* matrixMultiplyBC1(const double * m1, double ** m2);
double* matrixMultiplyGC2(const double * m1, double ** m2);
double* matrixActivate(const double * m);
double* SoftMax(const double * m);
