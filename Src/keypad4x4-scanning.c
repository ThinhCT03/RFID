/**


/** Includes ---------------------------------------------------------------- */
#include "keypad4x4-scanning.h"

GPIO_InitTypeDef _GPIO_InitStructKeypad;
GPIO_InitTypeDef _GPIO_InitStruct;
/** Public functions -------------------------------------------------------- */
/**
  ******************************************************************************
  * @brief	Initialize GPIO pins for keypad.
  * @param	None
  * @retval	None
  ******************************************************************************
  */
void KeypadInit()
{
	DelayInit();
	
	// GPIO clock for keypad columns and rows
	RCC_APB2PeriphClockCmd(KEYPAD_RCC_GPIO_COL, ENABLE);
	RCC_APB2PeriphClockCmd(KEYPAD_RCC_GPIO_ROW, ENABLE);
	
	// Configure GPIO as output open drain for keypad columns
	_GPIO_InitStructKeypad.GPIO_Pin = KEYPAD_PIN_COL0 | KEYPAD_PIN_COL1 |
		KEYPAD_PIN_COL2 | KEYPAD_PIN_COL3;
	_GPIO_InitStructKeypad.GPIO_Mode = GPIO_Mode_Out_OD;
	_GPIO_InitStructKeypad.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(KEYPAD_GPIO_COL, &_GPIO_InitStructKeypad);
	
	// Configure GPIO as input with pull-up resistor for keypad rows
	_GPIO_InitStructKeypad.GPIO_Pin = KEYPAD_PIN_ROW0 | KEYPAD_PIN_ROW1 |
		KEYPAD_PIN_ROW2 | KEYPAD_PIN_ROW3;
	_GPIO_InitStructKeypad.GPIO_Mode = GPIO_Mode_IPU;
	_GPIO_InitStructKeypad.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(KEYPAD_GPIO_ROW, &_GPIO_InitStructKeypad);
}

void LEDInit()
{
    // GPIO clock for LED pins
    RCC_APB2PeriphClockCmd(LED_RCC_GPIO, ENABLE);

    // Configure GPIO as output push-pull for LED1 (Assuming LED1 is on Pin LED_PIN1)
    _GPIO_InitStruct.GPIO_Pin = LED_PIN1;
    _GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    _GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_GPIO, &_GPIO_InitStruct);

    // Configure GPIO as output push-pull for LED2 (Assuming LED2 is on Pin LED_PIN2)
    _GPIO_InitStruct.GPIO_Pin = LED_PIN2;
    _GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    _GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_GPIO, &_GPIO_InitStruct);
}
/**
  ******************************************************************************
  * @brief	Get which key is pressed by scanning the columns and read the rows.
  * @param	None
  * @retval	Pressed key char value.
  ******************************************************************************
  */
uint8_t KeypadGetKey()
{
	// Scan column 0 (column 0 pin is grounded, other column pins is open drain)
	GPIO_ResetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL0);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL1);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL2);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL3);
	DelayUs(1);
	// Read rows
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW0))
		return '0';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW1))
		return '4';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW2))
		return '8';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW3))
		return 'C';
		
	// Scan column 1 (column 1 pin is grounded, other column pins is open drain)
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL0);
	GPIO_ResetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL1);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL2);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL3);
	DelayUs(1);
	// Read rows
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW0))
		return '1';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW1))
		return '5';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW2))
		return '9';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW3))
		return 'D';
		
	// Scan column 2 (column 2 pin is grounded, other column pins is open drain)
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL0);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL1);
	GPIO_ResetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL2);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL3);
	DelayUs(1);
	// Read rows
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW0))
		return '2';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW1))
		return '6';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW2))
		return 'A';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW3))
		return 'E';
		
	// Scan column 3 (column 3 pin is grounded, other column pins is open drain)
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL0);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL1);
	GPIO_SetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL2);
	GPIO_ResetBits(KEYPAD_GPIO_COL, KEYPAD_PIN_COL3);
	DelayUs(1);
	// Read rows
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW0))
		return '3';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW1))
		return '7';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW2))
		return 'B';
	if (!GPIO_ReadInputDataBit(KEYPAD_GPIO_ROW, KEYPAD_PIN_ROW3))
		return 'F';
	
	return KEYPAD_NO_PRESSED;
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
