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
