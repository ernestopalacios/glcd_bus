/***************************************************************************
 * Osama's Lab KS0108 GLCD library; a library that facilitates interfacing KS0108 based GLCDs.
 *
 *   Copyright (C) 2010-2012  Osama's Lab
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as
 *   published by the Free Software Foundation, either version 3 of the
 *   License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/> 
 **************************************************************************/

#include <delay.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "font.h"

typedef unsigned char byte;
//DEBUG
//#define DEBUG_READ 0
//#define DEBUG_GLCD 0
//----------------------
#define E_DELAY 50
#define GLCD_DELAY_US 50
#define DATAPORT PORTC
#define DATADDR DDRC
#define DATAPIN PINC
//#define CONTROLPORT PORTB
#define CS1 PORTA.6
#define CS2 PORTA.7
#define RS  PORTD.6
#define RW  PORTD.5
#define EN  PORTD.7
//#define CS_ACTIVE_LOW   0   //Define this if your GLCD CS 
                              //is active low (refer to datasheet)
#pragma used+
                                                          
//--------Arabic----------
static int prevLet = 193;
static byte stat = 0;
static byte prevX = 0;
static byte prevY = 0;
//------------------------
void trigger()
{
   EN = 1; //EN high
   delay_us(E_DELAY);
   EN = 0; //EN low
   delay_us(E_DELAY);
}
//----------------------
void glcd_on()
{
    //Activate both chips
    #ifdef CS_ACTIVE_LOW
        CS1 = 0;
        CS2 = 0;
    #else    
        CS1 = 1;         
        CS2 = 1;
    #endif
    RS = 0;          //RS low --> command
    RW = 0;          //RW low --> write
    DATAPORT = 0x3F; //ON command  
    trigger();     
}           
//----------------------
void glcd_off()
{
    //Activate both chips
    #ifdef CS_ACTIVE_LOW
        CS1 = 0;
        CS2 = 0;
    #else
        CS1 = 1;         
        CS2 = 1;
    #endif
    RS = 0;          //RS low --> command
    RW = 0;          //RW low --> write   
    DATAPORT = 0x3E; //OFF command   
    trigger();      
}     
//----------------------
void set_start_line(byte line)
{
    RS = 0;                     //RS low --> command
    RW = 0;                     //RW low --> write
    //Activate both chips
    #ifdef CS_ACTIVE_LOW
        CS1 = 0;
        CS2 = 0;
    #else    
        CS1 = 1;         
        CS2 = 1;
    #endif    
    DATAPORT = 0xC0 | line;     //Set Start Line command  
    trigger();     
}
//----------------------
void goto_col(unsigned int x)
{
   byte pattern;
   RS = 0;              //RS low --> command
   RW = 0;              //RW low --> write   
   if(x<64)             //left section
   {
      #ifdef CS_ACTIVE_LOW
        CS1 = 0;          //select chip 1
        CS2 = 1;          //deselect chip 2
      #else          
        CS1 = 1;          //select chip 1
        CS2 = 0;          //deselect chip 2
      #endif
      pattern = x;      //put column address on data port    
   }
   else                 //right section
   {
      #ifdef CS_ACTIVE_LOW
        CS2 = 0;
        CS1 = 1;
      #else
        CS2 = 1;          //select chip 2
        CS1 = 0;          //deselct chip 1
      #endif
      pattern = x-64;   //put column address on data port
   }    
   pattern = (pattern | 0x40 ) & 0x7F;  //Command format
   DATAPORT = pattern; 
   trigger();     
}   
//----------------------
void goto_row(unsigned int y)
{    
   byte pattern;   
   RS = 0;                  //RS low --> command
   RW = 0;                  //RW low --> write         
   pattern = (y | 0xB8 ) & 0xBF; //put row address on data port set command     
   DATAPORT = pattern;   
   trigger();             
}
//----------------------
void goto_xy(unsigned int x,unsigned int y)
{    
    goto_col(x);
    goto_row(y);                                                     
}  
//----------------------
void glcd_write(byte b)
{
   RS = 1;          //RS high --> data
   RW = 0;          //RW low --> write     
   DATAPORT = b;    //put data on data port  
   delay_us(GLCD_DELAY_US);   
   trigger();
}
//------------------------
void glcd_clrln(byte ln)
{
    int i;
    goto_xy(0,ln);      //At start of line of left side
    goto_xy(64,ln);     //At start of line of right side (Problem)
    #ifdef CS_ACTIVE_LOW
        CS1 = 0;
    #else
        CS1 = 1;
    #endif    
    for(i=0;i<65;i++)
        glcd_write(0);
}
//-------------------------
void glcd_clear()
{
   int i;
   for(i=0;i<8;i++)
      glcd_clrln(i);
}
//-----------------------
byte is_busy()
{
    byte status = 0;        //Read data here
    
    EN = 0;                 //Low Enable
    delay_us(GLCD_DELAY_US);            //tf
    RW = 1;                 //Read
    RS = 0;                 //Status         
    delay_us(GLCD_DELAY_US);            //tasu
    EN = 1;                 //High Enable
    delay_us(GLCD_DELAY_US * 5);            //tr + max(td,twh)->twh
    
    //Dummy read
    EN = 0;                 //Low Enable
    delay_us(GLCD_DELAY_US * 5);            //tf + twl + chineese error    
    
    EN = 1;                 //High Enable
    delay_us(GLCD_DELAY_US);            //tr + td        
                                  
    status = DATAPIN;    //Input data
    EN = 0;                 //Low Enable
    delay_us(GLCD_DELAY_US);            //tdhr
    #ifdef DEBUG_READ
        printf("S:%x\n\r",status);
    #endif
    return (status & 0x80);           
}
//-----------------------   
byte glcd_read(byte column)
{
    byte read_data = 0; //Read data here
    DATADDR = 0x00;     //Input 
    
    //while(is_busy());
    RW = 1;             //Read
    RS = 1;             //Data
    #ifdef CS_ACTIVE_LOW
        CS1 = (column>63);
    #else         
        CS1 = (column<64);  //Enable/Disable CS1
    #endif
    CS2 = !CS1;         //Disable/Enable CS2
    delay_us(GLCD_DELAY_US);        //tasu
    EN = 1;             //Latch RAM data into ouput register
    delay_us(GLCD_DELAY_US);        //twl + tf
    
    //Dummy read
    //while(is_busy());
    EN = 0;             //Low Enable
    delay_us(20);       //tf + twl + chineese error    
    
    EN = 1;             //latch data from output register to data bus
    delay_us(GLCD_DELAY_US);        //tr + td(twh)       
                                  
    read_data = DATAPIN;    //Input data    
    EN = 0;             //Low Enable to remove data from the bus 
    delay_us(GLCD_DELAY_US);        //tdhr
    #ifdef DEBUG_READ
        printf("R:%x\n\r",read_data);
    #endif
    DATADDR = 0xFF;     //Output again
    return read_data;      
}
//-----------------------
/*byte get_point(unsigned int x,unsigned int y)
{
    byte data;
    goto_xy(x,((int)(y/8)));
    data = glcd_read();        
    return data;
}  */
//----------------------
void point_at(unsigned int x,unsigned int y,byte color)
{
    byte pattern;
    goto_xy(x,(int)(y/8));  
    switch (color)
    {               
        case 0:         //Light spot                        
            pattern = ~(1<<(y%8)) & glcd_read(x);                  
        break;    
        case 1:         //Dark spot            
            pattern = (1<<(y%8)) | glcd_read(x);
            #ifdef DEBUG_GLCD
                delay_ms(30);/////////////////////////////////////////
            #endif
        break;
    }           
    goto_xy(x,(int)(y/8));                                
    glcd_write(pattern);
}
//-----------------------
void h_line(unsigned int x,unsigned int y,byte l,byte s,byte c)
{
    int i;
    for(i=x; i<(l+x); i += (byte)(s+1))
        point_at(i,y,c);
}
//-----------------------
void v_line(unsigned int x,unsigned int y,signed int l,byte s,byte c)
{
    unsigned int i;
    for(i=y; i<(y+l); i += (byte)(s+1))
        point_at(x,i,c);
}
//-----------------------
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
            y01 = a*i + b + 0.5; //+ 0.5 to approximate to the nearest integer
                
            if( (signed char)(y01 - y010) > 1 )
            {
                //-------Subject to error
                v_line((i-1),(byte)(y010+1),(y01-y010-1),s,c);
            }
            else if( (signed char)(y010 - y01) > 1 )
            {
                //-------Subject to error
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
//-----------------------
void rectangle(unsigned int x1,unsigned int y1,
               unsigned int x2,unsigned int y2,
               byte s,byte c)
{
    h_line(x1,y1,(x2-x1),s,c);
    h_line(x1,y2,(x2-x1),s,c);
    v_line(x1,y1,(y2-y1),s,c);
    v_line(x2,y1,(y2-y1+1),s,c);
}
//-----------------------
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
//-----------------------
void h_parallelogram(unsigned int x1,unsigned int y1,
                     unsigned int x2,unsigned int y2,
                     byte l,byte s,byte c)
{
    h_line(x1,y1,l,s,c);
    h_line((x2-l+1),y2,l,s,c);
    line(x1,y1,(x2-l+1),y2,s,c);
    line((x1+l-1),y1,x2,y2,s,c);
}
//-----------------------
void v_parallelogram(unsigned int x1,unsigned int y1,
                     unsigned int x2,unsigned int y2,
                     byte l,byte s,byte c)
{
    v_line(x1,y1,l,s,c);
    v_line(x2,(y2-l+1),l,s,c);
    line(x1,y1,x2,(y2-l+1),s,c);
    line(x1,(y1+l-1),x2,y2,s,c);
}
//-----------------------
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
//-----------------------
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
//-----------------------
void circle(unsigned int x0,unsigned int y0,
            unsigned int r,byte s,byte c)
{
    byte i,y,y00;
    y00 = r;            //Point (0,r) is the 1st point
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
//-----------------------
//void ellipse(unsigned int x0,unsigned int y0,
//             unsigned int a,unsigned int b,
//             byte s,byte c)
//{
//    byte i,y,y00;
//    y00 = 1;
//    for(i=0; i < a; i++)
//    {
//        y = isqrt((int)a*a - (int)i*i);
//        point_at((x0+i)*(a+x0)/a,(y0+y)*(b+y0)/b,c);
//        point_at((x0+i)*(a+x0)/a,(y0-y)*(b+y0)/b,c);
//        point_at((x0-i)*(a+x0)/a,(y0+y)*(b+y0)/b,c);
//        point_at((x0-i)*(a+x0)/a,(y0-y)*(b+y0)/b,c);        
//        /*if(abs(y00-y)>1)
//        {
//            v_line(x0+(i-1),y0+min(y00,y)+1,abs(y00-y),s,c);
//            v_line(x0+(i-1),y0-max(y00,y),abs(y00-y),s,c);
//            v_line(x0-(i-1),y0+min(y00,y)+1,abs(y00-y),s,c);
//            v_line(x0-(i-1),y0-max(y00,y),abs(y00-y),s,c);
//            
//            printf("y=%u y00=%u\n\r",y,y00);
//        }*/
//        y00 = y;   
//    }
//    /*v_line(x0+(i-1) ,y0,y ,s,c);
//    v_line(x0+(i-1) ,y0-y ,y,s,c);
//    v_line(x0-(i-1) ,y0,y ,s,c);
//    v_line(x0-(i-1) ,y0-y ,y,s,c);*/    
//}  
//------------Arabic/English Writing-------
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
//--------------------------
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
//--------------------------
void putItSz(int c,int x,int y,byte sz)
{
  byte i,j,k;
  //char large[8][sz];  
  char large[8][8];
  
  goto_col(x);
  goto_row(y);
  for(i=0;i<8;i++)
  {                                     
	  enlarge(large[i],font[(8*c)+i],sz);		//c here;GCC (c-1)
  }
  for(j=0;j<sz;j++)
  {
	  for(i=0;i<8;i++)
	  {
		  for(k=0;k<sz;k++)
		  {
			  if(x+k+(sz*i) == 64) goto_xy(64,y);		//Problem 1: Forgot to change 3 to sz
			  glcd_write(large[i][j]);
		  }
	  }
	  goto_xy(x,++y);
  }
}
//--------------------------
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
//---------------------------
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
		  if(*(c+i) == 32)						//If space (i.e. new word)
		  {
			  x -= (8+space)*sz;				//Space between words
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
//------------BMP Display--------------------
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
