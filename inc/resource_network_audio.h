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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief capabilities
 */
#define RES_CAPABILITY_AUDIOTRACKDATA_MAIN_0 "/capability/audioTrackData/main/0" /**< audio track data */
#define RES_CAPABILITY_MEDIAPLAYBACK_MAIN_0  "/capability/mediaPlayback/main/0" /**< media play back */

#define PLAY  "play"
#define STOP  "stop"
#define PAUSE "pause"

#define NEXT  "next"
#define PREV  "previous"

/**
 * @brief play mode
 */
typedef enum {
	MODE_PLAY, /**< play */
	MODE_STOP, /**< stop */
	MODE_PAUSE /**< pause */
} play_mode_e;

/**
 * @brief play index
 */
typedef enum {
	INDEX_PREV, /**< previous */
	INDEX_NEXT, /**< next */
	INDEX_INIT  /**< initialize */
} play_index_e;

#ifdef __cplusplus
}
#endif /* __cplusplus */
