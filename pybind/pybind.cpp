#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "main.h"

namespace py = pybind11;

PYBIND11_MODULE(mmNEAT, m, py::mod_gil_not_used()) {
    m.doc() = "mmNEAT neural network module";

    m.def("setupNetwork", &setupNetwork, "Inputs : int numberNetworks, int numberInputs, int numberOutputs, int mutationChance");
    m.def("feedForward", &feedForward, py::call_guard<py::gil_scoped_release>(), "Inputs : vector<float>& inputs");
    m.def("mutateNetwork", &mutateNet, "Mutates Network, Inputs: vector<float>");
    m.def("getOutputs", &getOutputs, "Outputs : vector<vector<float>>");
}

