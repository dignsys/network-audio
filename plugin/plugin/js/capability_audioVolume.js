/*
 * Copyright (c) 2015 - 2017 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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

var capabilityAudioVolume = {
	'href' : "/capability/audioVolume/main/0",
	'value' : "50",
	'muteState' : false,

	'update' : function() {
		ocfDevice.getRemoteRepresentation(this.href, this.onRepresentCallback);
	},

	'onRepresentCallback' : function(result, deviceHandle, uri, rcsJsonString) {
		scplugin.log.debug(className, arguments.callee.name, result);
		scplugin.log.debug(className, arguments.callee.name, uri);

		if (result == "OCF_OK" || result == "OCF_RESOURCE_CHANGED" || result == "OCF_RES_ALREADY_SUBSCRIBED") {
			if(rcsJsonString["volume"] === undefined || rcsJsonString["mute"] === undefined) return;
			capabilityAudioVolume.value = rcsJsonString["volume"];
			capabilityAudioVolume.muteState = rcsJsonString["mute"];

			var styleText = '#' + 'volume_value' + '::-webkit-slider-runnable-track{background-size:' + capabilityAudioVolume.value + '% 100%} ';
			inlineStyle.textContent = styleText;
			document.getElementById("volume_value").value = capabilityAudioVolume.value;
			var image = document.getElementById("muteButton");
			var volume = document.getElementById("volume_value");
			if (capabilityAudioVolume.muteState == false) {
				image.src = "res/controller_ic_unmute.png";
				volume.disabled = false;
			} else {
				image.src = "res/controller_ic_mute.png";
				volume.disabled = true;
			}
		}
	},

	"clearBg" : function (image) {
		image.style.backgroundColor = "white";
	},

	'setVolume' : function(value) {
		scplugin.log.debug(className, arguments.callee.name, "audioVolume : " + value);
		var setRcsJson = {};
		setRcsJson["volume"] = value;
		setRcsJson["mute"] = this.muteState;
		ocfDevice.setRemoteRepresentation(this.href, setRcsJson, this.onRepresentCallback);
	},

	'setMute' : function(value) {
		scplugin.log.debug(className, arguments.callee.name, "audioVolume (mute): " + value);
		var image = document.getElementById("muteButton");
		image.style.backgroundColor = "cyan";
		var setRcsJson = {};
		setRcsJson["volume"] = this.value;
		setRcsJson["mute"] = value;
		ocfDevice.setRemoteRepresentation(this.href, setRcsJson, this.onRepresentCallback);
		setTimeout(this.clearBg, 500, image);
	},

	'muteToggle' : function() {
		if (this.muteState == false) {
			this.setMute(true);
		} else {
			this.setMute(false);
		}
	}
}
