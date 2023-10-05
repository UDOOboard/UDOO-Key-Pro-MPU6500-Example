// SPDX-License-Identifier: MIT
/*
 * Implementation file for accelerometer-driver component functions
 * Copyright (c) 2023 Seco SpA
 */

#include <esp_err.h>
#include <esp_log.h>

#include <string.h>

#include <accelerometer-driver.h>

const char *TAG = "accelerometer-driver";

extern void *mpu_get_new_driver_object();
extern esp_err_t mpu_accelerometer_read(void *, float *, float *, float *);
extern esp_err_t mpu_gyroscope_read(void *, float *, float *, float *);

esp_err_t mpu6500_sensor_init(mpu6500_sensor_t **target_sensor) {
  if (*target_sensor != NULL) {
    ESP_LOGE(TAG, "Target sensor structure already existing!");
    return ESP_ERR_INVALID_ARG;
  }

  *target_sensor = (mpu6500_sensor_t *)malloc(sizeof(mpu6500_sensor_t));
  memset(*target_sensor, '\0', sizeof(mpu6500_sensor_t));

  (*target_sensor)->driver_object = mpu_get_new_driver_object();

  return ESP_OK;
}

esp_err_t accelerometer_read(mpu6500_sensor_t *sensor, float *ax, float *ay,
                             float *az) {
  return mpu_accelerometer_read(sensor->driver_object, ax, ay, az);
}

esp_err_t gyroscope_read(mpu6500_sensor_t *sensor, float *gx, float *gy,
                         float *gz) {
  return mpu_gyroscope_read(sensor->driver_object, gx, gy, gz);
}
