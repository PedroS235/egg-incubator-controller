#ifndef PID_CONTROLLER
#define PID_CONTROLLER

class PidController
{
private:
    float kp, ki, kd;
    float error_sum, previous_error;

public:
    /**
     * @brief Construct a new Pid Controller object
     *
     * @param kp_: Proportional value
     * @param ki_: Integral value
     * @param kd_: Derivative value
     */
    PidController(float kp_, float ki_, float kd_);

    /**
     * @brief Retrives the correction to be made to the current value
     *
     * @param setpoint: Target value
     * @param current_value: Current value where to apply the PID
     * @return Correction value
     */
    float update(float setpoint, float current_value);
};

#endif /* PID_CONTROLLER */