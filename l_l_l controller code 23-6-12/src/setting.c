
#include <p18cxxx.h>
#include <string.h>
#include "setting.h"
#include "sseg.h"
#include <stdio.h>


void sett(unsigned char *cal,unsigned int *fsup,unsigned int *fsdn,unsigned int *slup,unsigned int *sldn,unsigned char *freq,unsigned char *disp,unsigned char *rtc,unsigned char *rev,char *logo)	// a pointer represents the setting paratemeters to be accepted
{
unsigned int d[10];
char di=1;
char z[6];	// used for display
char u=0;

d[0]=*cal;	// calibration, LCE
d[1]=*fsup;
d[2]=*fsdn;
d[3]=*slup;
d[4]=*sldn;
d[5]=*freq;
d[6]=*disp;
d[7]=*rtc;
d[8]=*rev;
d[9]=*logo;

while(1)
{
u++;
if(u>100)
u=0;

if(u%2==0)
{
max7219(0x6,0xc0);	// red up
max7219(0x7,0xc0);	// red up
}
else
{
max7219(0x6,0x00);	// scan limit (max 7)
max7219(0x7,0x00);	// scan limit (max 7)
}

max7219(0xb,0x07);	// scan limit (max 7)

if(di==1)
sprintf(z,"LCE  ");
else if(di==2)
sprintf(z,"FASUP");
else if(di==3)
sprintf(z,"FASDN");
else if(di==4)
sprintf(z,"SLOUP");
else if(di==5)
sprintf(z,"SLODN");
else if(di==6)
sprintf(z,"FRE  ");
else if(di==7)
sprintf(z,"DISP ");
else if(di==8)
sprintf(z,"RTC  ");
else if(di==9)
sprintf(z,"REV  ");
else if(di==10)
sprintf(z,"LOGO   ");
else
sprintf(z,"     ");

ss(&z[0]);
//while(PORTDbits.RD2==0 || PORTDbits.RD0==0);

//while((PORTDbits.RD2==1 && PORTDbits.RD0==1) && (PORTBbits.RB0==0 && PORTBbits.RB5==0));	// up and down dir memberane sw (auto sw and up dw sw)
if(PORTDbits.RD2==0)
{
if(di<10)
di++;
}
else if(PORTDbits.RD0==0)
{
if(di>0)
di--;
}


while(PORTBbits.RB0==1 || PORTBbits.RB5==1)	// auto sw and up dw sw
{
max7219(0x8,0x00);	// scan limit (max 7)
max7219(0x6,0x00);	// scan limit (max 7)
max7219(0x7,0x00);	// scan limit (max 7)

if(di==1)
{
sprintf(z,"LCE %d",d[0]);	
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[0]<5)
d[0]++;
}
else if(PORTDbits.RD2==0)
{
if(d[0]>1)
d[0]--;
}
}	// if(di==1) condition ends

else if(di==2)	// fast up
{
sprintf(z,"% 5d",d[1]);	
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[1]<5000)
d[1]++;
}
else if(PORTDbits.RD2==0)
{
if(d[1]>1000)
d[1]--;
}
}	// if(di==2) condition ends


else if(di==3)	// fast dn
{
sprintf(z,"% 5d",d[2]);	
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[2]<5000)
d[2]++;
}
else if(PORTDbits.RD2==0)
{
if(d[2]>1000)
d[2]--;
}
}	// if(di==3) condition ends


else if(di==4)	// slow up
{
sprintf(z,"% 5d",d[3]);	
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[3]<999)
d[3]++;
}
else if(PORTDbits.RD2==0)
{
if(d[3]>100)
d[3]--;
}
}	// if(di==4) condition ends


else if(di==5)	// slow dn
{
sprintf(z,"% 5d",d[4]);
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[4]<999)
d[4]++;
}
else if(PORTDbits.RD2==0)
{
if(d[4]>100)
d[4]--;
}
}	// if(di==5) condition ends

else if(di==6)	// frequency
{
sprintf(z,"% 5d",d[5]);
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[5]<10)
d[5]++;
}
else if(PORTDbits.RD2==0)
{
if(d[5]>1)
d[5]--;
}
}	// if(di==6) condition ends


else if(di==7)	// display brightness
{
sprintf(z,"% 5d",d[6]);
ss(&z[0]);

max7219(0xa,d[6]);	// scan limit (max 7)

if(PORTDbits.RD0==0)
{
if(d[6]<15)
d[6]++;
}
else if(PORTDbits.RD2==0)
{
if(d[6]>1)
d[6]--;
}
}	// if(di==7) condition ends

else if(di==8)	// rtc
{
sprintf(z,"% 5d",d[7]);
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[7]<1)
d[7]++;
}
else if(PORTDbits.RD2==0)
{
if(d[7]>0)
d[7]--;
}
}	// if(di==8) condition ends


else if(di==9)	// rtc
{
sprintf(z,"% 5d",d[8]);
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[8]<1)
d[8]++;
}
else if(PORTDbits.RD2==0)
{
if(d[8]>0)
d[8]--;
}
}	// if(di==9) condition ends

else if(di==10)	// rtc
{
sprintf(z,"% 5d",d[9]);
ss(&z[0]);

if(PORTDbits.RD0==0)
{
if(d[9]<1)
d[9]++;
}
else if(PORTDbits.RD2==0)
{
if(d[9]>0)
d[9]--;
}
}	// if(di==10) condition ends

delay(20000);

if(PORTDbits.RD1==0)	// enter sw
{
*cal=d[0];
*fsup=d[1];
*fsdn=d[2];
*slup=d[3];
*sldn=d[4];
*freq=d[5];
*disp=d[6];
*rtc=d[7];
*rev=d[8];
*logo=d[9];
return;
}	// condition for enter sw ends

}// s/w while loop ends

delay(20000);

if(PORTDbits.RD1==0)	// enter sw
{
*cal=d[0];
*fsup=d[1];
*fsdn=d[2];
*slup=d[3];
*sldn=d[4];
*freq=d[5];
*disp=d[6];
*rtc=d[7];
*rev=d[8];
*logo=d[9];
return;
}
}	// infinite loop ends
}