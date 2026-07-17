#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SESSION_STATE_IDLE = 0,
    SESSION_STATE_CONNECTED,
    SESSION_STATE_CONFIGURED,
    SESSION_STATE_RECORDING,
    SESSION_STATE_TRANSFER,
} session_state_t;

typedef struct {
    session_state_t state;
    uint32_t        session_duration_sec;
    uint32_t        session_start_ms;
    uint32_t        session_end_ms;
    bool            threshold_logging;
} session_ctx_t;

void session_init(session_ctx_t *ctx);
void session_on_connected(session_ctx_t *ctx);
void session_on_config_updated(session_ctx_t *ctx,
                               uint32_t duration_sec,
                               bool threshold_logging);
void session_start(session_ctx_t *ctx, uint32_t now_ms);
void session_stop(session_ctx_t *ctx, uint32_t now_ms);
bool session_is_active(session_ctx_t *ctx, uint32_t now_ms);
bool session_should_transfer(session_ctx_t *ctx, uint32_t now_ms);
session_state_t session_get_state(session_ctx_t *ctx);
