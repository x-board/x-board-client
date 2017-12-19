
#include <iostream>
#include <string>
#include <vector>

#include "x-board.hpp"

int invalidFormat()
{
    std::cout << std::endl;
    std::cout << "x-board expects a command in one of the following formats:" << std::endl;
    std::cout << std::endl;
    std::cout << "x-board set pin:<0-255> <high|low>" << std::endl;
    std::cout << "x-board set pin:<0-255> pwm:<0-255>" << std::endl;
    std::cout << std::endl;

    return -1;
}

int invalidPin(int pin)
{
    std::cout << "This board does not have a pin " << pin << "." << std::endl;

    return -1;
}

int invalidPinFunctionality(long pin, std::string functionality)
{
    std::cout << "This board does not support " << functionality << " on pin " << pin << "." << std::endl;

    return -1;
}

int main(int argc, char** argv)
{
    std::vector<std::string> args(argv, argv + argc);

    if (args.size() < 4)
    {
        return invalidFormat();
    }

    if (args[1] == "set")
    {
        if (args[2].compare(0, 4, "pin:") == 0)
        {
            int pin = std::stoi(args[2].substr(4));

            if (pin != 1 && (pin < 3 || pin > 5))
            {
                return invalidPin(pin);
            }

            if (args[3] == "high")
            {
                xboardSetDigital(pin, true);
            }
            else if (args[3] == "low")
            {
                xboardSetDigital(pin, false);
            }
            else if (args[3].compare(0, 4, "pwm:") == 0)
            {
                int value = std::stoi(args[3].substr(4));

                if (value < 0 || value > 255)
                {
                    return invalidFormat();
                }

                if (pin != 1 && pin != 4)
                {
                    return invalidPinFunctionality(pin, args[3]);
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
