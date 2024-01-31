void web_reply(void) {
  (void)logger.info(F("Responding to request."));
  (void)client.println(F("HTTP/1.1 200 OK"));
  (void)client.println(F("Content-type:text/html"));
  (void)client.println();

  // html buttons
  (void)client.println(F("Click <a href=\"/H\">here</a> turn the LED on<br>"));
  (void)client.println(F("Click <a href=\"/L\">here</a> turn the LED off<br><br>"));
  (void)client.println();

  (void)logger.debug(F("Reply:"));
  (void)logger.debug(F("HTTP/1.1 200 OK"));
  (void)logger.debug(F("Content-type:text/html"));
  (void)logger.debug(F(""));

  // html buttons
  (void)logger.debug(F("Click <a href=\"/H\">here</a> turn the LED on<br>"));
  (void)logger.debug(F("Click <a href=\"/L\">here</a> turn the LED off<br><br>"));
  (void)logger.debug(F(""));
}

bool web_processRequest() {
  (void)logger.debug(F("Request:"));
  String current_line = F("");

  while (client.connected()) {
    if (!client.available()) {
      break;
    }

    char c = client.read();

    if (c == '\n') {
      if (current_line.length() > 0) {
        // if the current line has stuff, reset the line and keep going
        (void)logger.debug(current_line);
        current_line = F("");
      } else {
        // if there are 2 new lines in a row, it's the end of the request
        web_reply();
        break;
      }
    } else if (c != '\r') {
      current_line += c;
    }

    if (current_line.endsWith("GET /H")) {
      (void)logger.info(F("Turning on LED."));
      digitalWrite(LED_PIN, HIGH);
    }

    if (current_line.endsWith("GET /L")) {
      (void)logger.info(F("Turning off LED."));
      digitalWrite(LED_PIN, LOW);
    }
  }
}

void web_run(void) {
  if (!client) {
    return;
  }

  String current_line = F("");
  if (client.connected()) {
    (void)logger.info(F("Client connected."));
    (void)logger.info(F("Receiving request."));
    web_processRequest();
  }

  client.stop();
  (void)logger.info(F("Client disconnected."));
}
