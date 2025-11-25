#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "stm32f4xx_hal.h"

// Motor limits
#define MAX_SPEED         100.0   // Maximum speed percentage
#define MIN_SPEED         -100.0  // Minimum speed percentage
#define PWM_MAX           1000    // Maximum PWM value

// Motor direction pins (adjust according to your hardware)
#define MOTOR1_DIR_Pin    GPIO_PIN_0
#define MOTOR1_DIR_Port   GPIOC
#define MOTOR2_DIR_Pin    GPIO_PIN_1
#define MOTOR2_DIR_Port   GPIOC

typedef struct {
    TIM_HandleTypeDef *htim;
    float speed;
    uint32_t pwm_channel1;
    uint32_t pwm_channel2;
} Motor_Driver;

// Function prototypes
void Motor_Init(Motor_Driver *motor, TIM_HandleTypeDef *htim, 
                uint32_t channel1, uint32_t channel2);
void Motor_Set_Speed(Motor_Driver *motor, float speed);
void Motor_Stop(Motor_Driver *motor);
void Motor_Set_Direction(uint8_t motor_num, uint8_t direction);

#endif /* MOTOR_DRIVER_H */
