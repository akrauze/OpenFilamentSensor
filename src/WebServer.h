#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <ArduinoJson.h>

// Platform-specific async TCP includes (ESPAsyncWebServer supports both platforms)
#if defined(ARDUINO_ARCH_ESP32)
    #include <AsyncTCP.h>
#elif defined(ARDUINO_ARCH_RP2040)
    #include <RPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include <LittleFS.h>

#include "SettingsManager.h"
#include "ElegooCC.h"

// Define SPIFFS as LittleFS
#define SPIFFS LittleFS

class WebServer
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
    WebServer(int port = 80);
    void begin();
    void loop();
};

#endif  // WEB_SERVER_H
