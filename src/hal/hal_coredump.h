#ifndef HAL_COREDUMP_H
#define HAL_COREDUMP_H

#include <Arduino.h>

#if defined(ARDUINO_ARCH_ESP32)
    #include <esp_core_dump.h>
    #include <esp_partition.h>

    static inline bool hal_coredumpAvailable() {
        return esp_core_dump_image_check() == ESP_OK;
    }

    static inline const esp_partition_t* hal_getCoredumpPartition() {
        return esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
                                        ESP_PARTITION_SUBTYPE_DATA_COREDUMP,
                                        nullptr);
    }

    static inline size_t hal_getCoredumpPartitionSize(const esp_partition_t* partition) {
        return partition ? partition->size : 0;
    }

    static inline bool hal_readCoredumpPartition(const esp_partition_t* partition,
                                                  size_t offset,
                                                  uint8_t* buffer,
                                                  size_t size) {
        if (!partition) return false;
        return esp_partition_read(partition, offset, buffer, size) == ESP_OK;
    }

    static inline bool hal_eraseCoredumpPartition(const esp_partition_t* partition) {
        if (!partition) return false;
        return esp_partition_erase_range(partition, 0, partition->size) == ESP_OK;
    }

    static inline void hal_systemAbort(const char* msg) {
        esp_system_abort(msg);
    }

#else
    // Stub implementations for platforms without coredump support
    static inline bool hal_coredumpAvailable() { return false; }
    static inline const void* hal_getCoredumpPartition() { return nullptr; }
    static inline size_t hal_getCoredumpPartitionSize(const void*) { return 0; }
    static inline bool hal_readCoredumpPartition(const void*, size_t, uint8_t*, size_t) { return false; }
    static inline bool hal_eraseCoredumpPartition(const void*) { return false; }
    static inline void hal_systemAbort(const char*) { /* No-op on RP2040 */ }
#endif

#endif // HAL_COREDUMP_H
