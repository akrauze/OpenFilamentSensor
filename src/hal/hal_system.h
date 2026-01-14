#ifndef HAL_SYSTEM_H
#define HAL_SYSTEM_H

#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)
    #include <esp_system.h>

    static inline void hal_restart() { ESP.restart(); }
    static inline uint32_t hal_getFreeHeap() { return ESP.getFreeHeap(); }
    static inline uint32_t hal_getMinFreeHeap() { return ESP.getMinFreeHeap(); }
    static inline uint32_t hal_getMaxAllocHeap() { return ESP.getMaxAllocHeap(); }
    static inline uint32_t hal_getCycleCount() { return ESP.getCycleCount(); }

    static inline const char* hal_getResetReason() {
        esp_reset_reason_t reason = esp_reset_reason();
        switch (reason) {
            case ESP_RST_POWERON:   return "Power-on";
            case ESP_RST_SW:        return "Software";
            case ESP_RST_PANIC:     return "Panic/Crash";
            case ESP_RST_INT_WDT:   return "Interrupt watchdog";
            case ESP_RST_TASK_WDT:  return "Task watchdog";
            case ESP_RST_WDT:       return "Other watchdog";
            case ESP_RST_BROWNOUT:  return "Brownout";
            case ESP_RST_DEEPSLEEP: return "Deep sleep";
            case ESP_RST_EXT:       return "External";
            default:                return "Unknown";
        }
    }

    static inline int hal_getResetReasonCode() {
        return (int)esp_reset_reason();
    }

    static inline bool hal_wasResetByPanic() {
        esp_reset_reason_t reason = esp_reset_reason();
        return (reason == ESP_RST_PANIC ||
                reason == ESP_RST_TASK_WDT ||
                reason == ESP_RST_INT_WDT);
    }

#elif defined(ARDUINO_ARCH_RP2040)
    #include <hardware/watchdog.h>

    static inline void hal_restart() { rp2040.reboot(); }
    static inline uint32_t hal_getFreeHeap() { return rp2040.getFreeHeap(); }
    static inline uint32_t hal_getMinFreeHeap() { return rp2040.getFreeHeap(); }
    static inline uint32_t hal_getMaxAllocHeap() { return rp2040.getFreeHeap(); }
    static inline uint32_t hal_getCycleCount() { return rp2040.getCycleCount(); }

    static inline const char* hal_getResetReason() {
        if (watchdog_caused_reboot()) {
            return "Watchdog";
        }
        return "Power-on";
    }

    static inline int hal_getResetReasonCode() {
        return watchdog_caused_reboot() ? 1 : 0;
    }

    static inline bool hal_wasResetByPanic() {
        return watchdog_caused_reboot();
    }
#endif

#endif // HAL_SYSTEM_H
