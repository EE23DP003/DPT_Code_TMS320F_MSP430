#include "F28x_Project.h"

void main(void)
{
    InitSysCtrl();
    InitGpio();

    // Set GPIO1 as output
    GPIO_SetupPinOptions(1, GPIO_OUTPUT, GPIO_PUSHPULL);
    // Set GPIO3 as input
    // GPIO_SetupPinOptions(3, GPIO_INPUT, GPIO_PULLUP);

    // Set user LEDs as output
    GPIO_SetupPinOptions(31, GPIO_OUTPUT, GPIO_PUSHPULL);
    GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);


    //while(1)
    {
        // Blink red user LED every second
        //GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        //DELAY_US(1000000);

        // Check if GPIO3 is low
        //if(GpioDataRegs.GPADAT.bit.GPIO3 == 0)
        {

            // Generate first pulse of 140 microseconds on GPIO1
            GpioDataRegs.GPASET.bit.GPIO1 = 1;
            DELAY_US(70);
            GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;

            // Delay of 20 microseconds
            DELAY_US(10);

            // Generate second pulse of 55 microseconds on GPIO1
            GpioDataRegs.GPASET.bit.GPIO1 = 1;
            DELAY_US(27.5);
            GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;

            // Turn ON Red user LED
            GpioDataRegs.GPBSET.bit.GPIO34 = 0;
            DELAY_US(1000000);
            // Turn OFF Red user LED
            GpioDataRegs.GPBSET.bit.GPIO34 = 1;

            // Turn ON blue user LED
            GpioDataRegs.GPASET.bit.GPIO31 = 0;

            //break;
        }
    }
}
