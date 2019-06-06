/* tng-base-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * io.h: IO driver
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "io.h"

#include "configs/config_io.h"

#include "bricklib2/logging/logging.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/os/coop_task.h"

IO io;
static CoopTask io_task;

void io_tick_task(void) {
	uint8_t i = 0;
	while (true) {
		switch(i) {
			case 0:
				XMC_GPIO_SetOutputHigh(IO_DO0_PIN);

				XMC_GPIO_SetOutputLow(IO_LED_DIO_PIN);
				coop_task_sleep_ms(500);
				XMC_GPIO_SetOutputHigh(IO_LED_DIO_PIN);
				break;
			case 1:
				XMC_GPIO_SetOutputLow(IO_LED_STATUS_R_PIN);
				coop_task_sleep_ms(500);
				XMC_GPIO_SetOutputHigh(IO_LED_STATUS_R_PIN);
				break;
			case 2:
				XMC_GPIO_SetOutputLow(IO_DO0_PIN);

				XMC_GPIO_SetOutputLow(IO_LED_STATUS_G_PIN);
				coop_task_sleep_ms(500);
				XMC_GPIO_SetOutputHigh(IO_LED_STATUS_G_PIN);
				break;
			case 3:
				XMC_GPIO_SetOutputLow(IO_LED_STATUS_B_PIN);
				coop_task_sleep_ms(500);
				XMC_GPIO_SetOutputHigh(IO_LED_STATUS_B_PIN);
				break;
		}
		i = (i + 1) % 4;
#if 0
		if(!XMC_GPIO_GetInput(IO_DI1_PIN)) {
			XMC_GPIO_SetOutputLow(IO_SW_STACK_PIN);
			XMC_GPIO_SetOutputLow(IO_SW_5V_PIN);
			XMC_GPIO_SetOutputLow(IO_SW_PWR_PIN);
		} else {
			XMC_GPIO_SetOutputHigh(IO_SW_STACK_PIN);
			XMC_GPIO_SetOutputHigh(IO_SW_5V_PIN);
			XMC_GPIO_SetOutputHigh(IO_SW_PWR_PIN);
		}
#endif

#if 0
		logd("DI0: %d, DI1: %d, MUSB: %d\n\r", XMC_GPIO_GetInput(IO_DI0_PIN), XMC_GPIO_GetInput(IO_DI1_PIN), XMC_GPIO_GetInput(IO_MUSB_CON_PIN));
#endif
	}
}


void io_init(void) {
	memset(&io, 0, sizeof(io));

	const XMC_GPIO_CONFIG_t output_pin_config = {
		.mode         = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
	};

	const XMC_GPIO_CONFIG_t input_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_LARGE,
	};

	XMC_GPIO_Init(IO_LED_PWR_PIN, &output_pin_config);
	XMC_GPIO_Init(IO_LED_DIO_PIN, &output_pin_config);
	XMC_GPIO_Init(IO_LED_STATUS_R_PIN, &output_pin_config);
	XMC_GPIO_Init(IO_LED_STATUS_G_PIN, &output_pin_config);
	XMC_GPIO_Init(IO_LED_STATUS_B_PIN, &output_pin_config);

	XMC_GPIO_Init(IO_DO0_PIN, &output_pin_config);

	XMC_GPIO_Init(IO_SW_STACK_PIN, &output_pin_config);
	XMC_GPIO_Init(IO_SW_5V_PIN, &output_pin_config);
	XMC_GPIO_Init(IO_SW_PWR_PIN, &output_pin_config);

	XMC_GPIO_Init(IO_SW_PWR_CUR_PIN, &input_pin_config);
	XMC_GPIO_Init(IO_MUSB_CON_PIN, &input_pin_config);

	XMC_GPIO_Init(IO_DI0_PIN, &input_pin_config);
	XMC_GPIO_Init(IO_DI1_PIN, &input_pin_config);

	coop_task_init(&io_task, io_tick_task);
}

void io_tick(void) {
	coop_task_tick(&io_task);
}
