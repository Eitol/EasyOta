//
// Created by hector on 08/03/18.
//

#ifndef NODE_OTASTRUCTS_H
#define NODE_OTASTRUCTS_H


struct OTAConfig {
    OTAConfig(String fwVersion, String serverUrl,
              String versionEndpoint, String firmwareEndpoint, bool debug)
            : fwVersion(std::move(fwVersion)), serverUrl(std::move(serverUrl)),
              versionEndpoint(std::move(versionEndpoint)),
              firmwareEndpoint(std::move(firmwareEndpoint)), debug(debug) {}

    String fwVersion;
    String serverUrl;
    String versionEndpoint;
    String firmwareEndpoint;
    bool debug = false;
};

enum UpdateCheckResultCode {
    DIFFERENT_VERSION = 1,  // The FW server version is not the same as the current one
    SAME_VERSION = 2,       // The FW server version is the same as the current one
    CHECK_FAILED = 3,       // A problem occurred when the version was checked
    NOT_FW_IN_SERVER = 4    // No hay firmwares alojados en el servidor
};

struct UpdateCheckResult {
    explicit UpdateCheckResult(UpdateCheckResultCode result = CHECK_FAILED, String serverFMVersion = "") :
            result(result), serverFMVersion(std::move(serverFMVersion)) {}

    UpdateCheckResultCode result;
    String serverFMVersion;
};


#endif //NODE_OTASTRUCTS_H
