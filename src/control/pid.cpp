#include "pid.h"
#include <algorithm>
#include <iostream>

PIDController::PIDController(int nj)
    : num_joints(nj), prev_errors(nj, 0.0), integral(nj, 0.0) {

    Kp = 150.0;  // proportional gain
    Ki = 0.0;    // integral gain
    Kd = 1.0;    // derivative gain
}

// Apply actions to the joints (placeholder)
void PIDController::apply(const std::vector<double>& target_positions) {
    // Here we just print the target positions
    // In real code, compute PID to reach targets
    for(int i=0;i<num_joints;i++){
        double error = target_positions[i]; // assuming current pos = 0
        integral[i] += error;
        double derivative = error - prev_errors[i];
        double output = Kp*error + Ki*integral[i] + Kd*derivative;
        prev_errors[i] = error;

        // Send output to joint motors (here just printing)
        // In real code: robot.setJointTorque(i, output);
        std::cout << output << " ";
    }
    std::cout << std::endl;
}