# PER MEMORY

A Priorized Experience Replay (PER) Memory for deep RL models. This module is implemented in C++ with 
compiler and openmp optimizations. It gives about 12x performance than the OpenAI python implementation.

## Install
```python setup.py install```

## Interfaces
- `PrioritizedMemory`
    - constructor: capacity, alpha, beta(LinearSchedule), error
    - add: TD error, sample (s, a, s', R)
    - sample: batchsize
    - update: index, new priority
- `LinearSchedule`
    - constructor: steps, beginval, endval
    - next: yields the next value
