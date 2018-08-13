#include "uart.h"
#include "led.h"


void uart_init(uint8_t baud_rate)
{
	rGPA1CON &= ~(0xff<<0);			// warning: 0x00001111
	rGPA1CON |= (0x2<<4)|(0x2<<0);
	
	rULCON2 &= ~(0x3<<0);
	rULCON2 |= (0x3<<0);
	
	rUCON2 &= ~((0x1<<2)|(0x1<<0));
	rUCON2 |= ((0x1<<2)|(0x1<<0));
	
	if (UART2_115200 == baud_rate)
	{
		rUBRDIV2 = 35;
		rUDIVSLOT2 = 0x0888;
	}
	else if (UART2_9600 == baud_rate)
	{
		rUBRDIV2 = 429;
		rUDIVSLOT2 = 0xD5D5;
	}
	else
	{
		
	}
}

//void uart_putc(char c)
void putc(unsigned char c)
{	
	// ���ڷ���һ���ַ�����ʵ���ǰ�һ���ֽڶ������ͻ�������ȥ
	// ��Ϊ���ڿ���������1���ֽڵ��ٶ�ԶԶ����CPU���ٶȣ�����CPU����1���ֽ�ǰ����
	// ȷ�ϴ��ڿ�������ǰ�������ǿյ�(�����Ѿ���������һ���ֽ�)
	while (!(rUTRSTAT2 & (1<<1)));
	
	rUTXH2 = c;
}

// ���ڽ��ճ�����ѯ��ʽ������һ���ֽ�
//char uart_getc(void)
unsigned char getc(void)
{
	while (!(rUTRSTAT2 & (1<<0)));
	
	return (rURXH2 & 0xFF);
}
















