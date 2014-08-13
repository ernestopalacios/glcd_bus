
#pragma used+
sfrb PINA=0;
sfrb DDRA=1;
sfrb PORTA=2;
sfrb PINB=3;
sfrb DDRB=4;
sfrb PORTB=5;
sfrb PINC=6;
sfrb DDRC=7;
sfrb PORTC=8;
sfrb PIND=9;
sfrb DDRD=0xa;
sfrb PORTD=0xb;
sfrb TIFR0=0x15;
sfrb TIFR1=0x16;
sfrb TIFR2=0x17;
sfrb PCIFR=0x1b;
sfrb EIFR=0x1c;
sfrb EIMSK=0x1d;
sfrb GPIOR0=0x1e;
sfrb EECR=0x1f;
sfrb EEDR=0x20;
sfrb EEARL=0x21;
sfrb EEARH=0x22;
sfrw EEAR=0X21;   
sfrb GTCCR=0x23;
sfrb TCCR0A=0x24;
sfrb TCCR0B=0x25;
sfrb TCNT0=0x26;
sfrb OCR0A=0x27;
sfrb OCR0B=0x28;
sfrb GPIOR1=0x2a;
sfrb GPIOR2=0x2b;
sfrb SPCR=0x2c;
sfrb SPSR=0x2d;
sfrb SPDR=0x2e;
sfrb ACSR=0x30;
sfrb OCDR=0x31;
sfrb SMCR=0x33;
sfrb MCUSR=0x34;
sfrb MCUCR=0x35;
sfrb SPMCSR=0x37;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif
#endasm

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

typedef char *va_list;

#pragma used+

char getchar(void);
void putchar(char c);
void puts(char *str);
void putsf(char flash *str);
int printf(char flash *fmtstr,...);
int sprintf(char *str, char flash *fmtstr,...);
int vprintf(char flash * fmtstr, va_list argptr);
int vsprintf(char *str, char flash * fmtstr, va_list argptr);

char *gets(char *str,unsigned int len);
int snprintf(char *str, unsigned int size, char flash *fmtstr,...);
int vsnprintf(char *str, unsigned int size, char flash * fmtstr, va_list argptr);

int scanf(char flash *fmtstr,...);
int sscanf(char *str, char flash *fmtstr,...);

#pragma used-

#pragma library stdio.lib

#pragma used+

unsigned char cabs(signed char x);
unsigned int abs(int x);
unsigned long labs(long x);
float fabs(float x);
int atoi(char *str);
long int atol(char *str);
float atof(char *str);
void itoa(int n,char *str);
void ltoa(long int n,char *str);
void ftoa(float n,unsigned char decimals,char *str);
void ftoe(float n,unsigned char decimals,char *str);
void srand(int seed);
int rand(void);
void *malloc(unsigned int size);
void *calloc(unsigned int num, unsigned int size);
void *realloc(void *ptr, unsigned int size); 
void free(void *ptr);

#pragma used-
#pragma library stdlib.lib

#pragma used+

signed char cmax(signed char a,signed char b);
int max(int a,int b);
long lmax(long a,long b);
float fmax(float a,float b);
signed char cmin(signed char a,signed char b);
int min(int a,int b);
long lmin(long a,long b);
float fmin(float a,float b);
signed char csign(signed char x);
signed char sign(int x);
signed char lsign(long x);
signed char fsign(float x);
unsigned char isqrt(unsigned int x);
unsigned int lsqrt(unsigned long x);
float sqrt(float x);
float ftrunc(float x);
float floor(float x);
float ceil(float x);
float fmod(float x,float y);
float modf(float x,float *ipart);
float ldexp(float x,int expon);
float frexp(float x,int *expon);
float exp(float x);
float log(float x);
float log10(float x);
float pow(float x,float y);
float sin(float x);
float cos(float x);
float tan(float x);
float sinh(float x);
float cosh(float x);
float tanh(float x);
float asin(float x);
float acos(float x);
float atan(float x);
float atan2(float y,float x);

#pragma used-
#pragma library math.lib

#pragma used+

char *strcat(char *str1,char *str2);
char *strcatf(char *str1,char flash *str2);
char *strchr(char *str,char c);
signed char strcmp(char *str1,char *str2);
signed char strcmpf(char *str1,char flash *str2);
char *strcpy(char *dest,char *src);
char *strcpyf(char *dest,char flash *src);
unsigned int strlenf(char flash *str);
char *strncat(char *str1,char *str2,unsigned char n);
char *strncatf(char *str1,char flash *str2,unsigned char n);
signed char strncmp(char *str1,char *str2,unsigned char n);
signed char strncmpf(char *str1,char flash *str2,unsigned char n);
char *strncpy(char *dest,char *src,unsigned char n);
char *strncpyf(char *dest,char flash *src,unsigned char n);
char *strpbrk(char *str,char *set);
char *strpbrkf(char *str,char flash *set);
char *strrchr(char *str,char c);
char *strrpbrk(char *str,char *set);
char *strrpbrkf(char *str,char flash *set);
char *strstr(char *str1,char *str2);
char *strstrf(char *str1,char flash *str2);
char *strtok(char *str1,char flash *str2);

unsigned int strlen(char *str);
void *memccpy(void *dest,void *src,char c,unsigned n);
void *memchr(void *buf,unsigned char c,unsigned n);
signed char memcmp(void *buf1,void *buf2,unsigned n);
signed char memcmpf(void *buf1,void flash *buf2,unsigned n);
void *memcpy(void *dest,void *src,unsigned n);
void *memcpyf(void *dest,void flash *src,unsigned n);
void *memmove(void *dest,void *src,unsigned n);
void *memset(void *buf,unsigned char c,unsigned n);
unsigned int strcspn(char *str,char *set);
unsigned int strcspnf(char *str,char flash *set);
int strpos(char *str,char c);
int strrpos(char *str,char c);
unsigned int strspn(char *str,char *set);
unsigned int strspnf(char *str,char flash *set);

#pragma used-
#pragma library string.lib

flash unsigned char font[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x4F,0x00,0x00,0x00,0x00,0x00, 
0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x00, 
0x00,0x24,0xFF,0x24,0xFF,0x24,0x00,0x00, 
0x00,0x44,0x4A,0xFF,0x4A,0x32,0x00,0x00, 
0x40,0x23,0x13,0x08,0xC4,0xC2,0x00,0x00, 
0x00,0x36,0x49,0x55,0x22,0x40,0x80,0x00, 
0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00, 
0x00,0x3C,0x42,0x81,0x00,0x00,0x00,0x00, 
0x00,0x81,0x42,0x3C,0x00,0x00,0x00,0x00, 
0x00,0x14,0x08,0x3E,0x08,0x14,0x00,0x00, 
0x00,0x10,0x10,0x7C,0x10,0x10,0x00,0x00, 
0x00,0x00,0x28,0x18,0x00,0x00,0x00,0x00, 
0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00, 
0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00, 
0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00, 
0x00,0x7E,0xFF,0x81,0x81,0xFF,0x7E,0x00, 
0x00,0x80,0x82,0xFE,0xFF,0x80,0x80,0x00, 
0x00,0xE2,0xF1,0x91,0x91,0x9F,0x8E,0x00, 
0x00,0x62,0xC3,0xC9,0xC9,0xFF,0x76,0x00, 
0x00,0x18,0x14,0x12,0xFF,0xFF,0x10,0x00, 
0x00,0x6F,0x8F,0x89,0x89,0xF9,0x71,0x00, 
0x00,0x7E,0xFF,0x89,0x89,0xF9,0x72,0x00, 
0x00,0x01,0x01,0xF1,0xFD,0x07,0x03,0x00, 
0x00,0x76,0xFF,0x89,0x89,0xFF,0x76,0x00, 
0x00,0x46,0x8F,0x89,0x89,0xFF,0x7E,0x00, 

0x00,0x00,0x66,0x66,0x00,0x00,0x00,0x00, 
0x00,0x00,0x56,0x36,0x00,0x00,0x00,0x00, 
0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00, 
0x00,0x24,0x24,0x24,0x24,0x24,0x00,0x00, 
0x00,0x00,0x41,0x22,0x14,0x08,0x00,0x00, 
0x00,0x02,0x01,0xB1,0x09,0x06,0x00,0x00, 
0x00,0x62,0x91,0xF1,0x81,0x7E,0x00,0x00, 
0x00,0xFE,0x11,0x11,0x11,0xFE,0x00,0x00, 
0x00,0xFF,0x89,0x89,0x89,0x76,0x00,0x00, 
0x00,0x7E,0x81,0x81,0x81,0x42,0x00,0x00, 
0x00,0xFF,0x81,0x81,0x42,0x3C,0x00,0x00, 
0x00,0xFF,0x89,0x89,0x89,0x81,0x00,0x00, 
0x00,0xFF,0x09,0x09,0x09,0x01,0x00,0x00, 
0x00,0x7E,0x81,0x91,0x91,0x72,0x00,0x00, 
0x00,0xFF,0x10,0x10,0x10,0xFF,0x00,0x00, 
0x00,0x00,0x81,0xFF,0x81,0x00,0x00,0x00, 
0x00,0x40,0x80,0x81,0x7F,0x01,0x00,0x00, 
0x00,0xFF,0x18,0x24,0x42,0x81,0x00,0x00, 
0x00,0xFF,0x80,0x80,0x80,0x80,0x00,0x00, 
0x00,0xFF,0x02,0x0C,0x02,0xFF,0x00,0x00, 
0x00,0xFF,0x04,0x08,0x10,0xFF,0x00,0x00, 
0x00,0x7E,0x81,0x81,0x81,0x7E,0x00,0x00, 
0x00,0xFF,0x11,0x11,0x11,0x0E,0x00,0x00, 
0x7E,0x81,0xA1,0x41,0xBE,0x00,0x00,0x00, 
0x00,0xFF,0x11,0x31,0x51,0x8E,0x00,0x00, 
0x00,0x86,0x89,0x89,0x89,0x71,0x00,0x00, 
0x00,0x01,0x01,0xFF,0x01,0x01,0x00,0x00, 
0x00,0x7F,0x80,0x80,0x80,0x7F,0x00,0x00, 
0x00,0x3F,0x40,0x80,0x40,0x3F,0x00,0x00, 
0x00,0x3F,0xC0,0x60,0xC0,0x3F,0x00,0x00, 
0x00,0xE3,0x14,0x08,0x14,0xE3,0x00,0x00, 
0x00,0x07,0x08,0xF0,0x08,0x07,0x00,0x00, 
0x00,0xC1,0xA1,0x91,0x89,0x87,0x00,0x00, 
0x00,0xFF,0x81,0x81,0x00,0x00,0x00,0x00, 
0x00,0x15,0x16,0x7C,0x16,0x15,0x00,0x00, 
0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00, 
0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00, 
0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00, 
0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00, 
0x00,0x60,0x94,0x94,0x94,0x78,0x00,0x00, 
0x00,0xFF,0x88,0x88,0x88,0x70,0x00,0x00, 
0x00,0x78,0x84,0x84,0x84,0x00,0x00,0x00, 
0x00,0x78,0x84,0x84,0x88,0x7F,0x00,0x00, 
0x00,0x78,0x94,0x94,0x94,0x58,0x00,0x00, 
0x00,0x10,0xFE,0x11,0x01,0x02,0x00,0x00, 
0x00,0x0C,0x92,0x92,0x92,0x7E,0x00,0x00, 
0x00,0xFF,0x10,0x08,0x08,0xF0,0x00,0x00, 
0x00,0x00,0x84,0xFD,0x80,0x00,0x00,0x00, 
0x00,0x60,0x80,0x80,0x7D,0x00,0x00,0x00, 
0x00,0xFF,0x30,0x48,0x84,0x00,0x00,0x00, 
0x00,0x00,0x81,0xFF,0x80,0x00,0x00,0x00, 
0x00,0xFC,0x04,0x38,0x04,0xF8,0x00,0x00, 
0x00,0xFC,0x08,0x04,0x04,0xF8,0x00,0x00, 
0x00,0x78,0x84,0x84,0x84,0x78,0x00,0x00, 
0x00,0xFC,0x14,0x14,0x14,0x08,0x00,0x00, 
0x00,0x08,0x14,0x14,0x18,0xFC,0x00,0x00, 
0x00,0xFC,0x08,0x04,0x04,0x08,0x00,0x00, 
0x00,0x88,0x94,0x94,0x94,0x60,0x00,0x00, 
0x00,0x04,0x7F,0x84,0x80,0x40,0x00,0x00, 
0x00,0x7C,0x80,0x80,0x40,0xFC,0x00,0x00, 
0x00,0x3C,0x40,0x80,0x40,0x3C,0x00,0x00, 
0x00,0x3E,0xC0,0x60,0xC0,0x3E,0x00,0x00, 
0x00,0x42,0x24,0x18,0x24,0x42,0x00,0x00, 
0x00,0x06,0x88,0x88,0x88,0x7E,0x00,0x00, 
0x00,0xC4,0xA4,0x94,0x8C,0x84,0x00,0x00, 
0x00,0x08,0x76,0x81,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00, 
0x00,0x81,0x76,0x08,0x00,0x00,0x00,0x00, 
0x00,0x08,0x08,0x2A,0x1C,0x08,0x00,0x00, 
0x00,0x08,0x1C,0x2A,0x08,0x08,0x00,0x00, 
0x00,0x7C,0x82,0x81,0x82,0x7C,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 
};

flash unsigned char map[62][6] = {
{193,193,193,193,0,0},
{194,194,254,254,1,0},
{195,195,31,31,1,0},
{196,196,252,252,1,0},
{197,197,197,197,1,1},
{198,189,191,190,1,1},
{199,199,192,192,1,0},
{200,130,132,131,1,1},
{201,201,253,253,1,0},
{202,133,135,134,1,1},
{203,136,138,137,1,1},
{204,139,204,139,1,1},
{205,140,205,140,1,1},
{206,17,206,17,1,1},
{207,207,19,19,1,0},
{208,208,143,143,1,0},
{209,209,27,27,1,0},
{210,210,145,145,1,0},
{211,146,148,147,1,1},
{212,149,151,150,1,1},
{213,23,154,153,1,1},
{214,155,157,156,1,1},
{215,215,215,215,0,0},
{216,216,158,158,1,1},
{217,217,159,159,1,1},
{218,160,162,161,1,1},
{219,163,165,164,1,1},
{220,220,220,220,0,0},
{221,166,168,167,1,1},
{222,169,171,170,1,1},
{223,172,174,173,1,1},
{224,224,224,224,0,0},
{225,175,177,176,1,1},
{226,226,226,226,0,0},
{227,178,180,179,1,1},
{228,181,183,182,1,1},
{229,184,186,185,1,1},
{230,230,188,188,1,0},
{231,231,231,231,0,0},
{232,232,232,232,0,0},
{233,233,233,233,0,0},
{234,234,234,234,0,0},
{235,235,235,235,0,0},
{236,189,191,190,1,1},
{237,189,191,190,1,1},
{238,238,238,238,0,0},
{239,239,239,239,0,0},
{240,240,240,240,0,0},
{241,241,241,241,0,0},
{242,242,242,242,0,0},
{243,243,243,243,0,0},
{245,245,245,245,0,0},
{246,246,246,246,0,0},
{247,247,247,247,0,0},
{248,248,248,248,0,0},
{251,249,251,250,1,1},
{187,187,244,244,1,0},
{129,28,30,29,1,1},
{144,24,26,25,1,1},
{152,20,22,21,1,1},
{142,142,18,18,1,0},
{141,16,141,16,1,1}
};

typedef unsigned char byte;

#pragma used+

static int prevLet = 193;
static byte stat = 0;
static byte prevX = 0;
static byte prevY = 0;

void trigger()
{
PORTD.7 = 1; 
delay_us(50);
PORTD.7 = 0; 
delay_us(50);
}

void glcd_on()
{

PORTA.6 = 1;         
PORTA.7 = 1;
PORTD.6 = 0;          
PORTD.5 = 0;          
PORTC = 0x3F; 
trigger();     
}           

void glcd_off()
{

PORTA.6 = 1;         
PORTA.7 = 1;
PORTD.6 = 0;          
PORTD.5 = 0;          
PORTC = 0x3E; 
trigger();      
}     

void set_start_line(byte line)
{
PORTD.6 = 0;                     
PORTD.5 = 0;                     

PORTA.6 = 1;         
PORTA.7 = 1;
PORTC = 0xC0 | line;     
trigger();     
}

void goto_col(unsigned int x)
{
byte pattern;
PORTD.6 = 0;              
PORTD.5 = 0;              
if(x<64)             
{
PORTA.6 = 1;          
PORTA.7 = 0;          
pattern = x;      
}
else                 
{
PORTA.7 = 1;          
PORTA.6 = 0;          
pattern = x-64;   
}    
pattern = (pattern | 0x40 ) & 0x7F;  
PORTC = pattern; 
trigger();     
}   

void goto_row(unsigned int y)
{    
byte pattern;   
PORTD.6 = 0;                  
PORTD.5 = 0;                  
pattern = (y | 0xB8 ) & 0xBF; 
PORTC = pattern;   
trigger();             
}

void goto_xy(unsigned int x,unsigned int y)
{    
goto_col(x);
goto_row(y);                                                     
}  

void glcd_write(byte b)
{
PORTD.6 = 1;          
PORTD.5 = 0;          
PORTC = b;    
delay_us(50);   
trigger();
}

void glcd_clrln(byte ln)
{
int i;
goto_xy(0,ln);      
goto_xy(64,ln);     
PORTA.6 = 1;
for(i=0;i<65;i++)
glcd_write(0);
}

void glcd_clear()
{
int i;
for(i=0;i<8;i++)
glcd_clrln(i);
}

byte is_busy()
{
byte status = 0;        

PORTD.7 = 0;                 
delay_us(50);            
PORTD.5 = 1;                 
PORTD.6 = 0;                 
delay_us(50);            
PORTD.7 = 1;                 
delay_us(50 * 5);            

PORTD.7 = 0;                 
delay_us(50 * 5);            

PORTD.7 = 1;                 
delay_us(50);            

status = PINC;    
PORTD.7 = 0;                 
delay_us(50);            
return (status & 0x80);           
}

byte glcd_read(byte column)
{
byte read_data = 0; 
DDRC = 0x00;     

PORTD.5 = 1;             
PORTD.6 = 1;             
PORTA.6 = (column<64);  
PORTA.7 = !PORTA.6;         
delay_us(50);        
PORTD.7 = 1;             
delay_us(50);        

PORTD.7 = 0;             
delay_us(20);       

PORTD.7 = 1;             
delay_us(50);        

read_data = PINC;    
PORTD.7 = 0;             
delay_us(50);        
DDRC = 0xFF;     
return read_data;      
}

void point_at(unsigned int x,unsigned int y,byte color)
{
byte pattern;
goto_xy(x,(int)(y/8));  
switch (color)
{               
case 0:         
pattern = ~(1<<(y%8)) & glcd_read(x);                  
break;    
case 1:         
pattern = (1<<(y%8)) | glcd_read(x);
break;
}           
goto_xy(x,(int)(y/8));                                
glcd_write(pattern);
}

void h_line(unsigned int x,unsigned int y,byte l,byte s,byte c)
{
int i;
for(i=x; i<(l+x); i += (byte)(s+1))
point_at(i,y,c);
}

void v_line(unsigned int x,unsigned int y,signed int l,byte s,byte c)
{
unsigned int i;
for(i=y; i<(y+l); i += (byte)(s+1))
point_at(x,i,c);
}

void line(unsigned int x1,unsigned int y1,
unsigned int x2,unsigned int y2,
byte s,byte c)
{
byte i;
byte y01;

byte temp;

float a;
float b;

byte y00;
byte y010;

if(x1==x2) 
{    
v_line(x1,min(y1,y2),abs(y2-y1)+1,s,c);
}
else if(y1==y2)
{
h_line(min(x1,x2),y1,abs(x2-x1)+1,s,c);
}
else    
{
if(x1>x2)
{
temp = x1;
x1 = x2;
x2 = temp;
temp = y1;
y1 = y2;
y2 = temp;
}

a = (float)(signed)(y2-y1)/(x2-x1);
b = y1 - a*x1;
y00 = a*x1 + b;
y010 = y00;    

for(i=(x1+1); i<=x2; i ++)
{
y01 = a*i + b + 0.5; 

if( (signed char)(y01 - y010) > 1 )
{

v_line((i-1),(byte)(y010+1),(y01-y010-1),s,c);
}
else if( (signed char)(y010 - y01) > 1 )
{

v_line((i-1),(byte)(y01+1),(y010-y01-1),s,c);
} 

if((i==x2) && (y00 == y01)) h_line(x1,y01,(x2-x1),0,c);                                  
y010 = y01;       
if( y00 ==  y01) continue;
h_line(x1,y00,(i-x1),0,c);
x1 = i;
y00 = y01;
}
point_at(x2,y2,c); 
}          
}

void rectangle(unsigned int x1,unsigned int y1,
unsigned int x2,unsigned int y2,
byte s,byte c)
{
h_line(x1,y1,(x2-x1),s,c);
h_line(x1,y2,(x2-x1),s,c);
v_line(x1,y1,(y2-y1),s,c);
v_line(x2,y1,(y2-y1+1),s,c);
}

void cuboid(unsigned int x11,unsigned int y11,
unsigned int x12,unsigned int y12,
unsigned int x21,unsigned int y21,
unsigned int x22,unsigned int y22,
byte s,byte c)
{
rectangle(x11,y11,x12,y12,s,c);
rectangle(x21,y21,x22,y22,s,c);
line(x11,y11,x21,y21,s,c);
line(x12,y11,x22,y21,s,c);
line(x11,y12,x21,y22,s,c);
line(x12,y12,x22,y22,s,c);
}

void h_parallelogram(unsigned int x1,unsigned int y1,
unsigned int x2,unsigned int y2,
byte l,byte s,byte c)
{
h_line(x1,y1,l,s,c);
h_line((x2-l+1),y2,l,s,c);
line(x1,y1,(x2-l+1),y2,s,c);
line((x1+l-1),y1,x2,y2,s,c);
}

void v_parallelogram(unsigned int x1,unsigned int y1,
unsigned int x2,unsigned int y2,
byte l,byte s,byte c)
{
v_line(x1,y1,l,s,c);
v_line(x2,(y2-l+1),l,s,c);
line(x1,y1,x2,(y2-l+1),s,c);
line(x1,(y1+l-1),x2,y2,s,c);
}

void h_parallelepiped(unsigned int x11,unsigned int y11,
unsigned int x12,unsigned int y12,byte l1,
unsigned int x21,unsigned int y21,
unsigned int x22,unsigned int y22,byte l2,
byte s,byte c)
{
h_parallelogram(x11,y11,x12,y12,l1,s,c);
h_parallelogram(x21,y21,x22,y22,l2,s,c);
line(x11,y11,x21,y21,s,c);
line(x12,y12,x22,y22,s,c);
line((x11+l1-1),y11,(x21+l2-1),y21,s,c);
line((x12-l1+1),y12,(x22-l2+1),y22,s,c);
}

void v_parallelepiped(unsigned int x11,unsigned int y11,
unsigned int x12,unsigned int y12,byte l1,
unsigned int x21,unsigned int y21,
unsigned int x22,unsigned int y22,byte l2,
byte s,byte c)
{
v_parallelogram(x11,y11,x12,y12,l1,s,c);
v_parallelogram(x21,y21,x22,y22,l2,s,c);
line(x11,y11,x21,y21,s,c);
line(x12,y12,x22,y22,s,c);
line(x11,(y11+l1-1),x21,(y21+l2-1),s,c);
line(x12,(y12-l1+1),x22,(y22-l2+1),s,c);
}

void circle(unsigned int x0,unsigned int y0,
unsigned int r,byte s,byte c)
{
byte i,y,y00;
y00 = r;            
for(i=0; i<r; i++)
{
y = isqrt((int)r*r - (int)i*i);
point_at((x0+i),(y0+y),c);
point_at((x0+i),(y0-y),c);
point_at((x0-i),(y0+y),c);
point_at((x0-i),(y0-y),c);        
if(abs(y00-y)>1)
{
v_line(x0+(i-1),y0+min(y00,y)+1,abs(y00-y),s,c);
v_line(x0+(i-1),y0-max(y00,y),abs(y00-y),s,c);
v_line(x0-(i-1),y0+min(y00,y)+1,abs(y00-y),s,c);
v_line(x0-(i-1),y0-max(y00,y),abs(y00-y),s,c);
}
y00 = y;   
}
v_line(x0+(i-1) ,y0,y ,s,c);
v_line(x0+(i-1) ,y0-y ,y,s,c);
v_line(x0-(i-1) ,y0,y ,s,c);
v_line(x0-(i-1) ,y0-y ,y,s,c);    
}

void putIt(int c,int x,int y)
{
byte i;
goto_col(x);
goto_row(y);
for(i=0;i<8;i++)
{
glcd_write(font[(8*c)+i]);
}
}

void enlarge(char *large,unsigned char c,byte size)
{
byte i,j,temp;
byte k = 0;
for(i=0;i<size;i++)
{
for(j=0;j<8;j++)
{
large[i] >>= 1;
temp = c & 0x01;
if(temp)
large[i] |= 0x80;
if(++k == size)
{
c >>= 1;
k = 0;
}
}
}
}

void putItSz(int c,int x,int y,byte sz)
{
byte i,j,k;

char large[8][8];

goto_col(x);
goto_row(y);
for(i=0;i<8;i++)
{                                     
enlarge(large[i],font[(8*c)+i],sz);		
}
for(j=0;j<sz;j++)
{
for(i=0;i<8;i++)
{
for(k=0;k<sz;k++)
{
if(x+k+(sz*i) == 64) goto_xy(64,y);		
glcd_write(large[i][j]);
}
}
goto_xy(x,++y);
}
}

void glcd_putchar(byte c,int x,int y,byte l,byte sz)
{
if(l == 1)
{       
switch(c)
{
case 129:
c = 250;
break;
case 144:
c = 251;
break;
case 152:
c = 252;
break;
case 142:
c = 253;
break;
case 141:
c = 254;
break;
}
if((c >= 193) && (prevLet >= 193) && (map[prevLet-193][5]) && (map[c-193][4]))
{
putIt(map[prevLet-193][stat+1],prevX,prevY);
stat = 2;
}else stat = 0;

if(c >= 193) putItSz(map[c-193][stat],x,y,sz);
else putItSz(c,x,y,sz);

prevLet = c;
prevX = x;
prevY = y;

}else putItSz(c,x,y,sz);
}

void glcd_puts(byte *c,int x,int y,unsigned char l,byte sz,signed char space)
{
char i = 0;
char special = 0;
while((i<strlen(c)) && l==0)
{
glcd_putchar(*(c+i),x,y,0,sz);
x += (8+space)*sz;
if(x>128-8*sz)
{
x=0;
y += sz;
}
i++;
}

while((i<strlen(c)) && l==1)
{
if((*(c+i) == 225) && (*(c+i+1) == 199))
special = 249;
else if((*(c+i) == 225) && (*(c+i+1) == 195))
special = 231;
else if((*(c+i) == 225) && (*(c+i+1) == 194))
special = 232;
else if((*(c+i) == 225) && (*(c+i+1) == 197))
special = 233;
if(special)
{
glcd_putchar(special,x-8*sz,y,1,sz);
i+=2;
x -= 8*sz;
special = 0;
}      
else
{
glcd_putchar(*(c+i),x-8*sz,y,l,sz);
if(*(c+i) == 32)						
{
x -= (8+space)*sz;				
}
else
{
x -= 8*sz;
}
i++;
} 
if(x < 8*sz+1)
{
x=128-8*sz;
y += sz;
}
}
prevLet = 193;
}

void bmp_disp(flash byte *bmp,unsigned int x1,unsigned int y1,
unsigned int x2,unsigned int y2)
{
unsigned int i,j;    
for(i=y1;i<=y2;i++)
{
for(j=x1;j<=x2;j++)
{                       
goto_xy(j,i);                              
glcd_write(bmp[(128*i)+j]);
}                                              
}
}

#pragma used-
#pragma used+

flash unsigned char arr[]={ 
0,192,240, 48, 56, 24, 24, 24, 24,152,176,176, 48, 48, 48, 96, 
96, 96, 96, 96, 96,192,192,192,192,192,192,192,128,128,128,128, 
128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,255,255,  0,  0, 12, 24,240,231, 15,253, 15,  7,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,129, 
131,131,131,195,231,103,230,198,  6, 14, 12, 12, 12, 12, 12, 24, 
24, 24,120,112,224,192,  0,  0,  0,  0,  0,224,224,  0,  0,  0, 
0,  0,128,192,224, 96,  0,224,224, 96, 96, 96, 96, 96, 96,224, 
192,  0,  0,  0,128,192, 96, 96,192,128,  0,  0,  0,224,224, 96, 
96, 96, 96, 96, 96,192,128,  0,  0,  0,128,192, 96, 96,192,128, 
0,  0,  0,  0,128,192, 96, 96, 96, 96, 96,192,128,  0,  0,  0, 
0,255,255,  0,  0,  0,  0,255,255,  0,255,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,128,192, 96, 48, 24,140,198, 99, 49, 
24,  8,  8,  9, 11, 11, 11,  9,  8,  8,  8,  8,  8,  8, 28, 62, 
54, 62, 28,  0,255,255,  0,  0,  0,  0,  0,255,255,112,248,140, 
142,  7,  3,  1,  0,  0,  0,255,255,224,224,224, 96, 96, 96,127, 
63,  0,254,255, 97, 96, 96, 96, 96, 97,255,254,  0,255,255,  0, 
0,  0,  0,  0,  0,255,255,  0,254,255, 97, 96, 96, 96, 96, 97, 
255,254,  0,255,255,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0, 
0,255,255,  0,  0,  0,  0,255,255,  0, 63, 48, 48, 48, 48, 48, 
48, 48, 48, 24, 12,198,227, 49, 24, 12,  6,  3,  1,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,255,255,  0,  0,  0,  0,  0, 63, 63,  0,  0,  1, 
3,  7, 14, 28, 56, 48,  0, 63, 63,  0,  0,  1,  3,  7, 14, 60, 
56,  0, 63, 63,  0,  0,  0,  0,  0,  0, 63, 63,  0, 63, 63, 48, 
48, 48, 48, 48, 48, 31, 15,  0, 63, 63,  0,  0,  0,  0,  0,  0, 
63, 63,  0, 15, 31, 48, 48, 48, 48, 48, 48, 56, 24,  0,  0,  0, 
0,255,255,  0,  0,  0,  0,255,255,  0,255,  3,  3,  3,  3,  3, 
3,  3,  3,  6, 12, 25, 51,102,204,152, 48, 96,192,128,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,255,255,  0,  0,  0,  0,255,255,  0,255,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  6, 12, 25, 51,102, 
68, 68, 68,228,244,180,244,228,  4,  4,  4,  4,  4,  4, 14, 31, 
27, 31, 14,  0,255,255,  0,  0,  0,252,  0,  0,  0,  0,  0,248, 
4,  4,  4,248,  0, 12,  4,  4,  4,252,  0,240,136,132,136,240, 
0,128,128,128,  0,252,132,132,  4,  4,  0,248,  4,  4,  4,  8, 
0,252,  0,  0,  0,252,  0,240,136,132,136,240,  0,252,  4,  4, 
4,248,  0,248,  4,  4,  4,248,  0,252, 68,196, 68, 56,  0,  0, 
0,255,255,  0,  0,  6,  3,  1, 28, 62, 55, 62, 28,  0,  0,  0, 
0,  0,  0,128,128,128,128,192,192,192,192,192,224, 96, 96, 96, 
48, 48, 48, 48, 49, 57, 25, 24, 24, 28, 12, 12, 12, 12, 14,  6, 
6,  6,  7,  3,  1,  0,  0,  0,  0, 15,  8,  8,  8,  8,  0,  7, 
8,  8,  8,  7,  0,  6,  8,  8,  8,  7,  0, 15,  0,  0,  0, 15, 
0,  0,  0,  0,  0, 15,  8,  8,  8,  8,  0,  7,  8,  8,  8,  4, 
0,  7,  8,  8,  8,  7,  0, 15,  0,  0,  0, 15,  0, 15,  8,  8, 
8,  7,  0,  7,  8,  8,  8,  7,  0, 15,  0,  0,  1, 14,  0,  0, 
0,  1,  7,  6, 14, 12, 12, 12, 12, 12,  6,  6,  6,  6,  3,  3, 
3,  3,  3,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

flash unsigned char bus[]={  
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,192,224,240,240,248,248,248,248,248,252,252, 
252,252,252,252,252,252,252,252,252,252,252,252,252,252,252,252, 
252,252,248,248,248,248,248,240,224,224,192,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,254,255,255,  3,  1,  3,  3,  3,  3,  3,  3,  3, 
3,  3,  3,  3,  3,  3,  3,255,255,  3,  3,  1,  3,  3,  3,  3, 
3,  3,  3,  3,  3,  3,  3,  3,  3,  7,255,254,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,255,255,255,192,192,192,192,192,192,192,192,192, 
192,192,192,192,192,192,224,255,255,224,192,192,192,224,208,200, 
196,196,196,196,200,208,224,192,224,240,255,255,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,255,255,255,255,255,255,255,255,255,255,255,255, 
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
255,255,255,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0, 63,255,255,225,225,225,225,255,255,255,249,217, 
217,217,217,217,217,217,217,217,217,217,217,217,217,217,217,217, 
201,251,255,255,255,225,225,193,225,247,255, 63,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0, 31, 63, 63, 63, 63, 63, 63,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0, 31, 63, 63, 63, 63, 63, 63, 31,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

flash unsigned char vacio[]={ 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,248,132,194,  2,  2,  2,  2,254,  2,  2,  2, 
194,254,  2,  2,  2,  2,196,248,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0, 30, 31,127,255,253,124, 28, 28, 28, 31, 28, 28, 28, 
31, 31,124,252,252,124, 31, 15,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

flash unsigned char frente[]={
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 56,252,  2, 
2,  2,  2,  2,  6,  6,  6,186,250,186,  2,  2,252, 56,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 62, 
254,242,242, 62, 62, 62, 63, 63,243,243,255, 62, 63,  0,  0,  0 
};

flash unsigned char chofer[]={
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,248,132,194,130,218,250,226,254,  2,  2,  2, 
194,254,  2,  2,  2,  2,196,248,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0, 30, 31,127,255,253,124, 31, 31, 31, 31, 28, 28, 28, 
31, 31,124,252,252,124, 31, 15,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

flash unsigned char GPS1[]={  
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
224, 16,144,144,128,  0,240,144,144,144, 96,  0, 96,144,144, 16, 
0,  0,  0,  0, 32,112,248,112, 32,  0,128,120,  0,252,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
3,  4,  4,  4,  3,  0,  7,  0,  0,  0,  0,  0,  4,  4,  4,  3, 
0,  0,  0, 16, 20, 20, 20, 20, 18,  9,  4, 10, 53, 24,  8,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

flash unsigned char GPS2[]={  
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
224, 16,144,144,128,  0,240,144,144,144, 96,  0, 96,144,144, 16, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,120,  0,252,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
3,  4,  4,  4,  3,  0,  7,  0,  0,  0,  0,  0,  4,  4,  4,  3, 
0,  0,  0, 16, 20, 20, 20, 20, 18,  9,  4, 10, 53, 24,  8,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
};

flash unsigned char GSM1[]={  
0,  0,  0,  0,  0,  0,  0,128,128,  0,224,224,  0,248,248,  0, 
254,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  6,  6,  0,  7,  7,  0,  7,  7,  0,  7,  7,  0,  7,  7,  0, 
7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0  
};

flash unsigned char GSM2[]={  
0,  0,  0,  0,  0,  0,  0,128,128,  0,224,224,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  6,  6,  0,  7,  7,  0,  7,  7,  0,  7,  7,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

flash unsigned char GSM3[]={     
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  6,  6,  0,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

flash unsigned char GSM4[]={ 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  6,  6,  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 
4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

#pragma used-

char rx_b0 [200             ];           

unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;

bit rx_buffer_overflow0;
bit BIT_UART;

interrupt [21] void usart0_rx_isr(void)
{  
char status,data;
status = (*(unsigned char *) 0xc0);
data   = (*(unsigned char *) 0xc6);
BIT_UART = (*(unsigned char *) 0xc0) & 0b10000000;

if ((status & ((1<<4) | (1<<2) | (1<<3))) == 0)
{
rx_b0 [rx_wr_index0++] = data;

if (rx_wr_index0 == 200             ) rx_wr_index0=0;
if (++rx_counter0 == 200             )
{
rx_counter0=0;
rx_buffer_overflow0=1;
}
}
}

char NOMBRE_DISP[] = "SITU";
char NUM_DISP[] = "BUS1697";

unsigned int btn1=0, btn2=0, btn3=0, btn4=0, btn5=0;  
char aux;

static unsigned int time_count, act = 1;
eeprom int seg=0,seg1=0,minu=0,min1=0,hora=0,hora1=0,dia=0,dia1=0,mes=0,mes1=0,an=0,an1=0; 
int gsm, gps, ind_sen; 
char reloj[8], fecha[8];  

interrupt [19] void timer0_ovf_isr(void)
{
TCNT0 = 6; 
++time_count; 

if ( time_count == 43 )
{
seg++; 
time_count = 0;  

if(seg==4) printf("AT$TTDEVID?\n\r");  
if(seg==9) printf("AT+CSQ\n\r");      

if (seg>9)
{
seg=0; seg1++;

if (seg1%2==0)  
{
printf("AT$TTNETIP?\n\r");
printf("IMPRIME!!!\n\r"); 
}else{
printf("AT$TTGPSQRY=10,0\n\r");   
}  

if(seg1>5)  
{
seg1=0; minu++;
if(minu>9)
{
minu=0; min1++;
if(min1>5)
{
min1=0; hora++;
if(hora>9)
{
hora=0; hora1++;
if((hora1==2 && hora==3)&&(min1==5 && minu==9)&&(seg1==5 && seg==9))
{
hora1=0; hora=0; min1=0; minu=0;seg1=0;seg=0;    
}
}
}
}
}
}
}
}

void buzz()
{       
PORTD.4=1; delay_ms( 100 );
PORTD.4=0; delay_ms( 100 );
}

void boton1()
{  
if( PINA.4 == 0 )
{
btn1++;
buzz();
aux = 1;

delay_ms( 200 );

if(btn1 > 1)  
btn1 = 0;
} 

switch (btn1) {
case 0:
if(aux==1)
{
bmp_disp( vacio, 0, 5, 25, 7);
btn2=0; 
aux=0; 

glcd_putchar(' ',76,7,0,1); 

glcd_puts("     ",44,7,0,1,-1); 
}      
break; 

case 1:
if(aux==1)
{
aux=0; 

bmp_disp(chofer,0,5,35,7); 

glcd_puts("RUTA:",44,7,0,1,-1);
} 
break;

case 2:
break;
};  
}

void boton2()
{     
if(PINA.3==0 && btn1==1)
{
btn2++; 
buzz(); 
delay_ms( 200 );

if(btn2>12) 
btn2=0;
}  
switch (btn2){
case 1:
glcd_putchar('A',77,7,0,1);
break;
case 2:
glcd_putchar('B',77,7,0,1);
break;
case 3:
glcd_putchar('C',77,7,0,1);
break; 
case 4:
glcd_putchar('D',77,7,0,1);
break; 
case 5:
glcd_putchar('E',77,7,0,1);
break; 
case 6:
glcd_putchar('F',77,7,0,1);
break; 
case 7:
glcd_putchar('G',77,7,0,1);
break; 
case 8:
glcd_putchar('H',77,7,0,1);
break;
case 9:
glcd_putchar('I',77,7,0,1);
break; 
case 10:
glcd_putchar('J',79,7,0,1);
break; 
case 11:
glcd_putchar('K',79,7,0,1);
break;
case 12:
glcd_putchar('L',79,7,0,1);
break;   
}; 

}

void boton3(){     
btn3++;
}

void boton4(){     
btn4++;
}

void boton5(){     
btn5++;
}

void dibujar_senal(void)
{
switch (ind_sen){
case 1:
bmp_disp(GSM3,0,0,20,1);
break;
case 2:
bmp_disp(GSM2,0,0,20,1);
break;
case 3:
bmp_disp(GSM1,0,0,20,1);
break;
case 4:
bmp_disp(GSM4,0,0,20,1);
break;
}; 

}

void obt(void)
{

int i,j,n=0,n1,n2,n3,n4,ini,coma=0,pos1=0,pos2=0,pos3=0,barras;

for (i=0; i<200              ;i++) 
{     

if ( rx_b0[i+0]== '+' &&    
rx_b0[i+1]== 'C' &&     
rx_b0[i+2]== 'S' &&    
rx_b0[i+3]== 'Q' &&   
rx_b0[i+4]== ':')    
{ 

barras = ((rx_b0[i+6]-48)*10)+(rx_b0[i+7]-48);

if( barras > 10 && barras < 15 ){
ind_sen=1;
}

else if( barras >= 15 && barras < 18){
ind_sen=2;
} 

else if( barras >= 18 && barras < 31){
ind_sen=3;
}

else if( barras > 31 && barras < 50){
ind_sen=4;
}

else{   }

}

if ( rx_b0[i+0]== 'N' && 
rx_b0[i+1]== 'E' && 
rx_b0[i+2]== 'T' && 
rx_b0[i+3]== 'I' && 
rx_b0[i+4]== 'P')
{ 
ini = i + 4; 

for (n=0; n<201; n++) 
{

if(rx_b0[ ini + n + 1 ] == ':' ) 
{
coma++; 
if(coma == 1) pos1 = n + ini + 1; 
}
}

if( rx_b0[ pos1 + 2] == 34 )
{      
if( (rx_b0[pos1+3] - 48) == 0 && 
(rx_b0[pos1+4] - 48) == 0 && 
(rx_b0[pos1+5] - 48) == 0 && 
(rx_b0[pos1+7] - 48) == 0 && 
(rx_b0[pos1+8] - 48) == 0 && 
(rx_b0[pos1+9] - 48) == 0)
{ 
gsm=0;   

}else
gsm=1;
}   
}

if ( rx_b0[i+0] == 'D' && 
rx_b0[i+1] == 'E' && 
rx_b0[i+2] == 'V' && 
rx_b0[i+3] == 'I' && 
rx_b0[i+4] == 'D')
{ 
ini = i+4; 

glcd_clrln(2); 
glcd_clrln(3); 
glcd_clrln(4); 
glcd_clrln(5);

for (n=0;n<201;n++)
{
if( rx_b0[ini+n+1] == ':') 
{
coma++; 
if(coma==1) pos1 = n+ini+1;
}
}

if(rx_b0[pos1+1]==34)
{ 
if( rx_b0[pos1+2] == NUM_DISP[0] && 
rx_b0[pos1+3] == NUM_DISP[1] && 
rx_b0[pos1+4] == NUM_DISP[2] && 
rx_b0[pos1+5] == NUM_DISP[3] )
{

act=1;  
}else{

glcd_clrln(2); 
glcd_clrln(3); 
glcd_clrln(4); 
glcd_clrln(5);

act=1;  
}

}
}

if ( rx_b0[i+0] == 'G' && 
rx_b0[i+1] == 'P' && 
rx_b0[i+2] == 'R' && 
rx_b0[i+3] == 'M' && 
rx_b0[i+4] == 'C')
{ 

ini=i+4;
for (n=0;n<201;n++) 
{
if(rx_b0[ini+n+1]==44) 
{
coma++;
if(coma==1) pos1=n+ini+1;
if(coma==2) pos2=n+ini+1;
if(coma==9) pos3=n+ini+1;
}
}

glcd_clrln(3);    
glcd_clrln(4);   
glcd_clrln(5);

if( (rx_b0[ pos1+1 ]-48)>= 0 && 
(rx_b0[ pos1+1 ]-48)< 10 &&
pos2 != (pos1 +1)
)
{

seg  =rx_b0[pos1 + 6 ]-48;
seg1 =rx_b0[pos1 + 5 ]-48;
minu =rx_b0[pos1 + 4 ]-48;
min1 =rx_b0[pos1 + 3 ]-48;
n2   =rx_b0[pos1 + 2 ]-48;
n1   =rx_b0[pos1 + 1 ]-48;

n3 = ( n1*10 ) + n2;   
n4 = n3 - 5;  

if( n4 < 0 )
{
n4    = n4 + 24;
hora  = n4 % 10;
hora1 = n4 / 10;
}  

hora = n4 % 10;
hora1= n4 / 10;

}

gps = rx_b0 [ pos2 + 1 ]; 
printf( "%c", gps);

if( (rx_b0[pos3+1]-48) >= 0 && 
(rx_b0[pos3+1]-48) < 10 )
{

dia1 = rx_b0[pos3+1]-48;
dia  = rx_b0[pos3+2]-48;
mes1 = rx_b0[pos3+3]-48;
mes  = rx_b0[pos3+4]-48;
an1  = rx_b0[pos3+5]-48;
an   = rx_b0[pos3+6]-48;  

if( n4 > 18)
dia = dia-1;  

}else{

an1  = an1;
an   = an;
mes1 = mes1;
mes  = mes;
dia1 = dia1;
dia  = dia; 
}
}
}

rx_counter0  = 0;
rx_wr_index0 = 0; 

BIT_UART=1;     

for (j=0;j<201;j++) 
{
rx_b0[j]=0;
};

}

void main(void)
{
#pragma optsize-
(*(unsigned char *) 0x61)=0x80;
(*(unsigned char *) 0x61)=0x00;
#pragma optsize+

DDRC = 0xff;

PORTA=0xFF;
DDRA=0xF0;

PORTB=0x00;
DDRB=0xFF;

PORTD=0x00;
DDRD=0b11110000;

(*(unsigned char *) 0xc0)=0x00;
(*(unsigned char *) 0xc1)=0x98;
(*(unsigned char *) 0xc2)=0x06;
(*(unsigned char *) 0xc5)=0x00;
(*(unsigned char *) 0xc4)=0x05;

TCCR0A=0x00;
TCCR0B=0x05;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

(*(unsigned char *) 0x6e)=0x01;

glcd_on();
delay_ms(10);
glcd_clear();

buzz();
buzz();

bmp_disp(arr,0,0,127,7);
delay_ms( 2000 );
glcd_clear();

bmp_disp(bus,0,0,45,7);

glcd_puts(NOMBRE_DISP,55,2,0,2,-1);    

glcd_puts(NUM_DISP,59,5,0,1,-1);

delay_ms( 2000 ); 
glcd_clear();             

#asm("sei")

bmp_disp(vacio,0,5,25,7);

printf("IMPRIME!!!\n\r"); 
printf("AT$TTDEVID?\n\r"); 
delay_us( 500 );
obt();

while (1)
{

if( BIT_UART == 0 ) 
{   
obt();
BIT_UART=1;  
}

boton1();

boton2();                                          

dibujar_senal();

printf("IMPRIME HORA!!!\n\r"); 

if(act ==1)
{
if( gsm == 1)
{
glcd_putchar('E',19,0,1,1);
}else{
glcd_putchar(' ',19,0,1,1);
} 

printf("hora sin sky %d\n", hora );
if( hora == -1 )
{
hora1 = 0; min1 = 0; seg1 = 0;
hora = 0;  min = 0;  seg = 0;
}

sprintf(reloj,"%d%d:%d%d:%d%d",hora1, hora, min1, minu, seg1, seg);
glcd_puts(reloj,7,2,0,2,-1);     

if( gps == 'A' )
{     
bmp_disp(GPS1,95,0,127,1);   
sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
glcd_puts(fecha,34,5,0,1,-1); 

}

else if (gps == 'V' || gps == '9' )
{
bmp_disp(GPS2,95,0,127,1);
sprintf(fecha,"20%d%d-%d%d-%d%d",an1, an, mes1, mes, dia1, dia);
glcd_puts(fecha,34,5,0,1,-1);
}
else
{ 
bmp_disp(GPS2,95,0,127,1);
glcd_puts(reloj,7,2,0,2,-1);  
glcd_puts(fecha,34,5,0,1,-1);
}
}

else 
{   
glcd_puts("Pantalla",30,2,0,1,-1);
glcd_puts("No Autorizada",15,4,0,1,-1);
}  

bmp_disp(frente,105,5,127,7);  
} 
}
