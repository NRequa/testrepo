/* main.c for Homework 6
; Brief description of the program
;   The LED toggles at 8 Hz and a varying duty-cycle
;   Repeat the functionality from Lab2-3 but now we want you to 
;   insert debugging instruments which gather data (state and timing)
;   to verify that the system is functioning as expected.
; Hardware connections (External: One button and one LED)
;  PE1 is Button input  (1 means pressed, 0 means not pressed)
;  PE0 is LED output (1 activates external LED on protoboard)
;  PF2 is Blue LED on Launchpad used as a heartbeat
; Instrumentation data to be gathered is as follows:
; After Button(PE1) press collect one state and time entry. 
; After Buttin(PE1) release, collect 7 state and
; time entries on each change in state of the LED(PE0): 
; An entry is one 8-bit entry in the Data Buffer and one 
; 32-bit entry in the Time Buffer
;  The Data Buffer entry (byte) content has:
;    Lower nibble is state of LED (PE0)
;    Higher nibble is state of Button (PE1)
;  The Time Buffer entry (32-bit) has:
;    24-bit value of the SysTick's Current register (NVIC_ST_CURRENT_R)
; Note: The size of both buffers is 50 entries. Once you fill these
;       entries you should stop collecting data
; The heartbeat is an indicator of the running of the program. 
; On each iteration of the main loop of your program toggle the 
; LED to indicate that your code(system) is live (not stuck or dead).
*/

// ***** 1. Pre-processor Directives Section *****
#include <stdint.h>
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void TExaS_Init(void); 
// ***** 3. Subroutines Section *****
void Ports_Init(void){ volatile unsigned long delay;
	// Clock start
	SYSCTL_RCGCGPIO_R |= 0x30;
	delay = 0;
	// Direction registers
	GPIO_PORTE_DIR_R |= 0x11;
	GPIO_PORTF_DIR_R |= 0x04;
	// Pull up resistors
	GPIO_PORTF_PUR_R |= 0x10;
	// ALT FUNCTIONS DIABLED
	GPIO_PORTF_AFSEL_R &= ~(0x04);
	GPIO_PORTE_AFSEL_R &= ~(0x04);
	// DIGITAL ENABLES
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTF_DEN_R |= 0x04;
}
void ms_delay(void){
	NVIC_ST_RELOAD_R = 80000 - 1;
	NVIC_ST_CURRENT_R = 0;
	while( (NVIC_ST_CTRL_R & 0x00010000) == 0){}
}
	
// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  //-UUU-
	NVIC_ST_CTRL_R &= ~0x03;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x05;
}
// Delay for the count units (ms)
void Delay(uint32_t count){
	uint32_t cont;
  //-UUU-
	for( cont = 0; cont < count; cont++){
		ms_delay();
	}
	
}
// -UUU- Declare your debug dump arrays and indexes into the
// arrays here
uint8_t data_buffer[50]; uint32_t time_buffer[50]; uint8_t data_index; uint8_t time_index;
uint8_t debug_last;
int main(void){ 
  TExaS_Init();  
  Ports_Init();   // initialize ports
  SysTick_Init(); // initialize SysTick 
  EnableInterrupts();  //Enable interrupts
  while(1){
  // -UUU- Your Code here
  }
}

void DebugCapture(void){
	if((time_index != 50) && (data_index != 50)){
		if( (GPIO_PORTE_DATA_R & 0x02) > debug_last){
		}
	}
	
	
}