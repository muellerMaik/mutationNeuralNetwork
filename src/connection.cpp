#include "connection.h"

Connection::Connection(
    int _connectionId,
    int _inputId,
    int _outputId,
    float _weight,
    bool _active
):  connectionId(_connectionId),
    inputId(_inputId),
    outputId(_outputId),
    weight(_weight),
    active(_active)
{}

void Connection::activeSwitch(){
    active = !active;
}

void Connection::mutateWeight(float mutationFactor){
    weight *= mutationFactor;
}

int Connection::getInputId() const{
    return inputId;
}

int Connection::getOutputId() const{
    return outputId;
}

float Connection::getWeight() const{
    return weight;
}

bool Connection::getActive() const{
    return active;
}
