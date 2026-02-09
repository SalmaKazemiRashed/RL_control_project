/*
#include <iostream>
#include <numeric>
#include "robot/humanoid.h"
#include "control/pid.h"
#include "RL/policy.h"
#include "system/latency.h"
#include "system/logger.h"

constexpr double DT = 0.002;

int main() {
    Humanoid robot(6); // 6-DOF
    GaussianPolicy policy(6);
    LatencyBuffer latency(5, 0.1);
    Logger logger("logs/log.csv");

    robot.reset();

    for (int t = 0; t < 5000; t++) {
        auto q = robot.get_positions();

        auto action = policy.act(q);

        std::vector<double> delayed_action(6, 0.0);
        for (int i = 0; i < 6; i++) {
            latency.push(action[i]);
            latency.pop(delayed_action[i]);
        }

        robot.step(delayed_action, DT);

        double error = std::accumulate(q.begin(), q.end(), 0.0,
            [](double s, double v){ return s + std::abs(v); });

        double energy = std::accumulate(delayed_action.begin(),
                                        delayed_action.end(), 0.0,
            [](double s, double a){ return s + a*a; });

        double reward = -error - 0.01 * energy;
        policy.update(q, action, reward);

        logger.log(t, error, energy,robot.get_positions());
    }

    std::cout << "Simulation finished.\n";
    return 0;
}
*/
#include "robot/humanoid.h"
#include "control/pid.h"
#include "RL/vla_policy.h"
#include "system/logger.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

int main() {
    // -------------------------
    // Initialize robot, PID, VLA policy, logger
    // -------------------------
    Humanoid robot;
    PIDController pid(robot.get_num_joints());
    VLA_Policy policy(robot.get_num_joints());

    Logger logger("vla_log.csv");
    logger.write_header({"q0","q1","q2","q3","q4","q5"});

    std::string instruction = "walk forward";

    const int num_steps = 200;   // number of timesteps to simulate

    for(int t = 0; t < num_steps; t++) {
        // -------------------------
        // Get camera image
        // -------------------------
        cv::Mat image = robot.getCameraImage();

        // -------------------------
        // Get joint actions from VLA policy
        // -------------------------
        std::vector<double> actions = policy.select_action(image, instruction);

        // -------------------------
        // Apply actions via PID controller
        // -------------------------
        pid.apply(actions);
        robot.applyAction(actions);

        // -------------------------
        // Step simulation
        // -------------------------
        robot.stepSimulation();

        // -------------------------
        // Log joint positions
        // -------------------------
        std::vector<double> joint_positions = robot.getJointPositions();
        logger.log_vector(joint_positions);

        // -------------------------
        // Compute reward and update policy
        // -------------------------
        double reward = robot.computeReward();
        policy.update_policy(actions, reward);

        // Optional: print progress every 20 steps
        if(t % 20 == 0) {
            std::cout << "Step " << t 
                      << " | Reward: " << reward << std::endl;
        }
    }

    std::cout << "Simulation finished. Log saved to vla_log.csv" << std::endl;
    return 0;
}