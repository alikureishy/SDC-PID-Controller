#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::init(double Kp_, double Kd_, double Ki_) {
  // Initialize gain coefficients:
  this->Kp = Kp_;
  this->Kd = Kd_;
  this->Ki = Ki_;

  // Initialize coefficient errors:
  this->p_error = 0.0;
  this->d_error = 0.0;
  this->i_error = 0.0;
}

void PID::updateError(double cte) {
  this->d_error = cte - this->p_error;
  this->i_error += cte;
  this->p_error = cte;
}

double PID::totalError() {
  return this->i_error;
}

double PID::getControlSignal() {
  double signal = -(this->Kp * this->p_error) - (this->Kd * this->d_error) - (this->Ki * this->i_error);
  return signal;
}