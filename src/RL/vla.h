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