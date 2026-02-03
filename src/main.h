#ifndef MAIN_H
#define MAIN_H

#include <vector>

void setupNetwork(int numberNetworks, int numberInputs, int numberOutputs, int mutationChance);
void feedForward(std::vector<float>& inputs);
void mutateNet(std::vector<float>& fitness);
std::vector<std::vector<float>> getOutputs();

#endif

