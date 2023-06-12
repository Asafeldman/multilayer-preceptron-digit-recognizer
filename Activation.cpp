#include "Activation.h"
#include "cmath"

Matrix activation::relu (const Matrix &mat)
{
  int rows = mat.get_rows (), cols = mat.get_cols ();
  Matrix relu_mat (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (mat (i, j) > 0)
      {
        relu_mat (i, j) = mat (i, j);
      }
    }
  }
  return relu_mat;
}

Matrix activation::softmax (const Matrix &mat)
{
  float exp_sum = 0;
  int rows = mat.get_rows (), cols = mat.get_cols ();
  Matrix soft_mat (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      float exp_ij = std::exp (mat (i, j));
      soft_mat (i, j) = exp_ij;
      exp_sum += exp_ij;
    }
  }
  return (1 / exp_sum) * soft_mat;
}

