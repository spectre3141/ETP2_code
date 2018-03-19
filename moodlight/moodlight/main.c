/*
 * moodlight.c
 *
 * Created: 15.03.2018 17:13:40
 * Author : jonas
 */ 

#include <avr/io.h>

// defines

int main(void)
{
	
	/* port configurations */
	DDRB |= (1<<PINB1);	// (OUTPUT: START signal)
	DDRD |= (1<<PIND6); // (OUTPUT:	DAC signal)
	
	/* configure PWM-channel for START */
	TCCR1A |= (1<<COM0A1) | (1<<COM0A0);
	TCCR1B |= (1<<WGM12) | (1<<CS01);
	/*
	clockfrequency is set to 8MHz and the formula for the pwm-frequency is
	as follows:	f=fclock/(2*(1+OCR1A)
	for a frequency of 50KHz the proper value is 79 or 0x4F
	*/
	OCR1A = 0x004F;
	
	
	/* configure PWM-channel for DAC */
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (1<<CS00);
	
    /* fluctuating pwm */
	uint8_t pwm_ratio = 0x00;
	uint8_t dir = 0x01;
    while (1)
    {
		/* set compare value */
		OCR0A = pwm_ratio;
		
		/* determine direction */
		if (pwm_ratio == 0xFF)
		{
			dir = 0x00;
		}
		if (pwm_ratio == 0x00)
		{
			dir = 0x01;
		}
		
		/* calculate new ration */
		if (dir > 0)
		{
			pwm_ratio++;
		} else {
			pwm_ratio--;
		}
    }
}

