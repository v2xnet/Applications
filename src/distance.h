/***************************************************************************
 *            covcrav_distance.h
 *
 *  mer. janvier 20 13:08:36 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_distance.h
 *
 * Copyright (C) 2021 - Anouar Chemek
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
/**
 * @file covcrav_distance.h
 * position calculation code.
 * @author hichem BARGAOUI
 * @author anouar Chemek
 */

#ifndef _POSITION_CALCULATION_H_
#define _POSITION_CALCULATION_H_ 1

#include "itsnet_header.h"


#define PI 3.14159265358979323846
#define RADIUS 6371 // Radius of the earth

int convert_format_lat(const double lat);

double inv_convert_format_lat(const int lat);

int convert_format_long(const double lon);

double inv_convert_format_long(const int lon);

int convert_time_stamp(const __time_t ts);

int convert_format_spd(const double spd);

double inv_convert_format_spd(const int spd);

double _deg2rad(double deg);

double haversine_distance(uint32_t lat11, uint32_t lon11, uint32_t lat22, uint32_t lon22);

int isrelevant(uint32_t lat1, uint32_t lon1, uint32_t lat2, uint32_t lon2, uint16_t radius);

#endif /* _POSITION_CALCULATION_H_ */
