/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */

#ifndef ACCEL_H
#define ACCEL_H

#include "driver/i2c.h"
#include "mpu6050.h"
#include "esp_system.h"
#include "esp_log.h"

extern mpu6050_handle_t mpu6050; //= NULL;

void i2c_sensor_mpu6050_init(void);

void get_accel(mpu6050_acce_value_t *acce);
float getTemp();

#endif