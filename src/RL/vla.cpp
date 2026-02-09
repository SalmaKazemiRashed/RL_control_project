/*#include "vla.h"
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
*/

// VLA policy
#include "vla.h"
#include <algorithm>
#include <chrono>

VLA_Policy::VLA_Policy(int num_joints_, int num_actions_, double epsilon_, double alpha_, double gamma_)
    : num_joints(num_joints_), num_actions(num_actions_), epsilon(epsilon_), alpha(alpha_), gamma(gamma_),
      q_table(num_joints_, std::vector<double>(num_actions_, 0.0)), last_actions(num_joints_, 0),
      uni_dist(0.0, 1.0), action_dist(0, num_actions_ - 1)
{
    rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
}

int VLA_Policy::select_action(int joint_idx) {
    double r = uni_dist(rng);
    int action;
    if (r < epsilon) {
        // Explore
        action = action_dist(rng);
    } else {
        // Exploit
        auto max_it = std::max_element(q_table[joint_idx].begin(), q_table[joint_idx].end());
        action = std::distance(q_table[joint_idx].begin(), max_it);
    }
    last_actions[joint_idx] = action;
    return action;
}

void VLA_Policy::update_q(int joint_idx, int action, double reward, int next_action) {
    double q_predict = q_table[joint_idx][action];
    double q_target = reward + gamma * q_table[joint_idx][next_action];
    q_table[joint_idx][action] += alpha * (q_target - q_predict);
}