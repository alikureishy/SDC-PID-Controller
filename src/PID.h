#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Kd_, Ki_) The initial PID coefficients
   */
  void init(double Kp_, double Kd_, double Ki_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void updateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double totalError();

  /**
   * Calculates the control signal to be sent to the device
   * being controlled.
   */
  double getControlSignal();

private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */
  double Kp;
  double Ki;
  double Kd;
};

#endif  // PID_H