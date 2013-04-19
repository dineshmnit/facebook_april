
#include <p18cxxx.h>
#include "rtc.h"

unsigned char Da,ta;

void d4()
{char j;
for(j=0;j<=2;j++);
}

void I2CInit()
{
        SDA = 1;
		d4();
        SCL = 1;
		d4();
}

void I2CStart()
{
        SCL = 1;
	d4();
        SDA = 0;
	d4();
        SCL = 0;
	d4();
}

void I2CRestart(){
        SCL = 0;
		d4();
        SDA = 1;
		d4();
        SCL = 1;
		d4();
        SDA = 0;
		d4();
}

void I2CStop(){

        SCL = 0;
		d4();
        SDA = 0;
		d4();
        SCL = 1;
		d4();
        SDA = 1;
		d4();
}


void I2CAck()
{
TRISD = 0x7f;
        SDA = 0;
		d4();
        SCL = 1;
		d4();
        SCL = 0;
		d4();
        SDA = 1;
		d4();
TRISD = 0x3f;
}  

void I2CNak(){
        SDA = 1;
		d4();
        SCL = 1;
		d4();
        SCL = 0;
		d4();
}

void I2CSend(unsigned char Data)
{
         unsigned char i;
         for(i=0;i<8;i++)
{
                SCL = 0;
				d4();
                if((Data&0x80)==0)
                        SDA = 0;
						
                else
                        SDA = 1;
				 d4();
                SCL = 1;
				d4();
                Data<<=1;
         }
         SCL = 0;
		 d4();
         SDA = 1;
		 d4();
}

unsigned char I2CRead()
{
        unsigned char i;
		Da=0;
		ta=0;
	TRISD = 0x7f;	//making SDA as input

        for(i=0;i<4;i++)
		{
                SCL = 0;
				d4();
                SCL = 1;
				d4();
                if( PORTDbits.RD6==1)	//SDA
                   Da= Da+1;
				
				if(i<3)
				Da<<=1;
        }
		 //Da=Da+48;	// to change the value to ascii

		 for(i=4;i<8;i++)
		{
                SCL = 0;
				d4();
                SCL = 1;
				d4();
                if( PORTDbits.RD6==1)	// SDA
                   ta= ta+1;
		
				if(i<7)
				ta<<=1;
        }
	//	ta=ta+48;	// to change the value to ascii
        SCL = 0;
		d4();
	TRISD = 0x3f;	// making SDA as o/p
        SDA = 1;
		d4();   
Da=Da*10+ta;
return Da; 
}


void i2cinit()
{
    I2CInit();	// releasing the SDA and SCL lines	
		I2CStart();
                I2CSend(0xD0);	// slave address
                I2CAck();
                I2CSend(0x00);	// address
				I2CAck();
				I2CSend(0x00);	// data (turning on the IC and setting sec.s to zero
I2CAck();			
I2CStop();	

if(read_mem(0x06)==0)	// if ran for the first time (reading yr)
{
write_mem(0x01,0);	// writing min
write_mem(0x02,0);	// writing hr
write_mem(0x04,1);	// writing day
write_mem(0x05,4);	// write current month to month mem location in rtc
write_mem(0x06,12);	// write current yr to yr mem location in rtc

write_mem(0x08,0);	// mem location in rtc to save mins
write_mem(0x09,0);	// mem location in rtc to save hrs
write_mem(0x0a,0);	// mem location in rtc to save days
}

}	// function i2cinit() ends


unsigned char read_mem(unsigned char d)
{
unsigned char t;

I2CStart();
I2CSend(0xD0);  // device address in write mode
	I2CAck();
  I2CSend(d);  // memory add to be read
I2CAck();

I2CRestart();
 
I2CSend(0xD1); // device address in read mode
	I2CAck(); 
t=I2CRead();
  I2CNak();
 I2CStop();
return t;
}

void write_mem(unsigned char addr,unsigned char data)
{
unsigned char t;

I2CStart();
I2CSend(0xD0);  // device address in write mode
	I2CAck();
  I2CSend(addr);  // memory add to be read
I2CAck();
  I2CSend(data);  // memory add to be read
I2CAck();
 I2CStop();
}

void i2ctime(int *pe,int *te)
{
int minn,hrr,dayy,pee[3],tee[3],i,min,hr,day;

minn=read_mem(0x01);	//reading mins
hrr=read_mem(0x02);		//reading hrs
dayy=read_mem(0x04);	//reading days

for(i=0;i<3;i++)
{
pee[i]=*pe;
tee[i]=*te;
*pe++;
*te++;
}

min=minn-pee[0];
if(min<0)
min=-1*min;

hr=hrr-pee[1];
if(hr<0)
hr=-1*hr;

day=dayy-pee[2];
if(day<0)
day=-1*day;

tee[0]=tee[0]+min;
tee[1]=tee[1]+hr;
tee[2]=tee[2]+day;

write_mem(0x08,tee[0]);	//saving in RTC RAM at mem. location 0x08.
write_mem(0x09,tee[1]);	//saving in RTC RAM at mem. location 0x09.
write_mem(0x0a,tee[2]);	//saving in RTC RAM at mem. location 0x0a.

}