#include "neuron.h"
#include "activationFunctions.h"

Neuron::Neuron(
    int _neuronId, 
    int _layer, 
    float _bias, 
    enum kind _neuronKind, 
    enum activation _activationFunc,
    float _value,
    bool _active
):  neuronId(_neuronId),
    layer(_layer),
    bias(_bias),
    neuronKind(_neuronKind),
    activationFunc(_activationFunc),
    value(_value),
    active(_active)
{}

void Neuron::activeSwitch(){
    active = !active;
}

void Neuron::valueUpdate(float inputValue, float inputWeight){
    value += (inputValue * inputWeight);
}

void Neuron::valueSet(float inputValue){
    value = inputValue;
}

void Neuron::addBias(){
    value += bias;
}

void Neuron::resetValue(){
    value = 0.0f;
}

void Neuron::mutateBias(float mutationFactor){
    bias *= mutationFactor;
}

void Neuron::applyActivation(){
    value = activationFunction(value, activationFunc);
}

void Neuron::increaseLayer(){
    layer++;
}

int Neuron::getId() const{
    return neuronId;
}

int Neuron::getLayer() const{
    return layer;
}

float Neuron::getValue() const{
    return value;
}

bool Neuron::getActive() const{
    return active;
}

kind Neuron::getKind() const{
    return neuronKind;
}
