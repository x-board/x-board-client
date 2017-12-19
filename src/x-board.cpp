
#include "x-board.hpp"

extern "C"
{
  #include "../lsquaredc/lsquaredc.h"
}

#define XB_MODE_SET 0x01

#define XB_OP_SET_DIGITAL 0x01
#define XB_OP_SET_ANALOG 0x02

#define XB_ANALOG_MODE_PWM 0x01

#define XB_VAL_DIGITAL_HIGH 1
#define XB_VAL_DIGITAL_LOW 0


void sendMessage(uint16_t* message, int size)
{
    int i2c_handle = i2c_open(2);

    i2c_send_sequence(i2c_handle, message, size, 0);

    i2c_close(i2c_handle);
}

void xboardSetDigital(uint8_t pin, bool on)
{
    uint16_t message[] = {36<<1, XB_MODE_SET, XB_OP_SET_DIGITAL, pin, on ? XB_VAL_DIGITAL_HIGH : XB_VAL_DIGITAL_LOW};

    sendMessage(message, 5);
}

void xboardSetPWM(uint8_t pin, uint8_t value)
{
    uint16_t message[] = {36<<1, XB_MODE_SET, XB_OP_SET_ANALOG, XB_ANALOG_MODE_PWM, pin, value};

    sendMessage(message, 6);
}
