/***************************************************************************
 *            util.c
 *
 *  mar. mai 11 18:31:38 2021
 *  Copyright  2021  anouar chemek
 *  <user@host>
 ****************************************************************************/
/*
 * util.c
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
#include "util.h"

extern struct itsnet_position_vector pos_vector;
extern int nbr_neighbors;


/*
bool covcrav_get_connected_status(void)
{
    FILE* fp;
    char* status = malloc(10 * sizeof(char));
    fp = popen("systemctl status itsnet | grep 'active (running)' | cut -d: -f2 | cut -d'(' -f1", "r");
    if(fp != NULL) {
        fscanf(fp, "%s", status);
        pclose(fp);
    }
    if(!strcmp(status,"active"))
        return true;
    else
        return false;
         
} */


bool covcrav_get_gps_status(void)
{
   if(pos_vector.latitude)
       return true;
    return false;
        
}

bool covcrav_get_connected_status(void)
{

    if(nbr_neighbors)/* WHen neighborhood are detected, this mean all necessary services are loaded and actif */
        return true;
    return false;
        
}


bool covcrav_get_sync_status(struct ntptimeval tv)
{
    if(tv.esterror != 16000000)
        return true;
    return false;
}


long covcrav_get_offset_value(struct ntptimeval tv)
{
    return tv.esterror;
}


/*
char* covcrav_get_offset_value()
{
   FILE* fp;
    char* offset = malloc(32 * sizeof(char));
    fp = popen("/usr/sbin/ntpq -p | /usr/bin/grep '*SHM' | /usr/bin/awk '{ print $9 }'", "r");
    if(fp != NULL) {
        fscanf(fp,"%s", offset);
        pclose(fp);
    }

    return offset;
}
*/