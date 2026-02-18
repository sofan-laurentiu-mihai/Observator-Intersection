#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t ms_count = 0, ms_count2 = 0;
volatile uint8_t semaforA_state = 0;
volatile uint8_t semaforB_state = 0, led_state = 0, led2_state = 0;

void schimbare_stare_A_and_B() {
	switch (semaforA_state) {
		case 0:
		PORTB = 0b00001001;
		PORTD = 0b00000100;
		PORTC = 0b00000010 | 0b00100000;
		ms_count = 4000;
		semaforA_state = 1;
		TCCR2 = 0b00001111;
		break;

		case 1:
		PORTB = 0b00010010;
		PORTD = 0b00000010;
		PORTC = 0b00000010 | 0b00100000;
		ms_count = 2000;
		semaforA_state = 2;
		semaforB_state = 0;
		TCCR2 = 0;
		PORTA &= ~(1 << PA0);
		TCCR1B = 0;
		break;

		case 2:
		PORTB = 0b00100100;
		switch (semaforB_state) {
			case 0:
			PORTD = 0b00000001;
			PORTC = 0b00000001 | 0b00001000;
			ms_count = 4000;
			semaforB_state = 1;
			TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
			break;

			case 1:
			PORTD = 0b00000010;
			PORTC = 0b00000001 | 0b00001000;
			ms_count = 2000;
			semaforB_state = 2;
			TCCR1B = 0;
			PORTA &= ~(1 << PA1);
			break;

			case 2:
			PORTD = 0b00000100;
			PORTC = 0b00000010 | 0b00100000;
			ms_count = 4000;
			semaforB_state = 0;
			semaforA_state = 0;
			TCCR2 = 0b00001111;
			break;
		}
		break;
	}
}

ISR(TIMER0_COMP_vect) {
	if (ms_count > 0) {
		ms_count--;
		if (ms_count == 0) {
			schimbare_stare_A_and_B();
		}
	}
}

ISR(TIMER2_COMP_vect) {
	led_state = !led_state;
	if (led_state) {
		PORTA |= (1 << PA0);
		} else {
		PORTA &= ~(1 << PA0);
	}
}

ISR(TIMER1_COMPA_vect) {
	if (semaforA_state == 2) {
		led2_state = !led2_state;
		if (led2_state) {
			PORTA |= (1 << PA1);
			} else {
			PORTA &= ~(1 << PA1);
		}
		} else {
		PORTA &= ~(1 << PA1);
	}
}

void init_timer0() {
	TCCR0 = 0b00001011;
	TCNT0 = 0;
	OCR0 = 125;
	TIMSK |= 0b00000010;
}

void init_timer2() {
	TCCR2 = 0b00001111;
	TCNT2 = 0;
	OCR2 = 250;
	TIMSK |= 0b10000000;
}

void init_timer1() {
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCNT1 = 0;
	OCR1A = 250;
	TIMSK |= (1 << OCIE1A);
}

int main() {
	DDRB = 0b11111111;
	DDRD = 0b11111111;
	DDRC = 0b11111111;
	DDRA = 0b11111111;

	init_timer0();
	init_timer2();
	init_timer1();
	schimbare_stare_A_and_B();
	SREG |= (1 << 7);

	while (1) {
	}
}
