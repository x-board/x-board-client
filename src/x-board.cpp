
#include "x-board.hpp"

#include <vector>
#include <cstdlib>

extern "C"
{
  #include "../lsquaredc/lsquaredc.h"
}

#define XB_MODE_ADMIN 0x00
#define XB_MODE_SET 0x01

#define XB_OP_PING 0x01
#define XB_OP_LIST_PINS_LENGTH 0x02
#define XB_OP_LIST_PINS 0x03

#define XB_OP_SET_DIGITAL 0x01
#define XB_OP_SET_ANALOG 0x02

#define XB_ANALOG_MODE_PWM 0x01

#define XB_VAL_DIGITAL_HIGH (uint8_t)0x01
#define XB_VAL_DIGITAL_LOW (uint8_t)0x00

#define XB_RESPONSE_PONG 0x01


int countReads(std::vector<uint16_t> message)
{
    int reads = 0;

    for (uint16_t b : message)
    {
        if (b == I2C_READ)
        {
            reads++;
        }
    }

    return reads;
}

std::vector<uint8_t> sendMessage(std::vector<uint16_t>  message)
{
    int responseLength = countReads(message);
    uint8_t* response = (uint8_t*)malloc(responseLength);

    int i2c_handle = i2c_open(2);
    i2c_send_sequence(i2c_handle, message.data(), message.size(), response);
    i2c_close(i2c_handle);

    std::vector<uint8_t> result(response, response + responseLength);
    free(response);

    return result;
}

uint8_t writeAddress(uint8_t address)
{
    return address << 1;
}

uint8_t readAddress(uint8_t address)
{
    return (address << 1) | 1;
}

void xboardSetDigital(uint8_t pin, bool on)
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_SET, XB_OP_SET_DIGITAL, pin, on ? XB_VAL_DIGITAL_HIGH : XB_VAL_DIGITAL_LOW};

    sendMessage(message);
}

void xboardSetPWM(uint8_t pin, uint8_t value)
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_SET, XB_OP_SET_ANALOG, XB_ANALOG_MODE_PWM, pin, value};

    sendMessage(message);
}

bool xboardPing()
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_ADMIN, XB_OP_PING, I2C_RESTART, readAddress(36), I2C_READ};

    std::vector<uint8_t> response = sendMessage(message);

    return response[0] == XB_RESPONSE_PONG;
}

std::vector<uint8_t> xboardListPins()
{
    std::vector<uint16_t> lengthMessage = {writeAddress(36), XB_MODE_ADMIN, XB_OP_LIST_PINS_LENGTH, I2C_RESTART, readAddress(36), I2C_READ };
    std::vector<uint8_t> length = sendMessage(lengthMessage);

    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_ADMIN, XB_OP_LIST_PINS, I2C_RESTART, readAddress(36)};

    for (int i = 0; i < length[0]; i++)
    {
        message.push_back(I2C_READ);
    }

    return sendMessage(message);
}
