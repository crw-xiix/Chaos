let packetBase = require('./packetBase.js');

class packet extends packetBase {
    constructor() {
        super();
    }

    /**
     * Create sort-of unique ID
     */
    static getUniqueID() {
        function s4() {
            return Math.floor((1 + Math.random()) * 0x10000).toString(16).substring(1);
        }
        return s4() + s4() + '-' + s4();
    }

    /**
     * Message packet: Identify client for who they are
     * @param {*} id 
     */
    static identify(id) {
        let p = new packet();
        p.type = 100;
        p.id = id;
        p.x = 1;
        p.y = 1;
        return JSON.stringify(p);
    }

    /**
     * Message packet: Disconnected client information
     * @param {*} id 
     */
    static disconnect(id) {
        let p = new packet();
        p.type = 900;
        p.id = id;
        p.msg = new Date().toTimeString();
        return JSON.stringify(p);
    }

    /**
     * Message packet: Heartbeat
     * @param {*} clientCount 
     */
    static heartbeat(clientCount) {
        let p = new packet();
        p.type = 0;
        p.msg = new Date().toTimeString();
        p.c = clientCount;
        return JSON.stringify(p);
    }

    /**
     * Message packet: Coordinate
     * @param {*} id 
     * @param {*} player 
     */
    static coordinate(id, player) {
        let p = new packet();
        p.type = 1;
        p.id = id;
        p.x = player.x;
        p.y = player.y;
        p.globalX = player.globalX;
        p.globalY = player.globalY;
        return JSON.stringify(p);
    }
}
module.exports = packet;