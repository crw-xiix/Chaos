"use strict";

let s = require("./server.js");


let map = new Map();
let roomCode = 0;
        
function rc() {
    let tempRoomCode = roomCode;
    let x = '';
    x = x + String.fromCharCode((tempRoomCode % 26)+65);
    tempRoomCode = tempRoomCode / 26;
    x = x + String.fromCharCode((tempRoomCode % 26)+65);
    tempRoomCode = tempRoomCode / 26;
    x = x + String.fromCharCode((tempRoomCode % 26)+65);
    tempRoomCode = tempRoomCode / 26;
    x = x + String.fromCharCode((tempRoomCode % 26)+65);
    tempRoomCode = tempRoomCode / 26;
    roomCode++;
    roomCode = roomCode % (Math.pow(26,4));
    return x;
}
;

function create(d, id, ws) {
    let data = null;
    console.log("Message in");
    try {
        console.log(d);
        data = JSON.parse(d);
        
    } catch (e) {
        console.log("Parse Fail");
        
        return;
    }
    switch (data.request) {
        case "create":
            let roomCode = rc();
            let room = JSON.parse(`{"${roomCode}": []}`);
            room[roomCode].push(ws.id);
            map.set(roomCode, [JSON.stringify(room)]);
            console.log("ROOM CREATED:"+roomCode);
            ws.send(`{"request":"create", "roomcode":"${roomCode}"}`);
            
            break;
            
        case "join":
            if (map.has(data.roomcode)) {
                let code = data.roomcode.toString();
                let mapRoom = JSON.parse(map.get(code)[0])[code];
                if (!mapRoom.includes(ws.id)) {
                    mapRoom.push(ws.id);
                    console.log(`User ${ws.id} Joined ${code}`);
                } else {
                    console.log("User Has Already Joined");
                }
                ;
            };
            break;
    };
}


function sendMsg(m, id) {
    wss.clients.forEach((client) => {
        if (client.id === id) {
            client.send(m);
        }
        ;
    });
}

exports.create = create;