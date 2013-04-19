
////////// d contains data to be displayed //////////////////////

#include <p18cxxx.h>

#include "sseg.h"
#include "led.h"


void max7219(char addr, char data);


void delay(long j)
{
long i;
for(i=0;i<=j*2;i++)
{ //asm("NOP");
}
}


char sslib(char s)
{
char t=0;

if(s=='H')
t=0x37;
else if(s=='I')
t=0x30;
else if(s=='C')
t=0x4e;
else if(s=='N')
t=0x15;
else if(s=='D')
t=0x3d;
else if(s=='S')
t=0x5b;
else if(s=='L')
t=0x0e;
else if(s=='P')
t=0x67;
else if(s=='U')
t=0x1c;
else if(s=='A')
t=0x77;
else if(s=='F')
t=0x47;
else if(s=='Y')
t=0x3b;
else if(s=='E')
t=0x4f;
else if(s=='-')
t=0x01;
else if(s=='R')
t=0x05;
else if(s=='T')
t=0x0f;
else if(s=='O')
t=0x7e;
else if(s=='V')
t=0x3e;
else if(s=='0')
t=0x7e;
else if(s=='1')
t=0x30;
else if(s=='2')
t=0x6d;
else if(s=='3')
t=0x79;
else if(s=='4')
t=0x33;
else if(s=='5')
t=0x5b;
else if(s=='6')
t=0x5f;
else if(s=='7')
t=0x70;
else if(s=='8')
t=0x7f;
else if(s=='9')
t=0x7b;

return t;
}


void ss(char *x)
{
char i,j=5,t,g,z[5];


for(g=0;g<5;g++)	// assigning values in z array by pointer
{z[g]=*x;
*x++;
}

for(g=0;z[g]!='\0';g++);	// finding null point

max7219(0x9,0x00); // decode mode( for all digits)
//max7219(0xb,0x04);	// scan limit (max 7)

for(i=0;i<5;i++)
{
if(i<g)
t=sslib(z[i]);
else
t=0;

max7219(j,t);

j--;
}	// for loop ends

//max7219(0x01,0x00); 	//	first digit 
}	// function ends





void max7219(char addr, char data)
{
char i;
int te;

PORTCbits.RC3=1;	// load- Max7219
delay(10);
PORTCbits.RC6=0;	//Clk
delay(10);
PORTCbits.RC5=0;	//Din
delay(10);

for(i=15;i>=0;i--)
{
if(i>=12)
{
PORTCbits.RC6=1;	//Clk
delay(10);
PORTCbits.RC6=0;	//Clk
delay(10);
}	// if i<=3 condition ends

else if(i>=8 && i<=11)
{
te=addr & powi(i-8);

if(te>0)
PORTCbits.RC5=1;
else
PORTCbits.RC5=0;

delay(10);
PORTCbits.RC6=1;	//Clk
delay(10);
PORTCbits.RC6=0;	//Clk
delay(10);
}	// else if(i>=8 && i<=11) condition ends

else if(i<=7)
{
te=data & powi(i);
delay(10);

if(te>0)
PORTCbits.RC5=1;
else
PORTCbits.RC5=0;

delay(10);
PORTCbits.RC6=1;	//Clk
delay(10);
PORTCbits.RC6=0;	//Clk
}	// else if(i<=7) condition ends
}	// for loop ends
PORTCbits.RC3=0;	//load
delay(10);

PORTCbits.RC3=1;	//load
delay(10);
PORTCbits.RC6=1;	//Clk
delay(10);
}


int powi(char j)
{
char i;
int b=1;
for(i=1;i<=j;i++)
b=2*b;
return b;
}
