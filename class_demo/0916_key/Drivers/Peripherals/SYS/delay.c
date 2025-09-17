#include "delay.h"

// 核心：SysTick定时器延时基础函数（延时指定微秒数，内部调用）
// 原理：SysTick是Cortex-M4内核定时器，默认时钟为 HCLK/8（HCLK默认168MHz时，SysTick时钟=21MHz，周期≈47.619ns）
// 无需初始化：SysTick默认关闭，每次调用时临时配置，用完关闭，不影响其他功能
static void SysTick_DelayUs(uint32_t us)
{
    uint32_t temp;
    // 1. 配置SysTick：加载值 = 延时微秒数 × SysTick时钟频率（21MHz）/ 1e6（微秒转秒）
    // 注：21MHz = 21×10^6 Hz，故 1us 对应加载值 = 21×1 = 21
    SysTick->LOAD = (uint32_t)(us * 21);  
    SysTick->VAL = 0x00;                  		// 2. 清空当前计数值
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;  // 3. 使能SysTick（仅内核时钟，不触发中断）
    
    // 4. 等待计数完成（CTRL寄存器的COUNTFLAG位为1时表示计数结束）
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk));
    
    SysTick->CTRL = 0x00;  										// 5. 关闭SysTick，避免影响后续调用
    SysTick->VAL = 0x00;   										// 6. 清空计数值，复位状态
}

// 微秒级延时（对外接口）
void delay_Xus(uint16_t X)
{
    if (X == 0)
        return;
    SysTick_DelayUs(X);
}

// 毫秒级延时（对外接口：1ms = 1000us，循环调用微秒延时）
void delay_Xms(uint16_t X)
{
    while (X--)
    {
        SysTick_DelayUs(1000);
    }
}

// 秒级延时（对外接口：1s = 1000ms，循环调用毫秒延时）
void delay_Xs(uint16_t X)
{
    while (X--)
    {
        delay_Xms(1000);
    }
}
