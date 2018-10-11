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
#include "log.h"

extern int8_t get_playmode();
extern void   set_playmode();
extern bool   user_player_start();
extern bool   user_player_resume();
extern bool   user_player_stop();
extern bool   user_player_pause();

static const char* KEY_MODES = "modes";
static const char* KEY_SUPPORTEDMODES = "supportedModes";

static const char* g_supportedmodes[3] = { "play", "stop", "pause" };
static size_t g_length = 3;

bool handle_get_request_on_resource_capability_mediaplayback(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, KEY_MODES)) {
        int8_t mode = get_playmode();
        DBG("current g_playmode: [%d]", mode);
        resp_rep->set_str_array_value(resp_rep, KEY_MODES, (const char**)&g_supportedmodes[mode], 1);
    }
    if (req_msg->has_property_key(req_msg, KEY_SUPPORTEDMODES)) {
		resp_rep->set_str_array_value(resp_rep, KEY_SUPPORTEDMODES, (const char**)&g_supportedmodes, g_length);
    }
    return true;
}

bool handle_set_request_on_resource_capability_mediaplayback(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a SET request on %s\n", req_msg->resource_uri);

	DBG("current g_playmode: [%d]", get_playmode());

	uint32_t* str_value[2];
    size_t length;

	req_msg->rep->get_str_array_value(req_msg->rep, KEY_MODES, (char ***)&str_value, &length);
	DBG("requested mediaplayback: [%s]", *str_value[0]);

	/* check validation */
    // play
	if (0 == strncmp((const char*)*str_value[0], g_supportedmodes[0], strlen(g_supportedmodes[0]))) {
        set_playmode(0);
        user_player_resume();
    // stop
    } else if (0 == strncmp((const char*)*str_value[0], g_supportedmodes[1], strlen(g_supportedmodes[1]))) {
        set_playmode(1);
        user_player_stop();
    // pause
    } else if (0 == strncmp((const char*)*str_value[0], g_supportedmodes[2], strlen(g_supportedmodes[2]))) {
        set_playmode(2);
        user_player_pause();
	} else {
		ERR("Not supported value!!");
		// free(**str_value);
		return false;
	}

    int8_t mode = get_playmode();
	resp_rep->set_str_array_value(resp_rep, KEY_MODES, (const char**)&g_supportedmodes[mode], 1);
	resp_rep->set_str_array_value(resp_rep, KEY_SUPPORTEDMODES, (const char**)&g_supportedmodes, g_length);

	st_things_notify_observers(req_msg->resource_uri);

	// free(**str_value);

    return true;
}
