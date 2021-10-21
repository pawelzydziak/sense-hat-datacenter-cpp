#include <iostream>
#include "include/I2CClient.h"

int main()
{
    auto a = I2CClient::CreateClient();
    std::cout << (a == nullptr);
    return 0;
}
