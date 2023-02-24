/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2021 Anouar Chemek <anouarchemek@esprit.tn>
 * 
 * coVcrav is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * coVcrav is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <gtk/gtk.h>


#include <glib/gi18n.h>


#include "rhw.h"



Mix_Chunk* welcome;
Mix_Chunk* bip;


Mix_Chunk* fog_sent;
Mix_Chunk* rain_sent;
Mix_Chunk* wind_sent;
Mix_Chunk* storm_sent;
Mix_Chunk* tornado_sent;

Mix_Chunk* fog_recv;
Mix_Chunk* rain_recv;
Mix_Chunk* wind_recv;
Mix_Chunk* storm_recv;
Mix_Chunk* tornado_recv;

/* Signal handlers */
/* Note: These may not be declared static because signal autoconnection
 * only works with non-static methods
 */



int
main (int argc, char *argv[])
{
 	GtkWidget *window;
	GThread* covcrav_listener;
    GThread* covcrav_loc_disp;
    GThread* covcrav_mes_upd;
    GThread* covcrav_off_upd;

#ifdef ENABLE_NLS

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	
	gtk_init (&argc, &argv);
	  /* SDL AUDIO init */
    SDL_Init(SDL_INIT_AUDIO);
    if(Mix_OpenAudio(24000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        printf("%s", SDL_GetError());

    Mix_AllocateChannels(16);
    Mix_Volume(10, MIX_MAX_VOLUME / 2);

    /*loading sounds */
    welcome = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/welcome_covcrav.wav");
    bip = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/bip.wav");
    
    rain_sent = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/rain_sent.wav");
    wind_sent = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/wind_sent.wav");
    fog_sent = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/fog_sent.wav");
    storm_sent = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/storm_sent.wav");
    storm_sent = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/tornado_sent.wav");

    rain_recv = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/rain_recv.wav");
    wind_recv = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/wind_recv.wav");
    fog_recv = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/fog_recv.wav");
    storm_recv = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/storm_recv.wav");
    storm_recv = Mix_LoadWAV("/usr/share/covcrav_rhw/sounds/tornado_recv.wav");
    
   
	 /* playing welcome sound */
    /*Mix_VolumeChunk(welcome, MIX_MAX_VOLUME);
    Mix_PlayChannel(10, welcome, 0);*/
    init_services();
    window = create_window();
	gtk_widget_show (window);

	 /* itsnet_app threads */

    covcrav_listener = g_thread_new("covcrav socket listener", (GThreadFunc)socket_listen, NULL);
    covcrav_loc_disp = g_thread_new("covcrav local display", (GThreadFunc)covcrav_local_display, NULL);
    covcrav_mes_upd = g_thread_new("covcrav local data update", (GThreadFunc)covcrav_message_updater, NULL);
    covcrav_off_upd = g_thread_new("covcrav local data update", (GThreadFunc)covcrav_offset_updater, NULL);

	gtk_main ();
    g_thread_join(covcrav_listener);
    g_thread_join(covcrav_loc_disp);
    g_thread_join(covcrav_mes_upd);
    g_thread_join(covcrav_off_upd);


	g_free (priv);
	Mix_CloseAudio();
	
    Mix_FreeChunk(welcome);
    Mix_FreeChunk(rain_recv);
    Mix_FreeChunk(wind_recv);
    Mix_FreeChunk(fog_recv);

    Mix_FreeChunk(rain_sent);
    Mix_FreeChunk(wind_sent);
    Mix_FreeChunk(fog_sent);


	g_free(window);
    

	return 0;
}

