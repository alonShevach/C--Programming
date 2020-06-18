#include "Activation.h"

#ifndef CPP1_DENSE_H
#define CPP1_DENSE_H

/**
 * a class representing a dense in the mlpnetwork operation.
 */
class Dense
{
private:
    ActivationType activationType;
    Matrix wMat, biasMat;
public:

    /**
     * the constructor of the dense class.
     * @param w a weight matrix
     * @param bias a bias matrix
     * @param actType an enum of activation type.
     */
    Dense(const Matrix& w, const Matrix& bias, ActivationType actType);

    /**
     * a const getter, returning an activation according to the activation type.
     * @return an activation according to the activation type.
     */
    Activation getActivation() const;

    /**
     * a const getter, returning the bias matrix
     * @return the bias matrix
     */
    Matrix getBias() const;

    /**
     * a const getter, returning the weight matrix
     * @return the weight matrix
     */
    Matrix getWeights() const;

    /**
     * an override method overriding the () operator, operating the dense on the give matrix
     * @param matrix a const matrix to operate on.
     * @return the matrix after the operation.
     */
    Matrix operator()(const Matrix& matrix);
};

#endif //CPP1_DENSE_H
