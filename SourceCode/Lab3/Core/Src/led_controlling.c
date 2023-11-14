#include "led_controlling.h"

void DisplayNum(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g )
{
    HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, a);
    HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, b);
    HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, c);
    HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, d);
    HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, e);
    HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, f);
    HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, g);
}

void display7SEG(int num)
{
  switch (num)
  {
  case 0:
    DisplayNum(0, 0, 0, 0, 0, 0, 1);
    break;
  case 1:
    DisplayNum(1, 0, 0, 1, 1, 1, 1);
    break;
  case 2:
    DisplayNum(0, 0, 1, 0, 0, 1, 0);
    break;
  case 3:
    DisplayNum(0, 0, 0, 0, 1, 1, 0);
    break;
  case 4:
    DisplayNum(1, 0, 0, 1, 1, 0, 0);
    break;
  case 5:
    DisplayNum(0, 1, 0, 0, 1, 0, 0);
    break;
  case 6:
    DisplayNum(0, 1, 0, 0, 0, 0, 0);
    break;
  case 7:
    DisplayNum(0, 0, 0, 1, 1, 1, 1);
    break;
  case 8:
    DisplayNum(0, 0, 0, 0, 0, 0, 0);
    break;
  case 9:
    DisplayNum(0, 0, 0, 0, 1, 0, 0);
    break;
  
  default:
    break;
  }
}

void EnableSeg0()
{
  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
}
void DisableSeg0()
{
  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
}
void EnableSeg1()
{
  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
}
void DisableSeg1()
{
  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
}
void EnableSeg2()
{
  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
}
void DisableSeg2()
{
  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
}
void EnableSeg3()
{
  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
}
void DisableSeg3()
{
  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
}

void DisableAllSegs()
{
  DisableSeg0();
  DisableSeg1();
  DisableSeg2();
  DisableSeg3();
}

void Enable7SEG(uint8_t index)
{
  switch (index)
  {
  case 0:
    EnableSeg0();
    break;
  case 1:
    EnableSeg1();
    break;
  case 2:
    EnableSeg2();
    break;
  case 3:
    EnableSeg3();
    break;
  
  default:
    break;
  }
}

void Disable7SEG(uint8_t index)
{
  switch (index)
  {
  case 0:
    DisableSeg0();
    break;
  case 1:
    DisableSeg1();
    break;
  case 2:
    DisableSeg2();
    break;
  case 3:
    DisableSeg3();
    break;
  
  default:
    break;
  }
}

void TurnAllLightsOff()
{
  HAL_GPIO_WritePin(RED0_GPIO_Port, RED0_Pin, 1);
  HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
  //HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
  //HAL_GPIO_WritePin(RED3_GPIO_Port, RED3_Pin, 1);

  HAL_GPIO_WritePin(YEL0_GPIO_Port, YEL0_Pin, 1);
  HAL_GPIO_WritePin(YEL1_GPIO_Port, YEL1_Pin, 1);
  //HAL_GPIO_WritePin(YEL2_GPIO_Port, YEL2_Pin, 1);
  //HAL_GPIO_WritePin(YEL3_GPIO_Port, YEL3_Pin, 1);

  HAL_GPIO_WritePin(GRN0_GPIO_Port, GRN0_Pin, 1);
  HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, 1);
  //HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, 1);
  //HAL_GPIO_WritePin(GRN3_GPIO_Port, GRN3_Pin, 1);
}

void ToggleAllRedLeds()
{
  HAL_GPIO_TogglePin(RED0_GPIO_Port, RED0_Pin);
  HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
}

void ToggleAllYellowLeds()
{
  HAL_GPIO_TogglePin(YEL0_GPIO_Port, YEL0_Pin);
  HAL_GPIO_TogglePin(YEL1_GPIO_Port, YEL1_Pin);
}

void ToggleAllGreenLeds()
{
  HAL_GPIO_TogglePin(GRN0_GPIO_Port, GRN0_Pin);
  HAL_GPIO_TogglePin(GRN1_GPIO_Port, GRN1_Pin);
}