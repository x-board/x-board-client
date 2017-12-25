
#include <stdint.h>
#include <vector>

#include "Version.hpp"

#define PROTOCOL_VERSION_MAJOR 0
#define PROTOCOL_VERSION_MINOR 0
#define PROTOCOL_VERSION_PATCH 0
#define PROTOCOL_VERSION_MODIFIER 1

void xboardSetDigital(uint8_t pin, bool on);
void xboardSetPWM(uint8_t pin, uint8_t value);
std::vector<uint8_t> xboardListPins();
std::vector<uint8_t> xboardListCapabilities();
bool xboardPing();
uint16_t xboardReportDeviceIdentifier();
Version xboardReportDeviceVersion();
Version xboardReportProtocolVersion();
