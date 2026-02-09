//Simulate agent and save log.csv
#include "vla.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

int main() {
    const int num_joints = 6;
    const int num_actions = 11; // discretize joint angles [-1.5, 1.5] into 11 bins
    const int timesteps = 2000;

    VLA_Policy policy(num_joints, num_actions);

    std::ofstream csv("log_vla.csv");
    csv << "q0,q1,q2,q3,q4,q5\n";

    std::srand(std::time(nullptr));

    // Simple RL loop
    std::vector<double> joint_positions(num_joints, 0.0);

    for (int t = 0; t < timesteps; ++t) {
        std::vector<int> actions(num_joints);
        for (int j = 0; j < num_joints; ++j) {
            actions[j] = policy.select_action(j);
        }

        // Map actions to joint angles [-1.5, 1.5]
        for (int j = 0; j < num_joints; ++j) {
            joint_positions[j] = -1.5 + actions[j] * (3.0 / (num_actions - 1));
        }

        // Compute reward: keep humanoid upright (placeholder, random for demo)
        double reward = 1.0 - 0.1 * (std::abs(joint_positions[0]) + std::abs(joint_positions[3]));

        // Update Q-table
        for (int j = 0; j < num_joints; ++j) {
            int next_action = policy.select_action(j);
            policy.update_q(j, actions[j], reward, next_action);
        }

        // Write joint positions to CSV
        for (int j = 0; j < num_joints; ++j) {
            csv << joint_positions[j];
            if (j < num_joints - 1) csv << ",";
        }
        csv << "\n";
    }

    csv.close();
    std::cout << "Training finished. Saved log.csv\n";
    return 0;
}