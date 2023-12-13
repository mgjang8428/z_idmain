WiFiClient wifi;
HTTPClient net;
long sendCount = 0;
long previousSendCount = 0;

void wifiSetup() {
  WiFi.begin(WIFI_SSID, WIFI_PW);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    lcdWifiWait();
  }
  Serial.println("CONNECTED");
  lcdWifiSuccess();
}

void wifiLoop(Data data) {
  //lcdLoading();
  lcdGpsStatus(data.gpsValue.stat);
  if(WiFi.status() == WL_CONNECTED) {
    lcdNetDataSend();
    net.begin(SERVER_URL);

    net.addHeader("Content-Type",  "application/json");
    String netRequestData = makeDataToJson(data);

    int netResponseCode = net.POST(netRequestData);

    if (netResponseCode > 0) {
      String response = net.getString();
      Serial.println(netResponseCode);
      Serial.println(response);
      sendCount++;
    }
    lcdSendCont(sendCount, previousSendCount);
    previousSendCount = sendCount;
    net.end();
  }
}

String makeDataToJson(Data data) {
  DynamicJsonDocument doc(1024);
  String result;

  doc["no"] = data.deviceNo;
  doc["vibe"] = data.vibeValue;
  doc["gyro_x"] = data.gyroValue.x;
  doc["gyro_y"] = data.gyroValue.y;
  doc["gyro_z"] = data.gyroValue.z;
  doc["gps_stat"] = data.gpsValue.stat;
  doc["gps_lat"] = data.gpsValue.lat;
  doc["gps_lng"] = data.gpsValue.lng;

  serializeJson(doc, result);
  return result;
}