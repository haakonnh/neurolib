#ifndef NEUROLIB_H_
#define NEUROLIB_H_

#include <iostream>
#include <stddef.h>
#include <time.h>
#include <random>

#ifndef NEUROLIB_MALLOC
#include <stdlib.h>
#define NEUROLIB_MALLOC malloc
#endif /* NEUROLIB_MALLOC */

#ifndef NEUROLIB_ASSERT
#include <assert.h>
#define NEUROLIB_ASSERT assert
#endif /* NEUROLIB_ASSERT */


struct Matrix
{
    size_t rows;
    size_t cols;
    float* data;
};

#define MATRIX_AT(m, i, j) m.data[(i) * (m).cols + (j)]

float rand_float();

Matrix matrix_alloc(size_t rows, size_t cols);

void matrix_fill(Matrix a, float val);

void matrix_randomize(Matrix a, float low, float high);

void matrix_dot(Matrix dest, Matrix a, Matrix b);

void matrix_add(Matrix dest, Matrix b);

void matrix_print(Matrix a);



#endif /* NEUROLIB_H_ */

#ifdef NEUROLIB_IMPLEMENTATION

float rand_float() {
    return (float)rand() / (float)RAND_MAX;
}

Matrix matrix_alloc(size_t rows, size_t cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = (float*)malloc(sizeof(*m.data) * rows * cols);
    return m;
}

void matrix_fill(Matrix a, float val) {
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            MATRIX_AT(a, i, j) = val;
        }
    }
}

void matrix_dot(Matrix dest, Matrix a, Matrix b) {
    NEUROLIB_ASSERT(a.cols == b.rows);
    size_t n = a.cols;
    NEUROLIB_ASSERT(dest.rows == a.rows);
    NEUROLIB_ASSERT(dest.cols == b.cols);

    for (size_t i = 0; i < dest.rows; ++i) {
        for (size_t j = 0; j < dest.cols; ++j) {
            float sum = 0.0f;
            for (size_t k = 0; k < n; ++k) {
                sum += MATRIX_AT(a, i, k) * MATRIX_AT(b, k, j);
            }
            MATRIX_AT(dest, i, j) = sum;
        }
    }
}

void matrix_add(Matrix dest, Matrix b) {
    NEUROLIB_ASSERT(dest.rows == b.rows);
    NEUROLIB_ASSERT(dest.cols == b.cols);
    for (size_t i = 0; i < dest.rows; ++i) {
        for (size_t j = 0; j < dest.cols; ++j) {
            MATRIX_AT(dest, i, j) += MATRIX_AT(b, i, j);
        }
    }
}

void matrix_print(Matrix a) {
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            std::cout << MATRIX_AT(a, i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void matrix_randomize(Matrix a, float low = 0, float high = 1) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(low, high);
    for (size_t i = 0; i < a.rows; ++i) {
        for (size_t j = 0; j < a.cols; ++j) {
            MATRIX_AT(a, i, j) = dis(gen);
        }
    }
}

#endif /* NEUROLIB_IMPLEMENTATION */