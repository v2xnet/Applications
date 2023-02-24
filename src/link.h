/***************************************************************************
 *            covcrav_link.h
 *
 *  mer. janvier 20 12:40:19 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_link.h
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
 * @file covcrav_link.h
 * itsnet_app API link with itsnet daemon.
 * @author hichem BARGAOUI
 * @author anouar CHEMEK
 */
#ifndef __LINK_H_
#define __LINK_H_

#include "hmi.h"
#include "denm.h"
#define SOCK_PATH "/tmp/upper_layer_socket"
#define SOCK_ITSNET_PATH "/tmp/itsnet_socket"

int send_socket(message* m);
int itsnet_configure_node_id_request_send(struct message* m);
int itsnet_configure_node_id_confirm_receive(struct message* m);
int itsnet_get_node_id_request_send(struct message* m);
int itsnet_get_node_id_confirm_receive(struct message* m);
int itsnet_get_neighbor_list_request_send(struct message* m);
int itsnet_get_neighbor_list_confirm_reveive(struct message* m);
int itsnet_event_indication_receive(struct message* m);
int itsnet_position_sensor_request_receive(struct message* m);
itsnet_position_vector itsnet_get_position_vector_confirm_receive(struct message* m);
void itsnet_unicast_indication_receive(struct message* m);
void itsnet_geoanycast_indication_receive(struct message* m);
void itsnet_geobroadcast_indication_receive(struct message* m);
void socket_recv(struct message* m);
int itsnet_get_position_vector_request_send(struct message* m);
int itsnet_unicast_request_send(struct message* m);
int itsnet_position_sensor_request_send(struct message* m);
int itsnet_geoanycast_request_send(struct message* m);
int itsnet_geobroadcast_request_send(struct message* m,DENM_t* its_denm_packet);
int itsnet_get_security_param_request_send(struct message* m);
int itsnet_configure_security_param_request_send(struct message* m);
int server(int client_socket);
void* socket_listen(void* arg);
void* covcrav_message_updater(void* arg);
void* covcrav_offset_updater(void* arg);

#endif
