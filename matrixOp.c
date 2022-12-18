#include "matrixOp.h"


double ** ImgToMatrix(char * name) {
    char buf[50] = {0};

    double ** A = (double **) calloc(28, sizeof(double *));
    for(int i = 0; i < 28; i ++){
        A[i] = (double *)calloc(28, sizeof(double));
    }

    int line = 5, i = 1;
    int ch;
    double pixel;

    FILE *fp = fopen(name, "r");
    fseek(fp, SEEK_SET, 0);
    while(i < line){
       if(fgets(buf,50, fp)) i ++;
    }
    for(i = 0; i < 28; i ++){
        for(int j = 0; j < 28 ; j ++){
            ch = fgetc(fp);
            pixel = ch / 255.0;
            A[i][j] = pixel;
        }
    }
    fclose(fp);
    return A;
}

double * Reshape(double ** m){
    double * B = (double *) malloc(sizeof(double) * 784);

    for(int i = 0; i < 28; ++i){
        for (int j = 0; j < 28; ++j) {
            B[i * 28 + j] = m[i][j];
        }
    }
    return B;
}

double ** getMatrixC1(){

    double ** C1 = (double **) malloc(sizeof(double *) * 784);
    for(int i = 0; i < 784; i ++){
        C1[i] = (double *)malloc(sizeof(double) * 128);
    }

    char * fileName = "..\\Input files\\W1.txt";
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("File error");
        exit(0);
    }

    for(int i = 0; i < 784; ++i){
        for(int j = 0; j < 128; ++j){
            fscanf(fp, "%lf", &C1[i][j]);
        }
    }

    fclose(fp);
    return C1;
}
double ** getMatrixC2(){
    double ** C2 = (double **) malloc(sizeof(double *) * 128);
    for(int i = 0; i < 128; i ++){
        C2[i] = (double *)malloc(sizeof(double) * 10);
    }

    char * fileName = "..\\Input files\\W2.txt";
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("File error");
        exit(0);
    }

    for(int i = 0; i < 128; ++i){
        for(int j = 0; j < 10; ++j){
            fscanf(fp, "%lf", &C2[i][j]);
        }
    }

    fclose(fp);
    return C2;
}

double * getMatrixE1(){

    double * E1 = (double *) malloc(sizeof(double ) * 128);

    char * fileName = "..\\Input files\\B1.txt";
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("File error");
        exit(0);
    }

    for(int i = 0; i < 128; ++i){
        fscanf(fp, "%lf", &E1[i]);
    }
    fclose(fp);
    return E1;
}
double * getMatrixE2(){

    double * E2 = (double *) malloc(sizeof(double ) * 10);

    char * fileName = "..\\Input files\\B2.txt";
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("File error");
        exit(0);
    }

    for(int i = 0; i < 10; ++i){
        fscanf(fp, "%lf", &E2[i]);
    }
    fclose(fp);
    return E2;
}

double* matrixMultiplyBC1(const double * m1, double ** m2){
    double * D = (double *) calloc(128, sizeof(double ));
    double sum;

    for(int i = 0; i < 128; ++i){
        sum = 0;
        for(int j = 0; j < 784; ++j){
            sum += m1[j] * m2[j][i];
        }
        D[i] = sum;
    }
    return D;
}
double* matrixMultiplyGC2(const double * m1, double ** m2){
    double * H = (double *) calloc(10, sizeof(double ));
    double sum;

    for(int i = 0; i < 10; ++i){
        sum = 0;
        for(int j = 0; j < 128; ++j){
            sum += m1[j] * m2[j][i];
        }
        H[i] = sum;
    }
    return H;
}

double* matrixAddDE1(const double * m1, const double * m2){
    double * F = (double *) calloc(128,sizeof(double ));

    for(int i = 0; i < 128; i ++){
        F[i] = m1[i] + m2[i];
    }
    return F;
}
double* matrixAddHE2(const double * m1, const double * m2){
    double * L = (double *) calloc(10, sizeof(double ));

    for(int i = 0; i < 10; i ++){
        L[i] = m1[i] + m2[i];
    }
    return L;
}

double* matrixActivate(const double * m){
    double * G = (double *) calloc(128, sizeof(double ));

    for(int i = 0; i < 128; ++i){
        G[i] = fmax(m[i], 0);
    }
    return G;
}

double* SoftMax(const double * m){
    double * S = (double *) calloc(10, sizeof(double ));

    double max = 0, denominator = 0;
    for(int i = 0; i < 10; i ++){
        max = fmax(max, m[i]);
    }

    for(int i = 0; i < 10; ++ i){
        denominator += exp(m[i] - max);
    }
    for(int i = 0; i < 10; ++i){
        S[i] = exp(m[i] - max) / denominator;
    }
    return S;
}