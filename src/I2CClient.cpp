#include "../include/I2CClient.h"

I2CClient * I2CClient::client = nullptr;

I2CClient* I2CClient::CreateClient()
{
    if (client == nullptr)
        client = new I2CClient();
    return client;
}
