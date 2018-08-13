#include "lcd.h"

static uint32_t *pfb = (uint32_t *)FB_ADDR;

// ��ʼ��LCD
void lcd_init(void)
{
	// ������������LCD����
	GPF0CON = 0x22222222;
	GPF1CON = 0x22222222;
	GPF2CON = 0x22222222;
	GPF3CON = 0x22222222;
	
	// �򿪱���	GPD0_0��PWMTOUT0��
	GPD0CON &= ~(0xf<<0);
	GPD0CON |= (1<<0);			// output mode
	GPD0DAT &= ~(1<<0);			// output 0 to enable backlight
	
	// 10: RGB=FIMD I80=FIMD ITU=FIMD
	DISPLAY_CONTROL = 2<<0;
	
	// bit[26~28]:ʹ��RGB�ӿ�
	// bit[18]:RGB ����
	// bit[2]:ѡ��ʱ��ԴΪHCLK_DSYS=166MHz
	VIDCON0 &= ~( (3<<26)|(1<<18)|(1<<2) );
	
	// bit[1]:ʹ��lcd������
	// bit[0]:��ǰ֡������ʹ��lcd������
	VIDCON0 |= ( (1<<0)|(1<<1) );
	
	// bit[6]:ѡ����Ҫ��Ƶ
	// bit[6~13]:��Ƶϵ��Ϊ5����VCLK = 166M/(4+1) = 33M
	VIDCON0 |= 4<<6 | 1<<4;
	
	// H43-HSD043I9W1.pdf(p13) ʱ��ͼ��VSYNC��HSYNC���ǵ�����
	// s5pv210оƬ�ֲ�(p1207) ʱ��ͼ��VSYNC��HSYNC���Ǹ�������Ч��������Ҫ��ת
	VIDCON1 |= 1<<5 | 1<<6;
	
	// ����ʱ��
	VIDTCON0 = VBPD<<16 | VFPD<<8 | VSPW<<0;
	VIDTCON1 = HBPD<<16 | HFPD<<8 | HSPW<<0;
	// ���ó���(������Ļ)
	VIDTCON2 = (LINEVAL << 11) | (HOZVAL << 0);

	// ����window0
	// bit[0]:ʹ��
	// bit[2~5]:24bpp��RGB888��
	WINCON0 |= 1<<0;
	WINCON0 &= ~(0xf << 2);
	WINCON0 |= (0xB<<2) | (1<<15);

	// ����window0����������
	// ���õ����Դ�ռ�Ĵ�С
	VIDOSD0A = (LeftTopX<<11) | (LeftTopY << 0);
	VIDOSD0B = (RightBotX<<11) | (RightBotY << 0);
	VIDOSD0C = (LINEVAL + 1) * (HOZVAL + 1);

	// ����fb�ĵ�ַ
	VIDW00ADD0B0 = FB_ADDR;
	VIDW00ADD1B0 = (((HOZVAL + 1)*4 + 0) * (LINEVAL + 1)) & (0xffffff);

	// ʹ��channel 0��������
	SHADOWCON = 0x1;
}

// �����ص�(x, y)�����Ϊcolor��ɫ
inline void lcd_draw_pixel(uint32_t x, uint32_t y, uint32_t color)
{
	*(pfb + COL * y + x) = color;
}

// ��������Ļȫ������һ����ɫcolor
void lcd_draw_background(uint32_t color)
{
	uint32_t i, j;
	
	for (j=0; j<ROW; j++)
	{
		for (i=0; i<COL; i++)
		{
			lcd_draw_pixel(i, j, color);
		}
	}
}

