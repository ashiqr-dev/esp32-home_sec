#include "webserver_helpers.h"
#include <pgmspace.h>

WebServer server(80);

extern const char webpage[] PROGMEM;

void setup_webserver()
{
    server.on("/", []()
              { server.send_P(200, "text/html", webpage); });

    server.begin();
    Serial.println("WebServer started on port 80");
}

void handle_webserver()
{
    server.handleClient();
}


//---------------------------------------------------------//

const char webpage[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>
<head><title>ESP32 Dashboard</title></head>
<body>
<h1>Hello from ESP32!</h1>
<p>Status: OK</p>
</body>
</html>

)rawliteral";