/***************************************************************************
 *            covcrav_denm.c
 *
 *  mer. janvier 27 12:44:11 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_denm.c
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
#include "denm.h"

extern itsnet_position_vector pos_vector;

extern u_int16_t period;
static char file_name_emit[32];
static char file_name_recv[32];

int ID_EMIT = 0;
/* TODO
 * Figure 7: Originating ITS-S activity diagram: appDENM_trigger request
 * Final draft ETSI EN 302 637-3 V1.2.1 (2014-09
 * */
denm_t* encode_denm(int signal)
{
    static struct ntptimeval probe_emit;
    denm_t* new_denm = (denm_t*)malloc(sizeof(denm_t));
    ID_EMIT++; /*sequence number generation TODO*/
    ntp_gettime(&probe_emit);

    /* management container encoding */
    new_denm->management.action_id.originating_station_id = pos_vector.node_id;
    new_denm->management.action_id.sequence_number = ID_EMIT;
    new_denm->management.station_type = station_type_passengerCar;
    new_denm->management.detection_time = timeval_to_ms(&probe_emit); /* detection time of the event */
    new_denm->management.reference_time = timeval_to_ms(&probe_emit); /* the most recent value of received DENMs of the same actionID*/
    new_denm->management.event_position = pos_vector;
    new_denm->management.relevance_traffic_direction = relevance_traffic_direction_allTrafficDirections;
    // new_denm->management.termination=1; // For the application request type AppDENM_trigger, the termination DE shall
    // not be included in DENM.
    new_denm->management.transmission_interval = htons(period); /* every 100 ms */
    new_denm->management.relevance_distance = relevance_distance_lessThan500m;
    new_denm->management.validity_duration = 600; /*the default offset of 600 s starting from the detectionTime*/
    /* situation container -----> depends on callbacks signal*/
    new_denm->situation.information_quality = information_quality_highest;
    /*new_denm->situation.event_history = NULL;
    new_denm->situation.linked_cause = NULL;*/
    switch(signal) {
    case FOG_SIGNAL:

        new_denm->situation.event_type.causeCode = cause_code_type_adverseWeatherCondition_Visibility;
        new_denm->situation.event_type.sub_causeCode = adverse_weather_condition_VisibilitySubCauseCode_fog;
        break;

    case RAIN_SIGNAL:
        new_denm->situation.event_type.causeCode = cause_code_type_adverseWeatherCondition_Precipitation;
        new_denm->situation.event_type.sub_causeCode = adverse_weather_condition_PrecipitationSubCauseCode_heavyRain;
        break;

    case WIND_SIGNAL:
        new_denm->situation.event_type.causeCode = cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition;
        new_denm->situation.event_type.sub_causeCode =
            adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_strongWinds;
        break;
    case STORM_SIGNAL:
        new_denm->situation.event_type.causeCode = cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition;
        new_denm->situation.event_type.sub_causeCode =
            adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_thunderstorm;

    case TORNADO_SIGNAL:
        new_denm->situation.event_type.causeCode = cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition;
        new_denm->situation.event_type.sub_causeCode =
            adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_tornado;
        trace_sent_denm(new_denm, probe_emit);
    }

    /* location container */
    new_denm->location.event_speed.speed_value = pos_vector.speed;
    new_denm->location.event_speed.speed_confidence = speed_confidence_equalOrWithinOneMeterPerSec;
    new_denm->location.event_position_heading.heading_value = pos_vector.heading;
    new_denm->location.event_position_heading.heading_confidence = heading_confidence_equalOrWithinOneDegree;
    new_denm->location.roadType = road_type_urban_no_structural_separation_to_opposite_lanes;
    /* alacarte container */

    return new_denm;
}
void decode_denm(denm_t* payload, int* weather, int* seq_nb)
{
    /* If expiration time of timer T_O_Validity is in the past, send a failure notification to the ITS-S application and
     * omit the execution of further steps.*/
    static struct ntptimeval probe_recv;
    ntp_gettime(&probe_recv);

    // if(payload->management.validity_duration * 1000 >=
    // (timeval_to_ms(&probe_recv)-payload->management.detection_time)){
    if(payload->situation.event_type.causeCode == cause_code_type_adverseWeatherCondition_Visibility &&
        payload->situation.event_type.sub_causeCode == adverse_weather_condition_VisibilitySubCauseCode_fog)
        *weather = 1;
    if(payload->situation.event_type.causeCode == cause_code_type_adverseWeatherCondition_Precipitation &&
        payload->situation.event_type.sub_causeCode == adverse_weather_condition_PrecipitationSubCauseCode_heavyRain)
        *weather = 2;
    if(payload->situation.event_type.causeCode == cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition &&
        payload->situation.event_type.sub_causeCode ==
            adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_strongWinds)
        *weather = 3;
    if(payload->situation.event_type.causeCode == cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition &&
        payload->situation.event_type.sub_causeCode ==
            adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_thunderstorm)
        *weather = 4;
    if(payload->situation.event_type.causeCode == cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition &&
        payload->situation.event_type.sub_causeCode ==
            adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_tornado) {
        *weather = 5;
        trace_recv_denm(payload, probe_recv);
    }

    *seq_nb = payload->management.action_id.sequence_number;

    //}
}

DENM_t* denm_transmission_management(denm_t* payload) /* TODO: implement inside a separate management UNIT */
{
    DENM_t* its_packet;
    its_pdu_header_t* its_app_header;

    its_packet = (DENM_t*)malloc(sizeof(DENM_t));
    its_app_header = (its_pdu_header_t*)malloc(sizeof(its_pdu_header_t));

    /* construct pdu header */
    its_app_header->message_id = message_id_denm;
    its_app_header->protocol_version = protocol_version_current_version;
    its_app_header->station_id = pos_vector.node_id;
    /* construct message payload to the itsnet layer*/
    memcpy((void*)&its_packet->header, (void*)its_app_header, sizeof(its_pdu_header_t));
    memcpy((void*)&its_packet->payload, (void*)payload, sizeof(denm_t));

    free(its_app_header);
    return its_packet;
}
denm_t* denm_reception_management(DENM_t* packet) /* TODO: implement inside a separate management UNIT */
{
    its_pdu_header_t* its_app_header;
    denm_t* denm_payload;
    denm_payload = (denm_t*)malloc(sizeof(denm_t));
    its_app_header = (its_pdu_header_t*)malloc(sizeof(its_pdu_header_t));

    memcpy((void*)its_app_header, (void*)&packet->header, sizeof(its_pdu_header_t));
    if(its_app_header->message_id == message_id_denm) /* TODO: switch message_id in a separate management UNIT */
        memcpy((void*)denm_payload, (void*)&packet->payload, sizeof(denm_t));

    free(packet);
    free(its_app_header);
    return denm_payload;
}

void trace_recv_denm(denm_t* payload, struct ntptimeval t_recv)
{
  
    static FILE* f_recv;
    static char buff[64];
    static int period;
    static itsnet_node_id node_id;
    static int seq_nb;
	long offset;
    seq_nb = payload->management.action_id.sequence_number;
    node_id = payload->management.action_id.originating_station_id;
    period = ntohs(payload->management.transmission_interval);
    sprintf(buff, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", (node_id.id[0] & 0xFF), (node_id.id[1] & 0xFF),
        (node_id.id[2] & 0xFF), (node_id.id[3] & 0xFF), (node_id.id[4] & 0xFF), (node_id.id[5] & 0xFF),
        (node_id.id[6] & 0xFF), (node_id.id[7] & 0xFF));
    if(access("/tmp/OCB", F_OK) != -1)
        sprintf(file_name_recv, "%s_%s_%d.%s", "/root/recv", "OCB", period, "log");
    else
        sprintf(file_name_recv, "%s_%s_%d.%s", "/root/recv", "IBSS", period, "log");

    f_recv = fopen(file_name_recv, "a");
    /*sync=covcrav_get_sync_status(t_recv);*/
	offset=covcrav_get_offset_value(t_recv);
	
    fprintf(f_recv, "NODE_ID_ORIG %s SEQ_NUMBER %d TIME_RECV %lld OFFSET %ld PERIOD %d\n", buff, seq_nb,
        timeval_to_us(&t_recv), offset, period);
	
    fclose(f_recv);
}

void trace_sent_denm(denm_t* payload,struct ntptimeval t_emit)
{
    static FILE* f_emit;
    static char buff[64];
    static itsnet_node_id node_id;
    static int seq_nb;
	long offset;
    seq_nb = payload->management.action_id.sequence_number;
    node_id = payload->management.action_id.originating_station_id;
    sprintf(buff, "%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x", (node_id.id[0] & 0xFF), (node_id.id[1] & 0xFF),
        (node_id.id[2] & 0xFF), (node_id.id[3] & 0xFF), (node_id.id[4] & 0xFF), (node_id.id[5] & 0xFF),
        (node_id.id[6] & 0xFF), (node_id.id[7] & 0xFF));
    if(access("/tmp/OCB", F_OK) != -1)
        sprintf(file_name_emit, "%s_%s_%d.%s", "/root/emit", "OCB", period, "log");
    else
        sprintf(file_name_emit, "%s_%s_%d.%s", "/root/emit", "IBSS", period, "log");
    f_emit = fopen(file_name_emit, "a");

	offset=covcrav_get_offset_value(t_emit);  
    
    fprintf(f_emit, "NODE_ID_ORIG %s SEQ_NUMBER %d TIME_EMIT %lld OFFSET %ld PERIOD %d\n", buff, seq_nb,timeval_to_us(&t_emit),offset, period);
	
    fclose(f_emit);
}
