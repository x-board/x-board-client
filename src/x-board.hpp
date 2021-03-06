//
// This file is governed by the MITA license
// which can be found as MITA.LICENSE in the root of this project
// (or alternative at mita.jasperhorn.nl)
//

#include <stdint.h>
#include <vector>

#include "Version.hpp"

#define PROTOCOL_VERSION_MAJOR 0
#define PROTOCOL_VERSION_MINOR 2
#define PROTOCOL_VERSION_PATCH 0
#define PROTOCOL_VERSION_MODIFIER 1

void xboardSetDigital(uint8_t pin, bool on);
void xboardSetPWM(uint8_t pin, uint8_t value);
void xboardSetDigitalBlink(uint8_t pin, uint8_t onTime, uint8_t offTime, uint8_t shiftTime);
std::vector<uint8_t> xboardListPins();
std::vector<uint8_t> xboardListCapabilities();
bool xboardPing();
uint16_t xboardReportDeviceIdentifier();
Version xboardReportDeviceVersion();
Version xboardReportProtocolVersion();
