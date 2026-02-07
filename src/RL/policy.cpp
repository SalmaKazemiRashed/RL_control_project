#include "policy.h"
#include <cstdlib>

// This mimics policy-gradient intuition
GaussianPolicy::GaussianPolicy(int dim_)
    : dim(dim_), lr(0.01), mean(dim_, 0.0) {}

std::vector<double> GaussianPolicy::act(const std::vector<double>& state) {
    std::vector<double> action(dim);
    for (int i = 0; i < dim; i++) {
        double noise = ((double)rand() / RAND_MAX - 0.5) * 0.2;
        action[i] = mean[i] + noise;
    }
    return action;
}

void GaussianPolicy::update(const std::vector<double>&,
                            const std::vector<double>& action,
                            double reward) {
    for (int i = 0; i < dim; i++)
        mean[i] += lr * reward * action[i];
}