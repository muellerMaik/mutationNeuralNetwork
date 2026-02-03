#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random>

namespace RNG {
    float randomElite();
    float createRandomBias();
    float createRandomWeight();
    float mutationFactor();
    int mutate(int limit=0, int min=100);
    int pickRandomActivationFunction();
    int pickRandomLayer(int maxLayer);
    int pickRandomVectorIndex(int vectorSize);
}

bool inVector(std::vector<int> inputVector, int searchValue);

#endif
