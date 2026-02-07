#pragma once

class PID {
public:
    PID(double kp, double ki, double kd);

    double compute(double target, double current, double dt);

private:
    double kp, ki, kd;
    double prev_error;
    double integral;
};