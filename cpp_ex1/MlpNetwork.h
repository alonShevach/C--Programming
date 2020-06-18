//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#include "Matrix.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128}, {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};

/**
 * a class representing the mlpnetwork operation.
 */
class MlpNetwork
{
private:

    Dense denseArr[MLP_SIZE];
public:

    /**
     * a constructor for the mlpnetwork class.
     */
    MlpNetwork(Matrix weights[], Matrix biases[]);

    /**
     * an override method for the operator (), activating a mlpnetwork on a given image.
     * @param img a matrix representing the image.
     * @return a digit which the mlp discovered from the image.
     */
    Digit operator()(Matrix &img);
};

#endif // MLPNETWORK_H
