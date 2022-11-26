#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <omp.h>

#include "priority_mem.h"
#include "linear_schedule.h"

namespace py = pybind11;

PYBIND11_MODULE(per_memory, m) {
    m.doc() = "Fast Prioritized Experience Replay Mmeory";
    py::class_<PrioritizedMemory<py::tuple>>(m, "PrioritizedMemory")
        .def(py::init<size_t, double, LinearSchedule, double>(), "Constructor of PrioritizedMemory")
        .def("add", &PrioritizedMemory<py::tuple>::add, "add a sample to the memory")
        .def("sample", &PrioritizedMemory<py::tuple>::sample, "sample a batch of samples")
        .def("update", &PrioritizedMemory<py::tuple>::update, "update priorities")
        .def("get_capacity", &PrioritizedMemory<py::tuple>::get_capacity, "gets the capacity of memory")
        .def("__repr__",
            [](const PrioritizedMemory<py::tuple> &mem) {
            return "<per_memory.PrioritizedMemory capacity=" + std::to_string(mem.get_capacity()) + ">";
        });
    
    py::class_<LinearSchedule>(m, "LinearSchedule")
        .def(py::init<int, double, double>())
        .def("next", &LinearSchedule::next, "get the next schedule value")
        .def("__repr__",
            [](const LinearSchedule &schedule) {
            return "<per_memory.LinearSchedule initval=" + std::to_string(schedule.initval) 
                + ", finalval=" + std::to_string(schedule.finalval)
                + ", steps=" + std::to_string(schedule.timesteps) + ">";    
        });
}
