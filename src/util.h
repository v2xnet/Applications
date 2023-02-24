/***************************************************************************
 *            util.h
 *
 *  mar. mai 11 18:31:38 2021
 *  Copyright  2021  anouar chemek
 *  <user@host>
 ****************************************************************************/
/*
 * util.h
 *
 * Copyright (C) 2021 - anouar chemek
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __UTIL_H
#define __UTIL_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/timex.h>
#include <stdint.h>
#include <unistd.h>
#include "itsnet_header.h"

#define MSEC_PER_SEC 1000
#define MICROSEC_PER_MSEC 1000
#define MICROSEC_PER_SEC 1000000000

bool covcrav_get_gps_status(void);

bool covcrav_get_connected_status(void);

bool covcrav_get_sync_status(struct ntptimeval tv);

long covcrav_get_offset_value(struct ntptimeval tv);

/**
 * timespec_to_ms - Convert timeval to milliseconds
 * @ts:         pointer to the timesval variable to be converted
 *
 * Returns the scalar milliseconds representation of the timeval
 * parameter.
 */
static inline uint32_t timeval_to_ms(const struct ntptimeval* tv)
{
    return ((uint32_t)(tv->time.tv_sec * MSEC_PER_SEC) + (tv->time.tv_usec / MICROSEC_PER_MSEC));
}

static inline uint64_t timeval_to_us(const struct ntptimeval* tv)
{
    return ((uint64_t)(tv->time.tv_sec * MICROSEC_PER_SEC) + (tv->time.tv_usec));
}
#endif