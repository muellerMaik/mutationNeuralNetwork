#include <iostream>
#include <vector>
#include <algorithm> 
#include <execution>
#include "network.h"
#include "main.h"
#include "randomGenerator.h"
using namespace std;

vector<Network> networkVector;

void setupNetwork(int numberNetworks, int numberInputs, int numberOutputs, int mutationChance){
    for(size_t i = 0; i < numberNetworks; i++){        
        networkVector.push_back(Network(numberInputs, numberOutputs, mutationChance));
    }    
}
/*
void feedForward(vector<float>& inputs) {
    for(size_t i = 0; i < networkVector.size(); i++){
        networkVector[i].runNetwork(inputs);
    }
} 
*/

void feedForward(vector<float>& inputs) {
    for_each(
        execution::par,
        networkVector.begin(),
        networkVector.end(),
        [&](Network& net){
            net.runNetwork(inputs);
        }
    );
} 

void mutateNet(vector<float>& fitness){
    for(size_t i = 0; i < networkVector.size(); i++){
        networkVector[i].updateFitness(fitness[i]);
    }
    
    sort(networkVector.rbegin(), networkVector.rend());
    int elitism = int(networkVector.size()*0.1);
    float totalFitness = 0;   
    vector<float> eliteFitness; 
    for(size_t i = 0; i < elitism; i++){
        if(networkVector[i].getFitness() > 0.0f){
            totalFitness += networkVector[i].getFitness();
            eliteFitness.push_back(networkVector[i].getFitness());
        }
    }

    vector<float> cumulative;
    float sum = 0;
    for(auto f : eliteFitness){
        sum += f;
        cumulative.push_back(sum);
    }

    

    for(size_t i = elitism; i < networkVector.size(); i++){
        float r = RNG::randomElite() * sum;
        for(size_t j = 0; j < cumulative.size(); j++){
            if(r <= cumulative[j]){
                networkVector[i] = networkVector[j];
                break;
            }
        }
        networkVector[i].mutateNetwork();
    }
    eliteFitness.clear();
}

vector<vector<float>> getOutputs(){
    vector<vector<float>> outputVector;
    for(size_t i = 0; i < networkVector.size(); i++){
        outputVector.push_back(networkVector[i].getOutput());
    }
    return outputVector;
}
