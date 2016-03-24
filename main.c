#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int counter;

void toggleLed ();

int main(void)
{
    // set port B pin 1 to output
    DDRB  = 0x01;
    // set port b pin 1 to LOW
    PORTB = 0x00;

    // Time/Counter Control Register A Timer 0,
    // We don't want CTC or PWM
    TCCR0A = 0;
    // Set prescaler to 1024
    TCCR0B = 1<<CS02;
    TCCR0B |= 1<<CS02;

    // Initialize counter
    counter = 0;

    // Enable Overflow Interrupt
    TIMSK0 |= 1<<TOIE0;

    // Activate global interrupts
    sei();

    while (1) {
	// Every 256 cycles, reset counter and toggle LED on Port B Pin 1
	if (counter % 0x80 == 0) {
	    counter = 0;
	    toggleLed();
	}
    }

    return 0;   /* never reached */
}

// Turn LED on Port B Pin 1 on and off.
void toggleLed ()
{
    PORTB ^= 0x01;
}

// Overflow Interrupt: increase counter by 1.
ISR (TIMER0_OVF_vect)
{
    counter++;
}
