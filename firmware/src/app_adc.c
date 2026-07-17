#include "app_adc.h"
#include "adc_config.h"
#include "sdk_adc_driver.h"

void app_adc_init(void)
{
    sdk_adc_init(ADC_CHANNEL_0, ADC_REF_INTERNAL, ADC_ATTEN_NONE    // Configure ADC
}

bool app_adc_read_mv(uint16_t *value_mv)
{
    uint16_t raw = sdk_adc_read();
    *value_mv = sdk_adc_raw_to_mv(raw);
    return true;
}
