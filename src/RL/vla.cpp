#include "vla.h"
#include <algorithm>

static constexpr int IMAGE_DIM = 1024;
static constexpr int VISION_DIM = 64;
static constexpr int LANG_DIM = 32;
static constexpr int ACTIONS = 6;

VLA_Policy::VLA_Policy() {
    W_vision.resize(VISION_DIM, std::vector<double>(IMAGE_DIM, 0.01));
    W_language.resize(LANG_DIM, std::vector<double>(5000, 0.01));
    W_action.resize(ACTIONS, std::vector<double>(VISION_DIM + LANG_DIM, 0.01));
}

std::vector<double> VLA_Policy::encodeVision(const std::vector<double>& img) {
    std::vector<double> out(VISION_DIM, 0.0);
    for (int i = 0; i < VISION_DIM; ++i)
        for (int j = 0; j < IMAGE_DIM; ++j)
            out[i] += W_vision[i][j] * img[j];
    return out;
}

std::vector<double> VLA_Policy::encodeLanguage(const std::vector<int>& tokens) {
    std::vector<double> out(LANG_DIM, 0.0);
    for (int t : tokens)
        for (int i = 0; i < LANG_DIM; ++i)
            out[i] += W_language[i][t];
    return out;
}

std::vector<double> VLA_Policy::act(const Observation& obs) {
    auto v = encodeVision(obs.image);
    auto l = encodeLanguage(obs.language);

    v.insert(v.end(), l.begin(), l.end());

    int best = 0;
    double best_score = -1e9;

    for (int a = 0; a < ACTIONS; ++a) {
        double s = 0.0;
        for (size_t i = 0; i < v.size(); ++i)
            s += W_action[a][i] * v[i];

        if (s > best_score) {
            best_score = s;
            best = a;
        }
    }

    std::vector<double> action(ACTIONS, 0.0);
    action[best] = 1.0;
    return action;
}