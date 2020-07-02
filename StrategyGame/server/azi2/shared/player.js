let helper = require('./helper.js');

class player {
    constructor(id, x, y) {
        this.id = id;
        this.x = x;
        this.y = y;
        this.globalX = 0;
        this.globalY = 0;
        this.connected = true;
    }

    /**
     * Move player by given offset
     * @param {*} gameMap 
     * @param {*} x 
     * @param {*} y 
     */
    moveOffset(gameMap, x, y) {
        var oldPX = this.x;
        var oldPY = this.y;
        var oldGX = this.globalX;
        var oldGY = this.globalY;
    
        if (this.x < 16 || this.x > 83) {
            this.x += x;
        } else {
            this.x += x;
            this.globalX += x;
        }
        if (this.y < 12 || this.y > 88) {
            this.y += y;
        } else {
            this.y += y;
            this.globalY += y;
        }
        if (gameMap[(this.x)+(this.y)*100]===0) {
            this.x = oldPX;
            this.y = oldPY;
            this.globalX = oldGX;
            this.globalY = oldGY;
        }
    
        this.x = helper.constrain(this.x, 0, 99);
        this.y = helper.constrain(this.y, 0, 99);
        this.globalX = helper.constrain(this.globalX, 0, 100-1024/32);
        this.globalY = helper.constrain(this.globalY, 0, 100-800/32);
    }
}
module.exports = player;