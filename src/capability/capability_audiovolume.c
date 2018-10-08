/*
 * resource_capability_audiovolume_main_0.c
 *
 *  Created on: Oct 5, 2018
 *      Author: osboxes
 */

#include <stdio.h>
#include <stdbool.h>
#include "st_things.h"
#include "log.h"

#define VALUE_STR_LEN_MAX 32

static const char* KEY_VOLUME = "volume";
static int64_t g_volume;

static const char* KEY_MUTE = "mute";
static bool g_mute;

static const char* KEY_VOLUME_COMMAND = "command";
static const char* VALUE_VOLUME_COMMAND_INC = "increase";
static const char* VALUE_VOLUME_COMMAND_DEC = "decrease";
static const char* VALUE_VOLUME_COMMAND_MAX = "max";
static const char* VALUE_VOLUME_COMMAND_MIN = "min";
static char g_volume_cmd[VALUE_STR_LEN_MAX+1] = "increase";

extern bool user_player_get_volume(float *vol);
extern bool user_player_is_muted(bool *muted);
extern bool user_player_set_mute(bool muted);
extern bool user_player_set_volume(float vol);

bool handle_get_request_on_resource_capability_audiovolume_main_0(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
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

	if (req_msg->has_property_key(req_msg, KEY_VOLUME_COMMAND))
		WARN("key[%s] exists..Ignore It!", KEY_VOLUME_COMMAND);

    return true;  // FIXME: Modify this line with the appropriate return value.
}

bool handle_set_request_on_resource_capability_audiovolume_main_0(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
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

	char *str_value = NULL;
	if (req_msg->rep->get_str_value(req_msg->rep, KEY_VOLUME_COMMAND, &str_value)) {
		DBG("requested volume_cmd: [%s]", str_value);

		strncpy(g_volume_cmd, str_value, VALUE_STR_LEN_MAX);
		if (0 == strncmp(g_volume_cmd, VALUE_VOLUME_COMMAND_INC, strlen(VALUE_VOLUME_COMMAND_INC)))
			DBG("TODO");
		else if (0 == strncmp(g_volume_cmd, VALUE_VOLUME_COMMAND_DEC, strlen(VALUE_VOLUME_COMMAND_DEC)))
			DBG("TODO");
		else if (0 == strncmp(g_volume_cmd, VALUE_VOLUME_COMMAND_MAX, strlen(VALUE_VOLUME_COMMAND_MAX)))
			DBG("TODO");
		else if (0 == strncmp(g_volume_cmd, VALUE_VOLUME_COMMAND_MIN, strlen(VALUE_VOLUME_COMMAND_MIN)))
			DBG("TODO");
		else
			ERR("Not supported command");

		resp_rep->set_str_value(resp_rep, KEY_VOLUME_COMMAND, g_volume_cmd);
		free(str_value);
	}

	st_things_notify_observers(req_msg->resource_uri);

    return true;  // FIXME: Modify this line with the appropriate return value.
}
