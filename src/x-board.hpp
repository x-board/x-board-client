
#include <stdint.h>
#include <vector>

void xboardSetDigital(uint8_t pin, bool on);
void xboardSetPWM(uint8_t pin, uint8_t value);
std::vector<uint8_t> xboardListPins();
bool xboardPing();
