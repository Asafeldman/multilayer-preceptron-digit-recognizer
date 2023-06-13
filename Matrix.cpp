#include "Matrix.h"
#include "stdexcept"
#include "iostream"
#include "cmath"
#include "cstring"
#define DEF_ROWS 1
#define DEF_COLS 1
#define DEF_DIM 1
#define DEF_VAL 0
#define MIN_VAL 0.1

Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  _dims.rows = rows, _dims.cols = cols, _matrix = new float[rows * cols];
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      (*this) (i, j) = DEF_VAL;
    }
  }
}

Matrix::Matrix () : _dims ({DEF_ROWS, DEF_COLS}),
                    _matrix (new float[DEF_DIM]{DEF_VAL})
{}

Matrix::Matrix (const Matrix &mat)
{
  _dims.rows = mat._dims.rows, _dims.cols = mat._dims.cols;
  _matrix = new float[_dims.rows * _dims.cols];
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
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
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      std::cout << (*this) (i, j) << " ";
    }
    std::cout << std::endl;
  }
}

float Matrix::norm () const
{
  float sum = 0;
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      sum += ((*this) (i, j) * (*this) (i, j));
    }
  }
  return std::sqrt (sum);
}

Matrix Matrix::dot (const Matrix &mat) const
{
  if (_dims.rows != mat._dims.rows || _dims.cols != mat._dims.cols)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  Matrix prod (*this);
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      prod (i, j) *= mat (i, j);
    }
  }
  return prod;
}

Matrix &Matrix::vectorize ()
{
  _dims.rows *= _dims.cols;
  _dims.cols = 1;
  return *this;
}

float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      sum += (*this) (i, j);
    }
  }
  return sum;
}

Matrix &Matrix::transpose ()
{
  Matrix temp (_dims.cols, _dims.rows);
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      temp (j, i) = (*this) (i, j);
    }
  }
  delete[] _matrix;
  _dims.rows = temp._dims.rows, _dims.cols = temp._dims.cols;
  _matrix = new float[_dims.rows * _dims.cols];
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
    {
      (*this) (i, j) = temp (i, j);
    }
  }
  return *this;
}

int Matrix::argmax () const
{
  int max_idx = 0;
  float max_val = _matrix[max_idx];
  for (int i = 0; i < _dims.rows * _dims.cols; ++i)
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
  if (lhs._dims.rows != rhs._dims.rows || lhs._dims.cols != rhs._dims.cols)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  Matrix sum (lhs);
  for (int i = 0; i < lhs._dims.rows; ++i)
  {
    for (int j = 0; j < lhs._dims.cols; ++j)
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
    _dims.rows = rhs._dims.rows, _dims.cols = rhs._dims.cols;
    _matrix = new float[_dims.rows * _dims.cols];
    std::memcpy (_matrix, rhs._matrix, _dims.rows * _dims.cols * sizeof
        (float));
  }
  return *this;
}

Matrix &Matrix::operator+= (const Matrix &rhs)
{
  if (_dims.rows != rhs._dims.rows || _dims.cols != rhs._dims.cols)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  (*this) = (*this) + rhs;
  return *this;
}

Matrix operator* (const Matrix &lhs, const Matrix &rhs)
{
  if (lhs._dims.cols != rhs._dims.rows)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
  int rows = lhs._dims.rows, cols = rhs._dims.cols, n = lhs._dims.cols;
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
  Matrix mult (_dims.rows, _dims.cols);
  for (int i = 0; i < _dims.rows; ++i)
  {
    for (int j = 0; j < _dims.cols; ++j)
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
  if (i >= _dims.rows || i < 0 || j >= _dims.cols || j < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i * _dims.cols + j];
}

float Matrix::operator() (int i, int j) const
{
  if (i >= _dims.rows || i < 0 || j >= _dims.cols || j < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i * _dims.cols + j];
}

float &Matrix::operator[] (const int i)
{
  if (i >= _dims.rows * _dims.cols || i < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i];
}

float Matrix::operator[] (int i) const
{
  if (i >= _dims.rows * _dims.cols || i < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i];
}

std::ostream &operator<< (std::ostream &os, const Matrix &rhs)
{
  if (!os)
  {
    throw std::runtime_error (STREAM_ERR);
  }
  for (int i = 0; i < rhs._dims.rows; ++i)
  {
    for (int j = 0; j < rhs._dims.cols; ++j)
    {
      os << (rhs (i, j) > MIN_VAL ? "**" : "  ");
    }
    os << std::endl;
  }
  return os;
}

std::istream &operator>> (std::istream &is, Matrix &rhs)
{
  for (int i = 0; i < rhs._dims.rows; ++i)
  {
    for (int j = 0; j < rhs._dims.cols; ++j)
    {
      if (!is.read (reinterpret_cast<char *>(&rhs (i, j)), sizeof (float)))
      {
        throw std::runtime_error (STREAM_ERR);
      }
    }
  }
  return is;
}
