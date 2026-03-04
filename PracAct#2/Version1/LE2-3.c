#include <xc.h>

void delay (int cnt) {
	int i, j;
	for (i = cnt; i != 0; i--) // loop until i=0
	       for (j = 0; j < 5000; j++); // loop until j=999
}

void dataCtrl( unsigned char DATA) {
	PORTB = DATA; // load data to PORTB
	RC0 = 1;	// set RS to 1 (data reg)
	RC2 = 0;	// set RW to 0 (write)
	RC1 = 1;	// set E to 1
	delay(1);	// call delay
	RC1 = 0;	// set E to 0 (strobe)
}

void instCtrl (unsigned char INST) {
	PORTB = INST;	 // load instruction to PORTB
	RC0 = 0;	// set RS to 0 (instruction reg)
	RC2 = 0;	// set RW to 0 (write)
	RC1 = 1;	// set E to 1
	delay(1);	// call delay
	RC1 = 0;	// set E to 0 (strobe)
}	
	
	
void initLCD() {
	delay(1);
	instCtrl(0x38); // set function to 8 bits, 2 line display, 5x7
	instCtrl(0x08);
	instCtrl(0x01); // Display clear
	instCtrl(0x06); // entry mode set: increase, display is not shifted
	instCtrl(0x0E); // display on, cursor on, blink off
}	

void main() {
	unsigned char data;
	TRISB = 0x00;	// sets PORTB as output
	TRISC = 0x00;	// sets PORTC as output
	TRISD = 0xFF;	// sets PORTD as input
	initLCD();	// go to initialize lcd function
	int i = 0;
	while(1) {
		if (RD4==1) {
			data = PORTD & 0x0F; // mask input

			if(i==20) {	//checks if line 1 is full
				instCtrl(0xC0); //set line 2 to ram 
			}
			else if(i==40) {	//checks if line 3 is full
				instCtrl(0x94); //set line 3 to ram 
			}
			else if(i==60) {	//checks if line 3 is full
				instCtrl(0xD4); //set line 4 to ram 
			}
			else if(i>=80) {	//checks if max characters were used in all 4 lines
				initLCD(); // resets display when full
				i=0;
			}
			
			if (data == 0x00) dataCtrl('1');
			else if (data == 0x01) dataCtrl('2');
			else if (data == 0x02) dataCtrl('3');
			else if (data == 0x04) dataCtrl('4');
			else if (data == 0x05) dataCtrl('5');
			else if (data == 0x06) dataCtrl('6');
			else if (data == 0x08) dataCtrl('7');
			else if (data == 0x09) dataCtrl('8');
			else if (data == 0x0A) dataCtrl('9');
			else if (data == 0x0C) dataCtrl('*');
			else if (data == 0x0D) dataCtrl('0');
			else if (data == 0x0E) dataCtrl('#');
			i++;
		}
	}

}