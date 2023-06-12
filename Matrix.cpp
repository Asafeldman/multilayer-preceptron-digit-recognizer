#include "Matrix.h"
#include "stdexcept"
#include "iostream"
#include "cmath"

Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  _rows = rows, _cols = cols, _matrix = new float[rows * cols];
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      (*this) (i, j) = 0;
    }
  }
}

Matrix::Matrix () : _rows (1), _cols (1), _matrix (new float[1]{0.0f})
{}

Matrix::Matrix (const Matrix &mat)
{
  _rows = mat._rows, _cols = mat._cols;
  _matrix = new float[_rows * _cols];
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      (*this) (i, j) = mat (i, j);
    }
  }
}

Matrix::~Matrix ()
{
  delete[] _matrix;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      std::cout << (*this) (i, j) << " ";
    }
    std::cout << std::endl;
  }
}

float Matrix::norm () const
{
  float sum = 0;
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      sum += ((*this) (i, j) * (*this) (i, j));
    }
  }
  return std::sqrt (sum);
}

Matrix Matrix::dot (const Matrix &mat) const
{
  Matrix prod (*this);
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      prod (i, j) *= mat (i, j);
    }
  }
  return prod;
}

Matrix &Matrix::vectorize ()
{
  _rows *= _cols;
  _cols = 1;
  return *this;
}

float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      sum += (*this) (i, j);
    }
  }
  return sum;
}

Matrix &Matrix::transpose ()
{
  Matrix transposed (_cols, _rows);
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      transposed (i, j) = (*this) (j, i);
    }
  }
  delete[] _matrix;
  _rows = transposed._rows, _cols = transposed._cols;
  _matrix = new float[_rows * _cols];
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      (*this) (i, j) = transposed (i, j);
    }
  }
  delete[] transposed._matrix;
  return *this;
}

int Matrix::argmax () const
{
  int max_idx = 0;
  float max_val = _matrix[max_idx];
  for (int i = 0; i < _rows * _cols; ++i)
  {
    if ((*this)[i] > max_val)
    {
      max_val = (*this)[i];
      max_idx = i;
    }
  }
  return max_idx;
}

Matrix operator+ (const Matrix &lhs, const Matrix &rhs)
{
  if (lhs._rows != rhs._rows || lhs._cols != rhs._cols)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  Matrix sum (lhs);
  for (int i = 0; i < lhs._rows; ++i)
  {
    for (int j = 0; j < lhs._cols; ++j)
    {
      sum (i, j) += rhs (i, j);
    }
  }
  return sum;
}

Matrix &Matrix::operator= (const Matrix &rhs)
{
  if (this != &rhs)
  {
    delete[] _matrix;
    _rows = rhs._rows, _cols = rhs._cols;
    _matrix = new float[_rows * _cols];
    std::memcpy (_matrix, rhs._matrix, _rows * _cols * sizeof (float));
  }
  return *this;
}

Matrix &Matrix::operator+= (const Matrix &rhs)
{
  (*this) = (*this) + rhs;
  return *this;
}

Matrix operator* (const Matrix &lhs, const Matrix &rhs)
{
  if (lhs._cols != rhs._rows)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  int rows = lhs._rows, cols = rhs._cols, n = lhs._cols;
  Matrix prod (rows, cols);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      float entry_ij = 0;
      for (int k = 0; k < n; ++k)
      {
        entry_ij += (lhs (i, k) * rhs (k, j));
      }
      prod (i, j) = entry_ij;
    }
  }
  return prod;
}

Matrix Matrix::operator* (float c) const
{
  Matrix mult (_rows, _cols);
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      mult (i, j) = c * (*this) (i, j);
    }
  }
  return mult;
}

Matrix operator* (const float c, Matrix &rhs)
{
  return rhs * c;
}

float &Matrix::operator() (int i, int j)
{
  if (i >= _rows || j >= _cols)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i * _cols + j];
}

float Matrix::operator() (int i, int j) const
{
  if (i >= _rows || j >= _cols)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i * _cols + j];
}

float &Matrix::operator[] (const int i)
{
  if (i >= _rows * _cols)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i];
}

float Matrix::operator[] (int i) const
{
  if (i >= _rows * _cols)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i];
}

std::ostream &operator<< (std::ostream &os, const Matrix &rhs)
{
  for (int i = 0; i < rhs._rows; ++i)
  {
    for (int j = 0; j < rhs._cols; ++j)
    {
      if (rhs (i, j) > 0.1)
      { std::cout << "**"; }
      else
      { std::cout << "  "; }
    }
    std::cout << std::endl;
  }
  return os;
}
std::istream &operator>> (std::istream &is, const Matrix &rhs)
{
  for (int i = 0; i < rhs._rows; ++i)
  {
    for (int j = 0; j < rhs._cols; ++j)
    {
      if (!is.good ())
      {
        throw std::runtime_error (RUNTIME_ERR);
      }
    }
    std::cout << std::endl;
  }
  return is;
}

















