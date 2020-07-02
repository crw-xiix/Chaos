class packetBase {
    constructor() {
        this.type = 0;
        this.id = '';
        this.x = 0;
        this.y = 0;
        this.globalX = 0;
        this.globalY = 0;
        this.msg = '';
        this.c = 0;
    }
}
module.exports = packetBase;