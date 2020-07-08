
/*jslint node: true */
"use strict";
let https = require('https');
let express = require('express');
let SocketServer = require('ws').Server;
let path = require('path');
let fs = require("fs");
let m = require("./message.js");


const { WSASERVICE_NOT_FOUND } = require('constants');


let PORT = 82;
const INDEX = path.join(__dirname, 'public/index.html');
const server = express()
    .use(express.static('public'))
    .use((req, res) => res.sendFile(INDEX) )
    .listen(PORT, () => {
        console.log(`Listening on ${ PORT }`);
    });
const wss = new SocketServer({ server });
let players = new Map();

let num = 0;

try {	
wss.on('connection', (ws) => {
    ws.id = num++;
    players.set('id', ws.id);
    //ROOM CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //players.push(..); // Add client to list

    ws.send(`Your Unique ID is: ${ws.id}`); // Tell client who they are
    
    ws.on('close', () => {
        console.log(`${ws.id}`);
	    players.delete('id', ws.id);
	    console.log(players);
    });
    
    ws.on('error', (x) => console.log(x));

    ws.onmessage = function(event) {
        m.create(event.data, ws.id, ws);
    };
    
});
} catch {
   console.log("err");
}
// Server heartbeat
setInterval(() => {
    wss.clients.forEach((client) => {
        client.send(`${client.id} is still alive. \r \n`);
	
    });
}, 30000);
sendMsg("t");
function sendMsg(m, id) {
    wss.clients.forEach((client) => {
        if (client.id === id) {
            client.send(m);
        };
    });
}

exports.sendMsg = sendMsg;