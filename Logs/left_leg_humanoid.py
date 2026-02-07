import pybullet as p
import pybullet_data
import pandas as pd
import time
import imageio
import numpy as np

# =========================
# Load joint log
# =========================
df = pd.read_csv("log.csv")  # expects q0–q5 columns

# =========================
# Connect to PyBullet
# =========================
if p.isConnected():
    p.disconnect()

p.connect(p.GUI)   # use p.DIRECT for headless
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
# Camera (GUI view)
# =========================
p.resetDebugVisualizerCamera(
    cameraDistance=6.0,
    cameraYaw=90,
    cameraPitch=-25,
    cameraTargetPosition=[0, 0, 1.0]
)

# =========================
# Offscreen camera (GIF)
# =========================
WIDTH, HEIGHT = 640, 480

view_matrix = p.computeViewMatrixFromYawPitchRoll(
    cameraTargetPosition=[0, 0, 1.0],
    distance=3.0,
    yaw=90,
    pitch=-25,
    roll=0,
    upAxisIndex=2
)

proj_matrix = p.computeProjectionMatrixFOV(
    fov=60,
    aspect=WIDTH / HEIGHT,
    nearVal=0.1,
    farVal=100.0
)

frames = []

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
# Map q0–q5 → leg joints
# =========================
JOINT_MAP = {
    # Right leg
    "q0": 9,    # right_hip
    "q1": 10,   # right_knee
    "q2": 11,   # right_ankle

    # Left leg
    "q3": 12,   # left_hip
    "q4": 13,   # left_knee
    "q5": 14    # left_ankle
}

# =========================
# Replay + record
# =========================
print("▶ Replaying motion and recording GIF...")

for _, row in df.iterrows():
    for q_name, joint_id in JOINT_MAP.items():
        target = max(-1.5, min(1.5, float(row[q_name])))
        p.setJointMotorControl2(
            bodyIndex=robot,
            jointIndex=joint_id,
            controlMode=p.POSITION_CONTROL,
            targetPosition=target,
            force=150
        )

    p.stepSimulation()

    # Capture frame
    img = p.getCameraImage(
        WIDTH,
        HEIGHT,
        viewMatrix=view_matrix,
        projectionMatrix=proj_matrix,
        renderer=p.ER_BULLET_HARDWARE_OPENGL
    )

    rgb = np.reshape(img[2], (HEIGHT, WIDTH, 4))[:, :, :3]
    frames.append(rgb)

    time.sleep(1 / 240)

print("✔ Motion finished")

# =========================
# Save GIF
# =========================
print(" Saving GIF...")
imageio.mimsave("humanoid_motion.gif", frames, fps=30)
print("✔ Saved humanoid_motion.gif")

input("Press ENTER to exit...")
p.disconnect()