<!--- Adding links to various images used in this document --->
[SwervingLeft]: https://github.com/safdark/SDC-PID-Controller/blob/master/docs/images/SwervingLeft.png "SwervingLeft"
[SwervingRight]: https://github.com/safdark/SDC-PID-Controller/blob/master/docs/images/SwervingRight.png "SwervingRight"

# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

[![SwervingLeft][SwervingLeft]](https://youtu.be/NWEMzFmz8qA "Click to see video on youtube")
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

The only parameter that I 'controlled' for was the steering angle, while the _throttle_ was kept at a constant of _0.3_.

### Steering Angle

The coefficients (P, I and D) of the PID controller each served the following needs in this simulation:
- The P coefficient was for the vehicle to quickly correct its position relative to a CTE (it became most important on sharp turns)
- The I coefficient was actually not needed in this project since there was no disturbance/noise that was working against the steering wheel. So, I maintained it at zero throughout.
- The D coefficient was very crucial for minimizing oscillations, especially when a snappy P coefficient was utilized.

I selected the parameters manually, based on intuition.

|| # || Kp || Kd || Ki || Outcome || Next step ||
| 1  | 0.03 | 0.005 | 0.0 | Car steady but drives off road very quickly. | Need to speed up error correction, so increase Kp. |
| 2  | 0.3 | 0.8 | 0.0 | Car was prompt in returning from edges (even sharp ones). Oscillations would converge, but to a high amplitude. Car drove off road on a couple of sharp turns. Passengers would be rather dizzy. | Need to reduce the amplitute of oscillations, while keeping everything else the same. |
| 3  | 0.3 | 1.3 | 0.0 | Oscillations reduced significantly. Responsiveness to sharp turns remained good. Kp value of 0.3 seems just right, if oscillations can be minimized. Speed went as high as 29. Still drove off road a couple of times. | Minimize oscillations further. |
| 4  | 0.3 | 1.9 | 0.0 | Most oscillations occur on the bridge. Elsehwere the car is relatively stable. Remains on the track, within the driving region at ALL times! | Improve oscillations further? |
| 5  | 0.3 | 2.5 | 0.0 | Quite stable, even on bridge. Remains on the track at ALL times. Reached speed of 34 mph!| Improve oscillations further? |
| 6  | 0.3 | 3.0 | 0.0 | Oscillations minimal. Remains on track at ALL times. Reaches speed of 34.6 mph! | Suficient! |

## Future Improvements

The following enhancements could be made in the future:
- Incorporate automated parameter tuning (using algorithms such as Twiddle etc)
- Incorporate deep-learning tools for parameter tuning (such as Deep Reinforcement Learning)
- Add a controller for the throttle as well, the goal being that the car should decrease the throttle when the the CTE changes too fast, and then increase the throttle when the CTE remains generally stable.
- Build a single cascading controller for the throttle, with an inner controller for the steering angle (though this would mean taking ~3x more measurements for the steering controller)

## Appendix A - Dependencies

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

## Appendix B - Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)
