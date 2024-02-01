#include <WiFiNINA.h>
#include <plogger.h>

#define RED_PIN 10
#define GREEN_PIN 9
#define BLUE_PIN 6
#define BRIGHTNESS 50

#define CONNECT_REATTEMPT_DELAY 10

const char *SSID = "HG8145V5_218F0";
const char *PASS = "znjuQ5ku";
int status = WL_IDLE_STATUS;

WiFiServer server(80);
WiFiClient client = server.available();

Logger logger(&Serial);

void setup(void) {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);
  while (!Serial)
    ;
  (void)logger.setLogLevel(LogLevel::Debug);
  (void)logger.infoLine(F("Serial port connected."));
  wifi_check();
  wifi_connect();

  (void)logger.infoLine(F("Starting server."));
  server.begin();
  wifi_printStatus();
}

void loop(void) {
  client = server.available();
  if (client) {
    web_run();
  }
}
