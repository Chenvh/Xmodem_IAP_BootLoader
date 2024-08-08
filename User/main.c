 /******************************************************************************
   * ����Ӳ�������������塤GD32E230C8T6    ʹ����Ƶ72Mhz    ����8Mhz
   * �� �� ��: V1.0
   * �޸�����: www.lckfb.com
   * �޸�����: 2023��11��02��
   * ���ܽ���:      
   *****************************************************************************
   * ��ɽ����Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ  
   * �����������www.lckfb.com   
   * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ  
   * ������̳��club.szlcsc.com   
   * ����ģ����ֲ�ֲ᣺��������GD32E230C8T6�����塿ģ����ֲ�ֲ�
   * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
   * ��������׬Ǯ���������й�����ʦΪ����
  ******************************************************************************/
#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "bsp_dma.h"
#include "bsp_usart.h"

#define FLASH_JUMP_ADDR							(0x08003000)
typedef  void (*pFunction)(void);


//����ջ����ַ
//addr:ջ����ַ
void MSR_MSP(uint32_t addr) 
{
    __ASM("MSR MSP, r0"); 			//set Main Stack value
    __ASM("BX r14");
}

/*!
* @brief ��ת��Ӧ�ó����
*        ִ����������
* @param[in1] : �û�������ʼ��ַ.
*
* @retval: ��
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
            NVIC->ICER[i] = 0xFFFFFFFF; // �ر��ж�
            NVIC->ICPR[i] = 0xFFFFFFFF; // ����жϱ�־λ
        }
		rcu_deinit();
		// �ر�SYSTICK
        SysTick->CTRL = 0;
        SysTick->LOAD = 0;
        SysTick->VAL = 0;	
		__set_PRIMASK(1);  //�ر����ж�
      /* Initialize user application's Stack Pointer */
      //__set_MSP(*(__IO uint32_t *)FLASH_JUMP_ADDR);
		//MSR_MSP(*(__IO uint32_t*) jump_address);


      jump_to_application();
    }    
    
}



int main(void)
{
	/* 
		��ʼ������ʡ��.....  
	*/
    systick_config();
	  usart_gpio_config(115200U); 	// ����0��ʼ��

#if USB_USART_DMA // ʹ��DMA
    printf("DMA receive\r\n");
    dma_config(); // DMA����
#else             // ʹ���ж�
    printf("Interrupt receive\r\n");
#endif
    /* enable the LED1 GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOC);
    /* configure LED1 GPIO port */ 
    gpio_mode_set(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_13);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    /* reset LED1 GPIO pin */
    gpio_bit_reset(GPIOC,GPIO_PIN_13);	
	
	// if(((FLASH_JUMP_ADDR+4)&0xFF000000)==0x08000000) //Judge if start at 0X08XXXXXX.
	// {
	// 	jump_to_app(FLASH_JUMP_ADDR); // Jump to  APP
	// }
	
	while(1)
	{
    
        /* �ȴ����ݴ������ */
        if (g_recv_complete_flag) // ���ݽ������
        {
            g_recv_complete_flag = 0;                   // �ȴ��´ν���
            printf("g_recv_length:%d ", g_recv_length); // ��ӡ���յ����ݳ���
            printf("g_recv_buff:%s\r\n", g_recv_buff);  // ��ӡ���յ�����
            memset(g_recv_buff, 0, g_recv_length);      // �������
            g_recv_length = 0;                          // ��ճ���
        }
		
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


