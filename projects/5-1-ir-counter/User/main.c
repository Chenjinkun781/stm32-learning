#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LightSensor.h"
#include "CountSensor.h"


int main (void)
{
	OLED_Init();
	CountSensor_Init();

	OLED_ShowString(1,3,"Count:");
	
	
	while (1)
	{
	OLED_ShowHexNum(1 , 7,CountSensor_Get() ,  5);
	}
}
