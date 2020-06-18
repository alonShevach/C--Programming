#include <math.h>
#include <iostream>
#include "Activation.h"
#include "Matrix.h"

/**
 * the constructor of the Activation class.
 * @param actType Enum of Activationtype.
 */
Activation :: Activation(ActivationType actType) : activationType(actType)
{
}

/**
 * a getter method for the Actiovation's activation type.
 * @return the activation type.
 */
ActivationType Activation ::  getActivationType()
{
    return activationType;
}

/**
 * override method for the () operator, activating the activation's activation type on the given matrix
 * @param input a given matrix to operate the activation on.
 * @return the matrix after the operation.
 */
Matrix Activation :: operator()(Matrix input)
{
    if (activationType == Relu)
    {
        Matrix Mat = Matrix(input.getRows(), input.getCols());
        for (int i = 0; i < input.getRows()*input.getCols(); ++i)
        {
            if (input[i] > 0)
            {
                Mat[i] = input[i];
            }
            else
            {
                Mat[i] = 0;
            }
        }
        return Mat;
    }
    else if (activationType == Softmax)
    {
        float sum = 0;
        float exp = 0;
        for (int i = 0; i< input.getRows(); ++i)
        {
            exp = std :: exp(input[i]);
            input[i] = exp;
            sum += exp;
        }
        float c = 1 / sum;
        return c*input;
    }
    else
    {
        std::cerr << "Error: bad activation type" << std::endl;
        exit(EXIT_FAILURE);
    }
}

