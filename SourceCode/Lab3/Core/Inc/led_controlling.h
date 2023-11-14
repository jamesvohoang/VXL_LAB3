#ifndef INC_LED_CONTROLLING_H_
#define INC_LED_CONTROLLING_H_

#include "main.h"

void DisplayNum(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g );

void display7SEG(int num);

void Enable7SEG(uint8_t index);
void Disable7SEG(uint8_t index);
void DisableAllSegs();

void TurnAllLightsOff();

void ToggleAllRedLeds();
void ToggleAllYellowLeds();
void ToggleAllGreenLeds();

#endif /* INC_LED_CONTROLLING_H_ */