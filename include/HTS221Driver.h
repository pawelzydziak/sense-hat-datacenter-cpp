#ifndef SENSEHAT_DATACENTRE_HTS221DRIVER_H
#define SENSEHAT_DATACENTRE_HTS221DRIVER_H


static constexpr auto HTS221_DEVICE_ADDRESS = 0x5F;

class HTS221Driver
{
public:
	explicit HTS221Driver(int fd) : device(fd){};

	virtual ~HTS221Driver() = default;

	void calibrate();

	static double CPUTempCorrection(double temp);

	double getHumidity() const;

	double getTemperature() const;

public:
	int device;
	int H0_RH_X2 = 0, H1_RH_X2 = 0, T0_DEGC_X8 = 0, T1_DEGC_X8 = 0, T1_T0_MSB = 0, H0_T0 = 0, H1_T0 = 0, T0_OUT = 0, T1_OUT = 0;
};


#endif //SENSEHAT_DATACENTRE_HTS221DRIVER_H
