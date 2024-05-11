#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"

#include <rtthread.h>

char c = 0;
int i = 0;

void run1(void *d)
{
	// i++;
	while(1)
	{
		i++;
		/* 延时 200ms */
		rt_thread_mdelay(200);
		i--;
		/* 延时 200ms */
		rt_thread_mdelay(200);
	}
}

void run2(void *d)
{
	c++;
	while(1)
	{
		c++;
		/* 延时 200ms */
		rt_thread_mdelay(200);
	}
}

int main(void)
{
	i++;
		rt_thread_mdelay(200);
	i--;
		rt_thread_mdelay(200);
#if 0		//reg
	RCC->APB2ENR = 0x00000010;
	GPIOC->CRH = 0x00300000;
	GPIOC->ODR = 0x00000000;
#else
	GPIO_InitTypeDef GPIO_InitStructure = 
	{

		GPIO_Pin_13,
		GPIO_Speed_50MHz,
		GPIO_Mode_Out_PP
	};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
#endif
	i++;



#if 1
	/* Start with the clocks in their expected state. */
	RCC_DeInit();
	
	/* Enable HSE (high speed external clock). */
	RCC_HSEConfig( RCC_HSE_ON );

	/* Wait till HSE is ready. */
	while( RCC_GetFlagStatus( RCC_FLAG_HSERDY ) == RESET )
	{
	}

	/* 2 wait states required on the flash. */
	*( ( unsigned long * ) 0x40022000 ) = 0x02;

	/* HCLK = SYSCLK */
	RCC_HCLKConfig( RCC_SYSCLK_Div1 );
	
	/* PLLCLK = 8MHz * 9 = 72 MHz. */
	RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );
	
	
	/* Enable PLL. */
	RCC_PLLCmd( ENABLE );

	/* Wait till PLL is ready. */
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}

	/* Select PLL as system clock source. */
	RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );

	/* Wait till PLL is used as system clock source. */
	while( RCC_GetSYSCLKSource() != 0x08 )
	{
	}
	
	

	
	
	

	/* Configure HCLK clock as SysTick clock source. */
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
#else

	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
#endif

	rt_thread_mdelay(200);
	i--;

	/* 线程控制块指针 */
	rt_thread_t thread1 = RT_NULL;
	rt_thread_t thread2 = RT_NULL;
	thread1 = rt_thread_create("thread1", run1, RT_NULL, 1024, 6, 20);

	if(thread1 != RT_NULL)
	{
		/* 启动线程 */
		rt_thread_startup(thread1);
	}

	thread2 = rt_thread_create("thread2", run2, RT_NULL, 1024, 6, 20);

	if(thread2 != RT_NULL)
	{
		/* 启动线程 */
		rt_thread_startup(thread2);
	}


	// while(1)
	// {
		
	// }
	return 0;
}


