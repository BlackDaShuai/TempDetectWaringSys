#include "main.h"
#include "keyscan.h"
int keyScan()
{
	if(KEY1 == 1)
	{
		while(KEY1 == 1){}
			HAL_GPIO_TogglePin(LEDB_GPIO_Port,LEDB_Pin);
			return 1;
	}
	else if(KEY2 == 1)
	{
		while(KEY2 == 1){}
			return 2;
	}
	else if(KEY3 == 1)
	{
		while(KEY3 == 1){}
			return 3;
	}
	else if(KEY4 == 1)
	{
		while(KEY4 == 1){}
			return 4;
	}
	else
	{
		return 0;
	}
}