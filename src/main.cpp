#include <Homie.h>

#define FW_NAME "cmv-firmware"
#define FW_VERSION "1.0.0"

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */

const int PIN_POWER_RELAY = D1;
const int PIN_SPEED_RELAY = D2;

HomieNode cmvNode("cmv", "switch");

bool cmvStateHandler(String value) {
  if (value == "off") {
    digitalWrite(PIN_POWER_RELAY, HIGH);
    digitalWrite(PIN_SPEED_RELAY, LOW);
    Homie.setNodeProperty(cmvNode, "state", "off");
    Serial.println("CMV is tunred off");
  } else if (value == "slow") {
    digitalWrite(PIN_POWER_RELAY, LOW);
    digitalWrite(PIN_SPEED_RELAY, LOW);
    Homie.setNodeProperty(cmvNode, "state", "slow");
    Serial.println("CMV is running slow");
  } else if (value == "fast") {
    digitalWrite(PIN_POWER_RELAY, LOW);
    digitalWrite(PIN_SPEED_RELAY, HIGH);
    Homie.setNodeProperty(cmvNode, "state", "fast");
    Serial.println("CMV is running fast");
  } else {
    return false;
  }

  return true;
}

void setup() {
  // Set to slow speed by default
  pinMode(PIN_POWER_RELAY, OUTPUT);
  digitalWrite(PIN_POWER_RELAY, LOW);
  pinMode(PIN_SPEED_RELAY, OUTPUT);
  digitalWrite(PIN_SPEED_RELAY, LOW);

  Homie.setFirmware(FW_NAME, FW_VERSION);
  cmvNode.subscribe("state", cmvStateHandler);
  Homie.registerNode(cmvNode);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
