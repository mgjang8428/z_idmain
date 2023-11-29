WiFiClient wifi;
HTTPClient net;

void wifiSetup() {
  WiFi.begin(WIFI_SSID, WIFI_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED");
}

void wifiLoop() {
  if(WiFi.status() == WL_CONNECTED) {
    net.begin(SERVER_URL);
    net.addHeader("Content-Type",  "application/json");
    String netRequestData = "{\"hihi\" : 45}";
    int netResponseCode = net.POST(netRequestData);

    if (netResponseCode > 0) {
      String response = net.getString();
      Serial.println(netResponseCode);
      Serial.println(response);
    }

    net.end();
  }
}