
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define XB_MODE_SET 0x01

#define XB_OP_SET_DIGITAL 0x01

#define XB_VAL_DIGITAL_HIGH 1
#define XB_VAL_DIGITAL_LOW 0

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("No mode or operation specified\n");
        return -1;
    }

    uint16_t message[] = {36<<1, 0, 0, 0, 0};
    int messageLength = 0;

    if (strcmp(argv[1], "set") == 0)
    {
        message[1] = XB_MODE_SET;

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
                printf("Invalid pin number for 'set'\n");
                return -1;
            }

            message[2] = XB_OP_SET_DIGITAL;
            message[3] = pin;

            if (strcmp(argv[3], "high") == 0)
            {
                message[4] = XB_VAL_DIGITAL_HIGH;
                messageLength = 5;
            }
            else if (strcmp(argv[3], "low") == 0)
            {
                message[4] = XB_VAL_DIGITAL_LOW;
                messageLength = 5;
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

    int i2c_handle = i2c_open(2);

    i2c_send_sequence(i2c_handle, message, messageLength, 0);

    return 0;
}
