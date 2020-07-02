class helper {
    /**
     * Constrain given number between min and max values
     * @param {*} number 
     * @param {*} min 
     * @param {*} max 
     */
    static constrain(number, min, max) {
        if (number < min ) number = min;
        if (number > max ) number = max;
        return number;
    }
}
module.exports = helper;