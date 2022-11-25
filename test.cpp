#include <priority_mem.h>
#include <iostream>

int main() {
    PriorityMemory<double> mem(20000);
    for (int i = 0; i < 10000; i++) {
        double pri = double(rand() % 10) / 10.0;
        mem.add(pri, pri);
    }
    int counter[10];
    for (int i = 0; i < 1000; i++) {
        auto [batch, idxes, weight] = mem.sample(10);
        for (int i = 0; i < 10; i++)
            counter[int(10*batch[i])]++;
    }
    for (int i = 0; i < 10; i++)
        printf("%d\n", counter[i]);
    return 0;
}