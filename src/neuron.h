#ifndef NEURON_H
#define NEURON_H
#include "enum.h"

class Neuron{
    int neuronId;
    int layer;
    float bias;
    enum kind neuronKind;
    enum activation activationFunc;
    float value;
    bool active;
    
    public:
    Neuron(
        int _neuronId, 
        int _layer, 
        float _bias, 
        enum kind _neuronKind = INPUT, 
        enum activation _activationFunc = LINEAR, 
        float _value = 0.0f,
        bool _active = true
    );
    
    void activeSwitch();
    void valueUpdate(float inputValue, float inputWeight);
    void addBias();
    void resetValue();
    void valueSet(float inputValue);
    void mutateBias(float mutationFactor);
    void increaseLayer();
    void applyActivation();
    int getId() const;
    int getLayer() const;
    float getValue() const;
    bool getActive() const;
    kind getKind() const;
};
#endif
