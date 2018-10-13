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


static const char* KEY_MODES = "modes";
static const char* KEY_SUPPORTEDMODES = "supportedModes";

bool handle_get_request_on_resource_capability_mediaplayback(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, KEY_MODES)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, KEY_SUPPORTEDMODES)) {
        // TODO: Write your implementation in this section.
    }
    return false;  // FIXME: Modify this line with the appropriate return value.
}

bool handle_set_request_on_resource_capability_mediaplayback(st_things_set_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a SET request on %s\n", req_msg->resource_uri);

    // TODO: Write your implementation in this section.
    return false;  // FIXME: Modify this line with the appropriate return value.
}
