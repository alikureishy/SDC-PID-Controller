# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Overview

This project entails building a PID controller that allows a car to drive while minimizing the cross-track-error (CTE). The CTE value is obtained from the simulator (listed below), along with the present speed and steering angle.

## Implementation

Upon receiving the CTE, the PID controller keeps track of 3 values:
- the current CTE (for the P term)
- the difference between the previous and current CTE (for the D term)
- the cumulative total CTE since the beginning of the simulation (for the I term)

It then uses the PID controller formula to calculate the control signal needed for the steering angle.

## Parameter Tuning

The coefficients (P, I and D) of the PID controller each served the following needs in this simulation:
- The P coefficient was for the vehicle to quickly correct its position relative to a CTE
- The I coefficient was actually not needed in this project since there was no disturbance/noise that was working against the steering wheel.
- The D coefficient was essential for minimizing oscillations, especially when a snappy P coefficient was utilized.

Steps I followed to select the parameters:
- Kept all coefficients to zero, and increased P to 0.1. Observed how quick the car was to respond to a CTE
- 



## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)
