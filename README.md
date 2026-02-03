# mutationNeuralNetwork
Use Pybind11 and CMake to create a .so you can Import.
Has the following functions you can use in python :
    m.def("setupNetwork", &setupNetwork, "Inputs : int numberNetworks, int numberInputs, int numberOutputs, int mutationChance");
    m.def("feedForward", &feedForward, py::call_guard<py::gil_scoped_release>(), "Inputs : vector<float>& inputs");
    m.def("mutateNetwork", &mutateNet, "Mutates Network, Inputs: vector<float>");
    m.def("getOutputs", &getOutputs, "Outputs : vector<vector<float>>");

You just get a 2D Vector that includes the Output of each Network.
Call setupNetwork only once at the beginning and define the Amounts of Networks, the Input/Output Size and mutationChance.
feedForward will only take a 1D vector of floats. So this is not usefull for anything with nD input Vectors.
mutationChance SHOULD be a number between 1-100 and represents how likely it is to Mutate.
mutateNetwork also needs the Fitness of you Agent to determin the what Networks to use as the Base for further Evolution.
However the mutationChance is dynamic and get's lower the more the Network mutates, if mutationChance is 10 at first the chance is 10/100 then 10/101.
This is a Softcap on the Complexity of the Network.
getOutputs returns a 2D vector. with the size [numberNetworks][numberOutputs] so each Network gives you the Output you want.
