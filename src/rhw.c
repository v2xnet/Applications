/***************************************************************************
 *            rhw.c
 *
 *  sam. avril 10 15:41:45 2021
 *  Copyright  2021  anouar chemek
 *  <user@host>
 ****************************************************************************/
/*
 * rhw.c
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

/**
 * @file covcrav_rhw.c
 * The covCrav Road Hazard Application component
 * @author hichem BARGAOUI
 * @author anouar CHEMEK
 */

#include "rhw.h"
#include "callbacks.h"



GtkBuilder* builder;
GtkWidget* window;
GtkWidget* fixed;

GtkWidget* button1;
GtkWidget* button2;
GtkWidget* button3;
GtkWidget* button4;
GtkWidget* button_off;
GtkWidget* button_reset;
GtkWidget* button_test;
GtkWidget* checkbutton1;
GtkWidget* checkbutton2;
GtkWidget* checkbutton3;
GtkWidget* label_nodeid;
GtkWidget* label_messages;
GtkWidget* label_neighbors;

GtkWidget* gps;
GtkWidget* connected;
GtkWidget* sync_;

/*GdkPixbuf *pix_sat;
GdkPixbuf *pix_con;
GError *error = NULL;*/

GtkWidget* combobox_period;
GtkWidget* combobox_nb_itr;
GtkWidget* combobox_g_area;

GtkWidget* label_id;
GtkWidget* label_offset;


static const char * period_tab[] = {"period", "500", "250", "100","75","50","25","15","10","5","2","1"};
static const char * nb_itr_tab[] = {"nbr iter", "1000", "500","250","100","50","20","10","5"};
static const char * g_area_tab[] = {"geo area", "500", "300", "200","100","75","50","25","10","5"};


/* Called when the window is closed */
void
on_window_destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}

GtkWidget* create_window (void)
{
	
    int i;
    GError* error = NULL;


	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, NULL);

	/* Get the window object from the ui file */
	window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
        if (!window)
        {
                g_critical ("Widget \"%s\" is missing in file %s.",
				TOP_WINDOW,
				UI_FILE);
        }
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	priv = g_malloc (sizeof (struct _Private));
	/* ANJUTA: Widgets initialization for covcrav.ui - DO NOT REMOVE */



	 fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));

    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    g_signal_connect((gpointer)button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);

    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    g_signal_connect((gpointer)button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);

    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect((gpointer)button3, "clicked", G_CALLBACK(on_button3_clicked), NULL);
    
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    g_signal_connect((gpointer)button4, "clicked", G_CALLBACK(on_button4_clicked), NULL);

    button_test = GTK_WIDGET(gtk_builder_get_object(builder, "button_test"));
    g_signal_connect((gpointer)button_test, "clicked", G_CALLBACK(on_button_test_clicked), NULL);

    button_off = GTK_WIDGET(gtk_builder_get_object(builder, "button_off"));
    g_signal_connect((gpointer)button_off, "clicked", G_CALLBACK(on_button_off_clicked), NULL);

    button_reset = GTK_WIDGET(gtk_builder_get_object(builder, "button_reset"));
    g_signal_connect((gpointer)button_reset, "clicked", G_CALLBACK(on_button_reset_clicked), NULL);

    checkbutton1 = GTK_WIDGET(gtk_builder_get_object(builder, "checkbutton1"));
    g_signal_connect((gpointer)checkbutton1, "toggled", G_CALLBACK(on_checkbutton1_toggled), NULL);
    
    checkbutton2 = GTK_WIDGET(gtk_builder_get_object(builder, "checkbutton2"));
    g_signal_connect((gpointer)checkbutton2, "toggled", G_CALLBACK(on_checkbutton2_toggled), NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2),TRUE);
    
    
    checkbutton3 = GTK_WIDGET(gtk_builder_get_object(builder, "checkbutton3"));
    g_signal_connect((gpointer)checkbutton2, "toggled", G_CALLBACK(on_checkbutton3_toggled), NULL);

	
	/*pix_sat = gdk_pixbuf_new_from_file ("/usr/share/covcrav_rhw/ui/satelite.png", &error);
	gps_status = gtk_image_new_from_pixbuf (pix_sat);*/
    
    /*pix_con = gdk_pixbuf_new_from_file ("/usr/share/covcrav_rhw/ui/connected.png", &error);
	con_status = gtk_image_new_from_pixbuf (pix_con);*/
    
    gps=GTK_WIDGET(gtk_builder_get_object(builder,"gps"));
    gtk_widget_hide(GTK_WIDGET(gps));
    
    
    connected=GTK_WIDGET(gtk_builder_get_object(builder,"connected"));
    gtk_widget_hide(GTK_WIDGET(connected));
    

    sync_=GTK_WIDGET(gtk_builder_get_object(builder,"sync"));
	gtk_widget_hide(GTK_WIDGET(sync_));

    
    
    combobox_period=GTK_WIDGET(gtk_builder_get_object(builder, "combobox_period"));
    g_signal_connect((gpointer)combobox_period, "changed", G_CALLBACK(on_combobox_period_changed), NULL);
    
    combobox_nb_itr=GTK_WIDGET(gtk_builder_get_object(builder, "combobox_nb_itr"));
    g_signal_connect((gpointer)combobox_nb_itr, "changed", G_CALLBACK(on_combobox_nb_itr_changed), NULL);
    
    combobox_g_area=GTK_WIDGET(gtk_builder_get_object(builder, "combobox_g_area"));
    g_signal_connect((gpointer)combobox_g_area, "changed", G_CALLBACK(on_combobox_g_area_changed), NULL);
    
    /* G_N_ELEMENTS is a macro which determines the number of elements in an array.*/ 
    for (i = 0; i < G_N_ELEMENTS (period_tab); i++)
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combobox_period), period_tab[i]);
        
    for (i = 0; i < G_N_ELEMENTS (nb_itr_tab); i++)
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combobox_nb_itr), nb_itr_tab[i]);
        
    for (i = 0; i < G_N_ELEMENTS (g_area_tab); i++)
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combobox_g_area), g_area_tab[i]);

    /* Choose to set the first row as the active one by default, from the beginning */
    gtk_combo_box_set_active (GTK_COMBO_BOX (combobox_period), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX (combobox_nb_itr), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX (combobox_g_area), 0);
    
    
   
   

    label_messages = GTK_WIDGET(gtk_builder_get_object(builder, "label_messages"));
    
    label_neighbors = GTK_WIDGET(gtk_builder_get_object(builder, "label_neighbors"));
    
    label_nodeid = GTK_WIDGET(gtk_builder_get_object(builder, "label_nodeid"));
    
    label_id = GTK_WIDGET(gtk_builder_get_object(builder, "label_id"));
    
    label_offset = GTK_WIDGET(gtk_builder_get_object(builder, "label_offset"));

	gtk_label_set_text(GTK_LABEL(label_messages), "covCrav v2.5");
   

	g_object_unref (builder);
	return window;
}


void init_services(void)
{
    system("exec /home/covcrav/phyCar/src/itsnet/extra/do_ocb.sh");
    system("touch /tmp/INDOOR");
    system("touch /tmp/OCB");
    system("systemctl restart wireless-adhoc");
    system("gpsctl -b 115200 /dev/ttyUSB0");
    system("systemctl restart gpsd");
    system("stty -F /dev/ttyUSB0 ispeed 115200 ospeed 115200");
    system("systemctl restart ntpd");
    system("systemctl restart itsnet");
    system("systemctl stop position-sensor");
    system("systemctl restart gps-data-sender");
}