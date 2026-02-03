#include <vector>
#include <cmath>
#include "activationFunctions.h"
#include "network.h"

int inovationNr = 0;


Network::Network(
    short _inputSize, 
    short _outputSize, 
    short _mutationChance
):  inputSize(_inputSize),
    outputSize(_outputSize),
    mutationChance(_mutationChance)
{
    createNetwork();
}

void Network::createNetwork(){
    for(size_t i = 0; i < (inputSize + outputSize); i++){
        if (i < inputSize){
            neurons.push_back(Neuron(i, 0, 0));
        }
        else{
            neurons.push_back(Neuron(i, maxLayer, RNG::createRandomBias(), OUTPUT));
        }
    }
    
    for(size_t i = 0; i < inputSize; i++){
        for(size_t j = outputSize; j < neurons.size(); j++){
            inovationNr++;
            connections.push_back(Connection(inovationNr, neurons[i].getId(), neurons[j].getId(), RNG::createRandomWeight()));
        }
    }
}

void Network::addConnection(connectionSetting setting, int leftId, int rightId){
    std::vector<std::vector<int>> legalConnections; 
    int connectionPick;

    switch(setting){
        case ALLRANDOM: {
            for(size_t inputNeuron = 0; inputNeuron < neurons.size(); inputNeuron++){
                for(size_t outputNeuron = 0; outputNeuron < neurons.size(); outputNeuron++){
                    if(neurons[inputNeuron].getLayer() < neurons[outputNeuron].getLayer()){
                        legalConnections.push_back({neurons[inputNeuron].getId(), neurons[outputNeuron].getId()});
                    }
                } 
            }

            connectionPick = RNG::pickRandomVectorIndex(legalConnections.size());

            inovationNr++;
            connections.push_back(Connection(inovationNr, legalConnections[connectionPick][0], legalConnections[connectionPick][1], RNG::createRandomWeight()));
            break;
        }
        case LEFTRANDOM: {
            for(size_t outputNeuron = 0; outputNeuron < neurons.size(); outputNeuron++){
                if(neurons[leftId].getLayer() < neurons[outputNeuron].getLayer()){
                    legalConnections.push_back({neurons[leftId].getId(), neurons[outputNeuron].getId()});
                } 
            }

            connectionPick = RNG::pickRandomVectorIndex(legalConnections.size());

            inovationNr++;
            connections.push_back(Connection(inovationNr, legalConnections[connectionPick][0], legalConnections[connectionPick][1], RNG::createRandomWeight()));
            break;
        }
        case RIGHTRANDOM: {
            for(size_t inputNeuron = 0; inputNeuron < neurons.size(); inputNeuron++){
                if(neurons[inputNeuron].getLayer() < neurons[rightId].getLayer()){
                    legalConnections.push_back({neurons[inputNeuron].getId(), neurons[rightId].getId()});
                } 
            }

            connectionPick = RNG::pickRandomVectorIndex(legalConnections.size());

            inovationNr++;
            connections.push_back(Connection(inovationNr, legalConnections[connectionPick][0], legalConnections[connectionPick][1], RNG::createRandomWeight()));
            break;
        }
        case NONERANDOM: {
            if(neurons[leftId].getLayer() >= neurons[rightId].getLayer()){
                break;
            }
            inovationNr++;
            connections.push_back(Connection(inovationNr, neurons[leftId].getId(), neurons[rightId].getId(), RNG::createRandomWeight()));
            break;
        }
    }
}

void Network::addNeuron(){
    int newLayer = RNG::pickRandomLayer(maxLayer);
    int outputCounter = 0;    
    while(newLayer == maxLayer && outputCounter < neurons.size()){
        if(neurons[outputCounter].getLayer() == newLayer){
            neurons[outputCounter].increaseLayer();
        }
        outputCounter++;
    }
    if (newLayer == maxLayer){
        maxLayer++;
    }
    bool pickedConnection = false;
    int tempId;
    short count = 0;
    do{
        
        tempId = RNG::pickRandomVectorIndex(connections.size());
        if(neurons[connections[tempId].getInputId()].getLayer() < newLayer && neurons[connections[tempId].getOutputId()].getLayer() > newLayer && connections[tempId].getActive()){
            pickedConnection = true;
            connections.erase(connections.begin()+tempId);
        }
        count++;
    }while(!pickedConnection && count < 15);
    if(pickedConnection){
        neurons.push_back(Neuron(neurons.size(), newLayer, RNG::createRandomBias(), HIDDEN, static_cast<activation>(RNG::pickRandomActivationFunction())));
        addConnection(NONERANDOM, neurons[connections[tempId].getInputId()].getId(), neurons.size()-1);
        addConnection(NONERANDOM, neurons.size()-1, neurons[connections[tempId].getOutputId()].getId());
    }
    else{
        addConnection(ALLRANDOM);
    }
    
}

void Network::ensureStructuralIntegrity(){
    std::vector<int> usedInput;
    std::vector<int> usedOutput;
    for(size_t i = 0; i < connections.size(); i++){
        if(!inVector(usedInput, connections[i].getInputId())){
            usedInput.push_back(connections[i].getInputId());
        }
        if(!inVector(usedOutput, connections[i].getOutputId())){
            usedOutput.push_back(connections[i].getOutputId());
        }
    }

    std::vector<int> possibleInput;
    std::vector<int> possibleOutput;    
    
    for (size_t i = 0; i < neurons.size(); i++){
        if(neurons[i].getKind() == HIDDEN){
            possibleInput.push_back(neurons[i].getId());
            possibleOutput.push_back(neurons[i].getId());
        }
        else if(neurons[i].getKind() == INPUT){
            possibleInput.push_back(neurons[i].getId());
        }
        else{
            possibleOutput.push_back(neurons[i].getId());
        }
    }
    if(!(usedInput.size() == possibleInput.size())){
        for(size_t i = 0; i < possibleInput.size(); i++){
            if(!(inVector(usedInput, possibleInput[i]))){
                addConnection(LEFTRANDOM, possibleInput[i]);
            }
        }        
    }
    if(!(usedOutput.size() == possibleOutput.size())){
        for(size_t i = 0; i < possibleOutput.size(); i++){
            if(!(inVector(usedOutput, possibleOutput[i]))){
                addConnection(RIGHTRANDOM, 0, possibleOutput[i]);
            }
        }
    }
}

void Network::feedForward(){
    short inputCount = 0;
    for (int i = 0; i < neurons.size(); i++) {
        if (neurons[i].getKind() == INPUT){
            neurons[i].valueSet(inputs[inputCount]);
            inputCount++;
        }

        if (inputs.size() == inputCount){
            break;
        }
    }

    short layerCounter = 0;
    while (layerCounter < maxLayer){
        for (int i = 0; i < connections.size(); i++){
            if (neurons[connections[i].getInputId()].getActive() && neurons[connections[i].getOutputId()].getActive() && neurons[connections[i].getInputId()].getLayer() == layerCounter){
                neurons[connections[i].getOutputId()].valueUpdate(neurons[connections[i].getInputId()].getValue(), connections[i].getWeight());
            }
        }

        for (int i = 0; i < neurons.size(); i++){
            if (neurons[i].getLayer() == layerCounter && neurons[i].getActive()){
                neurons[i].addBias();
                neurons[i].applyActivation();
            }
        }
            
        layerCounter++;
    }
    outputs.clear();
    short outputCount = 0;
    for (int i = 0; i < neurons.size(); i++){
        if (neurons[i].getKind() == OUTPUT){
            outputs.push_back(neurons[i].getValue());
            outputCount++;
        }
        neurons[i].resetValue();
    }
    outputs = softmax(outputs);
}

void Network::runNetwork(std::vector<float> input){
    inputs.clear();
    inputs = input;
    feedForward();
}

void Network::mutateNetwork(){
    for (size_t i = 0; i < neurons.size(); i++){
        if(mutationChance > RNG::mutate(neurons.size())){
            neurons[i].mutateBias(RNG::mutationFactor());
        }
    }

    for (size_t i = 0; i < connections.size(); i++){
        if(mutationChance > RNG::mutate(connections.size())){
            connections[i].mutateWeight(RNG::mutationFactor());
        }
    }

    for (size_t i = 0; i < mutationChance; i++){
        if(mutationChance > RNG::mutate(neurons.size())){
            addNeuron();
        }
        if(mutationChance > RNG::mutate(connections.size())){
            addConnection(ALLRANDOM);
        }
    }
    ensureStructuralIntegrity();
}

void Network::updateFitness(float fit){
    fitness = fit;
}

float Network::getFitness() {
    return fitness;
}

const std::vector<float>& Network::getOutput() const {
    return outputs;
}

bool Network::operator<(const Network& other) const {
    return fitness < other.fitness;
}


