//
// Created by hector on 08/03/18.
//


#include "EasyOTA.h"
#include "OTADebug.h"
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "OTAStructs.h"

EasyOTA::EasyOTA(OTAConfig config) : config(std::move(config)) {
    if (this->config.debug){
        OTADebug::debugOtaConfig(this->config);
    }
    this->firmwareURL = this->config.serverUrl + this->config.firmwareEndpoint;
    this->versionURL = this->config.serverUrl + this->config.versionEndpoint;
}

void EasyOTA::runUpdateRoutine(WiFiClient client) {
    UpdateCheckResult result = checkForUpdates(client);

    OTADebug::debugCheckUpdateResult(result, config.debug);

    if (result.result == DIFFERENT_VERSION) {
        HTTPUpdateResult r = updateFirmware(client);
        OTADebug::debugCheckUpdateResult(r, config.debug);
    }
}

UpdateCheckResult EasyOTA::checkForUpdates(WiFiClient client) {
    UpdateCheckResult result;
    httpClient.begin(client, this->versionURL);
    int httpCode = httpClient.GET();
    Serial.print("CODE: "+httpCode);
    if (httpCode == 200) {
        String serverFWVersion = httpClient.getString();
        if (serverFWVersion != this->config.fwVersion) {
            result = UpdateCheckResult(DIFFERENT_VERSION, serverFWVersion);
        } else {
            result = UpdateCheckResult(SAME_VERSION, serverFWVersion);
        }
    } else {
        if (httpCode == 404) {
            result = UpdateCheckResult(NOT_FW_IN_SERVER, String(""));
        } else {
            result = UpdateCheckResult(CHECK_FAILED, String(""));
        }
    }
    httpClient.end();
    return result;
}

HTTPUpdateResult EasyOTA::updateFirmware(WiFiClient client) {
    return ESPhttpUpdate.update(client, this->firmwareURL);
}
