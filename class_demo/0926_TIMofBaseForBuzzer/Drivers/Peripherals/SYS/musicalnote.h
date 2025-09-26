#ifndef __MUSICAL_NOTE_H
	#define __MUSICAL_NOTE_H
	#include "main.h"
	
	#define BEATS_PER_MINUTE	76

	typedef enum
	{
		Region_Bass 	= 0,		//低音区
		Region_Alto 	= 1,		//中音区
		Region_Treble = 2			//高音区
	} Note_Zone;						//音区枚举

	typedef enum
	{
		Solfege_Rest 	= 0,		//休止符
		Solfege_Do 		= 1,		//哆
		Solfege_Re 		= 2,		//来
		Solfege_Mi 		= 3,		//咪
		Solfege_Fa 		= 4,		//发
		Solfege_Sol		= 5,		//唆
		Solfege_La 		= 6,		//啦
		Solfege_Si 		= 7			//西
	} Note_Name;						//唱名枚举

	typedef enum
	{
		Rhythm_Sixteenth 	= 1,
		Rhythm_Eighth 		= 2,
		Rhythm_Quarter		= 4,
		Rhythm_Half 			= 8,
		Rhythm_Whole  		= 16,
		Rhythm_Duple 			= 32,
		Rhythm_Four				= 64,
		Rhythm_Eight 			= 128,
		Rhythm_Sixteen 		= 256
	} Note_Beat;						//节拍枚举

	typedef struct
	{
		uint8_t Solfege;			//唱名
		uint8_t Region;				//音区
		uint8_t Rhythm;				//节拍
	}MusicNote_TypeDef;			//音符初始化结构体

	uint16_t MusicalNote_GetFrequency(MusicNote_TypeDef *yinfu);
	uint16_t MusicalNote_GetDuration(MusicNote_TypeDef *yinfu);
#endif
