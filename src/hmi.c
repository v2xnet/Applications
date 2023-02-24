/***************************************************************************
 *            covcrav_hmi.c
 *
 *  mer. janvier 20 12:29:42 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_hmi.c
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

#include "hmi.h"

extern GObject* label_messages;
extern GObject* label_neighbors;
extern GObject* label_nodeid;

extern GObject* gps;
extern GObject* connected;
extern GObject* sync_;

extern GObject* label_id;
extern GObject* label_offset;

extern struct itsnet_position_vector pos_vector;
extern long offset_display;

static char buff_node_id[20];
static char buff_id[8];
extern char buff_neighbors[128];
extern bool gps_status;
extern bool con_status;
extern bool sync_status;

extern char signal_level[8];
extern char signal_quality[8];

extern int weather;
extern int ID_RECV;

static struct itsnet_node_id ego_node_id;

void print_node_id(struct itsnet_node_id node_id)
{
    printf("%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x ", (node_id.id[0] & 0xFF), (node_id.id[1] & 0xFF),
        (node_id.id[2] & 0xFF), (node_id.id[3] & 0xFF), (node_id.id[4] & 0xFF), (node_id.id[5] & 0xFF),
        (node_id.id[6] & 0xFF), (node_id.id[7] & 0xFF));
}
/*
 * display local data :
 * - nodeId
 * - status(ready or not) dependly of services (gpsd, gpsd-fix,
 * itsnet, wireless-adhoc and gps-data-sender or position-sensor
 * - clock offset
 * - neighbors
 * */

void* covcrav_local_display(void* arg)
{

    // gchar* buff = (gchar*)malloc(DISP_BUFF_SIZE * sizeof(gchar));
    /*
     * display Testbed Config
     * */
    char buff[16];

    while(1) {

        /*
         * show status : ready(green) ; not ready : nothing
         * */

        /*
         * display egoNodeId
         * */

        ego_node_id = pos_vector.node_id;
        g_snprintf(buff_node_id, 20, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", (ego_node_id.id[0] & 0xFF),
            (ego_node_id.id[1] & 0xFF), (ego_node_id.id[2] & 0xFF), (ego_node_id.id[3] & 0xFF),
            (ego_node_id.id[4] & 0xFF), (ego_node_id.id[5] & 0xFF), (ego_node_id.id[6] & 0xFF),
            (ego_node_id.id[7] & 0xFF));

        gtk_label_set_text(GTK_LABEL(label_nodeid), buff_node_id);

        /*
         * display clock offset to the gps clock (ms)
         * */
        if(offset_display != 16000000)
            g_snprintf(buff, 16, "%ld %s", offset_display,"µs");
        else
            g_snprintf(buff, 16, "%s", "NO_SYNC");

        gtk_label_set_text(GTK_LABEL(label_offset), buff);

        if(gps_status == true)
            gtk_widget_show(GTK_WIDGET(gps));
        else
            gtk_widget_hide(GTK_WIDGET(gps));

        if(con_status == true)
            gtk_widget_show(GTK_WIDGET(connected));
        else
            gtk_widget_hide(GTK_WIDGET(connected));

        if(sync_status == true)
            gtk_widget_show(GTK_WIDGET(sync_));
        else
            gtk_widget_hide(GTK_WIDGET(sync_));

        /*gtk_widget_show(GTK_WIDGET(gps));
        gtk_widget_show(GTK_WIDGET(connected));
        gtk_widget_show(GTK_WIDGET(sync_));*/

        /*
         * display wireless signal level
         * */
        // g_snprintf(buff,16,"Level:%s", signal_level);
        // gtk_label_set_text(GTK_LABEL(label_level), signal_level);

        /*
         * display Signal Quality
         * */
        // g_snprintf(buff,16,"Qual:%s dbm", signal_quality);
        // gtk_label_set_text(GTK_LABEL(label_qos), signal_quality);

        /* display neighbors stations
         *
         * */

        // g_strlcpy(buff, buff_neighbors,64);
        gtk_label_set_text(GTK_LABEL(label_neighbors), buff_neighbors);

        /*
         * display ID message
         * */
        if(ID_RECV != -1) {
            g_snprintf(buff_id, 8, "%d", ID_RECV);
            gtk_label_set_text(GTK_LABEL(label_id), buff_id);
        }
        /*
         * display weather message
         * */
        // g_mutex_lock(&mutex);
        switch(weather) {
        case 1:
            // g_strlcpy(buff,"FOG AREA",10);
            gtk_label_set_text(GTK_LABEL(label_messages), "FOG AREA");
            break;
        case 2:
            // g_strlcpy(buff, "RAIN AREA",10);
            gtk_label_set_text(GTK_LABEL(label_messages), "RAIN AREA");
            break;
        case 3:

            gtk_label_set_text(GTK_LABEL(label_messages), "WIND AREA");
            break;
        case 4:

            gtk_label_set_text(GTK_LABEL(label_messages), "STORM AREA");
            break;
        case 5:

            gtk_label_set_text(GTK_LABEL(label_messages), "TORNADO AREA");
        }
        weather = -1;
        usleep(500000);
    }
    /*if(buff != NULL)
        free(buff);*/
}
