// SPDX-License-Identifier: MIT
/*
 * Header file for accelerometer-driver component
 * Copyright (c) 2023 Seco SpA
 */

#pragma once

#include <esp_err.h>

typedef struct {
  void *driver_object;
} mpu6500_sensor_t;

esp_err_t mpu6500_sensor_init(mpu6500_sensor_t **target_sensor);
esp_err_t accelerometer_read(mpu6500_sensor_t *sensor, float *ax, float *ay,
                             float *az);
esp_err_t gyroscope_read(mpu6500_sensor_t *sensor, float *gx, float *gy,
                         float *gz);
