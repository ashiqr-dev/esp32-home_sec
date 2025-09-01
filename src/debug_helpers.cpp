#include <string.h>
#include <Arduino.h>
#include "debug_helpers.h"
#include "wifi_helpers.h"

// Declare telnetClient as an external variable if it's defined elsewhere
extern WiFiClient telnetClient;

Debug debug;

//-------------------------------------------------------

#ifdef SERIAL_ENABLED

void Debug::begin(unsigned long baud)
{
    Serial.begin(baud);
}

void Debug::print(const char *message, const char *tag)
{
#ifdef TELNET_ENABLED
    telnet_handle();
#endif

#ifdef SERIAL_ENABLED
    if (tag && tag[0] != '\0')
    {
        Serial.print('[');
        Serial.print(tag);
        Serial.print("] ");
    }
    Serial.print(message);
#endif

#ifdef TELNET_ENABLED
    if (telnetClient && telnetClient.connected())
    {
        if (tag && tag[0] != '\0')
        {
            telnetClient.print('[');
            telnetClient.print(tag);
            telnetClient.print("] ");
        }
        telnetClient.print(message);
    }
#endif
}

void Debug::println(const char *message, const char *tag)
{
#ifdef TELNET_ENABLED
    telnet_handle();
#endif

#ifdef SERIAL_ENABLED
    if (tag && tag[0] != '\0')
    {
        Serial.print('[');
        Serial.print(tag);
        Serial.print("] ");
    }
    Serial.println(message);
#endif

#ifdef TELNET_ENABLED
    if (telnetClient && telnetClient.connected())
    {
        if (tag && tag[0] != '\0')
        {
            telnetClient.print('[');
            telnetClient.print(tag);
            telnetClient.print("] ");
        }
        telnetClient.println(message);
    }
#endif
}

void debug_init(unsigned long baud)
{
    debug.begin(baud);
    debug.print("\n\n------------------------------------\n");
    debug.println("ESP32 starting...", "INFO");
}
#else

void Debug::begin(unsigned long) {}
void Debug::print(const char *, const char *) {}
void Debug::println(const char *, const char *) {}
void debug_init(unsigned long baud) {}

#endif