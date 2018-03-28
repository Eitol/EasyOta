//
// Created by hector on 08/03/18.
//

#ifndef NODE_OTADEBUG_H
#define NODE_OTADEBUG_H


#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "OTAStructs.h"

class OTADebug {
public:
    //////////////// DEBUG //////////////////////

    static void debugOtaConfig(OTAConfig &config){
        if (!config.debug){
            return;
        }
        Serial.println("fwVersion:"+config.fwVersion);
        Serial.println("serverUrl:"+config.serverUrl);
        Serial.println("versionEndpoint:"+config.versionEndpoint);
        Serial.println("firmwareEndpoint:"+config.firmwareEndpoint);
    }

    static void debugCheckUpdateResult(UpdateCheckResult updateCheckResult, bool debug) {
        if (!debug) {
            return;
        }
        switch (updateCheckResult.result) {
            case DIFFERENT_VERSION: {
                Serial.print("Available firmware version: ");
                Serial.println(updateCheckResult.serverFMVersion);
                break;
            }
            case SAME_VERSION: {
                Serial.println("Already on latest version");
                break;
            }
            case CHECK_FAILED: {
                Serial.print("Firmware version check failed, got HTTP response code ");
                break;
            }
        }
    }

    static void debugCheckUpdateResult(HTTPUpdateResult updateCheckResult, bool debug) {
        if (!debug) {
            return;
        }
        switch (updateCheckResult) {
            case HTTP_UPDATE_FAILED: {
                Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s", ESPhttpUpdate.getLastError(),
                              ESPhttpUpdate.getLastErrorString().c_str());
                break;
            }

            case HTTP_UPDATE_NO_UPDATES: {
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;
            }
            case HTTP_UPDATE_OK: { // Impossible (device restart after update)
                break;
            }
        }
    }
};


#endif //NODE_OTADEBUG_H
