/*
 * network_audio.c
 *
 *  Created on: Oct 5, 2018
 *      Author: osboxes
 */

#include <tizen.h>
#include <service_app.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "st_things.h"
#include "thing.h"
#include "log.h"

static bool service_app_create(void *user_data)
{
	FN_CALL;

	return true;
}

static void service_app_terminate(void *user_data)
{
	FN_CALL;
}

static void service_app_control(app_control_h app_control, void *user_data)
{
	FN_CALL;
	if (app_control == NULL) {
		ERR("app_control is NULL");
		return;
	}

	int ret;
	char *value = NULL;
	ret = app_control_get_extra_data(app_control, "cmd", &value);
	DBG("value: [%s]", value);
	if (value == NULL)
		init_thing();
	else
		ERR("Unknown command");

	free(value);
}

int main(int argc, char *argv[])
{
	FN_CALL;

	char ad[50] = {0,};
	service_app_lifecycle_callback_s event_callback;

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	return service_app_main(argc, argv, &event_callback, ad);
}
