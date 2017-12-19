
#include <cstdint>
#include <cstdbool>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "x-board.hpp"

int invalidFormat()
{
    printf("\n");
    printf("x-board expects a command in one of the following formats:\n");
    printf("\n");
    printf("x-board set pin:<0-255> <high|low>\n");
    printf("x-board set pin:<0-255> pwm:<0-255>\n");
    printf("\n");

    return -1;
}

int invalidPin(int pin)
{
    printf("This board does not have a pin %d.\n", pin);

    return -1;
}

int invalidPinFunctionality(long pin, char* functionality)
{
    printf("This board does not support %s on pin %d.\n", functionality, pin);

    return -1;
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        return invalidFormat();
    }

    if (strcmp(argv[1], "set") == 0)
    {
        if (strncmp(argv[2], "pin:", 2) == 0)
        {
            long pin = strtol(argv[2] + 4, 0, 10);

            if (pin != 1 && (pin < 3 || pin > 5))
            {
                return invalidPin(pin);
            }

            if (strcmp(argv[3], "high") == 0)
            {
                xboardSetDigital(pin, true);
            }
            else if (strcmp(argv[3], "low") == 0)
            {
                xboardSetDigital(pin, false);
            }
            else if (strncmp(argv[3], "pwm:", 4) == 0)
            {
                long value = strtol(argv[3] + 4, 0, 10);

                if (value < 0 || value > 255)
                {
                    return invalidFormat();
                }

                if (pin != 1 && pin != 4)
                {
                    return invalidPinFunctionality(pin, argv[3]);
                }

                xboardSetPWM(pin, value);
            }
            else
            {
                return invalidFormat();
            }
        }
        else
        {
            return invalidFormat();
        }
    }
    else
    {
        return invalidFormat();
    }

    return 0;
}
