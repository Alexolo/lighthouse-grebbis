
void wifiConnect() {
  // Connect to Wi-Fi network
  Serial.println();
  Serial.println("Connecting to...");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println(millis());
  while (WiFi.status() != WL_CONNECTED) {
    //delay(500);
    yield();
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(millis());
  Serial.println("Wi-Fi connected successfully");
}

void wifiPrintStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}

int wifiGetCurrentTime() {
  char * host = strcat(TIMEZONEDB_URL, TIMEZONEDB_API);
  int httpCode = 0;                                        // Variable to hold received data
  HTTPClient http;                                          // Declare an object of class HTTPClient
  
  Serial.print("Connecting to TimezoneDB...");
  http.begin(host);                                        // Connect to site
  httpCode = http.GET();                               // Check if data is coming in

  while (httpCode == 0) {                             // if no data is in
    Serial.print("No Data...");
    delay(1000);                                           // wait a sec
    http.begin(host);                                     // and try again
    httpCode = http.GET();
  }

  String payload = http.getString();                        // Save response as string
  Serial.println(payload);                              // Show response
  String unixTimeString = payload.substring(payload.indexOf("<timestamp>")+11,payload.indexOf("</timestamp>"));
  Serial.println(unixTimeString);

  http.end();                                                // Close connection to timezonedb
  return unixTimeString.toInt();
}
