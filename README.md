# PER MEMORY

A Priorized Experience Replay (PER) Memory for deep RL models. This module is implemented in C++ with 
compiler and openmp optimizations. It shows about 12x better performance than the OpenAI python implementation.

## Install
```python setup.py install```

## Interfaces
- `PrioritizedMemory`
    - `PrioritizedMemory(capacity: size_t, alpha: double, beta: LinearSchedule, error: double) -> None`: init function
    - `add(TD_error: double, sample: tuple(s, a, s', R)) -> None`: add a sample to buffer
    - `sample(batchsize: int) -> (batch: list[Sample], indexs: list[int], weights: list[int])`: sample `batchsize` samples from the memory
    - `update(index, new_priority) -> None`: update the priority of the index=`idx` element
- `LinearSchedule`
    - `LinearSchedule(steps: int, beginval: double, endval: double) -> None`: init function
    - `next() -> double`: yields the next value
