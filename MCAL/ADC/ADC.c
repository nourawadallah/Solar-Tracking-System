#include "c:\users\noura\Documents\Atmel Studio\7.0\DeciMetroExpress\DeciMetroExpress\MCAL\ADC\ADC.h"
#include "c:\users\noura\Documents\Atmel Studio\7.0\DeciMetroExpress\DeciMetroExpress\UTILS\atmega32_regs.h"
#include "c:\users\noura\Documents\Atmel Studio\7.0\DeciMetroExpress\DeciMetroExpress\UTILS\common_macros.h"

#ifndef ISR
#define ISR(vector) void vector(void) __attribute__((signal, used)); void vector(void)
#endif

#define ADC_vect __vector_16

static u16 *g_adcResult = NULL;
static void (*g_adcCallback)(void) = NULL;

// sets voltage reference and prescaler, then enables the adc
void ADC_init(const adc_config_t *config) {
	ADMUX = 0;
	ADMUX |= ((config->reference & 0x03) << REFS0);

	ADCSRA = 0;
	SET_BIT(ADCSRA, ADEN);
	ADCSRA |= (config->prescaler & 0x07);
}

// selects a channel, starts a conversion, and blocks until it's done
u16 ADC_readChannel(adc_channel_t channel) {
	ADMUX &= 0xE0;
	ADMUX |= (channel & 0x1F);

	SET_BIT(ADCSRA, ADSC);
	while (GET_BIT(ADCSRA, ADIF) == 0);
	SET_BIT(ADCSRA, ADIF);

	return ADC_DATA;
}

// selects a channel and starts a conversion
void ADC_readChannelAsync(adc_channel_t channel, u16 *result_ptr, void (*callback)(void)) {
	g_adcResult = result_ptr;
	g_adcCallback = callback;

	ADMUX &= 0xE0;
	ADMUX |= (channel & 0x1F);

	SET_BIT(ADCSRA, ADIE);
	SET_BIT(ADCSRA, ADSC);
}

// conversion-complete interrupt
ISR(ADC_vect) {
	if (g_adcResult != NULL) {
		*g_adcResult = ADC_DATA;
	}

	CLEAR_BIT(ADCSRA, ADIE);
	SET_BIT(ADCSRA, ADIF);

	if (g_adcCallback != NULL) {
		g_adcCallback();
	}
}