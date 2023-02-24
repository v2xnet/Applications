/***************************************************************************
 *            covcrav_hmi.h
 *
 *  mer. janvier 20 12:29:42 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_hmi.h
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
#ifndef __ITSNET_HMI_
#define __ITSNET_HMI_

#include <asm/types.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <SDL/SDL_mixer.h>
#include "distance.h"
#include "itsnet_types.h"
#include <sys/time.h>
#include <gtk/gtk.h>
#include <arpa/inet.h>


void print_node_id(struct itsnet_node_id node_id);
void* covcrav_local_display(void* arg);
    
#endif