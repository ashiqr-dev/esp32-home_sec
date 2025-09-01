#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include "secrets.h"
#include "wifi_helpers.h"
#include "debug_helpers.h"
#include "webserver_helpers.h"

#ifdef TELNET_ENABLED
WiFiServer telnetServer(TELNET_PORT);
WiFiClient telnetClient;
#endif

//-------------------------------------------------//

void setup_wifi()
{
    // Static IP configuration
    IPAddress local_IP(192, 168, 1, 204); // Device static IP
    IPAddress gateway(192, 168, 1, 1);    // Network gateway
    IPAddress subnet(255, 255, 255, 0);   // Subnet mask
    IPAddress primaryDNS(8, 8, 8, 8);     // Primary DNS (Google)
    IPAddress secondaryDNS(8, 8, 4, 4);   // Secondary DNS (Google)

    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    {
        debug.println("STA Failed to configure", "WIFI");
    }
}

void connect_to_wifi()
{
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    debug.print("\n\n");
    debug.print("Connecting to WiFi", "WIFI");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        debug.print(".");
    }
    debug.println("\n");
    debug.println("WiFi Connected!", "WIFI");
    debug.print("IP address: ", "WIFI");
    debug.println(WiFi.localIP().toString().c_str());
}

//-------------------------------------------------//

void setup_telnet()
{
#ifdef TELNET_ENABLED
    telnetServer.begin();
    telnetServer.setNoDelay(true);
    debug.print("Telnet Connected on port ", "WIFI");
    debug.print(String(TELNET_PORT).c_str());
    debug.println("\n");
#endif
}

void telnet_handle()
{
#ifdef TELNET_ENABLED
    // Accept new client
    if (telnetServer.hasClient())
    {
        if (!telnetClient || !telnetClient.connected())
        {
            if (telnetClient)
                telnetClient.stop();
            telnetClient = telnetServer.available();
        }
    }
#endif
}

void setup_mdns()
{
    if (!MDNS.begin(MDNS_HOSTNAME))
    {
        debug.println("Error starting mDNS", "WIFI");
    }
    else
    {
        debug.println("mDNS started: http://esp32.local", "WIFI");
    }
}

//-------------------------------------------------//

void setup_ota()
{
    ArduinoOTA.setHostname(OTA_HOSTNAME);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.begin();

    debug.println("OTA Ready", "WIFI");
    debug.print("Hostname: ", "WIFI");
    debug.println(ArduinoOTA.getHostname().c_str());
}

void ota_handle()
{
    ArduinoOTA.handle();
}