import pybullet as p
import pybullet_data
import numpy as np
import time
import csv
import imageio

# =========================
# Parameters
# =========================
LOG_FILE = "vla_log.csv"
GIF_FILE = "humanoid_replay.gif"
STEP_DELAY = 1/240
FPS = 20

# =========================
# Read log CSV
# =========================
joint_positions_list = []

with open(LOG_FILE, 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        joints = [float(row[f'q{i}']) for i in range(6)]
        joint_positions_list.append(joints)

# =========================
# Connect PyBullet
# =========================
p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0, 0, -9.8)

plane = p.loadURDF("plane.urdf")
robot = p.loadURDF("humanoid/humanoid.urdf", [0,0,1], useFixedBase=False)

# Disable default motors
num_joints = p.getNumJoints(robot)
for j in range(num_joints):
    p.setJointMotorControl2(robot, j, p.VELOCITY_CONTROL, force=0)

# =========================
# Setup for GIF
# =========================
frames = []
width, height = 640, 480

def capture_frame():
    view_matrix = p.computeViewMatrixFromYawPitchRoll(
        cameraTargetPosition=[0,0,1],
        distance=10,
        yaw=45,
        pitch=-30,
        roll=0,
        upAxisIndex=2
    )
    proj_matrix = p.computeProjectionMatrixFOV(
        fov=60,
        aspect=width/height,
        nearVal=0.1,
        farVal=100
    )
    img = p.getCameraImage(width, height, viewMatrix=view_matrix, projectionMatrix=proj_matrix)
    rgb = np.reshape(img[2], (height, width, 4))[:,:,:3].astype(np.uint8)
    return rgb

# =========================
# Replay joint positions
# =========================
for joint_positions in joint_positions_list:
    # Apply joint positions
    for i, joint_id in enumerate([9,10,11,12,13,14]):  # match your joint mapping
        target = np.clip(joint_positions[i], -1.5, 1.5)
        p.setJointMotorControl2(robot, joint_id, p.POSITION_CONTROL, targetPosition=target, force=150)

    p.stepSimulation()
    frames.append(capture_frame())
    time.sleep(STEP_DELAY)

# =========================
# Save GIF
# =========================
print("Saving GIF...")
imageio.mimsave(GIF_FILE, frames, fps=FPS)
print(f"GIF saved as {GIF_FILE}")

p.disconnect()