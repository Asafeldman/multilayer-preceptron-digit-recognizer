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
  _rows = rows, _cols = cols, _matrix = new float[rows * cols];
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      (*this) (i, j) = DEF_VAL;
    }
  }
}

Matrix::Matrix () : _rows (DEF_ROWS), _cols (DEF_COLS),
                    _matrix (new float[DEF_DIM]{DEF_VAL})
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
  if (_rows != mat._rows || _cols != mat._cols)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
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
  Matrix temp (_cols, _rows);
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
    {
      temp (j, i) = (*this) (i, j);
    }
  }
  delete[] _matrix;
  _rows = temp._rows, _cols = temp._cols;
  _matrix = new float[_rows * _cols];
  for (int i = 0; i < _rows; ++i)
  {
    for (int j = 0; j < _cols; ++j)
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
  if (_rows != rhs._rows || _cols != rhs._cols)
  {
    throw std::length_error (INVALID_DIM_ERR);
  }
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
  if (i >= _rows || i < 0 || j >= _cols || j < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i * _cols + j];
}

float Matrix::operator() (int i, int j) const
{
  if (i >= _rows || i < 0 || j >= _cols || j < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i * _cols + j];
}

float &Matrix::operator[] (const int i)
{
  if (i >= _rows * _cols || i < 0)
  {
    throw std::length_error (RANGE_ERR);
  }
  return _matrix[i];
}

float Matrix::operator[] (int i) const
{
  if (i >= _rows * _cols || i < 0)
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
  for (int i = 0; i < rhs._rows; ++i)
  {
    for (int j = 0; j < rhs._cols; ++j)
    {
      if (rhs (i, j) > MIN_VAL)
      { os << "**"; }
      else
      { os << "  "; }
    }
    os << std::endl;
  }
  return os;
}

std::istream &operator>> (std::istream &is, Matrix &rhs)
{

  if (!is)
  {
    throw std::runtime_error (STREAM_ERR);
  }
  is.seekg (0, std::istream::end);
  long file_size = is.tellg ();
  is.seekg (0, std::istream::beg);
  if (file_size < static_cast<long>(sizeof (float)) * rhs._rows * rhs._cols)
  {
    throw std::length_error (STREAM_ERR);
  }
  char *buffer = new char[file_size];
  is.read (buffer, file_size);

  auto *values = (float *) buffer;
  for (int i = 0; i < rhs._rows * rhs._cols; i++)
  {
    rhs[i] = values[i];
  }
  delete[] buffer;
  return is;
}