#ifndef OFS_WEB_SERVER_OFS_H
#define OFS_WEB_SERVER_OFS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncEventSource.h>
#include <ElegantOTA.h>
#include <LittleFS.h>

#include "SettingsManager.h"
#include "ElegooCC.h"

// Define SPIFFS as LittleFS
#define SPIFFS LittleFS

class OFSWebServer

{
   private:
    AsyncWebServer server;
    AsyncEventSource statusEvents;
    unsigned long lastStatusBroadcastMs = 0;
    unsigned long statusBroadcastIntervalMs = 5000;
    String lastIdlePayload;

    void buildStatusJson(DynamicJsonDocument &jsonDoc, const printer_info_t &elegooStatus);
    void broadcastStatusUpdate();

   public:
    OFSWebServer(int port = 80);
    void begin();
    void loop();
};

#endif  // OFS_WEB_SERVER_OFS_H
