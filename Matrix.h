// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#define INVALID_DIM_ERR "Error: Invalid matrix dimensions."
#define RANGE_ERR "Error: Index out of range."
#define STREAM_ERR "Error: A runtime error occurred."
#include "ostream"

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * Represents a matrix of floating-point numbers.
 */
class Matrix
{
 public:
  /**
   * Constructs a Matrix object with the specified number of rows and
   * columns and sets all entries to 0.
   * @param rows The number of rows in the matrix.
   * @param cols The number of columns in the matrix.
   */
  Matrix (int rows, int cols);

  /**
   * Constructs a Matrix object of size 1x1 and inits the single entry to 0.
   */
  Matrix ();

  /**
   * Copy constructor that creates a new Matrix object with the same values as
   * the given matrix.
   * @param mat The matrix to be copied.
   */
  Matrix (const Matrix &mat);

  /**
   * Destructor for the Matrix object. Deletes the current Matrix object's
   * _matrix field.
   */
  ~Matrix ();

  /**
   * Returns the number of rows in the matrix.
   * @return The number of rows.
   */
  int get_rows () const
  { return _rows; }

  /**
   * Returns the number of columns in the matrix.
   * @return The number of columns.
   */
  int get_cols () const
  { return _cols; }

  /**
   * Returns the Frobenius norm of the current Matrix object.
   * @return the Frobenius norm of the matrix.
   */
  float norm () const;

  /**
   * Returns the index of the maximum element in the current Matrix object.
   * @return The index of the maximum element.
   */
  int argmax () const;

  /**
   * Prints the current Matrix object in a plain row-by-row format.
   */
  void plain_print () const;

  /**
   * Transposes the current Matrix object.
   * @return Reference to the transposed matrix.
   */
  Matrix &transpose ();

  /**
   * Vectorizes the current Matrix object by reshaping it into a single column.
   * @return Reference to the vectorized matrix.
   */
  Matrix &vectorize ();

  /**
   * Calculates and returns the sum of all elements in the current Matrix
   * object.
   * @return The sum of all elements in the matrix.
   */
  float sum () const;

  /**
   * Performs element-wise multiplication between the current Matrix object and
   * another Matrix object (aka Hadamard product).
   * @param mat The matrix to perform element-wise multiplication with.
   * @return The resulting matrix after element-wise multiplication.
   */
  Matrix dot (const Matrix &mat) const;

  /**
 * Overloaded addition operator for adding two matrices.
 * @param lhs The left-hand side matrix.
 * @param rhs The right-hand side matrix.
 * @return The sum of the two matrices.
 */
  friend Matrix operator+ (const Matrix &lhs, const Matrix &rhs);

  /**
   * Overloaded assignment operator for assigning the values of some matrix to
   * the current Matrix object.
   * @param rhs The matrix to be assigned.
   * @return Reference to the assigned matrix.
   */
  Matrix &operator= (const Matrix &rhs);

  /**
   * Overloaded compound assignment operator for adding a matrix to the current
   * Matrix object.
   * @param rhs The matrix to be added.
   * @return Reference to the modified matrix after addition.
   */
  Matrix &operator+= (const Matrix &rhs);

  /**
   * Overloaded multiplication operator for matrix multiplication.
   * @param lhs The left-hand side matrix.
   * @param rhs The right-hand side matrix.
   * @return The product of the two matrices.
   */
  friend Matrix operator* (const Matrix &lhs, const Matrix &rhs);

  /**
   * Overloaded multiplication operator for scalar multiplication from the
   * right-hand side of the current Matrix object.
   * @param c The scalar value.
   * @return The resulting matrix after scalar multiplication.
   */
  Matrix operator* (float c) const;

  /**
   * Overloaded multiplication operator for scalar multiplication from the
   * left-hand side of a matrix.
   * @param c The scalar value.
   * @param rhs The matrix.
   * @return The resulting matrix after scalar multiplication.
   */
  friend Matrix operator* (float c, Matrix &rhs);

  /**
   * Overloaded function call operator for accessing and modifying the
   * current Matrix object's elements.
   * @param i The row index.
   * @param j The column index.
   * @return Reference to the matrix element at the specified indices.
   */
  float &operator() (int i, int j);

  /**
   * Overloaded function call operator for accessing the current Matrix
   * object's elements.
   * @param i The row index.
   * @param j The column index.
   * @return The value of the matrix element at the specified indices.
   */
  float operator() (int i, int j) const;

  /**
   * Overloaded subscript operator for accessing and modifying individual
   * elements in the current Matrix object.
   * @param i The linear index of the element.
   * @return A reference to the element at the specified index.
   */
  float &operator[] (int i);

  /**
   * Overloaded subscript operator for accessing individual elements in the
   * current Matrix object.
   * @param i The linear index of the element.
   * @return A reference to the element at the specified index.
   */
  float operator[] (int i) const;

  /**
   * Overloaded output stream operator for printing a matrix.
   * @param os The output stream.
   * @param rhs The matrix to be printed.
   * @return Reference to the output stream.
   */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &rhs);

  /**
   * Overloaded input stream operator for reading matrix elements from an
   * input stream.
   * @param is The input stream.
   * @param rhs The matrix to be filled with input values.
   * @return Reference to the input stream.
   */
  friend std::istream &operator>> (std::istream &is, Matrix &rhs);

 private:
  int _rows, _cols;
  float *_matrix;
};
#endif //MATRIX_H