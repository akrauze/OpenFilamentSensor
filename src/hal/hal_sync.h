#ifndef HAL_SYNC_H
#define HAL_SYNC_H

#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)
    // ESP32 FreeRTOS critical section primitives
    #define HAL_MUTEX_TYPE portMUX_TYPE
    #define HAL_MUTEX_INITIALIZER portMUX_INITIALIZER_UNLOCKED
    #define hal_enterCritical(mux) portENTER_CRITICAL(mux)
    #define hal_exitCritical(mux)  portEXIT_CRITICAL(mux)
    #define hal_delayMs(ms) vTaskDelay(pdMS_TO_TICKS(ms))

#elif defined(ARDUINO_ARCH_RP2040)
    // RP2040 uses interrupt disable for critical sections
    typedef uint32_t HAL_MUTEX_TYPE;
    #define HAL_MUTEX_INITIALIZER 0

    static inline void hal_enterCritical(HAL_MUTEX_TYPE* mux) {
        (void)mux;
        noInterrupts();
    }

    static inline void hal_exitCritical(HAL_MUTEX_TYPE* mux) {
        (void)mux;
        interrupts();
    }

    #define hal_delayMs(ms) delay(ms)
#endif

#endif // HAL_SYNC_H
