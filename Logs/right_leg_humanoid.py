import pybullet as p
import pybullet_data
import pandas as pd
import time

# =========================
# Load joint log
# =========================
df = pd.read_csv("log.csv")

# =========================
# Connect to PyBullet
# =========================
if p.isConnected():
    p.disconnect()

p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0, 0, -9.8)

# =========================
# Load environment
# =========================
plane = p.loadURDF("plane.urdf")

robot = p.loadURDF(
    "humanoid/humanoid.urdf",
    [0, 0, 1.0],
    useFixedBase=False
)

# =========================
# Camera setup (IMPORTANT)
# =========================
p.resetDebugVisualizerCamera(
    cameraDistance=5.0,
    cameraYaw=90,
    cameraPitch=-25,
    cameraTargetPosition=[0, 0, 1.0]
)

# =========================
# Disable default motors
# =========================
for j in range(p.getNumJoints(robot)):
    p.setJointMotorControl2(
        robot,
        j,
        p.VELOCITY_CONTROL,
        force=0
    )

# =========================
# Map q0–q5 → real joints
# =========================
JOINT_MAP = {
    "q0": 9,   # right_hip
    "q1": 10,  # right_knee
    "q2": 11,  # right_ankle
    "q3": 12,  # left_hip
    "q4": 13,  # left_knee
    "q5": 14   # left_ankle
}

# =========================
# Replay motion
# =========================
print("▶ Replaying motion...")

for _, row in df.iterrows():
    for q_name, joint_id in JOINT_MAP.items():
        p.setJointMotorControl2(
            bodyIndex=robot,
            jointIndex=joint_id,
            controlMode=p.POSITION_CONTROL,
            targetPosition=float(row[q_name]),
            force=150
        )

    p.stepSimulation()
    time.sleep(1/240)   # real-time speed

print("✔ Motion finished")

input("Press ENTER to exit...")
p.disconnect()