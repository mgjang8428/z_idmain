#define DEVICENO 10001

#define VIBESENSEPIN 4
//#define GYADDR 0x0D
#define LCDADDR 0x27
#define LCDROW 16
#define LCDCOLUMN 2
//Wifi Setting
#define WIFI_SSID "MG_Home_2.4G"
#define WIFI_PW "@@mgmn0405"
#define SERVER_URL "http://192.168.150.100:8080/test"

struct GyroValue {
  int x;
  int y;
  int z;
};

struct GpsValue {
  bool stat;
  double lat;
  double lng;
};

struct Data {
  int deviceNo;
  bool vibeValue;
  GyroValue gyroValue;
  GpsValue gpsValue;
};