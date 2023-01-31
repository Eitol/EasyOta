//
// Created by hector on 04/03/18.
//

#ifndef TEST_2_OTA_H
#define TEST_2_OTA_H

#include <Arduino.h>
#include <ESP8266httpUpdate.h>
#include "OTAStructs.h"


class EasyOTA {
public:
    explicit EasyOTA(OTAConfig config);

    /**
     *
     */
    void runUpdateRoutine(WiFiClient client);

    /**
     * Asks the server about the current firmware version.
     * For it uses the config.versionEndpoint.
     * @return The version ot the current firmware
     */
    UpdateCheckResult checkForUpdates(WiFiClient client);

    /**
     * Update the firmware ussing the config.firmwareEndpoint
     * @return The result
     */
    HTTPUpdateResult updateFirmware(WiFiClient client);


private:
    HTTPClient httpClient;
    OTAConfig config;
    String firmwareURL;
    String versionURL;
};


#endif //TEST_2_OTA_H
