#include "input_reading.h"

// the buffer that the final result is stored after
// debouncing
uint8_t buttonBuffer[N0_OF_BUTTONS];
// we define two buffers for debouncing
uint8_t debounceButtonBuffer1[N0_OF_BUTTONS];
uint8_t debounceButtonBuffer2[N0_OF_BUTTONS];
 // we define a flag for a button pressed more than 1 second .
uint8_t flagForButtonPress1s[N0_OF_BUTTONS];
 // we define counter for automatically increasing the value
 // after the button is pressed more than 1 second .
uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

static GPIO_TypeDef* ButtonPort[N0_OF_BUTTONS] = {GPIOB, GPIOB, GPIOB};

static uint16_t ButtonPin[N0_OF_BUTTONS] = {GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12};

 void button_reading() 
 {
    for(uint8_t i = 0; i < N0_OF_BUTTONS ; i++) 
    {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        //debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin);
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(ButtonPort[i], ButtonPin[i]);

        if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
            buttonBuffer[i] = debounceButtonBuffer1[i];

        if(buttonBuffer[i] == 0) 
        {
            // if a button is pressed , we start counting
            if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING)
            {
                counterForButtonPress1s[i]++;
            }
            else
            {
                // the flag is turned on when 1 second has passed
                // since the button is pressed .
                flagForButtonPress1s[i] = 1;
                // todo
            }
        } 
        else 
        {
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
    }
 }

uint8_t is_button_pressed(uint8_t index) 
{
    if(index >= N0_OF_BUTTONS) 
        return 0;
    return 1 - buttonBuffer[index];
}

uint8_t is_button_pressed_1s(uint8_t index) 
{
    if(index >= N0_OF_BUTTONS) 
        return 0 ;
    return (flagForButtonPress1s[index] == 1);
}
