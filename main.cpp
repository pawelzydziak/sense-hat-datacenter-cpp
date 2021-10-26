#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "include/senseHat.h"
#include "include/HTS221Driver.h"

static constexpr auto HTS221_REGISTER_STATUS_REG = 0x27;
static constexpr auto HTS221_REGISTER_TEMP_OUT_L = 0x2A;
static constexpr auto HTS221_REGISTER_TEMP_OUT_H = 0x2B;

int main()
{
	auto fd = wiringPiI2CSetup(humidityAddres);
	std::cout << fd << std::endl;

	HTS221Driver d(fd);

	d.calibrate();


	std::cout << d.getTemperature() << std::endl;
	std::cout << "Cpu corrected tmp " << HTS221Driver::CPUTempCorrection(d.getTemperature()) << std::endl;
	std::cout << "Humidity: " << d.getHumidity() << std::endl;
	return 0;
}
