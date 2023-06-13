#include "MlpNetwork.h"
#include "Matrix.h"

MlpNetwork::MlpNetwork (const Matrix weights[], const Matrix biases[]) :
    _in (weights[0], biases[0], relu), _h1 (weights[1], biases[1], relu),
    _h2 (weights[2], biases[2], relu), _out (weights[3], biases[3], softmax)
{}

digit MlpNetwork::operator() (Matrix &input) const
{
  input.vectorize ();
  Matrix r1 = _in (input);
  Matrix r2 = _h1 (r1);
  Matrix r3 = _h2 (r2);
  Matrix r4 = _out (r3);
  int index = r4.argmax ();
  return digit{static_cast<unsigned int>(index), r4[index]};
}
