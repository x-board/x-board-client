//
// This file is governed by the MITA license
// which can be found as MITA.LICENSE in the root of this project
// (or alternative at mita.jasperhorn.nl)
//

#include "Version.hpp"

Version::Version(uint8_t major, uint8_t minor, uint8_t patch, uint8_t modifier)
{
    this->major = major;
    this->minor = minor;
    this->patch = patch;
    this->modifier = modifier;
}
