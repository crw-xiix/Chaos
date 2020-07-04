
/*jslint node: true */
"use strict";
let https = require('https');
let express = require('express');
let SocketServer = require('ws').Server;
let path = require('path');
let fs = require("fs");


let PORT = 82;
const INDEX = path.join(__dirname, 'public/index.html');
const server = express()
        .use(express.static('public'))
        .use((req, res) => res.sendFile(INDEX))
        .listen(PORT, () => {
            console.log(`Listening on ${ PORT }`);
        });
        
        
const wss = new SocketServer({server});
let players = new Map();
let map = new Map();
let roomC1 = 65,
        roomC2 = 65,
        roomC3 = 65,
        roomC4 = 65
let num = 0;

function rc() {
    let x = String.fromCharCode(roomC1) + String.fromCharCode(roomC2) + String.fromCharCode(roomC3) + String.fromCharCode(roomC4);
    if (roomC4 < 90) {
        roomC4++;
    }
    if (roomC3 < 90 && roomC4 === 90) {
        roomC3++;
    }
    if (roomC2 < 90 && roomC3 === 90) {
        roomC2++;
    }
    if (roomC1 < 90 && roomC2 === 90) {
        roomC1++;
    }
    return x;
}


wss.on('connection', (ws) => {
    try {
        ws.id = num++;
        players.set('id', ws.id);
        //ROOM CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //players.push(..); // Add client to list
        ws.send(`Your Unique ID is: ${ws.id}`); // Tell client who they are

        ws.on('close', () => {
            // Send all clients message about disconnected remote user
            console.log(`${ws.id}`);
            players.delete('id', ws.id);
            console.log(players);
        });
        ws.on('error', (x) => console.log(x));
        ws.onmessage = function (event) {
            console.log(event.data);
            //var msg = JSON.parse(event.data);
            if (event.data.startsWith("{")) {
                let data = JSON.parse(event.data);
                console.log(data.request);
                switch (data.request) {
                    case "create":
                        let roomCode = rc();
                        let room = JSON.parse(`{"${roomCode}": []}`);
                        room[roomCode].push(ws.id);
                        map.set(roomCode, [JSON.stringify(room)]);
                        console.log("ROOM CREATED");
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
                        }
                        ;
                        break;
                };
            }
        };
    } catch (e) {
        console.log(e.toString());
        console.log("err");
    };
    });

// Server heartbeat
setInterval(() => {
    wss.clients.forEach((client) => {
        client.send(`${client.id} is still alive. \r \n`);

    });
}, 30000);

