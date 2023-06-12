#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"

namespace activation
{
    /**
     * @typedef activation_f
     * Function pointer type for an activation function that operates on a
     * Matrix (as part of the dense layers' implementation).
     */
    typedef Matrix (*activation_f) (const Matrix &);

    /**
     * An implementation of the ReLU activation function. Applies the ReLU
     * activation function element-wise to the input matrix.
     * @param mat The input matrix.
     * @return The output matrix after applying the ReLU activation function.
     */
    Matrix relu (const Matrix &mat);

    /**
     * An implementation of the Softmax activation function. Applies the
     * Softmax activation function to the input matrix.
     * @param mat The input matrix.
     * @returnT he output matrix after applying the Softmax activation
     * function.
     */
    Matrix softmax (const Matrix &mat);
}
#endif //ACTIVATION_H