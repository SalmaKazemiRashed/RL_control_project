#pragma once
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

class VLA_Policy {
public:
    VLA_Policy(int num_joints, int image_size = 64, int text_embed_dim = 16);

    // Given a camera image and text instruction, output joint actions [-1.5, 1.5]
    std::vector<double> select_action(const cv::Mat& image, const std::string& instruction);

    // Update policy based on reward (placeholder for Q-learning / RL)
    void update_policy(const std::vector<double>& actions, double reward);

private:
    int num_joints;
    int image_size;
    int text_embed_dim;

    // Tiny neural network weights
    Eigen::MatrixXd W1, W2, W3; // simple 3-layer MLP
    Eigen::VectorXd b1, b2, b3;

    // Helper functions
    Eigen::VectorXd preprocess_image(const cv::Mat& image);
    Eigen::VectorXd encode_text(const std::string& instruction);
    Eigen::VectorXd forward(const Eigen::VectorXd& input);
    Eigen::VectorXd relu(const Eigen::VectorXd& x);
};