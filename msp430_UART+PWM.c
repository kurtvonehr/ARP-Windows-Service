#include "msp430g2553.h"

#define MCU_CLOCK           1000000 //Main Clock frequency
#define PWM_FREQUENCY       46      // In Hertz, ideally 50Hz.

#define SERVO_STEPS         180     // Maximum amount of steps in degrees
#define SERVO_MIN           800     // The minimum duty cycle for this servo
#define SERVO_MAX           2200    // The maximum duty cycle

unsigned int PWM_Period     = (MCU_CLOCK / PWM_FREQUENCY);  // PWM Period
unsigned int PWM_Duty       = 0;                            // %
unsigned int servo_stepval, servo_stepnow;
unsigned int servo_lut[ SERVO_STEPS+1 ];
unsigned int i;

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);

static volatile char data;

void main(void)

{

    // Calculate the step value and define the current step, defaults to minimum.
    servo_stepval   = ( (SERVO_MAX - SERVO_MIN) / SERVO_STEPS );
    servo_stepnow   = SERVO_MIN;

    // Fill up the LUT
    for (i = 0; i < SERVO_STEPS; i++) {
        servo_stepnow += servo_stepval;
        servo_lut[i] = servo_stepnow;
    }

	 BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
	 DCOCTL =  CALDCO_1MHZ; // Set DCO to 1MHz

	 // Setup the PWM, etc.
	 P1DIR |= BIT6; // P1.6 as outputs
	 WDTCTL  = WDTPW + WDTHOLD;     // Kill watchdog timer
	 TACCTL1 = OUTMOD_7;            // TACCR1 reset/set
	 TACTL   = TASSEL_2 + MC_1;     // SMCLK, upmode
	 TACCR0  = PWM_Period-1;        // PWM Period
	 TACCR1  = PWM_Duty;            // TACCR1 PWM Duty Cycle

	/* Configure hardware UART */
	 P1SEL = BIT1 + BIT2 + BIT6; // P1.1 = RXD, P1.2=TXD
	 P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	 UCA0CTL1 |= UCSSEL_2; // Use SMCLK
	 UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
	 UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
	 UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
	 UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
	 IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt
	__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled

	 // Go to 0°
	 TACCR1 = servo_lut[0];

}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{

data = UCA0RXBUF;

	switch(data){
		 case 'u':
		 {
			 // Go to 0°
			 TACCR1 = servo_lut[0];
		 }
		 break;
		 case 'l':
		 {
			 // Go to 180°
			 TACCR1 = servo_lut[120];
		 }
		 break;
		 default:
 		{
		}
 		break;
	}
}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
 // Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
 // Example usage: UARTSendArray("Hello", 5);
 // int data[2]={1023, 235};
 // UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
	 while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
		 UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
		 TxArray++; //Increment the TxString pointer to point to the next character
	 }
}
