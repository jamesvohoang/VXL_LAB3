#include "input_processing.h"

ButtonState buttonState[N0_OF_BUTTONS] = {BUTTON_RELEASED, };
ModeState modeState = 3;

uint8_t durationOfRed = 7;
uint8_t durationOfYellow = 2;
uint8_t durationOfGreen = 5;

void IncreaseDurationOfLight()
{
    switch (modeState)
    {
        case MODIFY_FOR_RED:
            durationOfRed++;
            durationOfGreen++;
            // when increase duration of red or green, we should increase the other to keep logic in this traffic system.
            if(durationOfRed >= 100)
            {
                durationOfRed = 0;
                durationOfGreen = 0;
            }
            break;
        case MODIFY_FOR_YELLOW:
            durationOfYellow++;
            durationOfRed++;
            // this is in oder to keep duration of green + yellow = red.
            if(durationOfYellow >= 100)
                durationOfYellow = 0;
            break;
        case MODIFY_FOR_GREEN:
            durationOfGreen++;
            durationOfRed++;
            // the same with situation modify red one.
            if(durationOfGreen >= 100)
            {
                durationOfRed = 0;
                durationOfGreen = 0;
            }
            break;
        
        default:
            break;
    }
}

void fsm_for_input_processing(void)
{
	switch(buttonState[0])
    {
        case BUTTON_RELEASED:
            if(is_button_pressed(0))
            {
                buttonState[0] = BUTTON_PRESSED;
                TurnAllLightsOff();
            }
            break;

        case BUTTON_PRESSED:
            if(!is_button_pressed(0))
            {
                buttonState[0] = BUTTON_RELEASED;
                // Changing mode
                modeState++;
                if(modeState >= 4) 
                    modeState = 0;
            }
            //else 
            //{
            //    if(is_button_pressed_1s(0))
            //    {
            //        buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
            //    }
            //}
            break;

        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if(!is_button_pressed(0))
            {
                buttonState[0] = BUTTON_RELEASED;
            }
            //todo
            break;
	}

    switch(buttonState[1])
    {
        case BUTTON_RELEASED:
            if(is_button_pressed(1))
            {
                buttonState[1] = BUTTON_PRESSED;
            }
            break;

        case BUTTON_PRESSED:
            if(!is_button_pressed(1))
            {
                buttonState[1] = BUTTON_RELEASED;
                IncreaseDurationOfLight();
            }
            break;

        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if(!is_button_pressed(1))
            {
                buttonState[1] = BUTTON_RELEASED;
            }
            //todo
            IncreaseDurationOfLight();
            break;
	}

    switch(buttonState[2])
    {
        case BUTTON_RELEASED:
            if(is_button_pressed(2))
            {
                buttonState[2] = BUTTON_PRESSED;
            }
            break;

        case BUTTON_PRESSED:
            if(!is_button_pressed(2))
            {
                buttonState[2] = BUTTON_RELEASED;
                modeState = 0;
            }
            break;

        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if(!is_button_pressed(2))
            {
                buttonState[2] = BUTTON_RELEASED;
                modeState = 0;
            }
            //todo
            break;
	}
}