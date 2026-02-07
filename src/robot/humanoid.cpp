// Here we define a very simple humanoid joint dynamics model:

#include "humanoid.h"
#include <random>

static std::default_random_engine gen;
static std::normal_distribution<double> noise(0.0, 0.005);

Humanoid::Humanoid(int joints)
    : n(joints), q(joints, 0.0), dq(joints, 0.0) {}      // Humanoid stores joint positions (q) and velocities (dq) for n joints

void Humanoid::reset() {
    std::fill(q.begin(), q.end(), 0.0);                   // reset() sets all joints and velocities to zero
    std::fill(dq.begin(), dq.end(), 0.0);
}

void Humanoid::step(const std::vector<double>& torques, double dt) {   // step() updates velocities from input torques, integrates them to positions, and adds small Gaussian noise
    for (int i = 0; i < n; i++) {
        dq[i] += torques[i] * dt;
        q[i] += dq[i] * dt + noise(gen);
    }
}

std::vector<double> Humanoid::get_positions() const { return q; }           // get_positions() / get_velocities() return the current joint states
std::vector<double> Humanoid::get_velocities() const { return dq; }