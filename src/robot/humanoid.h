#pragma once
#include <vector>
/*
class Humanoid {
public:
    Humanoid(int joints);

    void reset();
    void step(const std::vector<double>& torques, double dt);

    std::vector<double> get_positions() const;
    std::vector<double> get_velocities() const;

private:
    int n;
    std::vector<double> q, dq;
};
*/


class Humanoid {
public:
    std::vector<double> getCameraImage();
    std::vector<int> getInstruction();
    std::vector<double> getJointState();

    void applyAction(const std::vector<double>& action);
};