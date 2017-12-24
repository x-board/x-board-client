
#include "Version.hpp"

Version::Version(uint8_t major, uint8_t minor, uint8_t patch, uint8_t modifier)
{
    this->major = major;
    this->minor = minor;
    this->patch = patch;
    this->modifier = modifier;
}
