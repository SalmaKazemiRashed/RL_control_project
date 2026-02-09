
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

#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

class Humanoid {
public:
    Humanoid();

    // Returns current camera image
    cv::Mat getCameraImage();

    // Returns number of joints
    int get_num_joints() const;

    // Returns current joint positions
    std::vector<double> getJointPositions() const;

    // Apply joint actions (from PID or policy)
    void applyAction(const std::vector<double>& action);

    // Step the physics simulation
    void stepSimulation();

    // Compute reward based on current state or actions
    double computeReward() const;

private:
    std::vector<double> joint_positions;
};