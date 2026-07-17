#include "app_ble.h"
#include "sleep_svc.h"
#include "app_session.h"
#include "app_logger.h"

extern session_ctx_t g_session;
extern adc_log_t     g_log;

void app_ble_init(void)
{
    ble_stack_init();
    gap_set_device_name(DEVICE_NAME);
    sleep_svc_init();
}

void app_ble_start_advertising(void)
{
    gap_start_advertising();
}

// This is called by sleep_svc when the app on the phone sends the control characteristic
void sleep_svc_on_write_ctrl(uint8_t value)
{
    uint32_t now_ms = app_get_time_ms();

    if (value == 0x01) {
        session_start(&g_session, now_ms);
    } else if (value == 0x00) {
        session_stop(&g_session, now_ms);
    }
}

void sleep_svc_on_write_duration(uint32_t duration_sec)
{
    session_on_config_updated(&g_session, duration_sec, g_log.threshold_enabled);
}

void sleep_svc_on_write_threshold(uint8_t enabled)
{
    g_log.threshold_enabled = (enabled != 0);
    session_on_config_updated(&g_session,
                              g_session.session_duration_sec,
                              g_log.threshold_enabled);
}
