
#include "x-board.hpp"

#include <vector>

extern "C"
{
  #include "../lsquaredc/lsquaredc.h"
}

#define XB_MODE_SET 0x01

#define XB_OP_SET_DIGITAL 0x01
#define XB_OP_SET_ANALOG 0x02

#define XB_ANALOG_MODE_PWM 0x01

#define XB_VAL_DIGITAL_HIGH (uint8_t)0x01
#define XB_VAL_DIGITAL_LOW (uint8_t)0x00


void sendMessage(std::vector<uint16_t>  message)
{
    int i2c_handle = i2c_open(2);

    i2c_send_sequence(i2c_handle, message.data(), message.size(), 0);

    i2c_close(i2c_handle);
}

void xboardSetDigital(uint8_t pin, bool on)
{
    std::vector<uint16_t> message = {36<<1, XB_MODE_SET, XB_OP_SET_DIGITAL, pin, on ? XB_VAL_DIGITAL_HIGH : XB_VAL_DIGITAL_LOW};

    sendMessage(message);
}

void xboardSetPWM(uint8_t pin, uint8_t value)
{
    std::vector<uint16_t> message = {36<<1, XB_MODE_SET, XB_OP_SET_ANALOG, XB_ANALOG_MODE_PWM, pin, value};

    sendMessage(message);
}
