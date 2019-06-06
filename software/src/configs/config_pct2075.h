/* tng-base-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_pct2075.h: Config for PCT2075
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

#ifndef CONFIG_PCT2075_H
#define CONFIG_PCT2075_H

#include "xmc_gpio.h"
#include "xmc_i2c.h"

#define PCT2075_I2C_BAUDRATE         100000

#define PCT2075_I2C_ADDRESS          0b1001111
#define PCT2075_I2C                  XMC_I2C0_CH1

#define PCT2075_SCL_PORT             XMC_GPIO_PORT0
#define PCT2075_SCL_PIN              8
#define PCT2075_SCL_PIN_MODE         XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7
#define PCT2075_SCL_INPUT            XMC_USIC_CH_INPUT_DX1
#define PCT2075_SCL_SOURCE           1
#define PCT2075_SCL_FIFO_SIZE        XMC_USIC_CH_FIFO_SIZE_16WORDS
#define PCT2075_SCL_FIFO_POINTER     32

#define PCT2075_SDA_PORT             XMC_GPIO_PORT0
#define PCT2075_SDA_PIN              6
#define PCT2075_SDA_PIN_MODE         XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT7
#define PCT2075_SDA_INPUT            XMC_USIC_CH_INPUT_DX0
#define PCT2075_SDA_SOURCE           2
#define PCT2075_SDA_FIFO_SIZE        XMC_USIC_CH_FIFO_SIZE_16WORDS
#define PCT2075_SDA_FIFO_POINTER     48

#endif