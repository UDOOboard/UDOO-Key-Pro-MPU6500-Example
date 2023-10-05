// SPDX-License-Identifier: MIT
/*
 * Main file for example firmware
 * Copyright (c) 2023 Seco SpA
 */

#include <accelerometer-driver.h>
#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char *TAG = "mpu6500-tester";

void app_main() {
  mpu6500_sensor_t *sensor = NULL;

  ESP_ERROR_CHECK(mpu6500_sensor_init(&sensor));

  while (1) {
    float a_x, a_y, a_z, g_x, g_y, g_z;
    ESP_ERROR_CHECK(accelerometer_read(sensor, &a_x, &a_y, &a_z));
    ESP_LOGI(TAG, "A (x, y, z) : (%+6.2f, %+6.2f, %+6.2f)", a_x, a_y, a_z);
    ESP_ERROR_CHECK(gyroscope_read(sensor, &g_x, &g_y, &g_z));
    ESP_LOGI(TAG, "G (x, y, z) : (%+6.2f, %+6.2f, %+6.2f)", g_x, g_y, g_z);

    vTaskDelay(pdMS_TO_TICKS(4000));
  }
}