/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "st_things.h"
#include "player.h"
#include "log.h"

#define RES_CAPABILITY_AUDIOTRACKDATA_MAIN_0 "/capability/audioTrackData/main/0"

extern int8_t get_playindex();
extern void   set_playindex();
extern void   set_playinfo();
extern player_state_e user_player_get_state();
extern bool user_player_stop();
extern bool user_player_start();

static const char* KEY_MODES = "modes";
static const char* KEY_SUPPORTEDMODES = "supportedModes";

static const char* g_supportedmodes[2] = { "previous", "next" };
static size_t g_length = 2;

static int8_t g_modes = 1;

bool handle_get_request_on_resource_capability_mediatrackcontrol(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, KEY_MODES)) {
        DBG("current g_modes: [%d]", g_modes);
        resp_rep->set_str_array_value(resp_rep, KEY_MODES, (const char**)&g_supportedmodes[g_modes], 1);
    }
    if (req_msg->has_property_key(req_msg, KEY_SUPPORTEDMODES)) {
		resp_rep->set_str_array_value(resp_rep, KEY_SUPPORTEDMODES, (const char**)&g_supportedmodes, g_length);
    }
    return true;
}

bool handle_set_request_on_resource_capability_mediatrackcontrol(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a SET request on %s\n", req_msg->resource_uri);

	DBG("current g_modes: [%d]", g_modes);

	player_state_e state;
	uint32_t* str_value[2];
    size_t length;

	req_msg->rep->get_str_array_value(req_msg->rep, KEY_MODES, (char ***)&str_value, &length);
	DBG("requested mediatrackcontrol: [%s]", str_value);

	/* check validation */
	//  previous
	if (0 == strncmp((const char*)*str_value[0], g_supportedmodes[0], strlen(g_supportedmodes[0]))) {
		g_modes = 0;
		set_playindex(-1);
		set_playinfo(get_playindex());
	// next
	} else if (0 == strncmp((const char*)*str_value[0], g_supportedmodes[1], strlen(g_supportedmodes[1]))) {
		g_modes = 1;
		set_playindex(1);
		set_playinfo(get_playindex());
	} else {
		ERR("Not supported value!!");
		// free(str_value);
		return false;
	}

	state = user_player_get_state();
	switch (state) {
	case PLAYER_STATE_NONE:
		break;
	case PLAYER_STATE_IDLE:
		break;
	case PLAYER_STATE_READY:
		break;
	case PLAYER_STATE_PLAYING:
		user_player_stop();
		user_player_start();
		break;
	case PLAYER_STATE_PAUSED:
		user_player_stop();
		break;
	default:
		ERR("this state is not allowed");
		break;
	}

	resp_rep->set_str_array_value(resp_rep, KEY_MODES, (const char**)&g_supportedmodes[g_modes], 1);
	resp_rep->set_str_array_value(resp_rep, KEY_SUPPORTEDMODES, (const char**)&g_supportedmodes, g_length);

	st_things_notify_observers(req_msg->resource_uri);
	// update request for title and artist info
	st_things_notify_observers(RES_CAPABILITY_AUDIOTRACKDATA_MAIN_0);

	// free(str_value);

    return true;
}
