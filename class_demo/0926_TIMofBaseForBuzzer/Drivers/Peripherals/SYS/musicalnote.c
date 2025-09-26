#include "musicalnote.h"

uint16_t FREQ[3][8] = 										
{
	{0,	262,	294,	330,	349,	392,	440,	494},			//低音区
	{0,	523,	587,	659,	698,	784,	880,	988},			//中音区
	{0,	1046,	1175,	1318,	1397,	1568,	1760,	1976},		//高音区
};
//根据音符结构体对象得到其振动频率（单位：Hz）
uint16_t MusicalNote_GetFrequency(MusicNote_TypeDef *yinfu)
{
	return FREQ[yinfu->Region][yinfu->Solfege];
}
//根据音符结构体对象得到其演奏时长（单位：ms）
uint16_t MusicalNote_GetDuration(MusicNote_TypeDef *yinfu)
{
	float s = (yinfu->Rhythm/16.0) * (60.0/BEATS_PER_MINUTE);	//单位：s
	return (uint16_t)(1000*s);																//单位：ms	
}
