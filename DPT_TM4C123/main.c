#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"



//Definitions for SysTick CSR (Control and Status Register)
#define ENABLE (1 << 0)         // CSR bit 0 to enable the SysTick timer
#define CLK_SRC (1<<2)         // CSR bit 2 to take system clock
#define COUNT_FLAG  (1 << 16) // CSR bit 16 automatically set to 1 when SysTick reaches 0
#define CLOCK_MHZ 16         // Default System Clock

// GPIO PORTF and Systick function declarations
void GPIO_PORTF_Init (void);   //GPIO PORTF Initialization Function
void Systick_Delay (uint32_t us);     //Systick Delay function

/* Main Program */

int main(void)
{
    GPIO_PORTF_Init ();
    //while(1)
    {


        GPIO_PORTF_DATA_R = 0X00;    // Red, Blue and Green LED turned OFF
        Systick_Delay (5);                 // Call Delay function
        GPIO_PORTF_DATA_R = 0X0E;  // All pins on Port F turned ON
        Systick_Delay (750);               // Call Delay function
        GPIO_PORTF_DATA_R = 0X00;    // Red, Blue and Green LED turned OFF
        Systick_Delay (30);                 // Call Delay function
        GPIO_PORTF_DATA_R = 0X0E;  // All pins on Port F turned ON
        Systick_Delay (40);               // Call Delay function
        GPIO_PORTF_DATA_R = 0X00;    // Red, Blue and Green LED turned OFF

    }
}

void GPIO_PORTF_Init (void)
{
    SYSCTL_RCGC2_R |= 0x00000020; //enable clock to GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B; //Unlock GPIO Port F commit register
    GPIO_PORTF_CR_R = 0x1F; //Make PORTF configurable
    GPIO_PORTF_DEN_R = 0x1F; //Enable digital functions on PortF
    GPIO_PORTF_DIR_R = 0x0E; //Set LEDs as outputs (1), switches as inputs (0)
    GPIO_PORTF_PUR_R = 0x11; //Pull-up resistor for user switches enabled
}


/* Delay Function */
void Systick_Delay (uint32_t us)
{
    NVIC_ST_CURRENT_R = 0;                  // SysTick current value register cleared
    NVIC_ST_RELOAD_R = us*16;              // SysTick reload value for 'us' microseconds
    NVIC_ST_CTRL_R |= ( ENABLE | CLK_SRC );  // SysTick Enable, use system clock

    while ((NVIC_ST_CTRL_R & COUNT_FLAG) == 0)  // wait until systick count flag is set
    {
           // do nothing
    }
    NVIC_ST_CTRL_R = 0;                // Disable SysTick when COUNT_FLAG is set
}
