


#ifndef RGB_H_
#define RGB_H_

#define  F_CPU  8000000UL
#include <util/delay.h>

#include "StdTypes.h"
#include "Timers.h"


#ifdef RGBFILE

#define NUMBEROFCOLORS 10
#define REDPIN   OCR1A
#define GREENPIN OCR1B
#define BLUEPIN   OCR0

#define R 0
#define G 1
#define B 2

const static u8 ArrayOfColors[NUMBEROFCOLORS][3]=
{
{40,60,20},//black
{255,255,255},//white
{255,0,0},//red
{0,255,0},//green
{0,0,255},//blue
{160,85,0},//yellow
{255,0,10},//pink
{255,30,0},//orange
{153,220,0},//white green
{51,204,204},
};
#endif


void RGB_Init(void);
void RGB_SetDuty(u8 r,u8 g,u8 b);
void RGB_SetColor(u8 color);
void RGB_RelaxMode(u8 color1,u8 color2);



#endif /* RGB_H_ */