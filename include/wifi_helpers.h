#pragma once
#include "config.h"

void setup_wifi();
void connect_to_wifi();

void setup_ota();
void ota_handle();

#ifdef TELNET_ENABLED
void setup_telnet();
void telnet_handle();
#endif