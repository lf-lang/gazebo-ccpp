# LF Gazebo package for CCpp target

## Requirements
- Linux (ubuntu 24.04) system. macOS should also work

## Getting started

Install Gazebo Harmonic following this guide: https://gazebosim.org/docs/harmonic/install/

Verify installation with:
```sh
gz sim src/models/simple_robot.sdf
```

Install Eigen3:

```sh
sudo apt libeigen3-dev
```

Run the basic demo which will just launch a simulation of a small car not moving.

```sh
lingo run -a GazeboBasicDemo
```

Run the collision avoidance demo where the car will avoid a wall.

```sh
lingo run -a GazeboCollisionAvoidanceDemo
```
