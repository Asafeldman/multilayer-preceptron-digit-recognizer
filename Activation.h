#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"

namespace activation
{
    typedef Matrix (*activation_f) (const Matrix &);
    Matrix relu (const Matrix &mat);
    Matrix softmax (const Matrix &mat);
}
#endif //ACTIVATION_H