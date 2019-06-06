/* tng-base-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * pct2075.h: PCT2075 driver
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

#include "pct2075.h"
#include "configs/config_pct2075.h"

#include "pac1933.h"
#include "configs/config_pac1933.h"

#include "bricklib2/logging/logging.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/os/coop_task.h"

PCT2075 pct2075;
static CoopTask pct2075_task;

void pct2075_tick_task(void) {
	while (true) {
		uint8_t raw_temperature[2] = {0, 0};
		int16_t temperature;
		uint32_t ret = 0;
		do {
			pct2075.i2c_fifo->address = PCT2075_I2C_ADDRESS;
			ret = i2c_fifo_coop_read_register(pct2075.i2c_fifo, 0x00, 2, raw_temperature);
			pct2075.i2c_fifo->address = PAC1933_I2C_ADDRESS;

			if(ret != 0) {
				coop_task_sleep_ms(110);
			}
		} while(ret != 0);

		// TODO: Handle ret errors! (re-init i2c)

		temperature = (((raw_temperature[0] & 0b01111111) << 3) | (raw_temperature[1] >> 5))*125/100;
		if(raw_temperature[0] & (1 << 7)) {
			temperature = -temperature;
		}
		logd("Temperature: %d.%d °C\n\r", temperature/10, temperature%10);

		coop_task_sleep_ms(500);
	}
}

void pct2075_init_i2c(void) {
#if 0
	pct2075.i2c_fifo.baudrate         = PCT2075_I2C_BAUDRATE;
	pct2075.i2c_fifo.address          = PCT2075_I2C_ADDRESS;
	pct2075.i2c_fifo.i2c              = PCT2075_I2C;

	pct2075.i2c_fifo.scl_port         = PCT2075_SCL_PORT;
	pct2075.i2c_fifo.scl_pin          = PCT2075_SCL_PIN;
	pct2075.i2c_fifo.scl_mode         = PCT2075_SCL_PIN_MODE;
	pct2075.i2c_fifo.scl_input        = PCT2075_SCL_INPUT;
	pct2075.i2c_fifo.scl_source       = PCT2075_SCL_SOURCE;
	pct2075.i2c_fifo.scl_fifo_size    = PCT2075_SCL_FIFO_SIZE;
	pct2075.i2c_fifo.scl_fifo_pointer = PCT2075_SCL_FIFO_POINTER;

	pct2075.i2c_fifo.sda_port         = PCT2075_SDA_PORT;
	pct2075.i2c_fifo.sda_pin          = PCT2075_SDA_PIN;
	pct2075.i2c_fifo.sda_mode         = PCT2075_SDA_PIN_MODE;
	pct2075.i2c_fifo.sda_input        = PCT2075_SDA_INPUT;
	pct2075.i2c_fifo.sda_source       = PCT2075_SDA_SOURCE;
	pct2075.i2c_fifo.sda_fifo_size    = PCT2075_SDA_FIFO_SIZE;
	pct2075.i2c_fifo.sda_fifo_pointer = PCT2075_SDA_FIFO_POINTER;

	i2c_fifo_init(&pct2075.i2c_fifo);
#endif

	// I2C Fifo Init already done by PAC1933 driver
	pct2075.i2c_fifo = &pac1933.i2c_fifo;
}

void pct2075_init(void) {
	memset(&pct2075, 0, sizeof(pct2075));

	pct2075_init_i2c();
	coop_task_init(&pct2075_task, pct2075_tick_task);
}

void pct2075_tick(void) {
	coop_task_tick(&pct2075_task);
}
