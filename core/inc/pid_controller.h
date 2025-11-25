#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <stdint.h>

// PID limits for anti-windup
#define MAX_OUTPUT       100.0
#define MIN_OUTPUT       -100.0
#define INTEGRAL_LIMIT   50.0

typedef struct {
    float kp;           // Proportional gain
    float ki;           // Integral gain
    float kd;           // Derivative gain
    float integral;     // Integral sum
    float prev_error;   // Previous error for derivative
    float output;       // PID output
    uint32_t last_time; // Last computation time
} PID_Controller;

// Function prototypes
void PID_Init(PID_Controller *pid, float kp, float ki, float kd);
float PID_Compute(PID_Controller *pid, float setpoint, float measured_value);
void PID_Reset(PID_Controller *pid);
void PID_Set_Tuning(PID_Controller *pid, float kp, float ki, float kd);

#endif /* PID_CONTROLLER_H */
