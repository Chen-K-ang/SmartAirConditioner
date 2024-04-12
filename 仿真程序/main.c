/**********************************
包含头文件
**********************************/
#include "main.h"
#include "lcd1602.h"
#include "key.h"
#include "dht11.h"

/**********************************
引脚定义
**********************************/
sbit motor1 = P1^5; //加热
sbit motor2 = P1^6; //制冷
sbit motor3 = P1^7; //除湿

/**********************************
变量定义
**********************************/
uchar key_num = 0;               //按键标志位
uchar flag_display = 0;	         //显示标志位
uint temp_value = 0;	         //温度
uint temp_min = 16;	             //温度最小值
uint temp_max = 30;              //温度最大值
uint humi_value = 0;	         //湿度
uint humi_max = 60;	             //湿度最大值

/**********************************
函数声明
**********************************/
void Delay_function(uint x);	//延时函数
void Key_function(void);	    //按键函数
void Monitor_function(void);    //监测函数
void Display_function(void);    //显示函数
void Manage_function(void);	    //处理函数

/****
*******	主函数 
*****/
void main()
{
	//motor init
    P1 = 0x00;
	
	Lcd1602_Init();		//LCD1602初始化
	Delay_function(50);	//延时50ms
	lcd1602_clean();	//清屏
	Delay_function(50);	//延时50ms
	DHT11_Init();		//DHT11初始化
	Delay_function(50);	//延时50ms
	Delay_function(50);	//延时50ms

	while(1)
	{
		Key_function();		//按键函数
		Monitor_function();	//监测函数
		Display_function();	//显示函数
		Manage_function();	//处理函数
	
		Delay_function(10);	//延时10ms
	}
}

/****
*******	延时 x ms函数
*****/
void Delay_function(uint x)
{
	uint m,n;
	for(m=x;m>0;m--)
	for(n=110;n>0;n--);
}

/****
*******按键函数
*****/
void Key_function(void)
{
	key_num = Chiclet_Keyboard_Scan(0);	//按键扫描
	if(key_num != 0) {	//有按键按下
	
		switch (key_num) {
		case 1:					//按键1
			flag_display++;					//显示标志位+1
			if(flag_display > 3)			//一共4个模式
				flag_display = 0;

			lcd1602_clean();				//清屏
		break;

		case 4:
			switch (flag_display) {			//根据不同的显示标志位，改变不同限制值		
				case 1:						//改变温度最小值
					if(temp_min < 30)
						temp_min += 2;
				break;

				case 2:						//改变温度最大值
					if(temp_max < 30)
						temp_max += 2;
				break;
					
				case 3:						//改变湿度最大值，进行+10
					if(humi_max < 60)
						humi_max += 10;
				break;

				default:
				break;
			}
		break;

		case 5:	
			switch (flag_display) {
			case 1:							//改变温度最小值，进行-10
				if(temp_min > 16)
					temp_min -= 2;
			break;
				
			case 2:						    //改变温度最大值
				if(temp_max > 16)
					temp_max += 2;
			break;

			case 3:							//改变湿度最大值，进行-10
				if(humi_max > 30)
					humi_max -= 10;
			break;
			
			default:
			break;
			}
		break;

		default:
		break;
		}
	}
}

/****
*******监测函数
*****/
void Monitor_function(void)
{
	Dht11_Get_Temp_Humi_Value(&temp_value, &humi_value); //获取温湿度
}

/****
*******显示函数
*****/
void Display_function(void)
{
	switch (flag_display) {//根据不同的显示标志位，显示不同的设置界面
	
	case 0://界面0
		lcd1602_display_str(1,0,"T:");		//显示温度
		lcd1602_display_temp(1,2,temp_value * 10);

		lcd1602_display_str(2,0,"H:");		//显示湿度
		lcd1602_display_humi(2,2,humi_value * 10);
	break;

	case 1://设置温度下限值
		lcd1602_display_str(1,2,"Set Temp Min");
		lcd1602_display_num(2,7,temp_min);
	break;

	case 2://设置温度上限值
		lcd1602_display_str(1,2,"Set Temp Max");
		lcd1602_display_num(2,7,temp_max);
	break;

	case 3://设置湿度上限值
		lcd1602_display_str(1,2,"Set Humi Max");
		lcd1602_display_num(2,7,humi_max);
	break;

	default:
	break;
	}
}

/****
*******处理函数
*****/
void Manage_function(void)
{
		//温度、湿度超限，电机转动
		if (temp_value < temp_min) { //加热
			motor1 = 1;
			motor2 = 0;
			
		} else if (temp_value > temp_max) { //冷风
			motor1 = 0;
			motor2 = 1;
		} else {
			motor1 = 0;
			motor2 = 0;
		}
		
		if (humi_value > humi_max) { //除湿
			motor3 = 1;
			
		} else if (humi_value < humi_max) {
			motor3 = 0;
			
		} else {
		
		}
}
