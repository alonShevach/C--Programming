//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * a class representing an activation in the dense.
 */
class Activation
{
private:
    ActivationType activationType;
public:

    /**
     * the constructor of the Activation class.
     * @param actType Enum of Activationtype.
     */
    Activation(ActivationType actType);

    /**
     * a getter method for the Actiovation's activation type.
     * @return the activation type.
     */
    ActivationType getActivationType();

    /**
     * override method for the () operator, activating the activation's activation type on the given matrix
     * @param input a given matrix to operate the activation on.
     * @return the matrix after the operation.
     */
    Matrix operator()(Matrix input);
};

#endif //ACTIVATION_H
