/**********************************
���ߣ���Ƭ�����ֲ�
��վ��https://www.mcuclub.cn/
**********************************/


#ifndef _LCD1602_H_
#define _LCD1602_H_


/**********************************
����ͷ�ļ�
**********************************/
#include "main.h"


/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_PORT P0      		 //��������P0.0-P0.7
sbit LCD1602_RS=P2^5;						 //����/����ѡ������P2.5
sbit LCD1602_RW=P2^6;						 //��/дѡ��P2.6
sbit LCD1602_E=P2^7;						 //ʹ���ź�����P2.7
sbit LCD1602_BUSY=P0^7;					 //���״̬����P0.7


/**********************************
��������
**********************************/
void lcd1602_display_str(uchar hang, uchar add, uchar *dat);					//LCD1602��ʾ�ַ�������
void lcd1602_display_time(uchar hang, uchar add, uint time);					//LCD1602��ʾʱ�亯��(��ʾ��ʽ��**:**:**)
void lcd1602_display_temp(uchar hang, uchar add,uint temp);						//LCD1602��ʾ�¶Ⱥ���(��ʾ��ʽ��**.*��)
void lcd1602_display_humi(uchar hang, uchar add,uint humi);						//LCD1602��ʾʪ�Ⱥ���(��ʾ��ʽ��**.*%)
void lcd1602_display_light(uchar hang, uchar add,uint light);					//LCD1602��ʾ����ǿ�Ⱥ���(��ʾ��ʽ��**.*Lx)
void lcd1602_display_water(uchar hang, uchar add,uint water);						//LCD1602��ʾ���ٺ���(��ʾ��ʽ��**.*m/s)
void lcd1602_display_num(uchar hang, uchar add,uint num);							//LCD1602��ʾ���ֺ���(���4λ)
void lcd1602_clean();																									//LCD1602��������
void Lcd1602_Init();																									//LCD1602��ʼ������


#endif

