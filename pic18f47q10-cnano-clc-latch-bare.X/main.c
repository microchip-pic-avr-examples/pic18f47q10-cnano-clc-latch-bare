/**
* \file main.c
*
* \brief Main source file.
*
    (c) 2020 Microchip Technology Inc. and its subsidiaries.
	
    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.
    
	THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.
    
	IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

/* PIC18F47Q10 Configuration Bit Settings*/
#pragma config MCLRE = EXTMCLR    /* Master Clear Enable bit->MCLR pin (RE3) is MCLR */
#pragma config WDTE = OFF       /* WDT operating mode->WDT Disabled */
#pragma config LVP = ON       /* Low voltage programming enabled */

#include <xc.h>

/* Code Function Declarations */
static void CLK_init(void);
static void PORT_init(void);
static void TMR2_init(void);
static void TMR4_init(void);
static void CLC1_init(void);
static void PPS_init(void);
    
static void CLK_init(void)
{
    /* HFINTOSC Oscillator */
    OSCCON1bits.NOSC = 6 ;
    /* HFFRQ 64_MHz; */
    OSCFRQ = 0x08;
}

static void PORT_init(void)
{
    /*PORT RA2 output driver enabled*/
    TRISAbits.TRISA2 = 0 ; 
}

static void TMR2_init(void)
{
    /* Set TMR2 to generate a pulse every 4.096ms (Frequency = 24.41Hz)*/  
    /* Timer 2 clock source is FOSC/4 */
    T2CLKCONbits.CS = 1;  
    /* Load period values */
    T2PR = 0xFF;  
    /* Enable Timer2 */
    T2CONbits.ON = 1;
    /* set prescaller to 1:128 */
    T2CONbits.CKPS = 7;
    /* set postcaller to 1:2 */
    T2CONbits.OUTPS = 1;
}

static void TMR4_init(void)
{
    /* Set TMR4 to generate a pulse every 4.08ms (Frequency = 24.51Hz)*/
    /* Timer 4 clock source is FOSC/4 */
    T4CLKCONbits.CS = 1;
    /* Load period values */
    T4PR = 0xFE; 
    /* Enable Timer4 */
    T4CONbits.ON = 1;
    /* set prescaller to 1:128 */
    T4CONbits.CKPS = 7;
    /* set postcaller to 1:2 */
    T4CONbits.OUTPS = 1;
}
 
static void CLC1_init(void)
{
    /* Set the CLC1 to implement SR latch*/ 
    /*  Clear the output polarity register */
    CLC1POL = 0x00;
    /* Configure TMR2_OUT as input for first OR Gate */
    CLC1SEL0 = 0x13; 
    /* Configure TMR2_OUT as input for second OR Gate */
    CLC1SEL1 = 0x13;
    /* Configure TMR4_OUT as input for third OR Gate */
    CLC1SEL2 = 0x15;
    /* Configure TMR4_OUT as input for fourth OR Gate */
    CLC1SEL3 = 0x15;
    /* All 4 inputs are not inverted*/
    CLC1GLS0 = 0x02; 
    CLC1GLS1 = 0x08; 
    CLC1GLS2 = 0x20;  
    CLC1GLS3 = 0x80; 
    /* CLC1 enabled; MODE SR latch*/
    CLC1CONbits.EN = 1;
    CLC1CONbits.MODE = 3;
}

static void PPS_init(void)
{
    /*Configure RA2 for CLC1 output*/
    RA2PPS = 0x18;    
}
 
void main(void) {
    
    CLK_init();
    PORT_init();
    TMR2_init();
    TMR4_init();
    CLC1_init();
    PPS_init();
    
    while (1)
    {
        ;
    }
}
