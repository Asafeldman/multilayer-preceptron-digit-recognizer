// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#define INVALID_DIM_ERR "Error: Invalid matrix dimensions."
#define RANGE_ERR "Error: Index out of range."
#define RUNTIME_ERR "Error: Invalid input."
#include "ostream"

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

class Matrix
{
 public:
  Matrix (int rows, int cols);
  Matrix ();
  Matrix (const Matrix &mat);
  ~Matrix ();
  int get_rows () const { return _rows; }
  int get_cols () const { return _cols; }
  float norm () const;
  int argmax () const;
  void plain_print () const;
  Matrix &transpose ();
  Matrix &vectorize ();
  float sum () const;
  Matrix dot (const Matrix &mat) const;

  friend Matrix operator+ (const Matrix &lhs, const Matrix &rhs);
  Matrix &operator= (const Matrix &rhs);
  Matrix &operator+= (const Matrix &rhs);
  friend Matrix operator* (const Matrix &lhs, const Matrix &rhs);
  Matrix operator* (float c) const;
  friend Matrix operator* (float c, Matrix &rhs);
  float &operator() (int i, int j);
  float operator() (int i, int j) const;
  float &operator[] (int i);
  float operator[] (int i) const;
  friend std::ostream &operator<< (std::ostream &os, const Matrix &rhs);
  friend std::istream &operator>> (std::istream &is, const Matrix &rhs);

 private:
  int _rows, _cols;
  float *_matrix;
};
#endif //MATRIX_H