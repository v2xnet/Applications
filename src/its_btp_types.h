/*
 * its_btp_types.h
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

#include "itsnet_header.h"

typedef uint16_t destination_port_t; /* destination port type */
typedef uint16_t  max_packet_lifetime_t; 
typedef uint64_t  certificate_Id_t;
typedef uint8_t ssp_length_t;
typedef uint16_t rem_packet_lifetime_t;
typedef uint8_t rem_hop_limit_t;

#updated : ETSI TS 103 248 V2.1.1 (2021-08)
typedef enum btp_port
 {
     btp_Port_UNSPECIFIED = 0,
     btp_port_CAM = 2001,
     btp_port_DENM = 2002,
     btp_port_MAPEM = 2003,
     btp_port_SPATEM = 2004,
     btp_port_SAEM = 2005,
     btp_port_IVIM = 2006,
     btp_port_SREM = 2007,
     btp_port_SSEM = 2008,
     btp_port_CPM = 2009,
     btp_port_EVCSN = 2010,
     btp_port_TPG = 2011,
     btp_port_EV_RSR = 2012,
     btp_port_RTCMEM = 2013,
     btp_port_CTLM = 2014,
     btp_port_CRLM = 2015,
     btp_port_EC_AT = 2016,
     btp_port_MCDM = 2017,
     btp_port_VAM = 2018,
     btp_port_IMZM = 2019
 } e_btp_port;
 

typedef struct sec_report{

 }sec_report_t;

typedef struct traffic_class_Id{

 }traffic_class_Id_t;

typedef struct  sec_profile{

 }sec_profile_t;

/**
 *destinationAddress or
 *destinationArea is used for
 *this packet
 **/
typedef struct itsnet_destination_type{


}itsnet_destination_type_t;

typedef struct itsnet_destination_area{

 }itsnet_destination_area_t;


typedef struct  itsnet_address{

 }itsnet_address_t;

typedef struct itsnet_packet_transport{
	 

 }itsnet_packet_transport_t;

typedef struct itsnet_upper_protocol{

 }itsnet_upper_protocol_t;

typedef struct btp_tx_params{
	itsnet_upper_protocol upper_protocol;
	destination_port_t destination_port;
	itsnet_packet_transport_t transport_type;
	itsnet_address_t destination_address;
	itsnet_destination_area_t destination_area;
	itsnet_destination_type destination_type;
	sec_profile_t sec_profile;
	max_packet_lifetime_t max_packet_lifetime;
	traffic_class_Id_t traffic_class_Id;
 }btp_tx_params_t;

typedef struct btp_rx_params{
	itsnet_upper_protocol upper_protocol;
	itsnet_packet_transport_t transport_type;
	itsnet_address_t destination_address;
	itsnet_destination_area_t destination_area;
	itsnet_destination_type destination_type;
	itsnet_position_vector source_position_vector; /*itsnet Long Position Vector*/
	sec_report_t sec_report;
	certificate_Id_t certificate_Id;
	uint8_t ssp_bits[4];
	ssp_length_t ssp_length;
	traffic_class_Id_t traffic_class_Id;
	rem_packet_lifetime_t rem_packet_lifetime; /*Remaining lifetime*/
	rem_hop_limit_t rem_hop_limit; /*Remaining hop limit*/
	
 }btp_rx_params_t;
