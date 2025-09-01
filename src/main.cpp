#include "wifi_helpers.h"
#include "debug_helpers.h"
#include "webserver_helpers.h"

void setup()
{
  debug_init(115200);

  setup_wifi();
  connect_to_wifi();

  setup_telnet();
  setup_ota();
  setup_webserver();
}

void loop()
{
  ota_handle();
  handle_webserver();
}