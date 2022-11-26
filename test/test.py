from per_memory import PrioritizedMemory, LinearSchedule
from memory import Memory as PyMemory
from time import time
import random

def test(mem):
    begin = time()
    for i in range(128 * 1024):
        mem.add(random.random(), ("s", "a", "s'", random.randint(0 ,10)) )
        if i % 128 == 0:
            batch, idxs, weight = mem.sample(128)
            for j in idxs:
                mem.update(j, random.random())
    end  = time()
    print(f"duration of {mem}: {end-begin}s")


if __name__ == '__main__':
    capacity = 20000
    sched = LinearSchedule(1024, 0.5, 1.0)
    test(PrioritizedMemory(capacity, 0.4, sched , 0.01))
    test(PyMemory(capacity))
