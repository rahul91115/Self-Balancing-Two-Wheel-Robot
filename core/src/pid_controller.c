#include "pid_controller.h"

void PID_Init(PID_Controller *pid, float kp, float ki, float kd) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->integral = 0;
    pid->prev_error = 0;
}

float PID_Compute(PID_Controller *pid, float current, float target) {
    float error = target - current;
    
    // Proportional
    float proportional = pid->kp * error;
    
    // Integral with anti-windup
    pid->integral += error;
    if (pid->integral > INTEGRAL_LIMIT) pid->integral = INTEGRAL_LIMIT;
    if (pid->integral < -INTEGRAL_LIMIT) pid->integral = -INTEGRAL_LIMIT;
    float integral = pid->ki * pid->integral;
    
    // Derivative
    float derivative = pid->kd * (error - pid->prev_error);
    pid->prev_error = error;
    
    return proportional + integral + derivative;
}
