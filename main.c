# include "gpio_driver.h"
#include "stm32f10x.h" 
//#include "systick_timer.h"
int signal;
int main()
{
 
	Gpio_init(PortA,0,IN,I_GP_PP);
	Gpio_init(PortC,13,out50,O_GP_PP);
	Gpio_init(PortA,12,out50,O_GP_PP);
	systick_init();
	__disable_irq();
	AFIO->EXTICR[0]=0X00;
	EXTI->IMR |=1;
	EXTI->RTSR |=1;
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();

	while (1)
	{
		Gpio_write(PortA,12,signal);
		if (signal)
		{
		 Gpio_write(PortC,13,HIGH);
		 delay(1000);
		 Gpio_write(PortC,13,LOW);
		 delay(1000);
			
		}
		else{
		 Gpio_write(PortC,13,LOW);
			
		}
	 
	}
	
}

void EXTI0_IRQHandler()
{
 EXTI->PR |=1;
 if(signal)
 {
  signal=0;
 }
 else
 {signal=1;}
}
