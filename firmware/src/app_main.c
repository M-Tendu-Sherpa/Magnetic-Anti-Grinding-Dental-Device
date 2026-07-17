#include "app_main.h"
#include "app_ble.h"
#include "app_adc.h"
#include "app_session.h"
#include "app_logger.h"
#include "app_transport.h"
#include "user_config.h"

static session_ctx_t g_session;
static adc_log_t     g_log;

static uint32_t app_get_time_ms(void); // wrap SDK timer

void app_init(void)
{
    // Initialize BLE stack and start advertising
    app_ble_init();
    app_ble_start_advertising();

    // Initialize ADC
    app_adc_init();

    // Initialize session and logger
    session_init(&g_session);
    logger_init(&g_log, true);
}

int main(void)
{
    system_init();
    app_init();

    while (1) {
        uint32_t now_ms = app_get_time_ms();

        // BLE event processing
        app_ble_process();

        // If session is active, poll ADC
        if (session_is_active(&g_session, now_ms)) {
            uint16_t value_mv;
            if (app_adc_read_mv(&value_mv)) {
                logger_add_sample(&g_log, now_ms, value_mv);
            }
        }

        // Check if the session ended. If true, then transfer data
        if (session_should_transfer(&g_session, now_ms) &&
            session_get_state(&g_session) == SESSION_STATE_RECORDING) {

            session_stop(&g_session, now_ms);
            session_get_state(&g_session);

            app_transport_send_log(&g_log);
            logger_reset(&g_log);
        }

        sdk_idle();
    }
}
