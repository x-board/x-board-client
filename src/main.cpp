
#include <iostream>
#include <string>
#include <vector>

#include "x-board.hpp"
#include "Version.hpp"

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

    if (args.size() < 1)
    {
        invalidFormat();
    }

    if (args[1] == "ping")
    {
        if (xboardPing())
        {
            std::cout << "Pong!" << std::endl;

            return 0;
        }
        else
        {
            std::cout << "*chirp* *chirp*" << std::endl;

            return -1;
        }
    }

    if (args.size() < 2)
    {
        invalidFormat();
    }

    if (args[1] == "list")
    {
        if (args[2] == "pins")
        {
            std::vector<uint8_t> pins = xboardListPins();

            bool first = true;
            bool pair = false;
            uint8_t leftPin;

            for (uint8_t pin : pins)
            {
                if (!pair)
                {
                    leftPin = pin;
                    pair = true;
                    continue;
                }

                pair = false;

                if (first)
                {
                    first = false;
                }
                else
                {
                    std::cout << ", ";
                }

                std::cout << (int)leftPin;

                if (leftPin != pin)
                {
                    std::cout << "-" << (int)pin;
                }
            }

            std::cout << std::endl;

            return 0;
        }
        else if (args[2] == "capabilities")
        {
            std::vector<uint8_t> capabilities = xboardListCapabilities();

            bool first = true;

            std::cout << "{";

            for (uint8_t capability : capabilities)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    std::cout << ", ";
                }

                std::cout << (int)capability;
            }

            std::cout << "}" << std::endl;

            return 0;
        }
    }
    else if (args[1] == "report")
    {
        if (args[2] == "device")
        {
            uint16_t deviceIdentifier = xboardReportDeviceIdentifier();

            if (deviceIdentifier == 1)
            {
                std::cout << "Digispark" << std::endl;
            }
            else
            {
                std::cout << "Device with identifier: " << (int)deviceIdentifier << std::endl;
            }

            return 0;
        }
        else if (args[2] == "device-version")
        {
            Version version = xboardReportDeviceVersion();

            std::cout << (int)version.major << "." << (int)version.minor << "." << (int)version.patch;

            if (version.modifier == 1)
            {
                std::cout << "-0.unreleased";
            }

            std::cout << std::endl;

            return 0;
        }
    }

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
