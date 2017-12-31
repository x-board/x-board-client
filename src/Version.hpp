//
// This file is governed by the MITA license
// which can be found as MITA.LICENSE in the root of this project
// (or alternative at mita.jasperhorn.nl)
//

#ifndef VERSION_HPP
#define VERSION_HPP

#include <cstdint>

class Version
{
public:
    Version(uint8_t major, uint8_t minor, uint8_t patch, uint8_t);

    uint8_t major;
    uint8_t minor;
    uint8_t patch;

    uint8_t modifier;
};

#endif // VERSION_HPP
