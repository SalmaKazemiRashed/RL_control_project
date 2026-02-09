/// Continious-action RL (Gaussian policy)
#pragma once
#include <vector>
/*
class GaussianPolicy {
public:
    GaussianPolicy(int dim);

    std::vector<double> act(const std::vector<double>& state);
    void update(const std::vector<double>& state,
                const std::vector<double>& action,
                double reward);

private:
    int dim;
    double lr;
    std::vector<double> mean;
};
*/

struct Observation {
    std::vector<double> image;    // vision
    std::vector<int> language;    // instruction tokens
    std::vector<double> state;    // joint positions
};

class Policy {
public:
    virtual ~Policy() = default;
    virtual std::vector<double> act(const Observation& obs) = 0;
};