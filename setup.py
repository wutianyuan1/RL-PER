from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension(
        "per_memory",
        ["per_interface.cpp"],
        include_dirs=["./"],
    ),
]

setup(name='per_memory', ext_modules=ext_modules)