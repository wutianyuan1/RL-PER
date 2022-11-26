#pragma once
#include <algorithm>
#include <cmath>

class LinearSchedule {
public:
    LinearSchedule(int timesteps_, double initval_, double finalval_) 
    : timesteps(timesteps_), initval(initval_), finalval(finalval_), step(0) {};
    LinearSchedule(const LinearSchedule& other) 
    : timesteps(other.timesteps), initval(other.initval), finalval(other.finalval), step(other.step) {};

    inline double next() {
        step++;
        double fraction = std::min(1.0, (double)step / (double)timesteps);
        return initval + (finalval - initval) * fraction;
    }

    int timesteps;
    double initval;
    double finalval;
    int step;
};
