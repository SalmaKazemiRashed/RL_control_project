/*
#pragma once
#include "policy.h"
#include <vector>

class VLA_Policy : public Policy {
public:
    VLA_Policy();

    std::vector<double> act(const Observation& obs) override;

private:
    std::vector<std::vector<double>> W_vision;
    std::vector<std::vector<double>> W_language;
    std::vector<std::vector<double>> W_action;

    std::vector<double> encodeVision(const std::vector<double>& img);
    std::vector<double> encodeLanguage(const std::vector<int>& tokens);
};
*/


/// VLA Policy class, ε-greedy RL, Q-table
#ifndef VLA_H
#define VLA_H

#include <vector>
#include <random>

class VLA_Policy {
public:
    VLA_Policy(int num_joints, int num_actions, double epsilon=0.2, double alpha=0.1, double gamma=0.95);

    virtual ~VLA_Policy() = default;

    // Select action index for a joint using epsilon-greedy
    int select_action(int joint_idx);

    // Update Q-table
    void update_q(int joint_idx, int action, double reward, int next_action);

    // Get last selected action for logging
    std::vector<int> get_last_actions() const { return last_actions; }

private:
    int num_joints;
    int num_actions;
    double epsilon;
    double alpha; // learning rate
    double gamma; // discount factor
    std::vector<std::vector<double>> q_table;
    std::vector<int> last_actions;

    std::mt19937 rng;
    std::uniform_real_distribution<double> uni_dist;
    std::uniform_int_distribution<int> action_dist;
};

#endif // VLA_H