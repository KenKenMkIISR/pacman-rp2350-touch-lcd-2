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
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "qmi8658.h"

#define TILTSHRESHOLD 2500
#define NOCKTIME 10
#define NOCKTHRESHOLD 50000000

int16_t acc_x, acc_y, acc_z, gyr_x, gyr_y, gyr_z;
int16_t acc_x1, acc_y1, acc_z1, gyr_x1, gyr_y1, gyr_z1;
uint8_t imu_key,imu_nocked;

void check_imu(void){
    static int nocking=0,nockingcounter;
    read_qmi8658();
    imu_key=0;
    if(acc_x>TILTSHRESHOLD) imu_key|=1;
    else if(acc_x<-TILTSHRESHOLD) imu_key|=2;
    if(acc_y>TILTSHRESHOLD) imu_key|=4;
    else if(acc_y<-TILTSHRESHOLD) imu_key|=8;

    int dx=acc_x-acc_x1;
    int dy=acc_y-acc_y1;
    int dz=acc_z-acc_z1;
    int d=dx*dx+dy*dy+dz*dz;
	if(!nocking){
		if(d>=NOCKTHRESHOLD){
			nocking=1;
			nockingcounter=0;
			imu_nocked=1;
		}
	}
	else{
		nockingcounter++;
		if(d<NOCKTHRESHOLD && nockingcounter>NOCKTIME){
			nocking=0;
		}
        imu_nocked=0;
	}
}

void read_qmi8658(void){
    uint8_t reg;
    uint16_t i2cbuf[6];
    reg=0x35;
    i2c_write_blocking(I2C_CH, QMI8658_AD, &reg, 1, true);
    i2c_read_blocking(I2C_CH, QMI8658_AD, (uint8_t *)i2cbuf, 12, false);
    acc_x1=acc_x;
    acc_y1=acc_y;
    acc_z1=acc_z;
    gyr_x1=gyr_x;
    gyr_y1=gyr_y;
    gyr_z1=gyr_z;
    acc_x=i2cbuf[0];
    acc_y=i2cbuf[1];
    acc_z=i2cbuf[2];
    gyr_x=i2cbuf[3];
    gyr_y=i2cbuf[4];
    gyr_z=i2cbuf[5];
}

int init_imu(void){
    uint8_t reg, id=0;
    uint8_t conf[]={2,0x40,3,0x16,4,0x56,8,0x03};
    i2c_init(I2C_CH, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    reg=0;
    i2c_write_blocking(I2C_CH, QMI8658_AD, &reg, 1, false);
    sleep_ms(100);
    i2c_write_blocking(I2C_CH, QMI8658_AD, &reg, 1, true);
    i2c_read_blocking(I2C_CH, QMI8658_AD, &id, 1, false);
    if(id!=0x05) return 1; // chip id error

    i2c_write_blocking(I2C_CH, QMI8658_AD, &conf[0], 2, false);
    i2c_write_blocking(I2C_CH, QMI8658_AD, &conf[2], 2, false);
    i2c_write_blocking(I2C_CH, QMI8658_AD, &conf[4], 2, false);
    i2c_write_blocking(I2C_CH, QMI8658_AD, &conf[6], 2, false);
    sleep_ms(100);
    read_qmi8658();
    acc_x1=acc_x;
    acc_y1=acc_y;
    acc_z1=acc_z;
    gyr_x1=gyr_x;
    gyr_y1=gyr_y;
    gyr_z1=gyr_z;
    return 0;
}
