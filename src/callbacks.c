/***************************************************************************
 *            covcrav_callbacks.c
 *
 *  mer. janvier 20 12:57:37 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_callbacks.c
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
 * @file covcrav_callbacks.c
 * Event slot from GUI
 * @author hichem BARGAOUI
 * @author anouar CHEMEK
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "callbacks.h"
#include "denm.h"
#include "link.h"
#include <SDL/SDL_mixer.h>
#include <arpa/inet.h>

static const char * period_tab[] = {"period", "500", "250", "100","75","50","25","15","10","5","2","1"};
static const char * nb_itr_tab[] = {"nbr iter", "1000", "500","250","100","50","20","10","5"};
static const char * g_area_tab[] = {"geo area", "500", "300", "200","100","75","50","25","10","5"};

extern Mix_Chunk* fog_sent;
extern Mix_Chunk* rain_sent;
extern Mix_Chunk* wind_sent;
extern Mix_Chunk* storm_sent;
extern Mix_Chunk* tornado_sent;

extern struct itsnet_position_vector pos_vector;

extern GtkWidget window;
/*extern GtkWidget* checkbutton1;
extern GtkWidget* checkbutton2;*/

extern gchar offset[20];
int sound = 0;

double GEO_AREA = 300;
uint16_t period = 500;
int nbr_packet = 1000;
static int count = 0;
// send a FOG warning

void on_button1_clicked(GtkButton* button, gpointer user_data)
{
    struct message* m;

    denm_t* denm_payload;
    DENM_t* its_denm_packet;
    count++;

    if(count % 2 == 0) {
        m = (message*)malloc(sizeof(message));
        memset(m, 0, sizeof(message));

        m->payload.itsnet_geobroadcast_req.geo_area.latitude = pos_vector.latitude;
        m->payload.itsnet_geobroadcast_req.geo_area.longitude = pos_vector.longitude;
        m->payload.itsnet_geobroadcast_req.geo_area.geo_area_size = GEO_AREA;

        denm_payload = encode_denm(FOG_SIGNAL);
        its_denm_packet = denm_transmission_management(denm_payload); // TODO: repetition

        itsnet_geobroadcast_request_send(m, its_denm_packet);
        if(sound) {
            Mix_VolumeChunk(fog_sent, MIX_MAX_VOLUME);
            Mix_PlayChannel(FOG_SIGNAL, fog_sent, 0);
        }
        free(m);
        free(denm_payload);
    }
}
// send a rain warning

void on_button2_clicked(GtkButton* button, gpointer user_data)
{
    struct message* m;

    denm_t* denm_payload;
    DENM_t* its_denm_packet;
    count++;

    if(count % 2 == 0) {
        m = (message*)malloc(sizeof(message));
        memset(m, 0, sizeof(message));

        m->payload.itsnet_geobroadcast_req.geo_area.latitude = pos_vector.latitude;
        m->payload.itsnet_geobroadcast_req.geo_area.longitude = pos_vector.longitude;
        m->payload.itsnet_geobroadcast_req.geo_area.geo_area_size = GEO_AREA;

        denm_payload = encode_denm(RAIN_SIGNAL);
        its_denm_packet = denm_transmission_management(denm_payload); // TODO: repetition

        itsnet_geobroadcast_request_send(m, its_denm_packet);
        if(sound) {
            Mix_VolumeChunk(rain_sent, MIX_MAX_VOLUME);
            Mix_PlayChannel(RAIN_SIGNAL, rain_sent, 0);
        }
        free(m);
        free(denm_payload);
    }
}
// send a strong wind warning

void on_button3_clicked(GtkButton* button, gpointer user_data)
{
    struct message* m;

    denm_t* denm_payload;
    DENM_t* its_denm_packet;

    count++;
    if(count % 2 == 0) {
        m = (message*)malloc(sizeof(message));
        memset(m, 0, sizeof(message));

        m->payload.itsnet_geobroadcast_req.geo_area.latitude = pos_vector.latitude;
        m->payload.itsnet_geobroadcast_req.geo_area.longitude = pos_vector.longitude;
        m->payload.itsnet_geobroadcast_req.geo_area.geo_area_size = GEO_AREA;

        denm_payload = encode_denm(WIND_SIGNAL);
        its_denm_packet = denm_transmission_management(denm_payload); // TODO: repetition

        itsnet_geobroadcast_request_send(m, its_denm_packet);
        if(sound) {
            Mix_VolumeChunk(wind_sent, MIX_MAX_VOLUME);
            Mix_PlayChannel(WIND_SIGNAL, wind_sent, 0);
        }
        free(m);
        free(denm_payload);
    }
}
// send a storm warning

void on_button4_clicked(GtkButton* button, gpointer user_data)
{
    struct message* m;

    denm_t* denm_payload;
    DENM_t* its_denm_packet;
    count++;

    if(count % 2 == 0) {
        m = (message*)malloc(sizeof(message));
        memset(m, 0, sizeof(message));

        m->payload.itsnet_geobroadcast_req.geo_area.latitude = pos_vector.latitude;
        m->payload.itsnet_geobroadcast_req.geo_area.longitude = pos_vector.longitude;
        m->payload.itsnet_geobroadcast_req.geo_area.geo_area_size = GEO_AREA;

        denm_payload = encode_denm(STORM_SIGNAL);
        its_denm_packet = denm_transmission_management(denm_payload); // TODO: repetition

        itsnet_geobroadcast_request_send(m, its_denm_packet);
        if(sound) {
            Mix_VolumeChunk(storm_sent, MIX_MAX_VOLUME);
            Mix_PlayChannel(STORM_SIGNAL, storm_sent, 0);
        }
        free(m);
        free(denm_payload);
    }
}

// send a tornado warning ( TESTBED )
void on_button_test_clicked(GtkButton* button, gpointer user_data)
{
    /* TODO: denm packet repetition must be done by the use of yhe management denm transmission */
    int i;
    struct message* m;

    denm_t* denm_payload;
    DENM_t* its_denm_packet;
    count++;

    if(count % 2 == 0) {
        m = (message*)malloc(sizeof(message));
        memset(m, 0, sizeof(message));

        m->payload.itsnet_geobroadcast_req.geo_area.latitude = pos_vector.latitude;
        m->payload.itsnet_geobroadcast_req.geo_area.longitude = pos_vector.longitude;
        m->payload.itsnet_geobroadcast_req.geo_area.geo_area_size = GEO_AREA;

        if(sound) {
            Mix_VolumeChunk(tornado_sent, MIX_MAX_VOLUME);
            Mix_PlayChannel(TORNADO_SIGNAL, tornado_sent, 0);
        }

        for(i = 0; i < nbr_packet; i++) {
            denm_payload = encode_denm(TORNADO_SIGNAL);
            its_denm_packet = denm_transmission_management(denm_payload); // TODO: repetition
            itsnet_geobroadcast_request_send(m, its_denm_packet);
            usleep(period * 1000);
            free(denm_payload);
        }

        free(m);
    }
}

void on_button_off_clicked(GtkButton* button, gpointer user_data)
{
    system("sync");
    system("systemctl halt");
}

void on_button_reset_clicked(GtkButton* button, gpointer user_data)
{
    system("systemctl restart wireless-adhoc");
    
    system("gpsctl -b 115200 /dev/ttyUSB0");
    
    system("systemctl restart itsnet");
    if(access("/tmp/INDOOR", F_OK) == -1) {
        system("systemctl restart position-sensor");
    } else {
         system("systemctl restart gps-data-sender");
    }

    sleep(3);
    system("systemctl restart ntpd");
    system("systemctl restart gpsd");
    system("stty -F /dev/ttyUSB0 ispeed 115200 ospeed 115200");
}

void on_checkbutton1_toggled(GtkToggleButton* togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(togglebutton))
        sound = 1;
    else
        sound = 0;
}

void on_checkbutton2_toggled(GtkToggleButton* togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)){
        system("exec /home/covcrav/phyCar/src/itsnet/extra/do_ocb.sh");
        system("touch /tmp/OCB");
    }else{
        system("exec /home/covcrav/phyCar/src/itsnet/extra/do_ibss.sh");
        system("rm -f /tmp/OCB");
    }
    system("systemctl restart wireless-adhoc");
    system("systemctl restart itsnet");
}

void on_checkbutton3_toggled(GtkToggleButton* togglebutton, gpointer user_data)
{
    if(gtk_toggle_button_get_active(togglebutton)){
        system("systemctl stop gps-data-sender");
        system("systemctl start position-sensor");
        system("rm -f /tmp/INDOOR");

    } else {
        system("systemctl stop position-sensor");
        system("systemctl start gps-data-sender");
        system("touch /tmp/INDOOR");
    }
    system("gpsctl -b 115200 /dev/ttyUSB0");
    /*system("systemctl restart gpsd");*/
    system("systemctl restart itsnet");
}

void on_combobox_period_changed(GtkComboBox* widget, gpointer user_data)
{
    int i;
    i = gtk_combo_box_get_active(widget);
    period = atoi(period_tab[i]);
}

void on_combobox_nb_itr_changed(GtkComboBox* widget, gpointer user_data)
{
    int i;
    i = gtk_combo_box_get_active(widget);
    nbr_packet = atoi(nb_itr_tab[i]);
}
void on_combobox_g_area_changed(GtkComboBox* widget, gpointer user_data)
{
    int i;
    i = gtk_combo_box_get_active(widget);
    // g_print("\nselected_g_area index:%d",i);
    GEO_AREA = atof(g_area_tab[i]);
    // g_print("\nselected_g_area is:%lf",GEO_AREA);
}
