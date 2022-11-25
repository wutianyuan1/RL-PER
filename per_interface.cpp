#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include "priority_mem.h"

namespace py = pybind11;

PYBIND11_MODULE(per_memory, m) {
    m.doc() = "Fast Prioritized Experience Replay Mmeory";
    py::class_<PriorityMemory<py::tuple>>(m, "PriorityMemory")
        .def(py::init<size_t>())
        .def("add", &PriorityMemory<py::tuple>::add)
        .def("sample", &PriorityMemory<py::tuple>::sample)
        .def("update", &PriorityMemory<py::tuple>::update)
        .def("__repr__",
        [](const PriorityMemory<py::tuple> &mem) {
            return "<per_memory.PriorityMemory named '" + std::to_string(mem.get_capacity()) + "'>";
        });
}
