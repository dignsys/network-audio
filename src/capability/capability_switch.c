/*
 * resource_capability_switch_main_0.c
 *
 *  Created on: Oct 5, 2018
 *      Author: osboxes
 */

#include <stdio.h>
#include <stdbool.h>
#include "st_things.h"
#include "log.h"

#define VALUE_STR_LEN_MAX 32

static const char* KEY_SWITCH = "power";
static const char* VALUE_SWITCH_ON = "on";
static const char* VALUE_SWITCH_OFF = "off";
static char g_switch[VALUE_STR_LEN_MAX+1] = "off";

extern bool user_player_start();
extern bool user_player_stop();

bool handle_get_request_on_resource_capability_switch_main_0(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, KEY_SWITCH)) {
        DBG("current g_switch: [%s]", g_switch);
        resp_rep->set_str_value(resp_rep, KEY_SWITCH, g_switch);
    }
    return true;  // FIXME: Modify this line with the appropriate return value.
}

bool handle_set_request_on_resource_capability_switch_main_0(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a SET request on %s\n", req_msg->resource_uri);

	DBG("current g_switch: [%s]", g_switch);

	char *str_value = NULL;
	req_msg->rep->get_str_value(req_msg->rep, KEY_SWITCH, &str_value);
	DBG("requested switch: [%s]", str_value);

	/* check validation */
	if ((0 != strncmp(str_value, VALUE_SWITCH_ON, strlen(VALUE_SWITCH_ON)))
		&& (0 != strncmp(str_value, VALUE_SWITCH_OFF, strlen(VALUE_SWITCH_OFF)))) {
		ERR("Not supported value!!");
		free(str_value);
		return false;
	}

	if (0 != strncmp(str_value, g_switch, strlen(g_switch))) {
		strncpy(g_switch, str_value, VALUE_STR_LEN_MAX);
		if (0 == strncmp(g_switch, VALUE_SWITCH_ON, strlen(VALUE_SWITCH_ON)))
			user_player_start();
		else
			user_player_stop();
	}
	resp_rep->set_str_value(resp_rep, KEY_SWITCH, g_switch);

	st_things_notify_observers(req_msg->resource_uri);

	free(str_value);
    return true;  // FIXME: Modify this line with the appropriate return value.
}
