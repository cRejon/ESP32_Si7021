/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_system.h"
*/
#include "driver/i2c.h"

#include "si7021.h"


float si7021_read_hum(void)
{
    uint8_t data_h, data_l;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SI7021_DEFAULT_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, SI7021_MEASRH_HOLD_CMD, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    
    vTaskDelay(30 / portTICK_RATE_MS);
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SI7021_DEFAULT_ADDRESS << 1 | READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &data_h, ACK_VAL);
    i2c_master_read_byte(cmd, &data_l, NACK_VAL);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    uint16_t hum = data_h << 8 | data_l;

    float humidity = hum;
    humidity *= 125;
    humidity /= 65536;
    humidity -= 6;

    return humidity > 100.0 ? 100.0 : humidity;
}

float si7021_read_temp(void)
{
    uint8_t data_h, data_l;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SI7021_DEFAULT_ADDRESS << 1 | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, SI7021_READPREVTEMP_CMD, ACK_CHECK_EN);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SI7021_DEFAULT_ADDRESS << 1 | READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &data_h, ACK_VAL);
    i2c_master_read_byte(cmd, &data_l, NACK_VAL);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    uint16_t temp = data_h << 8 | data_l;

    float temperature = temp;
    temperature *= 175.72;
    temperature /= 65536;
    temperature -= 46.85;

    return temperature;
}

esp_err_t si7021_i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, 0, 0, 0);
}

