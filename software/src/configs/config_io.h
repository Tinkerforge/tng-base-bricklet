/* tng-base-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_io.h: Config for IO
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

#ifndef CONFIG_IO_H
#define CONFIG_IO_H

#include "xmc_gpio.h"

#define IO_LED_PWR_PIN       P2_10
#define IO_LED_DIO_PIN       P1_3
#define IO_LED_STATUS_R_PIN  P1_0
#define IO_LED_STATUS_G_PIN  P1_1
#define IO_LED_STATUS_B_PIN  P1_2

#define IO_DI0_PIN           P0_0
#define IO_DI1_PIN           P0_9
#define IO_DO0_PIN           P0_12

#define IO_SW_STACK_PIN      P0_5
#define IO_SW_5V_PIN         P0_7
#define IO_SW_PWR_PIN        P2_1
#define IO_SW_PWR_CUR_PIN    P2_6

#define IO_MUSB_CON_PIN      P2_2

#endif