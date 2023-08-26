
/*
 * PinCommander - Controller
 *
 * Author: Superhac
 *
 *  Generic Public Domain - AKA do whatever you want!
 */

#include "accel.h"

static const char *TAG = "accel.c";

#define I2C_MASTER_SCL_IO 4       /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 5       /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_0  /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 400000 /*!< I2C master clock frequency */

mpu6050_handle_t mpu6050 = NULL;

static void i2c_bus_init(void)
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    esp_err_t ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    ret = i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

extern void i2c_sensor_mpu6050_init(void)
{
    esp_err_t ret;

    i2c_bus_init();
    mpu6050 = mpu6050_create(I2C_MASTER_NUM, MPU6050_I2C_ADDRESS);
    ret = mpu6050_config(mpu6050, ACCE_FS_4G, GYRO_FS_500DPS);
    ret = mpu6050_wake_up(mpu6050);
}

extern void get_accel(mpu6050_acce_value_t *acce)
{
    esp_err_t ret;
    ret = mpu6050_get_acce(mpu6050, acce);
    // printf("acce_x:%.2f, acce_y:%.2f, acce_z:%.2f\n", acce.acce_x, acce.acce_y, acce.acce_z);
}

extern float getTemp()
{
    esp_err_t ret;
    mpu6050_temp_value_t temp;

    ret = mpu6050_get_temp(mpu6050, &temp);
    printf("t:%.2f \n", temp.temp);

    return temp.temp;
}
