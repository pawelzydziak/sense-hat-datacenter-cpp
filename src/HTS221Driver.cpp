#include "../include/HTS221Driver.h"
#include "../include/registers.h"
#include "../include/senseHat.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdexcept>
#include <fstream>

void HTS221Driver::calibrate()
{
	int data;

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

	if (H0_T0 > 32768)
	{
		H0_T0 -= 65536;
	}

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H1_T0_OUT_L);
	H1_T0 = data;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_H1_T0_OUT_H);
	H1_T0 |= data << 8;

	if (H1_T0 > 32768)
	{
		H1_T0 -= 65536;
	}

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T0_OUT_L);
	T0_OUT = data;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T0_OUT_H);
	T0_OUT |= data << 8;

	if (T0_OUT > 32768)
	{
		T0_OUT -= 65536;
	}

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_OUT_L);
	T1_OUT = data;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_CALIB_T1_OUT_H);
	T1_OUT |= data << 8;

	if (T1_OUT > 32768)
	{
		T1_OUT -= 65536;
	}
}

double HTS221Driver::getTemperature() const
{
	int32_t data = 0;
	int32_t temperature = 0;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_TEMP_OUT_L);
	temperature = data;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_TEMP_OUT_H);
	temperature |= data << 8;

	if (temperature > 32768) temperature -= 65536;

	return T0_DEGC_X8 / 8.0 + (temperature - T0_OUT) * (T1_DEGC_X8 - T0_DEGC_X8) / 8.0 / (T1_OUT - T0_OUT); //to calibrate with cpu temp, but for now very strange values
}

double HTS221Driver::getHumidity() const
{
	int32_t data = 0;
	int32_t humidity = 0;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_STATUS_REG);

//	if (!(data & 0b10))
//	{
//		throw std::runtime_error("The humidity sensor is not ready.");
//	}

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_HUMIDITY_OUT_L);
	humidity = data;

	data = wiringPiI2CReadReg8(device, HTS221_REGISTER_HUMIDITY_OUT_H);
	humidity |= data << 8;

	if (humidity > 32768)
	{
		humidity -= 65536;
	}

	return H0_RH_X2 / 2.0 + (humidity - H0_T0) * (H1_RH_X2 - H0_RH_X2) / 2.0 / (H1_T0 - H0_T0);
}

double HTS221Driver::CPUTempCorrection(double temp)
{
	std::string val;
	std::string preparedTemp;
	float cpuTemperature;

	std::ifstream temperatureFile("/sys/class/thermal/thermal_zone0/temp");

	temperatureFile >> val;
	temperatureFile.close();
	preparedTemp = val.insert(2, 1, '.');
	cpuTemperature = std::stod(preparedTemp);
	return temp - cpuTemperature;
}

