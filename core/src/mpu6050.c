#include "mpu6050.h"

#define MPU6050_ADDR 0x68 << 1
#define PWR_MGMT_1   0x6B
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG  0x1B

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    // Wake up MPU6050
    uint8_t data = 0x00;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, PWR_MGMT_1, 1, &data, 1, 100);
    
    // Configure accelerometer ±4g
    data = 0x08;
    status |= HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, ACCEL_CONFIG, 1, &data, 1, 100);
    
    // Configure gyroscope ±500°/s
    data = 0x08;
    status |= HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, GYRO_CONFIG, 1, &data, 1, 100);
    
    return status;
}

HAL_StatusTypeDef MPU6050_Read_Data(MPU6050_Data *data) {
    uint8_t buffer[14];
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, 0x3B, 1, buffer, 14, 100);
    
    if (status == HAL_OK) {
        data->accel_x = (int16_t)(buffer[0] << 8 | buffer[1]);
        data->accel_y = (int16_t)(buffer[2] << 8 | buffer[3]);
        data->accel_z = (int16_t)(buffer[4] << 8 | buffer[5]);
        data->gyro_x = (int16_t)(buffer[8] << 8 | buffer[9]);
        data->gyro_y = (int16_t)(buffer[10] << 8 | buffer[11]);
        data->gyro_z = (int16_t)(buffer[12] << 8 | buffer[13]);
    }
    return status;
}

float calculate_tilt_angle(MPU6050_Data *data) {
    // Complementary filter to combine accelerometer and gyroscope data
    static float angle = 0;
    static uint32_t prev_time = 0;
    uint32_t current_time = HAL_GetTick();
    float dt = (current_time - prev_time) / 1000.0f;
    
    // Accelerometer angle
    float accel_angle = atan2(data->accel_y, data->accel_z) * 180 / M_PI;
    
    // Gyroscope angle integration
    angle = 0.98 * (angle + data->gyro_x * dt) + 0.02 * accel_angle;
    
    prev_time = current_time;
    return angle;
}
