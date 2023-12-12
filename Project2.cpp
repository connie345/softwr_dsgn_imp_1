

/* Project2.cpp
 * Ima Student
 * EE312, Summer 2017
 * Project 2, Matrix Multiplication
 */
// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Connie Wang
// cw39276
// Slip days used: 0
// Spring 2018
// Include the contents of this file at the top of every file that you submit, replacing the fields within <>.  Do not keep the <>.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"


void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[])
{

    uint32_t n = 0;
    uint32_t numRow = 0;
    uint32_t numCol = 0;
    while(numRow < a_rows){
        numCol=0;
        while(numCol < b_cols){
            n = 0;
            c[numRow*b_cols + numCol] = 0;
            while(n < a_cols){
                c[numRow*b_cols+numCol] += a[numRow*a_cols+n] * b[n*b_cols + numCol];
                n++;
            }
            numCol++;
        }
        numRow++;
    }
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {

    uint32_t n = 0;
    uint32_t numRow = 0;
    uint32_t numCol = 0;
    double** save;
    save = (double **)malloc(sizeof(double *) * a_rows);
    for(uint32_t i  = 0; i< a_rows; i++){
        save[i] = (double*)malloc(b_cols*sizeof(double));
    }
    while(numRow < a_rows) {
        numCol = 0;
        while (numCol < b_cols) {
            n = 0;
            save[numRow][numCol] = 0;
            while (n < a_cols) {
                save[numRow][numCol] += a[numRow][n] * b[n][numCol];
                n++;
            }
            numCol++;
        }
        numRow++;
    }

    return save;
    return NULL;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols) {
    uint32_t numRow = 0;
    uint32_t numCol = 0;
    double** save;
    save = (double **)malloc(sizeof(double *) * a_cols);
    for(uint32_t i = 0; i< a_cols; i++){
        save[i] = (double*)malloc(a_rows*sizeof(double));
    }
    while(numRow < a_cols) {
        numCol = 0;
        while (numCol < a_rows) {
            save[numRow][numCol] = a[numCol][numRow];
            numCol++;
        }
        numRow++;
    }

    return save;
    return NULL;
}
