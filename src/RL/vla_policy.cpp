#include "vla_policy.h"
#include <random>
#include <iostream>

VLA_Policy::VLA_Policy(int nj, int img_size, int txt_dim)
    : num_joints(nj), image_size(img_size), text_embed_dim(txt_dim) {

    int input_dim = image_size * image_size + text_embed_dim;

    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<> d(0.0, 0.1);

    auto rand_mat = [&](int rows, int cols) {
        Eigen::MatrixXd m(rows, cols);
        for(int i=0;i<rows;i++) for(int j=0;j<cols;j++) m(i,j) = d(gen);
        return m;
    };
    auto rand_vec = [&](int dim){
        Eigen::VectorXd v(dim);
        for(int i=0;i<dim;i++) v(i) = d(gen);
        return v;
    };

    W1 = rand_mat(64, input_dim); b1 = rand_vec(64);
    W2 = rand_mat(64, 64);       b2 = rand_vec(64);
    W3 = rand_mat(num_joints, 64); b3 = rand_vec(num_joints);
}

Eigen::VectorXd VLA_Policy::preprocess_image(const cv::Mat& image){
    cv::Mat gray, resized;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::resize(gray, resized, cv::Size(image_size, image_size));
    Eigen::VectorXd x(image_size*image_size);
    for(int i=0;i<image_size;i++)
        for(int j=0;j<image_size;j++)
            x(i*image_size + j) = resized.at<uchar>(i,j)/255.0; // normalize
    return x;
}

Eigen::VectorXd VLA_Policy::encode_text(const std::string& instruction){
    // Very simple placeholder: sum char codes modulo 16
    Eigen::VectorXd x = Eigen::VectorXd::Zero(text_embed_dim);
    for(size_t i=0;i<instruction.size();i++){
        x(i % text_embed_dim) += (instruction[i]-32)/96.0; // normalized
    }
    return x;
}

Eigen::VectorXd VLA_Policy::relu(const Eigen::VectorXd& x){
    Eigen::VectorXd y = x;
    for(int i=0;i<x.size();i++) y(i) = std::max(0.0, x(i));
    return y;
}

Eigen::VectorXd VLA_Policy::forward(const Eigen::VectorXd& input){
    Eigen::VectorXd h1 = relu(W1 * input + b1);
    Eigen::VectorXd h2 = relu(W2 * h1 + b2);
    Eigen::VectorXd out = W3 * h2 + b3;

    // clip outputs to [-1.5,1.5]
    for(int i=0;i<out.size();i++){
        if(out(i) > 1.5) out(i)=1.5;
        if(out(i) < -1.5) out(i)=-1.5;
    }
    return out;
}

std::vector<double> VLA_Policy::select_action(const cv::Mat& image, const std::string& instruction){
    Eigen::VectorXd img_vec = preprocess_image(image);
    Eigen::VectorXd txt_vec = encode_text(instruction);
    Eigen::VectorXd input(img_vec.size()+txt_vec.size());
    input << img_vec, txt_vec;
    Eigen::VectorXd out = forward(input);
    std::vector<double> actions(out.data(), out.data()+out.size());
    return actions;
}

void VLA_Policy::update_policy(const std::vector<double>& actions, double reward){
    // placeholder: you can implement RL update here
    (void)actions; (void)reward;
}