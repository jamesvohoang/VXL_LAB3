#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "main.h"
#include "input_reading.h"
#include "led_controlling.h"

typedef enum
{
    BUTTON_RELEASED, 
    BUTTON_PRESSED, 
    BUTTON_PRESSED_MORE_THAN_1_SECOND
}ButtonState;

typedef enum
{
    NORMAL,
    MODIFY_FOR_RED,
    MODIFY_FOR_YELLOW,
    MODIFY_FOR_GREEN
}ModeState;

extern ModeState modeState;
extern uint8_t durationOfRed;
extern uint8_t durationOfYellow;
extern uint8_t durationOfGreen;

void fsm_for_input_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */