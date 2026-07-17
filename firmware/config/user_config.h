#pragma once

#define DEVICE_NAME              "DA14531_SLEEP_DEV"
#define DEFAULT_SESSION_DURATION_SEC   (8 * 60 * 60)   // default of 8 hours
#define ADC_SAMPLE_PERIOD_MS           100             // sampling interval
#define ADC_THRESHOLD_MV               5               // minimum delta to log
#define MAX_LOG_SAMPLES                4096
