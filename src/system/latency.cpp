#include "latency.h"
#include <cstdlib>


/*
LatencyBuffer::LatencyBuffer(int delay_steps, double drop_prob)
    : delay(delay_steps), drop_probability(drop_prob) {}

bool LatencyBuffer::push(double value) {
    if ((double)rand() / RAND_MAX < drop_probability)
        return false; // dropped frame

    buffer.push(value);
    return true;
}

bool LatencyBuffer::pop(double& value) {
    if ((int)buffer.size() < delay)
        return false;

    value = buffer.front();
    buffer.pop();
    return true;
}
*/

#include "latency.h"

double Latency::measure() {
    return 0.0;
}