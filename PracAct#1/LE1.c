#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>

#define _XTAL_FREQ 4000000  

void main(void) {
    
    ADCON1 = 0x06; 

    TRISAbits.TRISA0 = 1;
    TRISBbits.TRISB0 = 0;

    PORTBbits.RB0 = 0;

    while(1) {
        
        if (PORTAbits.RA0 == 1) {
            
            __delay_ms(50); 

            if (PORTAbits.RA0 == 1) {
                
                for (int i = 0; i < 3; i++) {
                    PORTBbits.RB0 = 1;      
                    __delay_ms(150);        
                    PORTBbits.RB0 = 0;      
                    __delay_ms(150);        
                }

                while(PORTAbits.RA0 == 1); 
                
                __delay_ms(50); 
            }
        }
    }
    return;
}