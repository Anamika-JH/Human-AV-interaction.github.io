# Human-AV Interaction
🚀 **ROS Noetic-based TurtleBot | Lane Detection | Stanley Controller | XR Simulation**

## Project Overview
This project explores human-autonomous vehicle (AV) interaction using a **TurtleBot running on ROS Noetic**. The system integrates **lane detection-based trajectory tracking**, **Stanley controller-based navigation**, and **UDP communication with a Unity-based XR environment**. A pedestrian wearing an **Oculus headset** interacts with the virtual AV, which mirrors real-time robot movements.

## System Architecture
The project consists of multiple layers:

### **Robot Control Layer (ROS Noetic)**
- The TurtleBot runs ROS Noetic.
- It follows a trajectory using **lane detection and a Stanley controller**.
- Wheel odometry data is extracted and sent via UDP.

### **Perception Layer**
- A camera mounted on the TurtleBot detects lanes.
- A **two-lane detection system** helps in trajectory tracking.

### **Simulation Layer (Unity XR)**
- A Unity-based XR environment receives wheel odometry via **UDP**.
- The AV moves based on real-time data from the robot.

### **Human Interaction Layer**
- A pedestrian using an **Oculus headset** interacts with the AV.
- The system evaluates how humans and AVs coordinate in crossing scenarios.

## Resources
Resources can be accessed at: [Resources](https://drive.google.com/drive/folders/18T3t87dYajVvqO8WMyi9NXHBhyZbazkO?usp=sharing)  
Please **copy the resources folder inside the `Model` folder** in the repository.


## Acknowledgments
Parts of this project page were adopted from the [Nerfies](https://nerfies.github.io/) page.

## Website License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
