
#ifndef _ECAN_H
#define _ECAN_H


/***********************************************************
*                             Defines 
**********************************************************/
#define TRUE    1
#define FALSE   0


/**********************************************************
*                        Function Prototypes 
*********************************************************/
void InitECAN(void);

unsigned char ECAN_Receive(unsigned char *s);

void ECAN_Transmit(char s);

#endif