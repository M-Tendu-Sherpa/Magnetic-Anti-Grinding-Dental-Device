#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t timestamp_ms;
    uint16_t adc_value_mv;
} adc_sample_t;

typedef struct {
    adc_sample_t buffer[MAX_LOG_SAMPLES];
    uint16_t     head;
    uint16_t     count;
    uint16_t     last_value_mv;
    bool         threshold_enabled;
} adc_log_t;

void logger_init(adc_log_t *log, bool threshold_enabled);
void logger_reset(adc_log_t *log);
void logger_add_sample(adc_log_t *log, uint32_t ts_ms, uint16_t value_mv);
bool logger_get_sample(adc_log_t *log, uint16_t index, adc_sample_t *out);
uint16_t logger_get_count(adc_log_t *log);
