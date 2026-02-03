#ifndef CONNECTION_H
#define CONNECTION_H

class Connection{
    int connectionId;
    int inputId;
    int outputId;
    float weight;
    bool active;
    
    public:
    Connection(
        int _connectionId,
        int _inputId,
        int _outputId,
        float _weight,
        bool _active=true
    );
    
    void activeSwitch();
    void mutateWeight(float mutationFactor);
    int getInputId() const;
    int getOutputId() const;
    float getWeight() const;
    bool getActive() const;
};
#endif
