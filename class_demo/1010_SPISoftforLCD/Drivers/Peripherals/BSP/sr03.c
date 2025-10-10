#include "sr03.h" 

float distant;      //测量距离
uint32_t measure_Buf[3] = {0};   //存放定时器计数值的数组
uint8_t  measure_Cnt = 0;    //状态标志位
uint32_t high_time;   //超声波模块返回的高电平时间
 
 void delay_us(uint32_t us)//主频72M
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}
uint16_t SR04_GetData(void)
{
    switch (measure_Cnt) {
        case 0:
            TRIG_H;
            delay_us(30);
            TRIG_L;
            measure_Cnt++;
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim12, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
            HAL_TIM_IC_Start_IT(&htim12, TIM_CHANNEL_1);
//            return 0;  // 第一次调用返回0
						return distant;
        case 3:
            if (measure_Buf[1] > measure_Buf[0]) {  // 添加有效性检查
                high_time = measure_Buf[1] - measure_Buf[0];
                distant = (high_time * 0.034) / 2;
            } else {
                distant = 0;  // 处理无效的测量值
            }
            measure_Cnt = 0;
            TIM12->CNT = 0;
            HAL_TIM_IC_Stop_IT(&htim12, TIM_CHANNEL_1);
            return (uint16_t)distant;
        default:
            return 0;
    }
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//
{
	
	if(TIM12 == htim->Instance)// 判断触发的中断的定时器为tim12
	{
		switch(measure_Cnt){
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim12,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim12,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim12,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim12,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				measure_Cnt++;  
                         
		}
	
	}
	
}










































































