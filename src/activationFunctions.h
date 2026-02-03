#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H
#include <math.h>
#include <cmath>
#include "enum.h"
#include <vector>
inline float activationFunction(float value, activation activationFunc){
    //Linear    
    if (activationFunc == LINEAR){
        return value;
    }
    //ReLu
    if (activationFunc == RELU && value > 0){
        return value;
    }
    else if(activationFunc == RELU && value < 0){
        return 0.0f;
    }
    //tanh
    if (activationFunc == TANH){
        return tanhf(value);
    }
    //sigmoid
    if (activationFunc == SIGMOID){
        return (1 / (1 + expf(-value)));
    }
    return value;
}

inline std::vector<float> softmax(std::vector<float> output){
    float sumOutput = 0;
    float maxValue = output[0];

    for (int i = 1; i < output.size(); i++)
    {
        if (maxValue < output[i]){
            maxValue = output[i];
        }
    }

    for (int i = 0; i < output.size(); i++)
    {
        output[i] = expf(output[i] - maxValue);
        sumOutput += output[i];
    }

    for (int i = 0; i < output.size(); i++)
    {
        output[i] /= sumOutput;
    }

    return output;   
}
#endif
