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

var capabilityMediaPlayback = {
	'href' : "/capability/mediaPlayback/main/0",
	'value' : [ "stop" ],
	'changeColor' : function (coll, color) {
		for(var i=0, len=coll.length; i<len; i++)
		{
			coll[i].style["background-color"] = color;
		}
	},

	'update' : function() {
		ocfDevice.getRemoteRepresentation(this.href, this.onRepresentCallback);
	},

	'onRepresentCallback' : function(result, deviceHandle, uri, rcsJsonString) {
		scplugin.log.debug(className, arguments.callee.name, result);
		scplugin.log.debug(className, arguments.callee.name, uri);

		if (result == "OCF_OK" || result == "OCF_RESOURCE_CHANGED" || result == "OCF_RES_ALREADY_SUBSCRIBED") {
			if(rcsJsonString["modes"] === undefined) return;
			capabilityMediaPlayback.value[0] = rcsJsonString["modes"];

			var image = document.getElementById("playButton");
			if (capabilityMediaPlayback.value[0] == "play") {
				image.disabled = false;
				image.src = "res/controller_ic_play.png";
			} else if (capabilityMediaPlayback.value[0] == "pause") {
				image.disabled = false;
				image.src = "res/controller_ic_pause.png";
			} else {
				image.disabled = true;
				image.src = "res/controller_ic_play.png";
			}
		}
	},

	'set' : function(value) {
		scplugin.log.debug(className, arguments.callee.name, "playback : " + value);
		var coll = document.getElementsByClassName("play-button");
		this.changeColor(coll,"cyan");
		var setRcsJson = {};
		setRcsJson["modes"] = [value];
		ocfDevice.setRemoteRepresentation(this.href, setRcsJson, this.onRepresentCallback);
		setTimeout(this.changeColor, 500, coll, "white");
	},

	'toggle' : function() {
		if (this.value[0] == "play") {
			this.set("pause");
		} else if(this.value[0] == "stop") {
			this.set("play");
		} else {
			this.set("play");
		}
	}
}
