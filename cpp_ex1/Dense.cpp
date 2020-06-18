#include "Dense.h"
#include "Activation.h"
#include "Matrix.h"

/**
 * the constructor of the dense class.
 * @param w a weight matrix
 * @param bias a bias matrix
 * @param actType an enum of activation type.
 */
Dense :: Dense(const Matrix& w, const Matrix& bias, ActivationType actType) : activationType(actType), wMat(w), biasMat(bias)
{
}

/**
 * a const getter, returning an activation according to the activation type.
 * @return an activation according to the activation type.
 */
Activation Dense ::  getActivation() const
{
    Activation act = Activation(activationType);
    return act;
}

/**
 * a const getter, returning the bias matrix
 * @return the bias matrix
 */
Matrix Dense ::  getBias() const
{
    return biasMat;
}

/**
 * a const getter, returning the weight matrix
 * @return the weight matrix
 */
Matrix Dense ::  getWeights() const
{
    return wMat;
}

/**
 * an override method overriding the () operator, operating the dense on the give matrix
 * @param matrix a const matrix to operate on.
 * @return the matrix after the operation.
 */
Matrix Dense::operator()(const Matrix& matrix)
{
    Matrix newMat = wMat * matrix;
    newMat += getBias();
    Activation act = ActivationType (activationType);
    newMat = act(newMat);
    return newMat;
}