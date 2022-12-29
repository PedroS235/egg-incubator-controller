#include <pid_controller.h>

PidController::PidController(float kp_, float ki_, float kd_)
{
    kp = kp_;
    ki = ki_;
    kd = kd_;
}

float PidController::update(float setpoint, float current_value)
{
    // Compute the error
    float error = setpoint - current_value;

    // Compute P term
    float p = kp * error;

    // Compute I term
    error_sum += error;
    float i = ki * error_sum;

    // Compute D term
    float d = kd * (error - previous_error);

    // Compute correction
    float correction = p + i + d;

    previous_error = error;
    return correction;
}