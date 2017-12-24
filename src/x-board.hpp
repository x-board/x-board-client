
#include <stdint.h>
#include <vector>

#include "Version.hpp"

void xboardSetDigital(uint8_t pin, bool on);
void xboardSetPWM(uint8_t pin, uint8_t value);
std::vector<uint8_t> xboardListPins();
std::vector<uint8_t> xboardListCapabilities();
bool xboardPing();
uint16_t xboardReportDeviceIdentifier();
Version xboardReportDeviceVersion();
