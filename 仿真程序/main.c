/**********************************
����ͷ�ļ�
**********************************/
#include "main.h"
#include "lcd1602.h"
#include "key.h"
#include "dht11.h"

/**********************************
���Ŷ���
**********************************/
sbit motor1 = P1^5; //����
sbit motor2 = P1^6; //����
sbit motor3 = P1^7; //��ʪ

/**********************************
��������
**********************************/
uchar key_num = 0;               //������־λ
uchar flag_display = 0;	         //��ʾ��־λ
uint temp_value = 0;	         //�¶�
uint temp_min = 16;	             //�¶���Сֵ
uint temp_max = 30;              //�¶����ֵ
uint humi_value = 0;	         //ʪ��
uint humi_max = 60;	             //ʪ�����ֵ

/**********************************
��������
**********************************/
void Delay_function(uint x);	//��ʱ����
void Key_function(void);	    //��������
void Monitor_function(void);    //��⺯��
void Display_function(void);    //��ʾ����
void Manage_function(void);	    //������

/****
*******	������ 
*****/
void main()
{
	//motor init
    P1 = 0x00;
	
	Lcd1602_Init();		//LCD1602��ʼ��
	Delay_function(50);	//��ʱ50ms
	lcd1602_clean();	//����
	Delay_function(50);	//��ʱ50ms
	DHT11_Init();		//DHT11��ʼ��
	Delay_function(50);	//��ʱ50ms
	Delay_function(50);	//��ʱ50ms

	while(1)
	{
		Key_function();		//��������
		Monitor_function();	//��⺯��
		Display_function();	//��ʾ����
		Manage_function();	//������
	
		Delay_function(10);	//��ʱ10ms
	}
}

/****
*******	��ʱ x ms����
*****/
void Delay_function(uint x)
{
	uint m,n;
	for(m=x;m>0;m--)
	for(n=110;n>0;n--);
}

/****
*******��������
*****/
void Key_function(void)
{
	key_num = Chiclet_Keyboard_Scan(0);	//����ɨ��
	if(key_num != 0) {	//�а�������
	
		switch (key_num) {
		case 1:					//����1
			flag_display++;					//��ʾ��־λ+1
			if(flag_display > 3)			//һ��4��ģʽ
				flag_display = 0;

			lcd1602_clean();				//����
		break;

		case 4:
			switch (flag_display) {			//���ݲ�ͬ����ʾ��־λ���ı䲻ͬ����ֵ		
				case 1:						//�ı��¶���Сֵ
					if(temp_min < 30)
						temp_min += 2;
				break;

				case 2:						//�ı��¶����ֵ
					if(temp_max < 30)
						temp_max += 2;
				break;
					
				case 3:						//�ı�ʪ�����ֵ������+10
					if(humi_max < 60)
						humi_max += 10;
				break;

				default:
				break;
			}
		break;

		case 5:	
			switch (flag_display) {
			case 1:							//�ı��¶���Сֵ������-10
				if(temp_min > 16)
					temp_min -= 2;
			break;
				
			case 2:						    //�ı��¶����ֵ
				if(temp_max > 16)
					temp_max += 2;
			break;

			case 3:							//�ı�ʪ�����ֵ������-10
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
*******��⺯��
*****/
void Monitor_function(void)
{
	Dht11_Get_Temp_Humi_Value(&temp_value, &humi_value); //��ȡ��ʪ��
}

/****
*******��ʾ����
*****/
void Display_function(void)
{
	switch (flag_display) {//���ݲ�ͬ����ʾ��־λ����ʾ��ͬ�����ý���
	
	case 0://����0
		lcd1602_display_str(1,0,"T:");		//��ʾ�¶�
		lcd1602_display_temp(1,2,temp_value * 10);

		lcd1602_display_str(2,0,"H:");		//��ʾʪ��
		lcd1602_display_humi(2,2,humi_value * 10);
	break;

	case 1://�����¶�����ֵ
		lcd1602_display_str(1,2,"Set Temp Min");
		lcd1602_display_num(2,7,temp_min);
	break;

	case 2://�����¶�����ֵ
		lcd1602_display_str(1,2,"Set Temp Max");
		lcd1602_display_num(2,7,temp_max);
	break;

	case 3://����ʪ������ֵ
		lcd1602_display_str(1,2,"Set Humi Max");
		lcd1602_display_num(2,7,humi_max);
	break;

	default:
	break;
	}
}

/****
*******������
*****/
void Manage_function(void)
{
		//�¶ȡ�ʪ�ȳ��ޣ����ת��
		if (temp_value < temp_min) { //����
			motor1 = 1;
			motor2 = 0;
			
		} else if (temp_value > temp_max) { //���
			motor1 = 0;
			motor2 = 1;
		} else {
			motor1 = 0;
			motor2 = 0;
		}
		
		if (humi_value > humi_max) { //��ʪ
			motor3 = 1;
			
		} else if (humi_value < humi_max) {
			motor3 = 0;
			
		} else {
		
		}
}
