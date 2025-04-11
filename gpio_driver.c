# include "gpio_driver.h"
#include "stm32f10x.h" 

#define SYSTEM_CLOCK_HZ 108000000 // Example clock frequency
#define SYSTICK_LOAD_1MS (SYSTEM_CLOCK_HZ / 1000 - 1)

volatile unsigned long msTicks;
/// GPIO INIT function
void Gpio_init(unsigned short port , unsigned short pin , unsigned short dir, unsigned short dir_opt)
{
  unsigned short tpin = pin;
	unsigned short offset = 0x00;
	volatile unsigned long  *CR;
	
	if ( pin >7)
	{
	 tpin -=8;		
	 offset +=0x1;
	}
	if (port==1)
	{
		RCC_APB2EN |=0x4; // enable poort A
		CR = (volatile unsigned long*)(&GPIO_PORT_A +offset);
	}
	else if (port==2)
	{
		RCC_APB2EN |=0x8; // enable poort B
		CR = (volatile unsigned long*)(&GPIO_PORT_B +offset);
	}
	else if (port==3)
	{
		RCC_APB2EN |=0x10; // enable poort C
		CR = (volatile unsigned long*)(&GPIO_PORT_C +offset);
	}
	
	*CR &= ~(0xf<<(tpin*4)); /// Reset t pin 
	*CR |= (dir<<(tpin*4))|(dir_opt<<(tpin*4+2));
	}

	/// GPIO READ FUNCTION
	
	int Gpio_read(unsigned short port,unsigned short pin)
	{ volatile unsigned long* IDR;
	  unsigned short offset = 0x2;
		int value;
		if (port==1)
		{
			IDR = (volatile unsigned long*)(&GPIO_PORT_A +offset);
			
		}
		else if (port == 2)
		{
		 IDR = (volatile unsigned long*)(&GPIO_PORT_B+offset);
		}
		else if (port == 3)
		{
		 IDR = (volatile unsigned long*)(&GPIO_PORT_C+offset);
		}
		value = (*IDR & (0x1<<pin))>>pin ;
	 return value;
	
	}
/// GPIO WRITE FUNCTION
	
	void Gpio_write(unsigned short  port, unsigned short pin , unsigned short value)
	{
	 unsigned short offset = 0x3;
	 volatile unsigned long* Out;
		
	 if (port==1)
	 {
	  Out = (volatile unsigned long*)(&GPIO_PORT_A+offset);
	 }
	 else if(port==2)
	 {
     Out = (volatile unsigned long*)(&GPIO_PORT_B+offset);
	 }
	  else if(port==3)
	 {
     Out = (volatile unsigned long*)(&GPIO_PORT_C+offset);
	 }
 	 value ? (*Out |= (value<<pin)): (*Out &= ~(1<<pin));
	}
	
	/// GPIO Toggle function
	
	void Gpio_Toggle(unsigned short port, unsigned short pin)
	{
	   if (Gpio_read (port,pin))
		 {
		  Gpio_write(port,pin,0);
		 }
		 else
		 {
		  Gpio_write(port,pin,1);
		 }
     		
  }
	


void systick_init(void) {
    SysTick->CTRL = 0; // Disable SysTick
    SysTick->VAL = 0;  // Clear current value
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; // Enable SysTick with processor clock
}

void delayM(void) {
    SysTick->LOAD = SYSTICK_LOAD_1MS;
    SysTick->VAL = 0;
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
}

void delay(unsigned long t) {
    for (; t > 0; t--) {
        delayM();
    }
}