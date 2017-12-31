//
// This file is governed by the MITA license
// which can be found as MITA.LICENSE in the root of this project
// (or alternative at mita.jasperhorn.nl)
//

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
#define XB_OP_PROTOCOL_VERSION 0x02
#define XB_OP_LIST_PINS_LENGTH 0x03
#define XB_OP_LIST_PINS 0x04
#define XB_OP_LIST_CAPABILITIES_LENGTH 0x05
#define XB_OP_LIST_CAPABILITIES 0x06
#define XB_OP_DEVICE_IDENTIFIER 0x07
#define XB_OP_DEVICE_VERSION 0x08

#define XB_OP_SET_DIGITAL 0x01
#define XB_OP_SET_ANALOG 0x02
#define XB_OP_SET_BLINK 0x04

#define XB_ANALOG_MODE_PWM 0x02

#define XB_BLINK_MODE_DIGITAL 0x01

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

    for (int i = 0; i < responseLength; i++)
    {
        response[i] = -1;
    }

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

void xboardSetDigitalBlink(uint8_t pin, uint8_t onTime, uint8_t offTime, uint8_t shiftTime)
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_SET, XB_OP_SET_BLINK, XB_BLINK_MODE_DIGITAL, pin, onTime, offTime, shiftTime};

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

std::vector<uint8_t> xboardListCapabilities()
{
    std::vector<uint16_t> lengthMessage = {writeAddress(36), XB_MODE_ADMIN, XB_OP_LIST_CAPABILITIES_LENGTH, I2C_RESTART, readAddress(36), I2C_READ, I2C_READ };
    std::vector<uint8_t> lengthResponse = sendMessage(lengthMessage);

    uint16_t length = (((uint16_t)lengthResponse[0]) << 8) + lengthResponse[1];

    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_ADMIN, XB_OP_LIST_CAPABILITIES, I2C_RESTART, readAddress(36)};

    for (int i = 0; i < length; i++)
    {
        message.push_back(I2C_READ);
    }

    return sendMessage(message);
}

uint16_t xboardReportDeviceIdentifier()
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_ADMIN, XB_OP_DEVICE_IDENTIFIER, I2C_RESTART, readAddress(36), I2C_READ, I2C_READ};

    std::vector<uint8_t> response = sendMessage(message);

    return ((uint16_t)response[0] << 8) + response[1];
}

Version xboardReportDeviceVersion()
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_ADMIN, XB_OP_DEVICE_VERSION, I2C_RESTART, readAddress(36), I2C_READ, I2C_READ, I2C_READ, I2C_READ};

    std::vector<uint8_t> response = sendMessage(message);

    return Version(response[0], response[1], response[2], response[3]);
}

Version xboardReportProtocolVersion()
{
    std::vector<uint16_t> message = {writeAddress(36), XB_MODE_ADMIN, XB_OP_PROTOCOL_VERSION, I2C_RESTART, readAddress(36), I2C_READ, I2C_READ, I2C_READ, I2C_READ};

    std::vector<uint8_t> response = sendMessage(message);

    return Version(response[0], response[1], response[2], response[3]);
}

