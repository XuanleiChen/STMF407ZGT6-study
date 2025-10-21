#include "delay.h"

// 全局变量：存储SysTick的1个计数对应的微秒数（自动适配主频）
static float sysTick_us_per_tick = 0.0f;

/**
 * @brief  初始化延迟函数（必须在HAL_Init()之后调用，如main()中）
 * @note   自动计算当前主频下SysTick的计数周期，确保跨主频兼容
 */
void Delay_Init(void)
{
	// 1).获取当前AHB时钟频率（单位：Hz）
	//    HAL_RCC_GetHCLKFreq()是HAL库自带函数，自动适配时钟树配置
	uint32_t ahb_freq = HAL_RCC_GetHCLKFreq();

	// 2).SysTick默认分频8，故计数频率 = AHB频率 / 8
	//    1个计数的时间 = 1 / 计数频率 = 8 / AHB频率（单位：秒）→ 转微秒需×1e6
	sysTick_us_per_tick = (8.0f * 1000000.0f) / (float)ahb_freq;
}

/**
 * @brief  微秒级延迟
 * @param  us：需要延迟的微秒数（最大值约59652320μs，即~60秒，满足绝大多数场景）
 */
void Delay_Xus(uint32_t us)
{
	if (sysTick_us_per_tick == 0.0f)  // 防止未初始化
	{
		Delay_Init();
	}

	uint32_t tick_start = 0;
	uint32_t tick_target = 0;

	// 1. 计算需要的SysTick计数次数（向上取整，避免误差）
	tick_target = (uint32_t)(ceilf((float)us / sysTick_us_per_tick));

	// 2. 记录当前SysTick计数值（SysTick->VAL是24位寄存器，直接读取）
	tick_start = SysTick->VAL;
    
	// 3. 等待计数达到目标（SysTick递减计数，需判断溢出）
	while (1)
	{
		// 计算已流逝的计数（注意：SysTick递减，VAL值减小，溢出时从0xFFFFFF重新开始）
		uint32_t tick_elapsed = 0;
		if (SysTick->VAL <= tick_start)
		{
			tick_elapsed = tick_start - SysTick->VAL;
		}
		else
		{
		// 溢出情况：已流逝 = 初始值 + (最大值 - 当前值)
			tick_elapsed = tick_start + (0xFFFFFF - SysTick->VAL);
		}

		if (tick_elapsed >= tick_target)
		{
			break;  // 延迟结束
		}
	}
}

/**
 * @brief  毫秒级延迟（基于微秒延迟实现，简单可靠）
 * @param  ms：需要延迟的毫秒数（无上限，取决于uint32_t范围）
 */
void Delay_Xms(uint32_t ms)
{
	// 1ms = 1000μs，直接循环调用微秒延迟（也可单独优化，此处兼顾简洁性）
	while (ms--)
	{
		Delay_Xus(1000);
	}
}

/**
 * @brief  秒级延迟（基于毫秒延迟实现，满足长延迟需求）
 * @param  s：需要延迟的秒数（无上限，取决于uint32_t范围）
 */
void Delay_Xs(uint32_t s)
{
	// 1s = 1000ms，循环调用毫秒延迟
	while (s--)
	{
		Delay_Xms(1000);
	}
}
