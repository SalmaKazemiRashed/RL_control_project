# RL_control_project

The main file structure:

```plaintext
RL_control_project/
├── CMakeLists.txt
├── README.md
├── logs/
│   └── log.csv
└── src/
    ├── main.cpp
    ├── robot/
    │   ├── humanoid.cpp
    │   └── humanoid.h
    ├── control/
    │   ├── pid.cpp
    │   └── pid.h
    ├── RL/
    │   ├── policy.cpp
    │   └── policy.h
    ├── system/
    │   ├── latency.cpp
    │   ├── latency.h
    │   └── logger.h

```


This project explores reinforcement learning as an adaptive control layer
for embodied robotic systems under real-world deployment constraints.


## Motivation
Modern RL policies often fail when deployed on physical robots due to:
- Latency and dropped control frames
- Sensor noise and partial observability
- Energy constraints and instability
- Interaction with low-level controllers


This project investigates how learning-based policies can be integrated
safely and effectively into real-time robotic control loops.


## Architecture
High-level policy (continuous-action RL)
- Latency & drop modeling
- Safety-constrained torque commands
- Multi-joint humanoid dynamics

The system is implemented entirely in C++ with no ML frameworks, enabling
deterministic timing and low-level experimentation.

## Features
- Gaussian policy gradient (from scratch)
- Latency buffers and dropped frames
- Humanoid joint abstraction
- Noise injection for sim-to-real realism
- Energy-aware reward shaping
- Experiment logging and metrics

## Research Focus
This code is designed to:
- Expose failure modes of RL in real-time systems
- Quantify stability and adaptation under delays
- Serve as a testbed for sim-to-real strategies
- Bridge classical control and modern learning

## Future Work
- Hardware-in-the-loop deployment
- Vision-language-action integration
- Adaptive gain scheduling
- Safety-certified control layers



## How to run

- Install linux on windows (WSL + ubuntu).
```Bash
sudo apt update
sudo apt install build-essential
```
- Verify that GCC is visible:
```Bash
g++ --version
```

-  Create a build directory inside the project folder and then build the project.
```Bash
cd build
cmake ..
```

- Make it executable
```Bash
make -j
./RL_control_project
```

## Visualize log file
