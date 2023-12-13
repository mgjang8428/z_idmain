#define DEVICENO 10001

#define VIBESENSEPIN 4
//#define GYADDR 0x0D
#define LCDADDR 0x27
#define LCDROW 16
#define LCDCOLUMN 2
//gyro Calc Value
#define GYRO_DEGREES_PER_SEC 131
//Wifi Setting
// #define WIFI_SSID "MG_Home_2.4G"
// #define WIFI_PW "@@mgmn0405"
#define WIFI_SSID "hlm-hotspot"
#define WIFI_PW "@@mg5428"
#define SERVER_URL "http://hlm-nas.duckdns.org:7005/sensor/data"

struct GyroValue {
  int x;
  int y;
  int z;
  int initX;
  int initY;
  int initZ;
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