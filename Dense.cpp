#include "Matrix.h"
#include "Dense.h"

Dense::Dense (const Matrix &weights, const Matrix &bias, activation_f
activation_func)
    : _weights (weights), _bias (bias), _activation_func (activation_func)
{}

Matrix Dense::operator() (const Matrix &input) const
{
  return _activation_func ((_weights * input) + _bias);
}


