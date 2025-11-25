#include "main.h"
#include "mpu6050.h"
#include "pid_controller.h"
#include "motor_driver.h"

MPU6050_Data mpu_data;
PID_Controller pid;
Motor_Driver motors;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_TIM1_Init();  // For PWM motor control
    
    // Initialize modules
    MPU6050_Init(&hi2c1);
    PID_Init(&pid, 15.0, 0.5, 2.0);  // Tuned PID values
    Motor_Init(&motors, &htim1);
    
    while (1) {
        // Read sensor data
        if (MPU6050_Read_Data(&mpu_data) == HAL_OK) {
            // Calculate angle (complementary filter)
            float angle = calculate_tilt_angle(&mpu_data);
            
            // Compute PID output
            float output = PID_Compute(&pid, angle, 0.0);  // Target angle = 0 (balanced)
            
            // Drive motors
            Motor_Set_Speed(&motors, output);
        }
        HAL_Delay(10);  // 100Hz control loop
    }
}
