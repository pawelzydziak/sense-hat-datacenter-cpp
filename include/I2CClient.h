#ifndef SENSEHAT_DATACENTRE_I2CCLIENT_H
#define SENSEHAT_DATACENTRE_I2CCLIENT_H

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <cerrno>
#include <memory>
class I2CClient
{
protected:
    I2CClient()= default;
    static I2CClient* client;

public:
    I2CClient(I2CClient &) = delete;
    void operator=(const I2CClient&) = delete;

    static I2CClient* CreateClient();

};


#endif //SENSEHAT_DATACENTRE_I2CCLIENT_H
