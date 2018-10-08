/*
 * resource_capability_audiotrackdata_main_0.c
 *
 *  Created on: Oct 5, 2018
 *      Author: osboxes
 */

#include <stdio.h>
#include <stdbool.h>
#include "st_things.h"
#include "log.h"


static const char* PROP_THUMBNAIL = "thumbnail";
static const char* PROP_TRACKDESCRIPTION = "trackDescription";
static const char* PROP_TRACKNUMBER = "trackNumber";
static const char* PROP_ARTIST = "artist";
static const char* PROP_ALBUM = "album";
static const char* PROP_STATION = "station";
static const char* PROP_TRACKURI = "trackUri";
static const char* PROP_TITLE = "title";

bool handle_get_request_on_resource_capability_audiotrackdata_main_0(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, PROP_THUMBNAIL)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_TRACKDESCRIPTION)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_TRACKNUMBER)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_ARTIST)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_ALBUM)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_STATION)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_TRACKURI)) {
        // TODO: Write your implementation in this section.
    }
    if (req_msg->has_property_key(req_msg, PROP_TITLE)) {
        // TODO: Write your implementation in this section.
    }
    return false;  // FIXME: Modify this line with the appropriate return value.
}
