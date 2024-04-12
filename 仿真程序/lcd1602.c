/**********************************
����ͷ�ļ�
**********************************/
#include "lcd1602.h"


/**********************************
��������
**********************************/
/****
*******1602���æ���� 
*****/
void lcd1602_check_busy()
{  
	P0=0xff;
	do
	{
		LCD1602_RS=0;
		LCD1602_RW=1;
		LCD1602_E=0;
		LCD1602_E=1;
	} while(LCD1602_BUSY==1);
	LCD1602_E=0;
}

/****
*******1602д����æ���� 
*****/
void lcd1602_write_date(uchar date)
{
	lcd1602_check_busy();
	LCD1602_E=0;
	LCD1602_PORT=date;
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_E=1;
	LCD1602_E=0;
}

/****
*******1602д����� 
*****/
void lcd1602_write_com(uchar com)
{
	lcd1602_check_busy();
	LCD1602_E=0;
	LCD1602_PORT=com;
	LCD1602_RS=0;
	LCD1602_RW=0;
	LCD1602_E=1;
	LCD1602_E=0;
}

/****
*******LCD1602��ʾ�ַ������� 
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******           dat����Ҫ��ʾ���ַ����������ʽ " "
*****/
void lcd1602_display_str(uchar hang, uchar add, uchar *dat)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);			//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);	//�ڶ���

	while(*dat != '\0')
	{
		lcd1602_write_date(*dat++);
	
	}
}

/****
*******LCD1602��ʾʱ�亯��(��ʾ��ʽ��**:**:**)
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******           time����Ҫ��ʾ��ʱ�䣬����Ϊ��λ
*****/
void lcd1602_display_time(uchar hang, uchar add, uint time)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);				//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);		//�ڶ���

	
	lcd1602_write_date(time/3600/10%10+48);				//ʱ�ӵ�ʮλ
	lcd1602_write_date(time/3600/1%10+48);				//ʱ�ӵĸ�λ
	lcd1602_write_date(':');											//��
	lcd1602_write_date(time%3600/60/10%10+48);		//���ӵ�ʮλ
	lcd1602_write_date(time%3600/60/1%10+48);			//���ӵĸ�λ
	lcd1602_write_date(':');											//��
	lcd1602_write_date(time%60/10%10+48);					//���ӵ�ʮλ
	lcd1602_write_date(time%60/1%10+48);					//���ӵĸ�λ
}

/****
*******LCD1602��ʾ�¶Ⱥ���(��ʾ��ʽ��**.*��)
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******           temp����Ҫ��ʾ���¶�
*****/
void lcd1602_display_temp(uchar hang, uchar add,uint temp)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);			//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);	//�ڶ���

	lcd1602_write_date(temp/100%10+48);
	lcd1602_write_date(temp/10%10+48);
	lcd1602_write_date('.');
	lcd1602_write_date(temp/1%10+48);
	lcd1602_write_date(0xdf);				//��ʾ�¶ȵ�СԲȦ���ţ�0xdf��Һ�����ַ���ĸ÷��ŵ�ַ��
  lcd1602_write_date(0x43);				//��ʾ"C"���ţ�0x43��Һ�����ַ������дC�ĵ�ַ��
}

/****
*******LCD1602��ʾʪ�Ⱥ���(��ʾ��ʽ��**.*%)
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******           humi����Ҫ��ʾ��ʪ��
*****/
void lcd1602_display_humi(uchar hang, uchar add,uint humi)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);			//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);	//�ڶ���

	lcd1602_write_date(humi/100%10+48);
	lcd1602_write_date(humi/10%10+48);
	lcd1602_write_date('.');
	lcd1602_write_date(humi/1%10+48);
	lcd1602_write_date('%');
}

/****
*******LCD1602��ʾ����ǿ�Ⱥ���(��ʾ��ʽ��**.*Lx)
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******           light����Ҫ��ʾ�Ĺ���ǿ��
*****/
void lcd1602_display_light(uchar hang, uchar add,uint light)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);			//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);	//�ڶ���

	lcd1602_write_date(light/100%10+48);
	lcd1602_write_date(light/10%10+48);
	lcd1602_write_date('.');
	lcd1602_write_date(light/1%10+48);
	lcd1602_write_date('L');
	lcd1602_write_date('x');
}

/****
*******LCD1602��ʾ����(��ʾ��ʽ��**.*m/s)
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******          water����Ҫ��ʾ�����
*****/
void lcd1602_display_water(uchar hang, uchar add,uint water)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);			//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);	//�ڶ���

	lcd1602_write_date(water/100%10+48);
	lcd1602_write_date(water/10%10+48);
	lcd1602_write_date('.');
	lcd1602_write_date(water/1%10+48);
	lcd1602_write_date('%');
}

/****
*******LCD1602��ʾ���ֺ���(���4λ)
*******�������壺	hang��������ʾ����  1 ��һ��  2 �ڶ���
*******           add��ƫ������0-15
*******           num����Ҫ��ʾ�����ݣ����4λ
*****/
void lcd1602_display_num(uchar hang, uchar add, uint num)
{
	if(hang==1)   
		lcd1602_write_com(0x80+add);				//��һ��
	else
		lcd1602_write_com(0x80+0x40+add);		//�ڶ���

	if(num > 999)
		lcd1602_write_date(num/1000%10+48);	//ǧ
	if(num > 99)
		lcd1602_write_date(num/100%10+48);	//��
	if(num > 9)
		lcd1602_write_date(num/10%10+48);		//ʮ
	lcd1602_write_date(num/1%10+48);		//��
	lcd1602_write_date(' ');
	lcd1602_write_date(' ');
	lcd1602_write_date(' ');
}

/****
*******LCD1602�������� 
*****/
void lcd1602_clean()
{
	lcd1602_display_str(1,0,"                        ");
	lcd1602_display_str(2,0,"                        ");
}

/****
*******LCD1602��ʼ������ 
*****/
void Lcd1602_Init()
{
	lcd1602_write_com(0x38);
	lcd1602_write_com(0x0c);
	lcd1602_write_com(0x06);
	lcd1602_write_com(0x01);
}

