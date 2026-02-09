/*
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
*/

#include "humanoid.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>

Humanoid::Humanoid() {
    joint_positions = std::vector<double>(6, 0.0);
}

// Dummy camera image: return a grayscale OpenCV image
cv::Mat Humanoid::getCameraImage() {
    cv::Mat image(64, 64, CV_8UC3, cv::Scalar(128,128,128));
    return image;
}

int Humanoid::get_num_joints() const {
    return static_cast<int>(joint_positions.size());
}

std::vector<double> Humanoid::getJointPositions() const {
    return joint_positions;
}

void Humanoid::applyAction(const std::vector<double>& action) {
    for(size_t i=0;i<joint_positions.size();i++){
        joint_positions[i] += action[i];
        // clip to joint limits [-1.5, 1.5]
        if(joint_positions[i] > 1.5) joint_positions[i] = 1.5;
        if(joint_positions[i] < -1.5) joint_positions[i] = -1.5;
    }
}

void Humanoid::stepSimulation() {
    // placeholder: in real code, advance physics
}

double Humanoid::computeReward() const {
    // Example: reward for keeping joints near 0 (standing upright)
    double reward = 0.0;
    for(double q : joint_positions){
        reward -= q*q; // energy penalty
    }
    return reward;
}