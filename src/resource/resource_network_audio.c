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
#include <app_common.h>
#include "st_things.h"
#include "player.h"
#include "log.h"

static struct _playlist {
	char*  title;
	char*  artist;
	char*  filename;
	int8_t length;
} g_playlist[3] = {
	{ "Shine"    , "Declan DP", "Declan-DP-Shine.mp3", 19 },
	{ "Feel Good", "MBB"      , "Feel-Good.wav"      , 13 },
	{ "Alive"    , "Ikson"    , "Ikson-Alive.wav"    , 15 },
};

player_h g_player;

static int8_t g_playmode;
static int8_t g_playindex;

// #define AUDIO_FILE_NAME "sample.mp3"
static char audio_file[128];
static char title[128];
static char artist[128];

/* player : get mute */
bool user_player_is_muted(bool *muted)
{
	FN_CALL;

	int ret;
	ret = player_is_muted(g_player, muted);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_is_muted is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : set mute */
bool user_player_set_mute(bool muted)
{
	FN_CALL;

	int ret;
	ret = player_set_mute(g_player, muted);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_set_mute is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : set volume */
bool user_player_set_volume(float vol)
{
	FN_CALL;

	int ret;
	ret = player_set_volume(g_player, vol, vol);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_set_volume is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : get volume */
bool user_player_get_volume(float *vol)
{
	FN_CALL;

	int ret;
	float vol2;
	ret = player_get_volume(g_player, vol, &vol2);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_get_volume is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : start player */
bool user_player_start()
{
	FN_CALL;

	int ret;
	ret = player_set_uri(g_player, audio_file);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_set_uri is failed [%d:%s]", ret, audio_file);
		return false;
	}
	ret = player_prepare(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_prepare is failed [%d]", ret);
		return false;
	}
	ret = player_start(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_start is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : resume player */
bool user_player_resume()
{
	FN_CALL;

	int ret;

	ret = player_start(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_start is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : stop player */
bool user_player_stop()
{
	FN_CALL;

	int ret;
	ret = player_stop(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_stop is failed [%d]", ret);
		return false;
	}
	ret = player_unprepare(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_unprepare is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : pause player */
bool user_player_pause()
{
	FN_CALL;

	int ret;
	ret = player_pause(g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_pause is failed [%d]", ret);
		return false;
	}

	return true;
}

/* player : get state */
player_state_e user_player_get_state()
{
	FN_CALL;

	player_state_e state;
	int ret;
	ret = player_get_state(g_player, &state);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_get_state is failed [%d]", ret);
		return false;
	}

	switch (state)
	{
	case PLAYER_STATE_NONE:
		DBG("user_player_get_state: [state = %s]", "Player is not created");
		break;
	case PLAYER_STATE_IDLE:
		DBG("user_player_get_state: [state = %s]", "Player is created, but not prepared");
		break;
	case PLAYER_STATE_READY:
		DBG("user_player_get_state: [state = %s]", "Player is ready to play media");
		break;
	case PLAYER_STATE_PLAYING:
		DBG("user_player_get_state: [state = %s]", "Player is playing media");
		break;
	case PLAYER_STATE_PAUSED:
		DBG("user_player_get_state: [state = %s]", "Player is paused while playing media");
		break;
	default:
		ERR("this state is not allowed");
		break;
	}

	return state;
}

int8_t get_playmode()
{
	return g_playmode;
}

void set_playmode(int8_t mode)
{
	g_playmode = mode;
}

int8_t get_playindex()
{
	return g_playindex;
}

/**
 * @param index 0: init 1: increase, -1: decrease
 */
void set_playindex(int8_t index)
{
	if (1 == index) {
		g_playindex = (++g_playindex <= 2) ? g_playindex : 0;
	} else if (-1 == index) {
		g_playindex = (--g_playindex >= 0) ? g_playindex : 2;
	} else {
		g_playindex = index;
	}
	DBG("set_playindex: [index = %d, g_playindex = %d]", index, g_playindex);
}

/**
 * @param playindex index in playlist
 */
void set_playinfo(int8_t playindex)
{
	char *app_res_path = app_get_resource_path();

	snprintf(audio_file, sizeof(audio_file), "%s/%s", app_res_path, g_playlist[playindex].filename);
	snprintf(title, sizeof(title), "%s", g_playlist[playindex].title);
	snprintf(artist, sizeof(artist), "%s", g_playlist[playindex].artist);
	free(app_res_path);

	DBG("set_playinfo: [index = %d, title = %s, artist = %s]", playindex, title, artist);
}

char* get_artist()
{
	return artist;
}

char* get_title()
{
	return title;
}

/* player : init player */
bool user_player_init()
{
	FN_CALL;

	int ret;
	ret = player_create(&g_player);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_create is failed [%d]", ret);
		return false;
	}
	ret = player_set_looping(g_player, true);
	if (ret != PLAYER_ERROR_NONE) {
		ERR("player_set_looping is failed [%d]", ret);
		return false;
	}

	/*
	 * default playmode  = "stop"
	 * default playindex = 0
	*/
	set_playmode(1);
	set_playindex(0);
	set_playinfo(g_playindex);

	return true;
}
