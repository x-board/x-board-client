
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "x-board.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("No mode or operation specified\n");
        return -1;
    }

    if (strcmp(argv[1], "set") == 0)
    {

        if (argc < 4)
        {
            printf("Not enough arguments for 'set'\n");
            return -1;
        }

        if (strncmp(argv[2], "pin:", 2) == 0)
        {
            long pin = strtol(argv[2] + 4, 0, 10);

            if (pin != 1 && (pin < 3 || pin > 5))
            {
                printf("Invalid pin number for 'set': %d\n", pin);
                return -1;
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
                    printf("Invalid value for 'set <pin> pwm': %d\n", value);
                    return -1;
                }

                if (pin != 1 && pin != 4)
                {
                    printf("Invalid pin for 'set <pin> pwm': %d\n", pin);
                    return -1;
                }

                xboardSetPWM(pin, value);
            }
            else
            {
                printf("Invalid value for 'set <pin>': %s\n", argv[3]);
                return -1;
            }
        }
        else
        {
            printf("Unexpected argument for 'set'\n");
            return -1;
        }
    }
    else
    {
        printf("Unknown mode: %s\n", argv[1]);
        return -1;
    }

    return 0;
}
