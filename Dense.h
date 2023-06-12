#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
using namespace activation;

class Dense
{
 public:
  Dense (const Matrix &weights, const Matrix &bias, activation_f
  activation_func);

  Matrix get_weights () const { return _weights; }
  Matrix get_bias () const { return _bias; }
  activation_f get_activation () const { return _activation_func; }
  Matrix operator() (const Matrix &input) const;

 private:
  Matrix _weights, _bias;
  activation_f _activation_func;
};

#endif //DENSE_H
