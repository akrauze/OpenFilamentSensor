#ifndef HAL_PLATFORM_H
#define HAL_PLATFORM_H

// Platform detection based on Arduino architecture macros
#if defined(ARDUINO_ARCH_ESP32)
    #define HAL_PLATFORM_ESP32 1
    #define HAL_PLATFORM_NAME "ESP32"
#elif defined(ARDUINO_ARCH_RP2040)
    // arduino-pico uses ARDUINO_ARCH_RP2040 for both RP2040 and RP2350
    #define HAL_PLATFORM_RP2040 1
    // Detect RP2350 vs RP2040 using pico-sdk defines
    #if defined(PICO_RP2350)
        #define HAL_PLATFORM_RP2350 1
        #define HAL_PLATFORM_NAME "RP2350"
    #else
        #define HAL_PLATFORM_NAME "RP2040"
    #endif
#else
    #error "Unsupported platform: define ARDUINO_ARCH_ESP32 or ARDUINO_ARCH_RP2040"
#endif

// Feature availability flags
#if defined(HAL_PLATFORM_ESP32)
    #define HAL_HAS_COREDUMP 1
    #define HAL_HAS_PARTITION_API 1
    #define HAL_HAS_FREERTOS 1
#else
    #define HAL_HAS_COREDUMP 0
    #define HAL_HAS_PARTITION_API 0
    #define HAL_HAS_FREERTOS 0
#endif

// ISR attribute macro (places function in RAM on ESP32, no-op on RP2040)
#if defined(HAL_PLATFORM_ESP32)
    #define HAL_ISR_ATTR IRAM_ATTR
#else
    #define HAL_ISR_ATTR
#endif

// Include all HAL headers
#include "hal_sync.h"
#include "hal_system.h"
#include "hal_coredump.h"

#endif // HAL_PLATFORM_H
