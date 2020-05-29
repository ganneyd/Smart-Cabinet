#pragma once

#include "PCF8574.h"
#include "../Config/Config.h"

struct IOExpander:protected PCF8574{

    public:
    IOExpander();
    void begin();
    void IO_digitalWrite(uint8_t pin, uint8_t value);
};
