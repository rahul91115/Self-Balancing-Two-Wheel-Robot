#include "motor_driver.h"

void Motor_Init(Motor_Driver *motor, TIM_HandleTypeDef *htim) {
    motor->htim = htim;
    motor->speed = 0;
    
    // Start PWM for both motors
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);  // Motor 1
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);  // Motor 2
}

void Motor_Set_Speed(Motor_Driver *motor, float speed) {
    // Limit speed to safe range
    if (speed > MAX_SPEED) speed = MAX_SPEED;
    if (speed < -MAX_SPEED) speed = -MAX_SPEED;
    
    // Convert to PWM duty cycle
    uint16_t pwm_value = (uint16_t)(fabs(speed) * 100);
    
    // Set direction pins and PWM
    if (speed >= 0) {
        // Forward direction
        HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, GPIO_PIN_SET);
    } else {
        // Reverse direction
        HAL_GPIO_WritePin(MOTOR1_DIR_GPIO_Port, MOTOR1_DIR_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR2_DIR_GPIO_Port, MOTOR2_DIR_Pin, GPIO_PIN_RESET);
    }
    
    // Set PWM duty cycle
    __HAL_TIM_SET_COMPARE(motor->htim, TIM_CHANNEL_1, pwm_value);
    __HAL_TIM_SET_COMPARE(motor->htim, TIM_CHANNEL_2, pwm_value);
}
