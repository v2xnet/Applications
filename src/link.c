/***************************************************************************
 *            covcrav_link.c
 *
 *  mer. janvier 20 12:40:19 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_link.c
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

#include "link.h"
#include "denm.h"
#include "util.h"
#include <stdbool.h>

// struct itsnet_node_id node_id;
struct itsnet_position_vector pos_vector;
int nbr_neighbors=0;


bool gps_status = false;
bool con_status = false;
bool sync_status = false;

extern int sound;
extern double GEO_AREA;

extern Mix_Chunk* fog_recv;
extern Mix_Chunk* rain_recv;
extern Mix_Chunk* wind_recv;
extern Mix_Chunk* storm_recv;
extern Mix_Chunk* tornado_recv;

extern Mix_Chunk* bip;

char buff_neighbors[128];

int ID_RECV = -1;
int weather = -1;


long offset_display=0;


static int sock;

int send_socket(message* m)
{
    int length, len;
    struct sockaddr_un client_sockaddr;

    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sock == -1) {
        perror("socket");
        return 1;
    }

    memset(&client_sockaddr, 0, sizeof(struct sockaddr_un));
    client_sockaddr.sun_family = AF_UNIX;
    strcpy(client_sockaddr.sun_path, SOCK_ITSNET_PATH);

    len = sizeof(struct sockaddr_un);
    length = sizeof(struct message);

    sendto(sock, m, length, 0, (struct sockaddr*)&client_sockaddr, len);

    close(sock);

    return 0;
}

int itsnet_configure_node_id_request_send(struct message* m)
{
    int result;
    memset(m, 0, sizeof(message));
    m->msg_hdr.sid = itsnet_management_sap;
    m->msg_hdr.opcode = itsnet_confirm;
    m->msg_hdr.aid = itsnet_configure_node_id;
    result = send_socket(m);
    return result;
}

int itsnet_configure_node_id_confirm_receive(struct message* m)
{
    int result;
    result = 1;
    printf("The Old NodeId is :");
    print_node_id(m->payload.itsnet_configure_node_id_conf.old_id);
    printf("The New NodeId Configured : ");
    print_node_id(m->payload.itsnet_configure_node_id_conf.new_id);
    return result;
}

int itsnet_get_node_id_request_send(struct message* m)
{
    int result;
    memset(m, 0, sizeof(message));
    m->msg_hdr.aid = itsnet_get_node_id;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.sid = itsnet_management_sap;
    m->payload.itsnet_get_node_id_req.tmp = 1;
    result = send_socket(m);
    return result;
}

int itsnet_get_node_id_confirm_receive(struct message* m)
{
    print_node_id(m->payload.itsnet_get_node_id_conf.node_id);
    return 0;
}

int itsnet_get_neighbor_list_request_send(struct message* m)
{
    int result;
    m->msg_hdr.aid = itsnet_get_neighbor_list;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.sid = itsnet_management_sap;
    m->payload.itsnet_get_neighbor_list_req.tmp = 1;
    result = send_socket(m);
    return result;
}

int itsnet_get_neighbor_list_confirm_reveive(struct message* m)
{
    int result, i;
    
    result = 1;
    Uint32 lat1, long1, lat2, long2;
    double distance;
    char buff_old[32] = "";

    struct itsnet_node_id node_id;
    nbr_neighbors = m->payload.itsnet_get_neighbor_list_conf.neighbor_list_size;

    memset(buff_neighbors, 0, 128);
    lat1 = pos_vector.latitude;
    long1 = pos_vector.longitude;
    for(i = 0; i < nbr_neighbors; i++) {

        memset(buff_old, 0, 32);

        lat2 = m->payload.itsnet_get_neighbor_list_conf.neighbor_list_pos[i].latitude;
        long2 = m->payload.itsnet_get_neighbor_list_conf.neighbor_list_pos[i].longitude;
        distance = 1000 * haversine_distance(lat1, long1, lat2, long2);
        /**
         * display only cars belong to the geo area zone
         * */
        if(distance <= GEO_AREA) {
            node_id = m->payload.itsnet_get_neighbor_list_conf.neighbor_list_pos[i].node_id;

            sprintf(buff_old, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x~%.1lfm\n", (node_id.id[0] & 0xFF),
                (node_id.id[1] & 0xFF), (node_id.id[2] & 0xFF), (node_id.id[3] & 0xFF), (node_id.id[4] & 0xFF),
                (node_id.id[5] & 0xFF), (node_id.id[6] & 0xFF), (node_id.id[7] & 0xFF), distance);
            // printf("%s",buff_old);
            strcat(buff_neighbors, buff_old);
        }
    }

    return result;
}

int itsnet_event_indication_receive(struct message* m)
{

    switch(m->payload.itsnet_event_ind.event.type) {

    case itsnet_new_neighbor:
        printf("New Neighbor is added \n");
        printf("Node Identity :");
        print_node_id(m->payload.itsnet_event_ind.event.event.new_neighbor.node_id);
        printf("Node Latitude : %d \n", m->payload.itsnet_event_ind.event.event.new_neighbor.latitude);
        /*printf("Node Altitude : %d \n", m->payload.itsnet_event_ind.event.event.new_neighbor.altitude);*/
        printf("Node Speed : %d \n", m->payload.itsnet_event_ind.event.event.new_neighbor.speed);
        printf("Node Timestamp : %d \n", m->payload.itsnet_event_ind.event.event.new_neighbor.time_stamp);

        if(sound) {
            Mix_VolumeChunk(bip, MIX_MAX_VOLUME);
            Mix_PlayChannel(11, bip, 0);
        }
        break;
    case itsnet_other_event:
        printf("Other Event \n");
        break;
    default:
        printf("unknown type\n");
        break;
    }

    return 0;
}

int itsnet_position_sensor_request_receive(struct message* m)
{
    /*TODO*/

    return 0;
}

itsnet_position_vector itsnet_get_position_vector_confirm_receive(struct message* m)
{
    struct itsnet_position_vector result;
    result = m->payload.itsnet_get_position_vector_conf.position_vector;
    return (result);
}

void itsnet_unicast_indication_receive(struct message* m)
{
    printf("GeoUnicast Message is Received \n");
    printf("DATA %s: \n", m->payload.itsnet_unicast_ind.data);
    printf("from Node ID: ");
    print_node_id(m->payload.itsnet_unicast_ind.source_node_id);
}

void itsnet_geoanycast_indication_receive(struct message* m)
{

    printf("GeoAnycast Message is Received \n");
    printf("DATA %s: \n", m->payload.itsnet_geoanycast_ind.data);
    printf("from Node ID:");
    print_node_id(m->payload.itsnet_geoanycast_ind.source_node_id);
}
void itsnet_geobroadcast_indication_receive(struct message* m)
{
    struct itsnet_position_vector pos_fwd_vector;
    struct itsnet_position_vector pos_src_vector;

    struct itsnet_node_id src_node_id;
    struct itsnet_node_id fwd_node_id;
    struct itsnet_node_id ego_node_id;

    char s_node_id[64];
    char e_node_id[64];
    char f_node_id[64];

    DENM_t* ITS_packet;
    denm_t* denm_payload;

    ITS_packet = malloc(sizeof(DENM_t));

    pos_fwd_vector = m->payload.itsnet_geobroadcast_ind.forwarder_node_pos;
    pos_src_vector = m->payload.itsnet_geobroadcast_ind.source_node_pos;

    src_node_id = pos_src_vector.node_id;
    fwd_node_id = pos_fwd_vector.node_id;
    ego_node_id = pos_vector.node_id;

    sprintf(e_node_id, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", (ego_node_id.id[0] & 0xFF),
        (ego_node_id.id[1] & 0xFF), (ego_node_id.id[2] & 0xFF), (ego_node_id.id[3] & 0xFF), (ego_node_id.id[4] & 0xFF),
        (ego_node_id.id[5] & 0xFF), (ego_node_id.id[6] & 0xFF), (ego_node_id.id[7] & 0xFF));

    sprintf(s_node_id, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", (src_node_id.id[0] & 0xFF),
        (src_node_id.id[1] & 0xFF), (src_node_id.id[2] & 0xFF), (src_node_id.id[3] & 0xFF), (src_node_id.id[4] & 0xFF),
        (src_node_id.id[5] & 0xFF), (src_node_id.id[6] & 0xFF), (src_node_id.id[7] & 0xFF));

    sprintf(f_node_id, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", (fwd_node_id.id[0] & 0xFF),
        (fwd_node_id.id[1] & 0xFF), (fwd_node_id.id[2] & 0xFF), (fwd_node_id.id[3] & 0xFF), (fwd_node_id.id[4] & 0xFF),
        (fwd_node_id.id[5] & 0xFF), (fwd_node_id.id[6] & 0xFF), (fwd_node_id.id[7] & 0xFF));

    /* ITS payload received */
    memcpy((void*)ITS_packet, (void*)m->payload.itsnet_geobroadcast_ind.data, sizeof(DENM_t));
    denm_payload = denm_reception_management(ITS_packet);
    decode_denm(denm_payload, &weather, &ID_RECV);

    switch(weather) {
    case FOG_SIGNAL:
        if(sound) {
            Mix_VolumeChunk(fog_recv, MIX_MAX_VOLUME);
            Mix_PlayChannel(6, fog_recv, 0);
        }

        break;
    case RAIN_SIGNAL:
        if(sound) {
            Mix_VolumeChunk(rain_recv, MIX_MAX_VOLUME);
            Mix_PlayChannel(7, rain_recv, 0);
        }
        break;

    case WIND_SIGNAL:
        if(sound) {
            Mix_VolumeChunk(wind_recv, MIX_MAX_VOLUME);
            Mix_PlayChannel(8, wind_recv, 0);
        }
        break;
    case STORM_SIGNAL:
        if(sound) {
            Mix_VolumeChunk(storm_recv, MIX_MAX_VOLUME);
            Mix_PlayChannel(9, storm_recv, 0);
        }
        break;
    case TORNADO_SIGNAL:

        break;
    }

    free(denm_payload);
}

void socket_recv(struct message* m)
{
    switch(m->msg_hdr.aid) {
    case itsnet_unicast:
        itsnet_unicast_indication_receive(m);
        break;
    case itsnet_geoanycast:
        itsnet_geoanycast_indication_receive(m);
        break;
    case itsnet_geobroadcast:
        itsnet_geobroadcast_indication_receive(m);
        break;
    case itsnet_configure_node_id:
        itsnet_configure_node_id_confirm_receive(m);
        break;
    case itsnet_get_node_id:
        itsnet_get_node_id_confirm_receive(m);
        break;
    case itsnet_get_position_vector:
        pos_vector = itsnet_get_position_vector_confirm_receive(m);
        break;
    case itsnet_events:
        itsnet_event_indication_receive(m);
        break;
    case itsnet_position_sensor:
        itsnet_position_sensor_request_receive(m);
    case itsnet_get_neighbor_list:
        itsnet_get_neighbor_list_confirm_reveive(m);
        break;
    default:
        printf("unknown type\n");
        break;
    }
    free(m);
}

int itsnet_get_position_vector_request_send(struct message* m)
{
    int result;
    m->msg_hdr.sid = itsnet_management_sap;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.aid = itsnet_get_position_vector;
    result = send_socket(m);
    return (result);
}

int itsnet_unicast_request_send(struct message* m)
{
    int result;
    memset(m, 0, sizeof(message));
    m->msg_hdr.sid = itsnet_transport_sap;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.aid = itsnet_unicast;
    strncpy(m->payload.itsnet_unicast_req.data, "test", 5);
    result = send_socket(m);
    return result;
}

int itsnet_position_sensor_request_send(struct message* m)
{
    int result;
    memset(m, 0, sizeof(message));
    m->msg_hdr.sid = itsnet_management_sap;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.aid = itsnet_position_sensor;
    result = send_socket(m);
    return result;
}

int itsnet_geoanycast_request_send(struct message* m)
{
    int result;

    m->msg_hdr.sid = itsnet_transport_sap;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.aid = itsnet_geoanycast;
    strncpy(m->payload.itsnet_geobroadcast_req.data, "TEST", 5);
    result = send_socket(m);
    return result;
}

int itsnet_geobroadcast_request_send(struct message* m, DENM_t* its_denm_packet)
{
    int result;

    m->msg_hdr.sid = itsnet_transport_sap;
    m->msg_hdr.opcode = itsnet_request;
    m->msg_hdr.aid = itsnet_geobroadcast;

    memcpy((void*)m->payload.itsnet_geobroadcast_req.data, (void*)its_denm_packet, sizeof(DENM_t));
    result = send_socket(m);
    free(its_denm_packet);
    return result;
}

int itsnet_get_security_param_request_send(struct message* m)
{

    /*TODO*/
    int result;
    memset(m, 0, sizeof(message));
    result = send_socket(m);
    return result;
}

int itsnet_configure_security_param_request_send(struct message* m)
{

    /*TODO*/
    int result;
    memset(m, 0, sizeof(message));
    result = send_socket(m);
    return result;
}

int server(int client_socket)
{

    struct message* msg;
    while(1) {

        msg = (struct message*)malloc(sizeof(message));
        memset(msg, 0, sizeof(message));
        recv(client_socket, msg, sizeof(message), 0);
        socket_recv(msg);
    }
    return 0;
}

/**
 * listener
 * @param void
 */
void* socket_listen(void* arg)
{
    int s, len;
    struct sockaddr_un local;

    if((s = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    len = sizeof(local);
    unlink(local.sun_path);

    if(bind(s, (struct sockaddr*)&local, len) == -1) {
        perror("bind");
        close(s);
        exit(1);
    }
    server(s);
    close(s);
    unlink(SOCK_PATH);
    return NULL;
}

void* covcrav_message_updater(void* arg)
{

    struct message* m;

    /**  Socket Send    */
    while(1) {
        /*
         * request position vector from itsnet layer
         * */
        m = (message*)malloc(sizeof(message));
        memset(m, 0, sizeof(message));
        itsnet_get_position_vector_request_send(m);

        /*
         * request neighbors nodes from itsnet layer
         * */

        usleep(1000000); // every 1s

        memset(m, 0, sizeof(message));
        itsnet_get_neighbor_list_request_send(m);

        free(m);
    }
}

void* covcrav_offset_updater(void* arg)
{

  struct ntptimeval t1;

    while(1) {

        gps_status = covcrav_get_gps_status();

        con_status = covcrav_get_connected_status();
        
        ntp_gettime(&t1);
        sync_status = covcrav_get_sync_status(t1);
        offset_display=covcrav_get_offset_value(t1);
        
        usleep(1000000); // every 1s
    }
}
