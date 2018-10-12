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

#include <stdio.h>
#include "st_things.h"
#include "log.h"

extern char* get_artist();
extern char* get_title();

static const char* KEY_THUMBNAIL = "thumbnail";
static const char* KEY_TRACKDESCRIPTION = "trackDescription";
static const char* KEY_TRACKNUMBER = "trackNumber";
static const char* KEY_ARTIST = "artist";
static const char* KEY_ALBUM = "album";
static const char* KEY_STATION = "station";
static const char* KEY_TRACKURI = "trackUri";
static const char* KEY_TITLE = "title";

bool handle_get_request_on_resource_capability_audiotrackdata(st_things_get_request_message_s* req_msg, st_things_representation_s* resp_rep)
{
    DBG("Received a GET request on %s\n", req_msg->resource_uri);

    if (req_msg->has_property_key(req_msg, KEY_THUMBNAIL)) {
        DBG("thumnail [%s]", "");
        resp_rep->set_str_value(resp_rep, KEY_THUMBNAIL, "");
    }
    if (req_msg->has_property_key(req_msg, KEY_TRACKDESCRIPTION)) {
        DBG("trackDescription [%s]", "");
        resp_rep->set_str_value(resp_rep, KEY_TRACKDESCRIPTION, "");
    }
    if (req_msg->has_property_key(req_msg, KEY_TRACKNUMBER)) {
        DBG("trackNumber [%s]", "");
        resp_rep->set_str_value(resp_rep, KEY_TRACKNUMBER, "");
    }
    if (req_msg->has_property_key(req_msg, KEY_ARTIST)) {
        DBG("artist [%s]", get_artist());
        resp_rep->set_str_value(resp_rep, KEY_ARTIST, get_artist());
    }
    if (req_msg->has_property_key(req_msg, KEY_ALBUM)) {
        DBG("album [%s]", "");
        resp_rep->set_str_value(resp_rep, KEY_ALBUM, "");
    }
    if (req_msg->has_property_key(req_msg, KEY_STATION)) {
        DBG("station [%s]", "");
        resp_rep->set_str_value(resp_rep, KEY_STATION, "");
    }
    if (req_msg->has_property_key(req_msg, KEY_TRACKURI)) {
        DBG("trackUri [%s]", "");
        resp_rep->set_str_value(resp_rep, KEY_TRACKURI, "");
    }
    if (req_msg->has_property_key(req_msg, KEY_TITLE)) {
        DBG("title [%s]", get_title());
        resp_rep->set_str_value(resp_rep, KEY_TITLE, get_title());
    }
    return true;
}
