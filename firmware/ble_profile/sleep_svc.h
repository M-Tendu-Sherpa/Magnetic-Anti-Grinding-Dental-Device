#pragma once
#include <stdint.h>

#define SLEEP_SVC_UUID_BASE    {0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF,0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF}
#define SLEEP_SVC_UUID         0xFFF0
#define CHAR_UUID_SESSION_CTRL 0xFFF1
#define CHAR_UUID_DURATION     0xFFF2
#define CHAR_UUID_THRESHOLD    0xFFF3
#define CHAR_UUID_DATA         0xFFF4

void sleep_svc_init(void);
void sleep_svc_on_write_ctrl(uint8_t value);
void sleep_svc_on_write_duration(uint32_t duration_sec);
void sleep_svc_on_write_threshold(uint8_t enabled);
void sleep_svc_notify_data(const uint8_t *data, uint16_t len);
