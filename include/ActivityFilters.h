/*
 *
 * (C) 2016 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#ifndef _ACTIVITY_FILTERS_H_
#define _ACTIVITY_FILTERS_H_

#include <stdint.h>
#include <time.h>

typedef unsigned int uint;
class Flow;

typedef union {
  struct {
    uint samples;
    uint edge;
    uint minsamples;
  } rolling_mean;
  
  struct {
    uint minbytes;
    uint maxinterval;
    uint minflips;
    bool mustwait;
  } command_sequence;
} activity_filter_config;

typedef union {
  struct {
    uint64_t respBytes;
    uint64_t respCount;
    struct timeval lastPacket;
    bool reqSeen;
    bool srvWaited;
    bool cli2srv;
  } command_sequence;
} activity_filter_status;

/*
 * A filter to be applied to network packets in order to detect
 * activity.
 * 
 * @params activity_filter_config* filter specific configuration
 * @params activity_filter_status* filter specific status data
 * @params Flow* current flow
 * @params const struct timeval current packet time
 * @params bool cli2srv direction
 * @params u_int16_t current packet size
 * 
 * @return TRUE if activity has been detected, FALSE otherwise
 */
typedef bool (activity_filter_t)(const activity_filter_config *,
				 activity_filter_status *,
				 Flow *, const struct timeval *,
				 bool, uint16_t);
				
activity_filter_t activity_filter_fun_none;
activity_filter_t activity_filter_fun_rolling_mean;
activity_filter_t activity_filter_fun_command_sequence;
activity_filter_t activity_filter_fun_web;

#endif
