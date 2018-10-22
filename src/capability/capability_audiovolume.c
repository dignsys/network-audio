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

#define VALUE_STR_LEN_MAX 32

static const char* KEY_VOLUME = "volume";
static int64_t g_volume;

static const char* KEY_MUTE = "mute";
static bool g_mute;

extern bool user_player_get_volume(float *vol);
extern bool user_player_is_muted(bool *muted);
extern bool user_player_set_mute(bool muted);
extern bool user_player_set_volume(float vol);

bool handle_get_request_on_resource_capability_audiovolume(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);
	DBG("current g_volume: [%lld], g_mute:[%d]", g_volume, g_mute);

	if (req_msg->has_property_key(req_msg, KEY_VOLUME)) {
		DBG("key[%s] exists", KEY_VOLUME);
		float temp_vol = 0.0;
		user_player_get_volume(&temp_vol);
		g_volume = (int64_t) (temp_vol * 100);
		DBG("current g_volume: [%lld]", g_volume);
		resp_rep->set_int_value(resp_rep, KEY_VOLUME, g_volume);
	}

	if (req_msg->has_property_key(req_msg, KEY_MUTE)) {
		DBG("key[%s] exists", KEY_MUTE);
		user_player_is_muted(&g_mute);
		DBG("current g_mute: [%d]", g_mute);
		resp_rep->set_bool_value(resp_rep, KEY_MUTE, g_mute);
	}

    return true;
}

bool handle_set_request_on_resource_capability_audiovolume(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a SET request on %s\n", req_msg->resource_uri);
	DBG("current g_volume: [%lld], g_mute:[%d]", g_volume, g_mute);

	int64_t ivalue;
	if (req_msg->rep->get_int_value(req_msg->rep, KEY_VOLUME, &ivalue)) {
		DBG("requested volume: [%lld]", ivalue);
		g_volume = ivalue;
		float temp_vol = (float) (g_volume/100.);
		user_player_set_volume(temp_vol);
		resp_rep->set_int_value(resp_rep, KEY_VOLUME, g_volume);
	}

	bool bvalue;
	if (req_msg->rep->get_bool_value(req_msg->rep, KEY_MUTE, &bvalue)) {
		DBG("requested mute: [%d]", bvalue);
		g_mute = bvalue;
		user_player_set_mute(g_mute);
		resp_rep->set_bool_value(resp_rep, KEY_MUTE, g_mute);
	}

	st_things_notify_observers(req_msg->resource_uri);

    return true;
}
