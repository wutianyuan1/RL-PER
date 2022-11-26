from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension(
        "per_memory",
        ["per_interface.cpp"],
        include_dirs=["./"],
        cxx_std="17",
        extra_compile_args=["-O3", "-march=native", "-fopenmp", "-funroll-loops"],
        extra_link_args =["-fopenmp"],
        package_data={'my_package': ['per_memory.pyi']},
    ),
]

setup(name='per_memory', ext_modules=ext_modules)