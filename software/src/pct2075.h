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

#ifndef PCT2075_H
#define PCT2075_H

#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"

typedef struct {
    I2CFifo *i2c_fifo;
} PCT2075;

extern PCT2075 pct2075;

void pct2075_init(void);
void pct2075_tick(void);
void pct2075_tick_task(void);

#endif
