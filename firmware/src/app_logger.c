#include "app_logger.h"
#include "user_config.h"

void logger_init(adc_log_t *log, bool threshold_enabled)
{
    log->head = 0;
    log->count = 0;
    log->last_value_mv = 0;
    log->threshold_enabled = threshold_enabled;
}

void logger_reset(adc_log_t *log)
{
    log->head = 0;
    log->count = 0;
}

void logger_add_sample(adc_log_t *log, uint32_t ts_ms, uint16_t value_mv)
{
    if (log->threshold_enabled) {
        uint16_t diff = (value_mv > log->last_value_mv)
                        ? (value_mv - log->last_value_mv)
                        : (log->last_value_mv - value_mv);
        if (diff < ADC_THRESHOLD_MV) {
            return;       // ignore small changes
        }
    }

    log->last_value_mv = value_mv;

    if (log->count < MAX_LOG_SAMPLES) {
        uint16_t idx = log->head;
        log->buffer[idx].timestamp_ms = ts_ms;
        log->buffer[idx].adc_value_mv = value_mv;
        log->head = (log->head + 1) % MAX_LOG_SAMPLES;
        log->count++;
    }
}

bool logger_get_sample(adc_log_t *log, uint16_t index, adc_sample_t *out)
{
    if (index >= log->count) return false;
    uint16_t start = (log->head + MAX_LOG_SAMPLES - log->count) % MAX_LOG_SAMPLES;
    uint16_t idx   = (start + index) % MAX_LOG_SAMPLES;
    *out = log->buffer[idx];
    return true;
}

uint16_t logger_get_count(adc_log_t *log)
{
    return log->count;
}
