 /******************************************************************************
   * 测试硬件：立创开发板·GD32E230C8T6    使用主频72Mhz    晶振8Mhz
   * 版 本 号: V1.0
   * 修改作者: www.lckfb.com
   * 修改日期: 2023年11月02日
   * 功能介绍:      
   *****************************************************************************
   * 梁山派软硬件资料与相关扩展板软硬件资料官网全部开源  
   * 开发板官网：www.lckfb.com   
   * 技术支持常驻论坛，任何技术问题欢迎随时交流学习  
   * 立创论坛：club.szlcsc.com   
   * 其余模块移植手册：【立创·GD32E230C8T6开发板】模块移植手册
   * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
   * 不靠卖板赚钱，以培养中国工程师为己任
  ******************************************************************************/
#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>


#define FLASH_JUMP_ADDR							(0x08003000)
typedef  void (*pFunction)(void);


//设置栈顶地址
//addr:栈顶地址
void MSR_MSP(uint32_t addr) 
{
    __ASM("MSR MSP, r0"); 			//set Main Stack value
    __ASM("BX r14");
}

/*!
* @brief 跳转到应用程序段
*        执行条件：无
* @param[in1] : 用户代码起始地址.
*
* @retval: 无
*/
void jump_to_app(uint32_t app_addr)
{ 
    
    pFunction jump_to_application;
    uint32_t jump_address;
    
    /* Check if valid stack address (RAM address) then jump to user application */
    if (((*(__IO uint32_t*)app_addr) & 0x2FFE0000 ) == 0x20000000)
    {
      /* Jump to user application */
      jump_address = *(__IO uint32_t*) (app_addr + 4);
      jump_to_application = (pFunction) jump_address;
		
			
        for(int i = 0; i < 8; i++) {
            NVIC->ICER[i] = 0xFFFFFFFF; // 关闭中断
            NVIC->ICPR[i] = 0xFFFFFFFF; // 清除中断标志位
        }
		rcu_deinit();
		// 关闭SYSTICK
        SysTick->CTRL = 0;
        SysTick->LOAD = 0;
        SysTick->VAL = 0;	
		__set_PRIMASK(1);  //关闭总中断
      /* Initialize user application's Stack Pointer */
      //__set_MSP(*(__IO uint32_t *)FLASH_JUMP_ADDR);
		//MSR_MSP(*(__IO uint32_t*) jump_address);


      jump_to_application();
    }    
    
}



int main(void)
{
	/* 
		初始化程序省略.....  
	*/
    //systick_config();

    /* enable the LED1 GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOC);
    /* configure LED1 GPIO port */ 
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    /* reset LED1 GPIO pin */
    gpio_bit_reset(GPIOC,GPIO_PIN_13);	
	
	if(((FLASH_JUMP_ADDR+4)&0xFF000000)==0x08000000) //Judge if start at 0X08XXXXXX.
	{
		jump_to_app(FLASH_JUMP_ADDR); // Jump to  APP
	}
	
	while(1)
	{
	
	}
}





#if 0
extern pFunction Jump_To_Application;
extern uint32_t JumpAddress;

int main(void)
{
    systick_config();

    /* enable the LED1 GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOC);
    /* configure LED1 GPIO port */ 
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    /* reset LED1 GPIO pin */
    gpio_bit_set(GPIOC,GPIO_PIN_13);
    delay_ms(100);

    /* Test if user code is programmed starting from address "ApplicationAddress" */
    if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    { 
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) ApplicationAddress);
      Jump_To_Application();
    }

    while(1)
    {


    }
}
#endif


