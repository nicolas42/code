<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width">
  <title>JS Bin</title>
</head>
<body>

  <!-- An Image and the Console if needed -->
<img id="img01" width="400" height="400">
<p id="console"></p>


</body>
  
<script>

// Conway's Game Of Life in all its monochromatic 100x100 pixel glory
//
// There's a lot of 4's in this program because there's 4 bytes in a pixel.
// The number of neighbours of a cell is kept in its alpha channel until it's needed
// A cell is seen as being alive if it's red channel is 0 (indicating that the pixel is black)
//
// Creating an image in javascript sucks.
// create a HTML canvas element then get its 2 dimensional context
// then get the image itself from that

function print(str){
	document.querySelector('#console').innerHTML += str;
}

function println(str){
	document.querySelector('#console').innerHTML += (str + "<br>");
}

// Initialize Image
if (true) {  
  
  var yellow = [ 255, 255, 0, 255 ];
  var orange = [ 255, 150,10,255 ];
  var white = [255,255,255,255];
  var black = [0,0,0,255];

  var width = 100;
  var height = 100;

  var canvas=document.createElement("canvas");
  canvas.width=width;
  canvas.height=height;

  // get the image from the context - image: {width, height, data}
  var ctx=canvas.getContext("2d");
  var imgData=ctx.getImageData(0,0,width, height);
  var data=imgData.data;

  // Make White Image
   for (var i = 0; i < data.length; i += 4) {
    data[i+0] = white[0];
    data[i+1] = white[1];
    data[i+2] = white[2];
    data[i+3] = white[3];
   }


  // gosper glider gun
  var coords = [2, 6, 2, 7, 3, 6, 3, 7, 12, 6, 12, 7, 12, 8, 13, 5, 13, 9, 14, 4, 14, 10, 15, 4, 15, 10, 16, 7, 17, 5, 17, 9, 18, 6, 18, 7, 18, 8, 19, 7, 22, 4, 22, 5, 22, 6, 23, 4, 23, 5, 23, 6, 24, 3, 24, 7, 26, 2, 26, 3, 26, 7, 26, 8, 36, 4, 36, 5, 37, 4, 37, 5];
  // coords is a list of x,y coordinates

  // draw that gosper thing
  var i;
  for(i=0;i<coords.length; i+=2){
      var x = coords[i];
      var y = coords[i+1];

      var pos = (y*width*4) + (x*4)
      data[pos+0] = black[0];
      data[pos+1] = black[1];
      data[pos+2] = black[2];
      data[pos+3] = black[3];
  }

  // actually draw image - put data in canvas context
  ctx.putImageData(imgData,0,0);
  document.querySelector('#img01').src = canvas.toDataURL();

}
  
// evolve();
window.setInterval(evolve, 20);

function evolve(){

  var x;
  var y;
  var pos;

  // zero neighbors
  for (y = 1; y < height-1; y = y + 1) {
    for (x = 1; x < width-1; x = x + 1) {
      pos = y*width*4 + x*4;

      data[pos+3] = 0 // keep number of neighbours in alpha channel
    }
  }


  // update neighbors
  for (y = 1; y < height-1; y = y + 1) {
    for (x = 1; x < width-1; x = x + 1 ){
      pos = y*width*4 + x*4;

      if (data[pos+0] === black[0]) { // currCell.isAlive
				// alpha channel contains number of neighbours (red pixel position + 3)
        data[pos-(4*width)-4+3] += 1
        data[pos-(4*width)+3] += 1
        data[pos-(4*width)+4+3] += 1
        data[pos-4+3] += 1
        // data[pos]
        data[pos+4+3] += 1
        data[pos+(4*width)-4+3] += 1
        data[pos+(4*width)+3] += 1
        data[pos+(4*width)+4+3] += 1
      }
    }
  }
  
//  Print Neighbours
//  document.querySelector('#console').innerHTML = "";
//  for (y = 1; y < height-1; y = y + 1) {
//    for (x = 1; x < width-1; x = x + 1 ){
//      pos = y*width*4 + x*4;
//
//      print(""+data[pos+3]+" ");
//    }
//      print("<br>");
//  }
  
  // update the living
  for (y = 1; y < height-1; y = y + 1 ){
    for (x = 1; x < width-1; x = x + 1) {
      pos = y*width*4 + x*4;
      var num = data[pos+3] // number of neighbours
      var live = 0; // determines whether cell lives or dies
      
      if (data[pos+0] === black[0]) { // currCell.isAlive
        if (num < 2) {
          live = 0 // false
        } else if ( (num === 2) || (num === 3) ) {
          live = 1 // true
        } else if (num > 3) {
          live = 0 // false
        }
      } else {
        if (num === 3) {
          live = 1 // true
        }
      }
      if (live === 1) {
        data[pos+0] = black[0];
        data[pos+1] = black[1];
        data[pos+2] = black[2];
        data[pos+3] = black[3];
      } else  {
          data[pos+0] = white[0];
          data[pos+1] = white[1];
          data[pos+2] = white[2];
          data[pos+3] = white[3];			
      }
    }
  }

  // actually draw image
  ctx.putImageData(imgData,0,0);
  document.querySelector('#img01').src = canvas.toDataURL();
  

}

 
  
</script>
  
</html>