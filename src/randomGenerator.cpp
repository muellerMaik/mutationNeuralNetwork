#include "randomGenerator.h"

namespace RNG {

    // Random engine
    static std::mt19937 gen(std::random_device{}());
    
    

    float randomElite()
    {
        static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen);
    }

    float createRandomBias()
    {
        static std::uniform_real_distribution<float> dis(-2.0f, 2.0f);
        return dis(gen);
    }

    float createRandomWeight()
    {
        static std::uniform_real_distribution<float> dis(-1.5f, 1.5f);
        return dis(gen);
    }
    float mutationFactor(){
        static std::uniform_real_distribution<float> dis(0.5f, 1.5f);
        return dis(gen);
    }

    int mutate(int limit, int min)
    {
        static std::uniform_int_distribution<int> dis(0, (limit+min));
        return dis(gen);
    }

    int pickRandomActivationFunction()
    {
        static std::uniform_int_distribution<int> dis(0, 3);
        return dis(gen);
    }

    int pickRandomLayer(int maxLayer)
    {
        if (maxLayer < 1) return 0;
        std::uniform_int_distribution<int> dis(1, maxLayer);
        return dis(gen);
    }

    int pickRandomVectorIndex(int vectorSize)
    {
        if (vectorSize < 1) return 0;
        std::uniform_int_distribution<int> dis(0, vectorSize - 1);
        return dis(gen);
    }

} // namespace RNG

bool inVector(std::vector<int> inputVector, int searchValue){
    for (size_t i = 0; i < inputVector.size(); i++){
        if(inputVector[i] == searchValue){
            return true;
        }
    }
    return false;
}
