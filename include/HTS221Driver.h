//
// Created by darlo on 22/10/2021.
//

#ifndef SENSEHAT_DATACENTRE_HTS221DRIVER_H
#define SENSEHAT_DATACENTRE_HTS221DRIVER_H


static constexpr auto HTS221_DEVICE_ADDRESS = 0x5F;

class HTS221Driver
{
public:
	HTS221Driver(int fd) : device(fd){};

	virtual ~HTS221Driver() = default;

	void calibrate();
	static double CPUTempCorrection(double temp);

	double getHumidity();

	double getTemperature();

public:
	int device;
	int H0_RH_X2, H1_RH_X2, T0_DEGC_X8, T1_DEGC_X8, T1_T0_MSB, H0_T0, H1_T0, T0_OUT, T1_OUT;
};


#endif //SENSEHAT_DATACENTRE_HTS221DRIVER_H
