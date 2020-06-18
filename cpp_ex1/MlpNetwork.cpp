#include "Matrix.h"
#include "MlpNetwork.h"
#include "Digit.h"

/**
 * a constructor for the mlpnetwork class.
 */
MlpNetwork :: MlpNetwork(Matrix weights[], Matrix biases[]): denseArr
{
    Dense(weights[0], biases[0], Relu), Dense(weights[1], biases[1], Relu),
    Dense(weights[2], biases[2], Relu), Dense(weights[3], biases[3], Softmax)
}

{
}

/**
 * an override method for the operator (), activating a mlpnetwork on a given image.
 * @param img a matrix representing the image.
 * @return a digit which the mlp discovered from the image.
 */
Digit MlpNetwork :: operator()(Matrix &img)
{
    Matrix r1 = img;
    for (const auto & i : denseArr)
    {
        // maybe del.
        r1 = i.getActivation()(((i.getWeights() * r1) + i.getBias()));
    }
    int index = 0;
    for (int i = 0; i < r1.getRows(); ++i)
    {
        if (r1[i] > r1[index])
        {
            index = i;
        }
    }
    Digit num = Digit();
    num.value = index;
    num.probability = r1[index];
    return num;
}
