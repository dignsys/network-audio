#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <app_common.h>
#include "st_things.h"
#include "player.h"
#include "network_audio.h"

#define AUDIO_FILE_NAME "sample.mp3"

static player_h g_player;

static char audio_file[128];

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
		ERR("player_set_uri is failed [%d]", ret);
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

	char *app_res_path = app_get_resource_path();
	snprintf(audio_file, sizeof(audio_file), "%s/%s", app_res_path, AUDIO_FILE_NAME);
	free(app_res_path);

	return true;
}
