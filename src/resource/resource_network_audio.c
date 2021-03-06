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
#include "resource_network_audio.h"

// 3 samples for playing
#define NO_OF_PLAYLIST	3
static struct _playlist {
	char*  title;
	char*  artist;
	char*  filename;
} g_playlist[3] = {
	{ "Shine"    , "Declan DP", "Declan-DP-Shine.mp3" },
	{ "Feel Good", "MBB"      , "Feel-Good.wav"       },
	{ "Alive"    , "Ikson"    , "Ikson-Alive.wav"     },
};

player_h g_player;

static int8_t g_playmode;
static int8_t g_playindex;

static char audio_file[128];
static char title[128];
static char artist[128];

/* player : get mute */
bool user_player_is_muted(bool *muted)
{
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

/**
 * @brief  get the current mode
 * @return @c MODE_PLAY: play, MODE_STOP: stop, MODE_PAUSE: pause
 */
play_mode_e get_playmode()
{
	return g_playmode;
}

/**
 * @param[in] mode MODE_PLAY: play, MODE_STOP: stop, MODE_PAUSE: pause
 */
void set_playmode(play_mode_e mode)
{
	g_playmode = mode;
}

/**
 * @brief  get the current location of the playlist
 * @return @c INDEX_INIT: init INDEX_NEXT: increase, INDEX_PREV: decrease
 */
play_index_e get_playindex()
{
	return g_playindex;
}

/**
 * @param[in] index INDEX_INIT: init INDEX_NEXT: increase, INDEX_PREV: decrease
 */
void set_playindex(play_index_e index)
{
	if (INDEX_NEXT == index) {
		g_playindex = (++g_playindex < NO_OF_PLAYLIST) ? g_playindex : 0;
	} else if (INDEX_PREV == index) {
		g_playindex = (--g_playindex >= 0) ? g_playindex : NO_OF_PLAYLIST - 1;
	} else {
		// INDEX_INIT
		g_playindex = 0;
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
	set_playmode(MODE_STOP);
	set_playindex(INDEX_INIT);
	set_playinfo(g_playindex);

	return true;
}
