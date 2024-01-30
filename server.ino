#include <WiFiNINA.h>
#include <plogger.h>

#define LED_PIN 13
#define CONNECT_REATTEMPT_DELAY 10

const char *SSID = "HG8145V5_218F0";
const char *PASS = "znjuQ5ku";
int status = WL_IDLE_STATUS;

WiFiServer server(80);
WiFiClient client = server.available();

Logger logger(&Serial);

void setup(void) {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial)
    ;
  (void)logger.setLogLevel(LogLevel::Debug);
  (void)logger.info(F("Serial port connected."));
  wifi_check();
  wifi_connect();

  (void)logger.info(F("Starting server."));
  server.begin();
  wifi_printStatus();
}

void loop(void) {
  client = server.available();
  if (client) {
    web_run();
  }
}
