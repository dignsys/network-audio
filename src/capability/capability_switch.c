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

#include <peripheral_io.h>
#include "st_things.h"
#include "log.h"
#include "resource_network_audio.h"

#define VALUE_STR_LEN_MAX	32
#define LED_ON				1		// High
#define LED_OFF				0		// Low

static const char* KEY_SWITCH = "power";
static const char* VALUE_SWITCH_ON = "on";
static const char* VALUE_SWITCH_OFF = "off";
static char g_switch[VALUE_STR_LEN_MAX+1] = "off";
extern peripheral_gpio_h led_h;

extern int  resource_write_led(peripheral_gpio_h handle, int write_value);
extern bool user_player_start();
extern bool user_player_stop();
extern void set_playmode();

bool handle_get_request_on_resource_capability_switch(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, KEY_SWITCH)) {
        DBG("current g_switch: [%s]", g_switch);
        resp_rep->set_str_value(resp_rep, KEY_SWITCH, g_switch);
    }
    return true;
}

bool handle_set_request_on_resource_capability_switch(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
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
		if (0 == strncmp(g_switch, VALUE_SWITCH_ON, strlen(VALUE_SWITCH_ON))) {
			user_player_start();
	    	set_playmode(MODE_PLAY);

			resource_write_led(led_h, LED_ON);
		} else {
			user_player_stop();
	    	set_playmode(MODE_STOP);

			resource_write_led(led_h, LED_OFF);
		}
	}
	resp_rep->set_str_value(resp_rep, KEY_SWITCH, g_switch);

	st_things_notify_observers(req_msg->resource_uri);
	// update request for play mode
	st_things_notify_observers(RES_CAPABILITY_MEDIAPLAYBACK_MAIN_0);

	free(str_value);
    return true;
}
