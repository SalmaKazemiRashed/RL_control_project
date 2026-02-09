#include "pid.h"
/*
PID::PID(double kp_, double ki_, double kd_)
    : kp(kp_), ki(ki_), kd(kd_), prev_error(0.0), integral(0.0) {}

double PID::compute(double target, double current, double dt) {
    double error = target - current;
    integral += error * dt;
    double derivative = (error - prev_error) / dt;
    prev_error = error;

    return kp * error + ki * integral + kd * derivative;
}
*/

#pragma once
#include "pid.h"

double PID::step(double target, double current) {
    return target - current;
}