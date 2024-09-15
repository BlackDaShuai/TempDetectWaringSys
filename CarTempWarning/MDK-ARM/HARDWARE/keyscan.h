#ifndef __KEYSCAN_H__
#define __KEYSCAN_H__

#define KEY1 (!(HAL_GPIO_ReadPin(Key1_GPIO_Port,Key1_Pin)))
#define KEY2 (!(HAL_GPIO_ReadPin(Key2_GPIO_Port,Key2_Pin)))
#define KEY3 (!(HAL_GPIO_ReadPin(Key3_GPIO_Port,Key3_Pin)))
#define KEY4 (!(HAL_GPIO_ReadPin(Key4_GPIO_Port,Key4_Pin)))

int keyScan(void);


#endif