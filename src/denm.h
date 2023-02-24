/***************************************************************************
 *            covcrav_denm.h
 *
 *  mer. janvier 27 00:47:22 2021
 *  Copyright  2021  Anouar Chemek
 *  <user@host>
 ****************************************************************************/
/*
 * covcrav_denm.h
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
#ifndef __COVCRAV_DENM_
#define __COVCRAV_DENM_

#include "itsnet_header.h"
#include "common.h"
#include "list.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/timex.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>




/* TODO Reimplement using the Draft ETSI EN 302 637-3 V1.3.0 (2018-08) */

typedef uint16_t transmission_interval_t;       /* transmission_interval */

typedef uint32_t validity_duration_t;           /* validity_duration */

typedef uint8_t termination_t;                  /* Termination */

typedef uint8_t station_type_t;                 /* station_type */

typedef uint8_t road_type_t;                    /* RoadType */

typedef uint8_t relevance_traffic_direction_t;  /* Relevance Traffic Direction */

typedef uint8_t relevance_distance_t;           /* Relevance distance */

typedef uint8_t cause_code_type_t;              /* cause_code_type */

typedef uint8_t sub_cause_code_type_t;          /* SubCauseCodeType */
/*
   typedef long
    adverse_weather_condition_PrecipitationSubCauseCode_t;

   typedef long adverse_weather_condition_VisibilitySubCauseCode_t;

   typedef long
    adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_t;
   typedef long adverse_weather_condition_AdhesionSubCauseCode_t;
 */
typedef uint16_t path_delta_time_t;             /* path_delta_time */

typedef uint8_t information_quality_t;          /* information_quality */

typedef uint16_t sequence_number_t;             /* SequenceNumber */

typedef uint16_t heading_value_t;               /* heading_value */

typedef uint16_t speed_value_t;                 /* speed_value */

typedef uint8_t heading_confidence_t;           /* heading_confidence */

typedef uint8_t speed_confidence_t;             /* speed_confidence */

typedef int8_t temperature_t;                   /* Temperature */

typedef int8_t lane_position_t;                 /* lane position of the event position*/

typedef uint16_t event_delta_time_t;            /* event delta time */

typedef uint32_t position_of_occupants_t;       /* position_of_occupants */

typedef uint8_t request_response_indication_t;

typedef uint8_t positioning_solution_type_t;  /* positioning_solution_type */

typedef enum speed_confidence {
	speed_confidence_equalOrWithinOneCentimeterPerSec	= 1,
	speed_confidence_equalOrWithinOneMeterPerSec		= 100,
	speed_confidence_outOfRange				= 126,
	speed_confidence_unavailable				= 127
} e_speed_confidence;

typedef enum transmission_interval {
	transmission_interval_oneMilliSecond	= 1,
	transmission_interval_tenSeconds	= 10000
} e_transmission_interval;

typedef enum heading_value {
	heading_value_wgs84North	= 0,
	heading_value_wgs84East		= 900,
	heading_value_wgs84South	= 1800,
	heading_value_wgs84West		= 2700,
	heading_value_unavailable	= 3601
} e_heading_value;

typedef enum speed_value {
	speed_value_standstill		= 0,
	speed_value_oneCentimeterPerSec = 1,
	speed_value_unavailable		= 16383
} e_speed_value;

typedef enum heading_confidence {
	heading_confidence_equalOrWithinZeroPointOneDegree	= 1,
	heading_confidence_equalOrWithinOneDegree		= 10,
	heading_confidence_outOfRange				= 126,
	heading_confidence_unavailable				= 127
} e_heading_confidence;

typedef enum validity_duration {
	validity_duration_timeOfDetection		= 0,
	validity_duration_oneSecondAfterDetection	= 1
} e_validity_duration;

typedef enum termination { termination_is_cancellation = 0, Termination_is_negation = 1 } e_termination;


typedef enum temperature {
	temperature_equalOrSmallerThanMinus60Deg	= -60,
	temperature_oneDegreeCelsius			= 1,
	temperature_equalOrGreaterThan67Deg		= 67
} e_Temperature;

typedef enum station_type {
	station_type_unknown		= 0,
	station_type_pedestrian		= 1,
	station_type_cyclist		= 2,
	station_type_moped		= 3,
	station_type_motorcycle		= 4,
	station_type_passengerCar	= 5,
	station_type_bus		= 6,
	station_type_lightTruck		= 7,
	station_type_heavyTruck		= 8,
	station_type_trailer		= 9,
	station_type_specialVehicles	= 10,
	station_type_tram		= 11,
	station_type_roadSideUnit	= 15
} e_station_type;

typedef enum road_type {
	road_type_urban_no_structural_separation_to_opposite_lanes		= 0,
	road_type_urban_with_structural_separation_to_opposite_lanes		= 1,
	road_type_non_urban_no_structural_separation_to_opposite_lanes		= 2,
	road_type_non_urban_with_structural_separation_to_opposite_lanes	= 3
} e_road_type;

typedef enum relevance_traffic_direction {
	relevance_traffic_direction_allTrafficDirections	= 0,
	relevance_traffic_direction_upstreamTraffic		= 1,
	relevance_traffic_direction_downstreamTraffic		= 2,
	relevance_traffic_direction_oppositeTraffic		= 3
} e_relevance_traffic_direction;

typedef enum relevance_distance {
	relevance_distance_lessThan50m		= 0,
	relevance_distance_lessThan100m		= 1,
	relevance_distance_lessThan200m		= 2,
	relevance_distance_lessThan500m		= 3,
	relevance_distance_lessThan1000m	= 4,
	relevance_distance_lessThan5km		= 5,
	relevance_distance_lessThan10km		= 6,
	relevance_distance_over10km		= 7
} e_relevance_distance;


typedef enum adverse_weather_condition_PrecipitationSubCauseCode {
	adverse_weather_condition_PrecipitationSubCauseCode_unavailable		= 0,
	adverse_weather_condition_PrecipitationSubCauseCode_heavyRain		= 1,
	adverse_weather_condition_PrecipitationSubCauseCode_heavySnowfall	= 2,
	adverse_weather_condition_PrecipitationSubCauseCode_softHail		= 3
} e_AdverseWeatherCondition_PrecipitationSubCauseCode;

typedef enum adverse_weather_condition_VisibilitySubCauseCode {
	adverse_weather_condition_VisibilitySubCauseCode_unavailable		= 0,
	adverse_weather_condition_VisibilitySubCauseCode_fog			= 1,
	adverse_weather_condition_VisibilitySubCauseCode_smoke			= 2,
	adverse_weather_condition_VisibilitySubCauseCode_heavySnowfall		= 3,
	adverse_weather_condition_VisibilitySubCauseCode_heavyRain		= 4,
	adverse_weather_condition_VisibilitySubCauseCode_heavyHail		= 5,
	adverse_weather_condition_VisibilitySubCauseCode_lowSunGlare		= 6,
	adverse_weather_condition_VisibilitySubCauseCode_sandstorms		= 7,
	adverse_weather_condition_VisibilitySubCauseCode_swarmsOfInsects	= 8
} e_adverse_weather_condition_VisibilitySubCauseCode;

typedef enum adverse_weather_condition_ExtremeWeatherConditionSubCauseCode {
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_unavailable	= 0,
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_strongWinds	= 1,
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_damagingHail	= 2,
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_hurricane		= 3,
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_thunderstorm	= 4,
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_tornado		= 5,
	adverse_weather_condition_ExtremeWeatherConditionSubCauseCode_blizzard		= 6
} e_adverse_weather_condition_ExtremeWeatherConditionSubCauseCode;

typedef enum adverse_weather_condition_AdhesionSubCauseCode {
	adverse_weather_condition_AdhesionSubCauseCode_unavailable	= 0,
	adverse_weather_condition_AdhesionSubCauseCode_heavyFrostOnRoad = 1,
	adverse_weather_condition_AdhesionSubCauseCode_fuelOnRoad	= 2,
	adverse_weather_condition_AdhesionSubCauseCode_mudOnRoad	= 3,
	adverse_weather_condition_AdhesionSubCauseCode_snowOnRoad	= 4,
	adverse_weather_condition_AdhesionSubCauseCode_iceOnRoad	= 5,
	adverse_weather_condition_AdhesionSubCauseCode_blackIceOnRoad	= 6,
	adverse_weather_condition_AdhesionSubCauseCode_oilOnRoad	= 7,
	adverse_weather_condition_AdhesionSubCauseCode_looseChippings	= 8,
	adverse_weather_condition_AdhesionSubCauseCode_instantBlackIce	= 9,
	adverse_weather_condition_AdhesionSubCauseCode_roadsSalted	= 10
} e_adverse_weather_condition_AdhesionSubCauseCode;

typedef enum cause_code_type {
	cause_code_type_reserved					= 0,
	cause_code_type_traffic_condition				= 1,
	cause_code_type_accident					= 2,
	cause_code_type_roadworks					= 3,
	cause_code_type_adverse_weather_conditionAdhesion		= 6,
	cause_code_type_hazardous_location_surfaceCondition		= 9,
	cause_code_type_hazardous_location_obstacleOnTheRoad		= 10,
	cause_code_type_hazardous_location_animalOnTheRoad		= 11,
	cause_code_type_human_presenceOnTheRoad				= 12,
	cause_code_type_wrongWayDriving					= 14,
	cause_code_type_rescueAndRecoveryWorkInProgress			= 15,
	cause_code_type_adverseWeatherCondition_ExtremeWeatherCondition = 17,
	cause_code_type_adverseWeatherCondition_Visibility		= 18,
	cause_code_type_adverseWeatherCondition_Precipitation		= 19,
	cause_code_type_slowVehicle					= 26,
	cause_code_type_dangerousEndOfQueue				= 27,
	cause_code_type_vehicleBreakdown				= 91,
	cause_code_type_postCrash					= 92,
	cause_code_type_humanProblem					= 93,
	cause_code_type_stationaryVehicle				= 94,
	cause_code_type_emergencyVehicleApproaching			= 95,
	cause_code_type_hazardousLocation_DangerousCurve		= 96,
	cause_code_type_collisionRisk					= 97,
	cause_code_type_signalViolation					= 98,
	cause_code_type_dangerousSituation				= 99
} e_cause_code_type;

typedef enum information_quality {
	information_quality_unavailable = 0,
	information_quality_lowest	= 1,
	information_quality_highest	= 7
} e_information_quality;

typedef enum path_delta_time { path_delta_time_tenMilliSecondsInPast = 1 } e_path_delta_time;

typedef enum protocol_version { protocol_version_current_version = 1 } e_protocol_version;

typedef enum lane_position {
	lane_position_offTheRoad		= -1,
	lane_position_hardShoulder		= 0,
	lane_position_outermostDrivingLane	= 1,
	lane_position_secondLaneFromOutside	= 2
} e_lane_position;

typedef enum position_of_occupants {
	position_of_occupants_row1LeftOccupied	= 0,
	position_of_occupants_row1RightOccupied = 1,
	position_of_occupants_row1MidOccupied	= 2,
	position_of_occupants_row1NotDetectable = 3,
	position_of_occupants_row1NotPresent	= 4,
	position_of_occupants_row2LeftOccupied	= 5,
	position_of_occupants_row2RightOccupied = 6,
	position_of_occupants_row2MidOccupied	= 7,
	position_of_occupants_row2NotDetectable = 8,
	position_of_occupants_row2NotPresent	= 9,
	position_of_occupants_row3LeftOccupied	= 10,
	position_of_occupants_row3RightOccupied = 11,
	position_of_occupants_row3MidOccupied	= 12,
	position_of_occupants_row3NotDetectable = 13,
	position_of_occupants_row3NotPresent	= 14,
	position_of_occupants_row4LeftOccupied	= 15,
	position_of_occupants_row4RightOccupied = 16,
	position_of_occupants_row4MidOccupied	= 17,
	position_of_occupants_row4NotDetectable = 18,
	position_of_occupants_row4NotPresent	= 19
} e_position_of_occupants;

typedef enum request_response_indication {
	request_response_indication_request	= 0,
	request_response_indication_response	= 1
} e_request_response_indication;

typedef enum positioning_solution_type {
	positioning_solution_type_noPositioningSolution = 0,
	positioning_solution_type_sGNSS			= 1,
	positioning_solution_type_dGNSS			= 2,
	positioning_solution_type_sGNSSplusDR		= 3,
	positioning_solution_type_dGNSSplusDR		= 4,
	positioning_solution_type_dR			= 5
	                                                  /*
	                                                   * Enumeration is extensible
	                                                   */
} e_positioning_solution_type;


typedef enum message_id {
	message_id_denm		= 1,
	message_id_cam		= 2,
	message_id_poi		= 3,
	message_id_spat		= 4,
	message_id_map		= 5,
	message_id_ivi		= 6,
	message_id_ev_rsr	= 7
} e_message_id;



/*
 * DF_DeltaReferencePosition as defined in ETSI TS 102 894-2 V1.2.1
 * */
typedef struct delta_reference_position {
	int32_t delta_latitude;
	int32_t delta_longitude;
	int16_t deltaAltitude;
}delta_reference_position_t;

/*
 * DF_EventPoint as defined in ETSI TS 102 894-2 V1.2.1 clause A.110.
 * */
typedef struct event_point {
	delta_reference_position_t event_position;
	event_delta_time_t event_delta_time;
	information_quality_t information_quality;
} event_point_t;


/*DF_EventHistory as defined in ETSI TS 102 894-2 V1.2.1.
 * */
typedef struct event_history {
	event_point_t event_pt;
	struct list_head list;
} event_history_t;

/*
 * DF_PathPoint as defined in ETSI TS 102 894-2 V1.2.1
 * */
typedef struct path_point {
	delta_reference_position_t path_position;
	path_delta_time_t path_delta_time;
} path_point_t;

/*
 * DF_PathHistory as defined in ETSI TS 102 894-2 V1.2.1. Size of the Array shall be 23
   as defined in ETSI EN 302 637-2 V1.3.2.
 * */
typedef struct path_history {
	path_point_t path_pt;
	struct list_head list;
} path_history_t;

/*
 * DF_Traces as defined in ETSI TS 102 894-2 V1.2.1. Size of the Array shall be 7.
 * */
typedef struct traces {
	uint8_t count;
	path_history_t values[7];
} traces_t;

typedef struct heading {
	heading_value_t heading_value;
	heading_confidence_t heading_confidence;
} heading_t;

typedef struct speed {
	speed_value_t speed_value;
	speed_confidence_t speed_confidence;
} speed_t;

/*
 * DF_ActionID as defined in ETSI TS 102 894-2 V1.2.1.
 * */
typedef struct action_id {
	itsnet_node_id originating_station_id;
	sequence_number_t sequence_number;
} action_id_t;


/* CauseCode */
typedef struct cause_code {
	cause_code_type_t causeCode;
	sub_cause_code_type_t sub_causeCode;
} cause_code_t;

/*
 * DF_PositionOfPillars as defined in ETSI TS 102 894-2 V1.2.1
 * */
typedef struct position_of_pillars {
	uint8_t count;
	uint8_t values[3];
} position_of_pillars_t;

typedef struct road_works_container_extended { /* TODO*/
	/* TODO */
	uint8_t speedLimit;
} road_works_container_extended_t;

typedef struct stationary_vehicle_container { /* TODO */
	/* TODO */
	uint8_t number_of_occupants;
}stationary_vehicle_container_t;

typedef struct impact_reduction_container {
	uint8_t height_lon_carr_left;
	uint8_t height_lon_carr_right;
	uint8_t pos_lon_carr_left;
	uint8_t pos_lon_carr_right;
	position_of_pillars_t position_of_pillars;
	uint8_t pos_cent_mass;
	uint8_t wheel_base_vehicle;
	uint8_t turning_radius;
	uint8_t pos_front_ax;
	position_of_occupants_t position_of_occupants;
	uint16_t vehicle_mass;
	request_response_indication_t request_response_indication;
} impact_reduction_container_t;

/*
 * SituationContainer as defined in ETSI EN 302 637-3 V1.2.2.
 * */
typedef struct situation_container {
	information_quality_t information_quality;
	cause_code_t event_type;
	cause_code_t linked_cause /* OPTIONAL */;
	event_history_t event_history /* OPTIONAL */;
} situation_container_t;

/*
 * LocationContainer as defined in ETSI EN 302 637-3 V1.2.2.
 * */
typedef struct location_container {
	struct speed event_speed /* OPTIONAL */;
	struct heading event_position_heading /* OPTIONAL */;
	traces_t traces;
	road_type_t roadType /* OPTIONAL */;
} location_container_t;
/*
 * AlacarteContainer as defined in ETSI EN 302 637-3 V1.2.2.
 * */
typedef struct alacarte_container {
	lane_position_t lane_position;
	impact_reduction_container_t impact_reduction;
	temperature_t external_temperature;
	road_works_container_extended_t road_works; // not achieved
	positioning_solution_type_t positioning_solution;
	stationary_vehicle_container_t stationary_vehicle_container;
} alacarte_container_t;


typedef struct management_container {
	action_id_t action_id;
	itsnet_time_stamp detection_time;
	itsnet_time_stamp reference_time;
	termination_t termination /* OPTIONAL */;
	itsnet_position_vector event_position;
	double relevance_distance /* OPTIONAL */;
	relevance_traffic_direction_t relevance_traffic_direction /* OPTIONAL */;
	validity_duration_t validity_duration /* DEFAULT 600 */;
	transmission_interval_t transmission_interval /* OPTIONAL */;
	station_type_t station_type;
} management_t;

/* decentralized_environmental_notification_message */
typedef struct decentralized_environmental_notification_message {
	management_t management;
	situation_container_t situation /* OPTIONAL */;
	location_container_t location /* OPTIONAL */;
	//alacarte_container_t alacarte /* OPTIONAL */;
} denm_t;

/* ItsPduHeader */
typedef struct its_pdu_header {
	uint8_t protocol_version;
	uint8_t message_id;
	itsnet_node_id station_id;
} its_pdu_header_t;
/* DENM */
typedef struct DENM {
	its_pdu_header_t header;
	denm_t payload;
} DENM_t;




denm_t * encode_denm(int signal);
void decode_denm(denm_t* payload, int *weather, int *seq_nb);

DENM_t* denm_transmission_management(denm_t* payload);
denm_t* denm_reception_management(DENM_t* packet);

void trace_recv_denm(denm_t* payload, struct ntptimeval t_recv);
void trace_sent_denm(denm_t* payload, struct ntptimeval t_emit);

/*
   void denm_transmission_management(denm_t* data);
   void app_denm_trigger(denm_t *data);
   void app_denm_update(denm_t *data);
   void app_denm_trigger(denm_t *data);

   void denm_reception_management(denm_t* data);
   void keep_alive_forwarding(denm_t* data);
 */



#endif
