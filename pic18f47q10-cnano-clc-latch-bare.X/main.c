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

/* Code Macros */
/*  Define reload values PR2 & PR4 registers */
#define TIMER2PR 0xFF 
#define TIMER4PR 0xFE 
/*  Define NULL values for the CLC use */
#define CLCNULL 0x00 
/*  Define register values for PPS pin-mapping   */
#define PPS_CONFIG_RA2_CLC1_OUT 0x18 

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
    OSCCON1 = _OSCCON1_NOSC1_MASK
            | _OSCCON1_NOSC2_MASK;
    /* HFFRQ 64_MHz; */
    OSCFRQ = _OSCFRQ_FRQ3_MASK;
}

static void PORT_init(void)
{
    /*PORT RA2 output driver enabled*/
    TRISA &= ~_TRISA_TRISA2_MASK ; 
}

static void TMR2_init(void)
{
    /* Set TMR2 to generate a pulse every 4.096ms (Frequency = 24.41Hz)*/  
    /* Timer 2 clock source is FOSC/4 */
    T2CLKCON = _T2CLKCON_CS0_MASK;  
    /* Load period values */
    T2PR = TIMER2PR;  
    /* Enable Timer2 ; set prescaller to 1:128; set postcaller to 1:2*/
    T2CON = _T2CON_ON_MASK       
          | _T2CON_CKPS_MASK    
          | _T2CON_OUTPS0_MASK; 
}

static void TMR4_init(void)
{
    /* Set TMR4 to generate a pulse every 4.08ms (Frequency = 24.51Hz)*/
    /* Timer 4 clock source is FOSC/4 */
    T4CLKCON = _T4CLKCON_CS0_MASK;
    /* Load period values */
    T4PR = TIMER4PR; 
    /* Enable Timer4 ; set prescaller to 1:128; set postcaller to 1:2*/
    T4CON = _T4CON_ON_MASK   
          | _T4CON_CKPS_MASK    
          | _T4CON_OUTPS0_MASK;  
}
 
static void CLC1_init(void)
{
    /* Set the CLC1 to implement SR latch*/ 
    /*  Clear the output polarity register */
    CLC1POL = CLCNULL;
    /* Configure TMR2_OUT as input for first OR Gate */
    CLC1SEL0 = _CLC1SEL0_D1S0_MASK 
             | _CLC1SEL0_D1S1_MASK 
             | _CLC1SEL0_D1S4_MASK; 
    /* Configure TMR2_OUT as input for second OR Gate */
    CLC1SEL1 = _CLC1SEL1_D2S0_MASK 
             | _CLC1SEL1_D2S1_MASK 
             | _CLC1SEL1_D2S4_MASK;
    /* Configure TMR4_OUT as input for third OR Gate */
    CLC1SEL2 = _CLC1SEL2_D3S0_MASK 
             | _CLC1SEL2_D3S2_MASK 
             | _CLC1SEL2_D3S4_MASK;
    /* Configure PWM4_OUT as input for fourth OR Gate */
    CLC1SEL3 = _CLC1SEL3_D4S0_MASK 
             | _CLC1SEL3_D4S2_MASK 
             | _CLC1SEL3_D4S4_MASK;
    /* All 4 inputs are not inverted*/
    CLC1GLS0 = _CLC1GLS0_LC1G1D1T_MASK; 
    CLC1GLS1 = _CLC1GLS1_LC1G2D2T_MASK; 
    CLC1GLS2 = _CLC1GLS2_LC1G3D3T_MASK;  
    CLC1GLS3 = _CLC1GLS3_LC1G4D4T_MASK; 
    /* CLC1 enabled; MODE SR latch*/
    CLC1CON = _CLC1CON_EN_MASK 
            | _CLC1CON_MODE1_MASK 
            | _CLC1CON_MODE0_MASK;
}

static void PPS_init(void)
{
    /*Configure RA2 for CLC1 output*/
    RA2PPS = PPS_CONFIG_RA2_CLC1_OUT;    
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
