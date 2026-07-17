#include "app_transport.h"
#include "app_logger.h"
#include "sleep_svc.h"

#define DATA_CHUNK_MAX  20   // match ATT MTU / payload

extern adc_log_t g_log;

void app_transport_send_log(adc_log_t *log)
{
    uint16_t total = logger_get_count(log);
    uint16_t idx   = 0;

    uint8_t  buf[DATA_CHUNK_MAX];

    while (idx < total) {
        uint16_t offset = 0;

        while (idx < total && (offset + sizeof(adc_sample_t)) <= DATA_CHUNK_MAX) {
            adc_sample_t s;
            if (!logger_get_sample(log, idx, &s)) break;
          
            buf[offset + 0] = (uint8_t)(s.timestamp_ms & 0xFF);
            buf[offset + 1] = (uint8_t)((s.timestamp_ms >> 8) & 0xFF);
            buf[offset + 2] = (uint8_t)((s.timestamp_ms >> 16) & 0xFF);
            buf[offset + 3] = (uint8_t)((s.timestamp_ms >> 24) & 0xFF);

            buf[offset + 4] = (uint8_t)(s.adc_value_mv & 0xFF);
            buf[offset + 5] = (uint8_t)((s.adc_value_mv >> 8) & 0xFF);

            offset += 6;
            idx++;
        }

        if (offset > 0) {
            sleep_svc_notify_data(buf, offset);
        }
    }
}
