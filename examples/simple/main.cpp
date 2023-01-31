
#include <EasyOTA.h>
#include <WifiHelper.h>

const char *ssid = "ESP8266_TEST";
const char *password = "123456789abc";

// Modify this when change the version
//////////////////////////////////////
#define FW_VERSION "1244"
//////////////////////////////////////

#define OTA_SERVER_URL "http://192.168.3.243:8266"
#define OTA_GET_VERSION_ENDPOINT "/version"
#define OTA_GET_FIRMWARE_ENDPOINT "/firmware"
WiFiClient client;

void setup() {
    Serial.begin(9600);
    Serial.println("Booting");
    pinMode(2, OUTPUT);
    WifiHelper::startWIFI(ssid, password, true);
    OTAConfig config(
            FW_VERSION,
            OTA_SERVER_URL,
            OTA_GET_VERSION_ENDPOINT,
            OTA_GET_FIRMWARE_ENDPOINT,
            true
    );
    EasyOTA ota(config);
    ota.runUpdateRoutine(client);
}

void loop() {}