#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include "neuron.h"
#include "connection.h"
#include "randomGenerator.h"

class Network{
    short inputSize;
    short outputSize;
    short mutationChance;
    
    std::vector<Neuron> neurons;
    std::vector<Connection> connections;
    
    std::vector<float> inputs;
    std::vector<float> outputs;

    int maxLayer = 1;
    float fitness = 0;
    void createNetwork();
    void addConnection(connectionSetting setting, int leftId=0, int rightId=0);
    void addNeuron();
    void ensureStructuralIntegrity();
    void feedForward();
    public:
    Network(
        short _inputSize, 
        short _outputSize, 
        short _mutationChance
    );
    void runNetwork(std::vector<float> input);
    void mutateNetwork();
    void updateFitness(float fit);
    float getFitness();
    const std::vector<float>& getOutput() const;
    bool operator<(const Network& other) const;
};
#endif
