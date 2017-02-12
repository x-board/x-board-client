
#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc != 2 || (strcmp(argv[1], "HIGH") != 0 && strcmp(argv[1], "LOW") != 0))
    {
        printf("Failed\n");
        printf("argc: %d\n", argc);
        return -1;
    }

    int i2c_handle = i2c_open(2);
    uint16_t msg[] = {36<<1, 0x01, 0x01, 0x01, strcmp(argv[1], "LOW") == 0 ? 0x00 : 0x01};

    i2c_send_sequence(i2c_handle, msg, 5, 0);

    return 0;
}
