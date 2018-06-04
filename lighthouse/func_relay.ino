
void relaySetup() {
  pinMode(RELAY_PIN, RELAY_PIN_MODE);
  digitalWrite(RELAY_PIN, RELAY_PIN_VALUE);
}

void relayToggle() {
  digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));
}

void relayOff() {
  digitalWrite(RELAY_PIN, RELAY_OFF);
  //Serial.println("Relay is now off");

}

void relayOn() {
  digitalWrite(RELAY_PIN, RELAY_ON);
  //Serial.println("Relay is now on");
}

boolean relayBlink = false;
boolean relayBlinkCurrentlyOn = true;
int relayBlinkRemaining;
int relayBlinkOnPeriod;
int relayBlinkOffPeriod;
unsigned long relayBlinkStartMillis;
unsigned long relayBlinkToggleMillis;

void setRelayBlinkIntervals(int blinkNum, int blinkOn, int blinkOff) {
  if (!relayBlink) {
    Serial.println("NEW SET OF BLINKS");
    Serial.println(blinkNum);
    Serial.println(blinkOn);
    Serial.println(blinkOff);
    relayBlink = true;
    relayBlinkRemaining = blinkNum;
    relayBlinkOnPeriod = blinkOn * 1000;
    relayBlinkOffPeriod = blinkOff * 1000;

    relayOff();
    relayBlinkCurrentlyOn = false;
    updateNextBlinkInterval();
  }
}

void updateNextBlinkInterval() {
  if (relayBlinkRemaining >= 0) {
    relayBlinkStartMillis = currentMillis;
    if (relayBlinkCurrentlyOn) {
      relayBlinkToggleMillis = currentMillis + relayBlinkOnPeriod;
    }
    else {
      relayBlinkToggleMillis = currentMillis + relayBlinkOffPeriod;
      relayBlinkRemaining--;
    }
  }
  else {
    relayBlink = false;
  }
}

void doRelayBlinkIntervals() {
  if (relayBlink) {
    if (currentMillis >= relayBlinkToggleMillis) {
      if (relayBlinkCurrentlyOn) {
        relayOff();
        relayBlinkCurrentlyOn = false;
      }
      else {
        relayOn();
        relayBlinkCurrentlyOn = true;
      }
      updateNextBlinkInterval();
    }
  }
}


