// SPDX-License-Identifier: MIT
/*
 * Source file for MPU driver wrapper
 * Copyright (c) 2023 Seco SpA
 */

#include <esp_err.h>
#include <esp_log.h>

#include <I2Cbus.hpp>
#include <MPU.hpp>
#include <mpu/math.hpp>

static const char *TAG = "MPU-driver-wrapper";

extern "C" MPU_t *mpu_get_new_driver_object() {
  MPU_t *sensor = NULL;
  esp_err_t res = ESP_OK;

  i2c0.begin(GPIO_NUM_18, GPIO_NUM_21, 400000);

  sensor = new MPU_t();
  sensor->setBus(i2c0);
  sensor->setAddr(mpud::MPU_I2CADDRESS_AD0_HIGH);

  if ((res = sensor->testConnection()) != ESP_OK) {
    ESP_LOGE(TAG, "Failed to connect to the MPU, error=%#X (%s)", res,
             esp_err_to_name(res));
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  ESP_ERROR_CHECK(sensor->initialize());

  return sensor;
}

extern "C" esp_err_t mpu_accelerometer_read(MPU_t *MPU_driver, float *x,
                                            float *y, float *z) {
  mpud::raw_axes_t accelRaw;
  mpud::float_axes_t accelG;

  /* Reading */
  MPU_driver->acceleration(&accelRaw);
  /* Converting */
  accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);

  *x = accelG.x;
  *y = accelG.y;
  *z = accelG.z;

  return ESP_OK;
}

extern "C" esp_err_t mpu_gyroscope_read(MPU_t *MPU_driver, float *x, float *y,
                                        float *z) {
  mpud::raw_axes_t gyroRaw;
  mpud::float_axes_t gyroDPS;

  // Reading
  MPU_driver->rotation(&gyroRaw);
  // Converting
  gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);

  *x = gyroDPS[0];
  *y = gyroDPS[1];
  *z = gyroDPS[2];

  return ESP_OK;
}
