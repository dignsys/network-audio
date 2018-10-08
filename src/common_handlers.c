/*
 * common_handlers.c
 *
 *  Created on: Oct 5, 2018
 *      Author: osboxes
 */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "st_things.h"
#include "log.h"

extern bool user_player_init();

/* callback functions */
bool handle_reset_request(void)
{
    DBG("Received a request for RESET.");

	bool confirmed = true;
	DBG("confirmed : [%d]", confirmed);

	return confirmed; // FIXME: Modify this line with the appropriate return value.
}

void handle_reset_result(bool result)
{
    DBG("Reset %s.\n", result ? "succeeded" : "failed");

    // TODO: Write your implementation in this section.
}

bool handle_ownership_transfer_request(void)
{
    DBG("Received a request for Ownership-transfer.");

	bool confirmed = true;
	DBG("confirmed : [%d]", confirmed);

	return confirmed; // FIXME: Modify this line with the appropriate return value.
}

void handle_things_status_change(st_things_status_e things_status)
{
    DBG("Things status is changed: %d\n", things_status);

    // TODO: Write your implementation in this section.
}

bool init_user() {
	FN_CALL;

	bool ret = false;

	ret = user_player_init();

	return ret;  // FIXME: Modify this line with the appropriate return value.
}
