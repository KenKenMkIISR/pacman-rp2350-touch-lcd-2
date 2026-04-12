/*----------------------------------------------------------------------------

Copyright (C) 2026, KenKen, all right reserved.

This program supplied herewith by KenKen is free software; you can
redistribute it and/or modify it under the terms of the same license written
here and only for non-commercial purpose.

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of FITNESS FOR A PARTICULAR
PURPOSE. The copyright owner and contributors are NOT LIABLE for any damages
caused by using this program.

----------------------------------------------------------------------------*/
#define I2C_SDA 12
#define I2C_SCL 13
#define I2C_CH i2c0
#define QMI8658_AD 0x6b
int init_imu(void);
void check_imu(void);
void read_qmi8658(void);
extern int16_t acc_x, acc_y, acc_z, gyr_x, gyr_y, gyr_z;
extern int16_t acc_x1, acc_y1, acc_z1, gyr_x1, gyr_y1, gyr_z1;
extern uint8_t imu_key,imu_nocked;
