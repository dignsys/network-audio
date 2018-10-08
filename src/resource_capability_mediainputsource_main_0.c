/*
 * resource_capability_mediainputsource_main_0.c
 *
 *  Created on: Oct 5, 2018
 *      Author: osboxes
 */

#include <stdio.h>
#include <stdbool.h>
#include "st_things.h"
#include "log.h"


static const char* PROP_MODES = "modes";
static const char* PROP_SUPPORTEDMODES = "supportedModes";

bool handle_get_request_on_resource_capability_mediainputsource_main_0(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, PROP_MODES)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_SUPPORTEDMODES)) {
        // TODO: Write your implementation in this section.
    }
    return false;  // FIXME: Modify this line with the appropriate return value.
}

bool handle_set_request_on_resource_capability_mediainputsource_main_0(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a SET request on %s\n", req_msg->resource_uri);

    // TODO: Write your implementation in this section.
    return false;  // FIXME: Modify this line with the appropriate return value.
}
