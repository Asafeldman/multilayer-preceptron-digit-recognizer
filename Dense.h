#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
using namespace activation;

/**
 * Represents a dense layer in a neural network.
 */
class Dense
{
 public:

  /**
   * Constructs a Dense layer with the given weights, bias, and activation
   * function.
   * @param weights The weight matrix of the dense layer.
   * @param bias The bias matrix of the dense layer.
   * @param activation_func The activation function of the dense layer.
   */
  Dense (const Matrix &weights, const Matrix &bias, activation_f
  activation_func);

  /**
   * Returns the weight matrix of the current Dense layer object.
   * @return The weight matrix.
   */
  Matrix get_weights () const { return _weights; }

  /**
   * Returns the bias matrix of the current Dense layer object.
   * @return The bias matrix.
   */
  Matrix get_bias () const { return _bias; }

  /**
   * Returns the activation function of the current Dense layer object.
   * @return The activation function.
   */
  activation_f get_activation () const { return _activation_func; }

  /**
   * Applies the current Dense layer object on the input and returns an output
   * matrix.
   * @param input The input matrix to the dense layer.
   * @return The output matrix after applying the dense layer.
   */
  Matrix operator() (const Matrix &input) const;

 private:
  Matrix _weights, _bias;
  activation_f _activation_func;
};

#endif //DENSE_H
