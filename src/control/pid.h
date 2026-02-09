#pragma once
#include <vector>

class PIDController {
public:
    // Constructor: number of joints
    PIDController(int num_joints);

    // Apply target actions to the joints
    void apply(const std::vector<double>& target_positions);

private:
    int num_joints;
    std::vector<double> prev_errors;
    std::vector<double> integral;
    double Kp, Ki, Kd;
};