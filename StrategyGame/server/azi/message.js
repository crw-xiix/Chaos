"use strict";

let s = require("./server.js");

let map = new Map();
let roomC1 = 65,
roomC2 = 65,
roomC3 = 65,
roomC4 = 65;

function rc() {
	let x = String.fromCharCode(roomC1) + String.fromCharCode(roomC2) + String.fromCharCode(roomC3) + String.fromCharCode(roomC4);
	if (roomC4 < 90) {
	   roomC4++;
	}; 
	if (roomC3 < 90 && roomC4 === 90) {
	   roomC3++;
	};
	if (roomC2 < 90 && roomC3 === 90) {
	   roomC2++;
	};
	if (roomC1 < 90 && roomC2 === 90) {
	   roomC1++;
	};
	return x;
};

function create(d, id,ws) {
    if (d.data.startsWith("{")) {
		let data = JSON.parse(d.data);
		switch(data.request) {
		    case "create":
			let roomCode = rc();
			let room = JSON.parse(`{"${roomCode}": []}`);
			room[roomCode].push(ws.id);
			map.set(roomCode, [JSON.stringify(room)]);
			console.log("ROOM CREATED");
			s.sendMsg(`{"request":"create", "roomcode":"${roomCode}"}`, id);
            break;
            
            case "join":
			if(map.has(data.roomcode)) {
			let code = data.roomcode.toString();
			let mapRoom = JSON.parse(map.get(code)[0])[code];
		        if (!mapRoom.includes(ws.id)) {
			       mapRoom.push(ws.id);
			       console.log(`User ${ws.id} Joined ${code}`);
			    } else {
			      console.log("User Has Already Joined");
		        };
			};
	        break;
		};
		
	};
}

exports.create = create;