#ifndef MPU6050_H
#define MPU6050_H

#include "stm32f4xx_hal.h"
#include <math.h>

// MPU6050 Register Map
#define MPU6050_ADDR                 0x68 << 1
#define MPU6050_WHO_AM_I             0x75
#define MPU6050_PWR_MGMT_1           0x6B
#define MPU6050_ACCEL_CONFIG         0x1C
#define MPU6050_GYRO_CONFIG          0x1B
#define MPU6050_ACCEL_XOUT_H         0x3B

// Sensitivity scales
#define ACCEL_SENSITIVITY_4G         8192.0  // LSB/g
#define GYRO_SENSITIVITY_500DPS      65.5    // LSB/°/s

typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    float temperature;
} MPU6050_Data;

// Function prototypes
HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_Read_Data(MPU6050_Data *data);
HAL_StatusTypeDef MPU6050_Read_Raw(int16_t *accel, int16_t *gyro);
float calculate_tilt_angle(MPU6050_Data *data);
HAL_StatusTypeDef MPU6050_Calibrate(uint16_t samples);

#endif /* MPU6050_H */
