
#pragma once
#include <WiFi.h>
#include "config.h"

class Debug
{
public:
    void begin(unsigned long baud = 115200);
    void print(const char *message, const char *tag = nullptr);
    void println(const char *message, const char *tag = nullptr);
};

extern Debug debug;

void debug_init(unsigned long baud = 115200);