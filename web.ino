void web_logAndSend(const String &message) {
  (void)logger.debug(message);
  (void)client.print(message);
}

void web_logAndSendLine(const String &message) {
  (void)logger.debugLine(message);
  (void)client.println(message);
}

void web_reply(void) {
  (void)logger.info(F("Responding to request."));
  (void)web_logAndSendLine(F("HTTP/1.1 200 OK"));
  (void)web_logAndSendLine(F("Content-type:text/html"));
  (void)web_logAndSendLine(F(""));

  // html buttons
  (void)web_logAndSendLine(F("Click <a href=\"/A\">here</a> to light up white"
                             "<br>"));
  (void)web_logAndSendLine(F("Click <a href=\"/O\">here</a> turn off LED"
                             "<br>"));
  (void)web_logAndSendLine(F("Click <a href=\"/R\">here</a> to light up red"
                             "<br>"));
  (void)web_logAndSendLine(F("Click <a href=\"/G\">here</a> to light up green"
                             "<br>"));
  (void)web_logAndSendLine(F("Click <a href=\"/B\">here</a> to light up blue"
                             "<br>"));
  (void)web_logAndSendLine(F(""));
}

void web_processRequest() {
  String current_line = F("");

  (void)logger.debugLine(F("Request:"));

  while (client.connected()) {
    if (!client.available()) {
      break;
    }

    char c = client.read();

    if (c == '\n') {
      if (current_line.length() > 0) {
        // if the current line has stuff, reset the line and keep going
        (void)logger.debugLine(current_line);
        current_line = F("");
      } else {
        // if there are 2 new lines in a row, it's the end of the request
        web_reply();
        return;
      }
    } else if (c != '\r') {
      current_line += c;
    }

    if (current_line.equals("GET /R")) {
      analogWrite(RED_PIN, BRIGHTNESS);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
    }

    if (current_line.equals("GET /G")) {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, BRIGHTNESS);
      analogWrite(BLUE_PIN, 0);
    }

    if (current_line.equals("GET /B")) {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, BRIGHTNESS);
    }

    if (current_line.equals("GET /A")) {
      analogWrite(RED_PIN, BRIGHTNESS);
      analogWrite(GREEN_PIN, BRIGHTNESS);
      analogWrite(BLUE_PIN, BRIGHTNESS);
    }

    if (current_line.equals("GET /O")) {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
    }
  }
}

void web_run(void) {
  if (!client) {
    return;
  }

  String current_line = F("");
  if (client.connected()) {
    (void)logger.infoLine(F("Client connected."));
    (void)logger.infoLine(F("Receiving request."));
    web_processRequest();
  }

  client.stop();
  (void)logger.infoLine(F("Client disconnected."));
}
