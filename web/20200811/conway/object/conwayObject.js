
// How to resize canvas
// https://stackoverflow.com/questions/4938346/canvas-width-and-height-in-html5

var conwayObject = {

evolve: function(canvas, aliveColor, deadColor) {

    // The alpha channel is used to keep track of the number of neighbours

    var image = canvas.getContext("2d").getImageData(0, 0, canvas.width, canvas.height);

    var neighbours;
    var shouldLive; // 1 = live, 0 = die
    var stride = 4;

    // Set all neighbour values to zero
    for (y = 1; y < canvas.height - 1; y = y + 1) {
        for (x = 1; x < canvas.width - 1; x = x + 1) {
            pos = y * canvas.width * 4 + x * 4;

            image.data[pos + 3] = 0; 	// pos + 3 refers to the alpha channel of the pixel
        }
    }

    // Update Neighbors of surrounding cells
    // Add one to the neighbours of all of the surrounding cells
    // (3x3 square around the current cell) if the current cell is alive
    for (y = 1; y < canvas.height - 1; y = y + 1) {
        for (x = 1; x < canvas.width - 1; x = x + 1) {
            pos = y * canvas.width * 4 + x * 4;

            if (image.data[pos + 0] === aliveColor[0]) { // currCell.isAlive

                image.data[pos + 3 - (canvas.width - 1) * stride] += 1;
                image.data[pos + 3 - (canvas.width) * stride] += 1;
                image.data[pos + 3 - (canvas.width + 1) * stride] += 1;
                image.data[pos + 3 - 1 * stride] += 1;
                // position of the current cell
                image.data[pos + 3 + 1 * stride] += 1;
                image.data[pos + 3 + (canvas.width - 1) * stride] += 1;
                image.data[pos + 3 + (canvas.width) * stride] += 1;
                image.data[pos + 3 + (canvas.width + 1) * stride] += 1;
            }
        }
    }

    // Update who's alive and who's dead
    for (y = 1; y < canvas.height - 1; y = y + 1) {
        for (x = 1; x < canvas.width - 1; x = x + 1) {
            pos = y * canvas.width * 4 + x * 4;
            neighbours = image.data[pos + 3];
            shouldLive = 0; // determines whether cell lives or dies

            if (image.data[pos + 0] === aliveColor[0]) { // currCell.isAlive
                if (neighbours < 2) {
                    shouldLive = 0; // false
                } else if ((neighbours === 2) || (neighbours === 3)) {
                    shouldLive = 1; // true
                } else if (neighbours > 3) {
                    shouldLive = 0; // false
                }
            } else {
                if (neighbours === 3) {
                    shouldLive = 1; // true
                }
            }
            if (shouldLive === 1) {
                image.data[pos + 0] = aliveColor[0];
                image.data[pos + 1] = aliveColor[1];
                image.data[pos + 2] = aliveColor[2];
                image.data[pos + 3] = aliveColor[3];
            } else {
                image.data[pos + 0] = deadColor[0];
                image.data[pos + 1] = deadColor[1];
                image.data[pos + 2] = deadColor[2];
                image.data[pos + 3] = deadColor[3];
            }
        }
    }

    canvas.getContext("2d").putImageData(image, 0, 0);
},
drawRandomPoints: function(canvas, deadColor, aliveColor){

    // Draw initial random points to fill 10% of the usable space
    var ctx = canvas.getContext("2d");
    var rgbaDeadColor = 'rgba(' + deadColor[0] + ',' + deadColor[1] + ',' + deadColor[2] + ',' + deadColor[3] + ')';
    var rgbaAliveColor = 'rgba(' + aliveColor[0] + ',' + aliveColor[1] + ',' + aliveColor[2] + ',' + aliveColor[3] + ')';
    ctx.fillStyle = rgbaDeadColor // needs this format apparently
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (i = 0; i < 0.1 * canvas.width * canvas.height; i += 1) {
        var x = Math.round(Math.random() * (canvas.width - 1));
        var y = Math.round(Math.random() * (canvas.height - 1));
        ctx.fillStyle = rgbaAliveColor;
        ctx.fillRect(x, y, 1, 1);
    }
},

defaults: {
    canvas: document.querySelector("canvas"), 
    height: 200,
    width: 200,
    aliveColor: [0, 0, 255, 255], 
    deadColor: [255, 255, 255, 255], 
    delay: 200
},

pause: function(){clearInterval(this.timerID); },
play: function(){this.timerID = setInterval(()=>{this.evolve(this.canvas, this.aliveColor, this.deadColor)}, this.delay);},

init: function(){
    this.canvas = this.defaults.canvas,
    this.canvas.height = this.defaults.height,
    this.canvas.width = this.defaults.width,
    this.deadColor = this.defaults.deadColor,
    this.aliveColor = this.defaults.aliveColor,
    this.delay = this.defaults.delay,
    this.paused = this.defaults.paused,

    this.drawRandomPoints(this.canvas, this.deadColor, this.aliveColor);
    this.play();

},

canvas: undefined,
deadColor: undefined,
aliveColor: undefined,
delay: undefined,
paused: undefined,
timerID: undefined,

// canvas.addEventListener("mousedown",	pause,					false);
// canvas.addEventListener("mouseup",		play,					false);
// canvas.addEventListener("mousemove",	drawClickedPosition,	false);
};

