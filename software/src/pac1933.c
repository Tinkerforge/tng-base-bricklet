/* tng-base-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * pac1933.h: PAC1933 driver
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

#include "pac1933.h"

#include "configs/config_pac1933.h"

#include "bricklib2/logging/logging.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/os/coop_task.h"

#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"

PAC1933 pac1933;
static CoopTask pac1933_task;

void pac1933_tick_task(void) {
	while (true) {
		// TODO: Handle ret errors! (re-init i2c)

		uint8_t send = 0;
		i2c_fifo_coop_write_register(&pac1933.i2c_fifo, 0x00, 1, &send, true);
		coop_task_sleep_ms(500);

		uint8_t ids[3] = {0, 0, 0};
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0xFD, 1, &ids[0]);
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0xFE, 1, &ids[1]);
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0xFF, 1, &ids[2]);
		logd("Product ID: %x, Manufacturer ID: %x, Revision ID: %x\n\r", ids[0], ids[1], ids[2]);

		uint8_t vbus[3][2] = {{0, 0}, {0, 0}, {0, 0}};
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0x07, 2, vbus[0]);
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0x08, 2, vbus[1]);
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0x09, 2, vbus[2]);
		uint32_t voltage[3] = {0, 0, 0};

		for(uint8_t ch = 0; ch < 3; ch++) {
			voltage[ch] = (vbus[ch][0] << 8) | vbus[ch][1];
			voltage[ch] = voltage[ch] * 32000/0xFFFF;
		}
		logd("VBus 0: %dmV, VBus 1: %dmV, VBus 2: %dmV\n\r", voltage[0], voltage[1], voltage[2]);

		uint8_t vsense[3][2] = {{0, 0}, {0, 0}, {0, 0}};
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0x0b, 2, vsense[0]);
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0x0c, 2, vsense[1]);
		i2c_fifo_coop_read_register(&pac1933.i2c_fifo, 0x0d, 2, vsense[2]);
		uint32_t current[3] = {0, 0, 0};

		for(uint8_t ch = 0; ch < 3; ch++) {
			current[ch] = (vsense[ch][0] << 8) | vsense[ch][1];
			current[ch] = current[ch] * 5000/0xFFFF;
		}
		logd("VSense 0: %dmA, VSense 1: %dmA, VSense 2: %dmA\n\r", current[0], current[1], current[2]);
	}
}

void pac1933_init_i2c(void) {
	pac1933.i2c_fifo.baudrate         = PAC1933_I2C_BAUDRATE;
	pac1933.i2c_fifo.address          = PAC1933_I2C_ADDRESS;
	pac1933.i2c_fifo.i2c              = PAC1933_I2C;

	pac1933.i2c_fifo.scl_port         = PAC1933_SCL_PORT;
	pac1933.i2c_fifo.scl_pin          = PAC1933_SCL_PIN;
	pac1933.i2c_fifo.scl_mode         = PAC1933_SCL_PIN_MODE;
	pac1933.i2c_fifo.scl_input        = PAC1933_SCL_INPUT;
	pac1933.i2c_fifo.scl_source       = PAC1933_SCL_SOURCE;
	pac1933.i2c_fifo.scl_fifo_size    = PAC1933_SCL_FIFO_SIZE;
	pac1933.i2c_fifo.scl_fifo_pointer = PAC1933_SCL_FIFO_POINTER;

	pac1933.i2c_fifo.sda_port         = PAC1933_SDA_PORT;
	pac1933.i2c_fifo.sda_pin          = PAC1933_SDA_PIN;
	pac1933.i2c_fifo.sda_mode         = PAC1933_SDA_PIN_MODE;
	pac1933.i2c_fifo.sda_input        = PAC1933_SDA_INPUT;
	pac1933.i2c_fifo.sda_source       = PAC1933_SDA_SOURCE;
	pac1933.i2c_fifo.sda_fifo_size    = PAC1933_SDA_FIFO_SIZE;
	pac1933.i2c_fifo.sda_fifo_pointer = PAC1933_SDA_FIFO_POINTER;

	i2c_fifo_init(&pac1933.i2c_fifo);
}

void pac1933_init(void) {
	memset(&pac1933, 0, sizeof(pac1933));

	pac1933_init_i2c();
	coop_task_init(&pac1933_task, pac1933_tick_task);
}

void pac1933_tick(void) {
	coop_task_tick(&pac1933_task);
}
