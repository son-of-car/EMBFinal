#include "msp.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "gpio.h"

volatile uint16_t sensorIN = 255;
volatile uint16_t sensorOUT = 255;

void main() {

    uint16_t doorWidth = 255; // output of sensor if reflecting across whole doorway

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
                 WDT_A_CTL_HOLD;

    config_adc();
    config_gpio();
    config_uart();

    P1->DIR |= 1;

    while(1) {
        write_data(0b11111111);
        //write_data(0b00000000);

    }


    /*int numPeople = 0;
    uint8_t state = 0;

    while(1) {

        if(state == 0) {
            // while IR1 and IR2 at wall distance
                // continue sampling in ADC until one is not
                // if IR1 state = 1 if IR2 state = 2
            P1->OUT |= 1;
            while(sensorIN >= doorWidth || sensorOUT >= doorWidth) {
                    // Start conversion-software trigger
                    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
                    __sleep();
            }
            P1->OUT &= 0;
            if(sensorIN < doorWidth)
                state = 1;
            else if(sensorOUT < doorWidth)
                state = 2;
            else
                state = 0;
        }
        else if(state == 1) {
            P1->OUT &= 0;
            // while IR2 at wall distance
                // continue sampling in ADC until IR2 is not
                // go to state 3
            while(sensorOUT >= doorWidth) {
                // Start conversion-software trigger
                ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
                __sleep();
            }

            numPeople = numPeople + 1;
            state = 3;
        }
        else if(state == 2) {
            P1->OUT &= 0;
            // while IR1 at wall distance
                // continue sampling in ADC until IR1 is not
                // go to state 4
            while(sensorIN >= doorWidth) {
                // Start conversion-software trigger
                ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;
                __sleep();
            }

            numPeople = numPeople - 1;
            state = 3;
        }
        else if(state == 3) {
            write_data(numPeople); // send new number of people to ATMega for displaying
            // read_data() to get success from ATMega
            state = 0;
        }
        else
            state = 0;

    }*/
}

// ADC14 interrupt service routine
void ADC14_IRQHandler()
{
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        sensorIN = ADC14->MEM[0];   // Move A0 results
        sensorOUT = ADC14->MEM[1];   // Move A1 results, IFG is cleared
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
