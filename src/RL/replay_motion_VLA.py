import pybullet as p
import pybullet_data
import pandas as pd
import time
import imageio
import numpy as np

df = pd.read_csv("log_vla.csv")
assert not df.empty

p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0, 0, -9.8)

plane = p.loadURDF("plane.urdf")

robot = p.loadURDF(
    "humanoid/humanoid.urdf",
    [0, 0, 1.0],
    useFixedBase=True
)

# GUI camera
p.resetDebugVisualizerCamera(
    cameraDistance=6,
    cameraYaw=90,
    cameraPitch=-25,
    cameraTargetPosition=[0, 0, 1.0]
)

# Disable motors
for j in range(p.getNumJoints(robot)):
    p.setJointMotorControl2(robot, j, p.VELOCITY_CONTROL, force=0)

JOINT_MAP = {
    "q0": 9,
    "q1": 10,
    "q2": 11,
    "q3": 12,
    "q4": 13,
    "q5": 14
}

WIDTH, HEIGHT = 640, 480
proj = p.computeProjectionMatrixFOV(
    fov=60,
    aspect=WIDTH / HEIGHT,
    nearVal=0.1,
    farVal=100
)

frames = []

print("▶ Replaying motion")

for i, (_, row) in enumerate(df.iterrows()):
    for q, jid in JOINT_MAP.items():
        p.setJointMotorControl2(
            robot, jid,
            p.POSITION_CONTROL,
            targetPosition=float(np.clip(row[q], -1.5, 1.5)),
            force=200
        )

    p.stepSimulation()

    # 🔴 KEY FIX: update camera target every frame
    base_pos, _ = p.getBasePositionAndOrientation(robot)
    view = p.computeViewMatrixFromYawPitchRoll(
        cameraTargetPosition=base_pos,
        distance=6,
        yaw=90,
        pitch=-25,
        roll=0,
        upAxisIndex=2
    )

    img = p.getCameraImage(
        WIDTH, HEIGHT,
        viewMatrix=view,
        projectionMatrix=proj,
        renderer=p.ER_TINY_RENDERER
    )

    frame = np.reshape(img[2], (HEIGHT, WIDTH, 4))[:, :, :3]
    frames.append(frame.astype(np.uint8))

    time.sleep(1 / 240)

imageio.mimsave("humanoid_motion.gif", frames, fps=30)
print("✔ GIF saved")

# Keep GUI alive
print("🟢 Close window or Ctrl+C to exit")
while True:
    p.stepSimulation()
    time.sleep(1 / 240)