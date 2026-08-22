#ifndef ADC_H
#define ADC_H

#include "UTILS\STD_types.h"

// select voltage reference source
typedef enum {
    ADC_AREF,
    ADC_AVCC,
    ADC_INTERNAL_2_56V = 3
} adc_ref_t;

// select clock division prescaler factor
typedef enum {
    ADC_PRESCALER_2 = 1,
    ADC_PRESCALER_4,
    ADC_PRESCALER_8,
    ADC_PRESCALER_16,
    ADC_PRESCALER_32,
    ADC_PRESCALER_64,
    ADC_PRESCALER_128
} adc_prescaler_t;

// select analog input channel pin
typedef enum {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7
} adc_channel_t;

// group all adc configuration settings together
typedef struct {
    adc_ref_t reference;
    adc_prescaler_t prescaler;
} adc_config_t;

// initialize adc hardware with configuration settings
void ADC_init(const adc_config_t *config);

// read analog channel value (blocking)
u16 ADC_readChannel(adc_channel_t channel);

// start analog conversion without blocking (asynchronous)
void ADC_readChannelAsync(adc_channel_t channel, u16 *result_ptr, void (*callback)(void));

#endif
