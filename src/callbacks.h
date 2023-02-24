/***************************************************************************
 *            covcrav_callbacks.h
 *
 *  mer. janvier 20 12:57:38 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_callbacks.h
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
 * @file covcrav_callbacks.h
 * Event slot from GUI
 * @author hichem BARGAOUI
 * @author anouar CHEMEK
 */
#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__
#include <gtk/gtk.h>
#include "common.h"





void on_button1_clicked(GtkButton* widget, gpointer data);
void on_button2_clicked(GtkButton* widget, gpointer data);
void on_button3_clicked(GtkButton* widget, gpointer data);
void on_button4_clicked(GtkButton* button, gpointer user_data);
void on_button_test_clicked(GtkButton* button, gpointer user_data);
void on_button_off_clicked(GtkButton* widget, gpointer data);
void on_button_reset_clicked(GtkButton* widget, gpointer data);
void on_checkbutton1_toggled(GtkToggleButton* togglebutton, gpointer user_data);
void on_checkbutton2_toggled(GtkToggleButton* togglebutton, gpointer user_data);
void on_checkbutton3_toggled(GtkToggleButton* togglebutton, gpointer user_data);
void on_combobox_period_changed(GtkComboBox *widget, gpointer   user_data);
void on_combobox_nb_itr_changed(GtkComboBox *widget, gpointer   user_data);
void on_combobox_g_area_changed(GtkComboBox *widget, gpointer   user_data);
#endif
