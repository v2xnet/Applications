/***************************************************************************
 *            rhw.h
 *
 *  sam. avril 10 15:41:45 2021
 *  Copyright  2021  anouar chemek
 *  <user@host>
 ****************************************************************************/
/*
 * rhw.h
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
#ifndef __RHW_H
#define __RHW_H

#include "callbacks.h"
#include "rhw.h"
#include "hmi.h"
#include "link.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <glib/gi18n.h>



/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/covcrav_rhw.ui" */
#define UI_FILE "/usr/share/covcrav_rhw/ui/covcrav.ui"
#define TOP_WINDOW "window"
typedef struct _Private Private;
struct _Private
{
	/* ANJUTA: Widgets declaration for covcrav.ui - DO NOT REMOVE */
};

static Private* priv = NULL;


void init_services(void);
GtkWidget* create_window (void);

#endif