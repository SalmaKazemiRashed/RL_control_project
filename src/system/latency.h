#pragma once  
#include <queue>
/*
class LatencyBuffer {
public:
    LatencyBuffer(int delay_steps, double drop_prob);

    bool push(double value);
    bool pop(double& value);

private:
    int delay;
    double drop_probability;
    std::queue<double> buffer;
};
*/

#pragma once

class Latency {
public:
    double measure();
};