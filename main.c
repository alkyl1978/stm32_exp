/*
 * main.c
 *
 *  Created on: 18 нояб. 2014 г.
 *      Author: aleks
 */
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/hid.h>

#define LED0 GPIO1
#define LED0_PORT GPIOA
#define LED1 GPIO5
#define LED1_PORT GPIOB

uint32_t tick;


int main(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz(); // устанавливаем частоту 72 мгц

	rcc_periph_clock_enable(RCC_GPIOA); // включаем тактирования порта А
	rcc_periph_clock_enable(RCC_GPIOB); // включаем тактирование порта В

	gpio_set_mode(LED0_PORT, GPIO_MODE_OUTPUT_50_MHZ,
			      GPIO_CNF_OUTPUT_PUSHPULL, LED0); // включаем порт на вывод
	gpio_set_mode(LED1_PORT, GPIO_MODE_OUTPUT_50_MHZ,
				      GPIO_CNF_OUTPUT_PUSHPULL, LED1); // включаем порт на вывод

	// выключаем светодиоды
	gpio_set(LED0_PORT, LED0);
	gpio_set(LED1_PORT, LED1);

    // настраиваем системный таймер

	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
	systick_set_reload(8999);
	// разрешаем прерывания
	systick_interrupt_enable();
	// запускаем таймер
	systick_counter_enable();
	while(1)
	{

	}
	return 0;
}

// системное прерывание от системного таймера

void sys_tick_handler(void)
{
	tick++;
	if(tick==1000)
	{
		gpio_toggle(LED0_PORT,LED0);
		gpio_toggle(LED1_PORT,LED1);
		tick=0;
	}
}
