//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

class MlpNetwork
{
 public:
  /**
   * Constructs an instance of an MLP network.
   * @param weights An array of (4) weight matrices for each layer.
   * @param biases An array of (4) bias matrices for each layer.
   */
  MlpNetwork (const Matrix weights[], const Matrix biases[]);

  /**
   * Applies the MLP network to the input matrix and returns the predicted
   * digit
   *
   * @param input The input matrix.
   * @return The predicted digit.
   */
  digit operator() (Matrix &input) const;

 private:
  Dense _in, _h1, _h2, _out; /** All 4 layers of the network. */
};

#endif // MLPNETWORK_H