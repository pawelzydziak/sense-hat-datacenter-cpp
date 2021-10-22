#include "../include/HTS221Driver.h"
#include "../include/registers.h"
#include "../include/senseHat.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdexcept>

void HTS221Driver::calibrate()
{
    int data = 0;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H0_RH_X2);
    H0_RH_X2 = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H1_RH_X2);
    H1_RH_X2 = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T0_DEGC_X8);
    T0_DEGC_X8 = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_T0_MSB);
    T0_DEGC_X8 |= (data & 0x03) << 8;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_DEGC_X8);
    T1_DEGC_X8 = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_T0_MSB);
    T1_DEGC_X8 |= (data & 0x0C) << 6;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H0_T0_OUT_L);
    H0_T0 = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H0_T0_OUT_H);
    H0_T0 |= data << 8;

    if (H0_T0 > 32768) {
        H0_T0 -= 65536;
    }

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H1_T0_OUT_L);
    H1_T0 = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H1_T0_OUT_H);
    H1_T0 |= data << 8;

    if (H1_T0 > 32768) {
        H1_T0 -= 65536;
    }

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T0_OUT_L);
    T0_OUT = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T0_OUT_H);
    T0_OUT |= data << 8;

    if (T0_OUT > 32768) {
        T0_OUT -= 65536;
    }

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_OUT_L);
    T1_OUT = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_OUT_H);
    T1_OUT |= data << 8;

    if (T1_OUT > 32768) {
        T1_OUT -= 65536;
    }
}

double HTS221Driver::getTemperature()
{
    int32_t data = 0;
    int32_t temperature = 0;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_TEMP_OUT_L);
    temperature = data;

    data = wiringPiI2CReadReg8(device, HTS221_REGISTER_TEMP_OUT_H);
    temperature |= data << 8;

    if (temperature > 32768) {
        temperature -= 65536;
    }

    return T0_DEGC_X8 / 8.0 + (temperature - T0_OUT) * (T1_DEGC_X8 - T0_DEGC_X8) / 8.0 / (T1_OUT - T0_OUT);
}

