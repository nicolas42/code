// jquery pffft
// var $ = function(id) { return document.querySelector(id); }

function hue2rgb(p, q, t) {
    if (t < 0) {
        t += 1;
    }
    if (t > 1) {
        t -= 1;
    }
    if (t < 1 / 6) {
        return p + (q - p) * 6 * t;
    }
    if (t < 1 / 2) {
        return q;
    }
    if (t < 2 / 3) {
        return p + (q - p) * (2 / 3 - t) * 6;
    }
    return p;
}

function hsl_to_rgb(h, s, l) {
    let r;
    let g;
    let b;

    let q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    let p = 2 * l - q;

    if (s === 0) {
        r = 1;
        g = 1;
        b = 1; // achromatic
    } else {

        r = hue2rgb(p, q, h + 1 / 3);
        g = hue2rgb(p, q, h);
        b = hue2rgb(p, q, h - 1 / 3);
    }

    return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
}

function pixel_coordinates_to_mandelbrot_coordinate(canvas, mandelbrot, x, y)
{
    // at a particular zoom level the pixel space is defined to have a particular size in mandelbrot space
    // the width is 4/zoom and the height is smaller than that in accordance to the aspect ratio

    var aspect_ratio = canvas.width / canvas.height 

    var offset_x = ( x - (canvas.width / 2) ) / ( canvas.width / 2 ) * ( 2 / mandelbrot.zoom );
    var offset_y = ( y - (canvas.height / 2) ) / ( canvas.height / 2 ) * ( 2 / mandelbrot.zoom ) / aspect_ratio;

    var cx = mandelbrot.x + offset_x;
    var cy = mandelbrot.y + offset_y;

    return [cx, cy]; 
}

function draw_mandelbrot(canvas, mandelbrot) {

    var im = canvas.getContext("2d").getImageData(0, 0, canvas.width, canvas.height);

    // main loop
    // x and y are the pixel coordinates which starts top left and goes down
    for (var y = 0; y < im.height; y += 1) {
        for (var x = 0; x < im.width; x += 1) {

            var cx, cy;
            [cx, cy] = pixel_coordinates_to_mandelbrot_coordinate(canvas, mandelbrot, x, y);

            var zx = 0;
            var zy = 0;

            var in_set = true;
            var num_iterations = 1;
            for ( ; num_iterations <= mandelbrot.max_iterations; num_iterations += 1 ) {
                // z = z^2 + c
                // z = (zx+izy)^2 + (cx+icy) = ((zx)^2 - (zy)^2 + cx) + i(2xy + cy)
                var zx_temp = zx * zx - zy * zy + cx;
                zy = 2 * zx * zy + cy;
                zx = zx_temp;
                // if the length of complex vector exceeds 4 then assume the pixel is not in the set
                if (zx * zx + zy * zy > 4) {
                    in_set = false;
                    break;
                }
            }

            // color in pixel
            let black = [0, 0, 0, 255];
            let stride = 4;
            var pos = (y * im.width * stride) + (x * stride);
            if (in_set) {
                im.data[pos + 0] = black[0];
                im.data[pos + 1] = black[1];
                im.data[pos + 2] = black[2];
                im.data[pos + 3] = black[3];
            } else {
                // hue is determined by the number of iterations taken
                var rgb = hsl_to_rgb((num_iterations % 255) / 255, 1, 0.5);
                im.data[pos + 0] = rgb[0];
                im.data[pos + 1] = rgb[1];
                im.data[pos + 2] = rgb[2];
                im.data[pos + 3] = black[3]; // no opacity
            }


        }

    }
    canvas.getContext("2d").putImageData(im, 0, 0);

    // return img;
}


function update_mandelbrot_from_click(parameters, event) 
{
    // zoom in on left click, zoom out on right click
    // get position of clicked mouse cursor
    var rect = event.currentTarget.getBoundingClientRect();
    var x = event.clientX - rect.left;
    var y = event.clientY - rect.top;

    [ parameters.x, parameters.y ] = pixel_coordinates_to_mandelbrot_coordinate(canvas, parameters, x, y);

    if (event.which === 1) {
        parameters.zoom *= 2;
    } else if (event.which === 3) {
        parameters.zoom /= 2;
    }

}

function toggle_fullscreen( canvas, mandelbrot )
{ 
    mandelbrot.fullscreen = !mandelbrot.fullscreen; 
    // console.log( mandelbrot.fullscreen ); 
    if ( mandelbrot.fullscreen ) {
        canvas.width = window.innerWidth - 20;
        canvas.height = window.innerHeight - 20;
    } else {
        canvas.width = mandelbrot.w;
        canvas.height = mandelbrot.h;
    }
}

function load_object_from_url(parameters)
{
    // the argument allows for default parameters to be overriden
    window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function (_, key, value) {
        var result = parseFloat(value);
        if ( !isNaN(result) ) parameters[key] = result;
    });
    return parameters;
}

function save_object_to_url(obj)
{
    var str = "?"
    Object.keys(obj).forEach(function(key,index) {
        // key: the name of the object key
        // index: the ordinal position of the key within the object 
        str = str + key +"="+ (obj[key]).toString() +"&";
    });

    window.history.replaceState(
        "object or string", "Title", str // "?x=" + p.x + "&y=" + p.y + "&zoom=" + p.zoom + "&max_iterations=" + p.max_iterations
    );
}

// make element tree
function elt(type, ...children) {
    // from eloquent javascript
    // var tree = elt( "div", elt( "button", "toggle fullscreen") );
    // document.body.appendChild( tree );

    let node = document.createElement(type);
    for (let child of children) {
        if (typeof child != "string") node.appendChild(child);
        else node.appendChild(document.createTextNode(child));
    }
    return node;
}

function hide_scrollbars() {
    document.documentElement.style.overflow = 'hidden';  // firefox, chrome
    document.body.scroll = "no"; // ie only
}

function show_scrollbars() {
    document.documentElement.style.overflow = 'auto';  // firefox, chrome
    document.body.scroll = "yes"; // ie only
}


function toggle_content_editable(){
    // html element
    if ( document.documentElement.contentEditable === 'true' ) 
    {
        document.documentElement.contentEditable = 'false'; 
    } 
    else {
        document.documentElement.contentEditable = 'true';
    }
}


function append_elements(parent, arr )
{
    for ( var i=0; i<arr.length; i+= 1){
        // console.log(arr[i])
        var child = document.createElement(arr[i][0]);
        if ( arr[i][1] !== undefined ) child.innerText = arr[i][1];
        if ( arr[i][0] === "a" ){
            child.href = arr[i][2] ;
        } else {
            // event handler
            if ( arr[i][2] !== undefined && arr[i][3] !== undefined ) child.addEventListener(arr[i][2], arr[i][3])
        }
        parent.appendChild(child);
    }
}


function demo_mandelbrot1()
{
    // draw mandelbrot, set up its event handlers
    var mandelbrot = { 
        x: -0.6999687500000003, y: -0.2901249999999999, zoom: 500, 
        max_iterations: 600, w: 800, h: 500, fullscreen: 0 
    }
    mandelbrot = load_object_from_url(mandelbrot);

    var canvas = document.createElement('canvas');
    canvas.width = mandelbrot.w;
    canvas.height = mandelbrot.h;
    canvas.addEventListener("contextmenu", function (event) { event.preventDefault() } );
    canvas.addEventListener("mousedown",  function(event){ update_mandelbrot_from_click(canvas, mandelbrot, event); save_object_to_url(mandelbrot); } );

    draw_mandelbrot(canvas, mandelbrot);


    var buttons = document.createElement("div");

    append_elements(buttons, [ 
        [ "button", "toggle fullscreen",        "click", (e) => toggle_fullscreen( canvas, mandelbrot )   ],
        [ "label", "max iterations" ],
        [ "input", "max iterations",            "keyup", (e) => mandelbrot.max_iterations = parseFloat(elem.children[2].value) ],
        [ "button", "draw",                     "click", (e) =>  draw_mandelbrot( canvas, mandelbrot ) ],
        [ "button", "toggle content editable",  "click", (e) => toggle_content_editable() ],
        [ "button", "reset",                    "click", (e) => { mandelbrot = { x:0,y:0,zoom:1, max_iterations: 600, w: 800, h: 500, fullscreen: 0 }; draw_mandelbrot(canvas, mandelbrot); } ],
    ]);

    document.body.appendChild(canvas)
    document.body.appendChild(buttons)

}



// To Do
// Make object to form function

// <form action="/action_page.php">
// <label for="fname">First name:</label><br>
// <input type="text" id="fname" name="fname" value="John"><br>
// <label for="lname">Last name:</label><br>
// <input type="text" id="lname" name="lname" value="Doe"><br><br>
// <input type="submit" value="Submit">
// </form>


function update_object(obj, new_stuff)
{
    for (var key in new_stuff) {
        obj[key] = new_stuff[key];
    }
}


// save a file
// https://stackoverflow.com/questions/2897619/using-html5-javascript-to-generate-and-save-a-file
// usage
// save_file('test.txt', 'Hello world!');

function save_file(filename, text) {
    var pom = document.createElement('a');
    pom.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(text));
    pom.setAttribute('download', filename);

    if (document.createEvent) {
        var event = document.createEvent('MouseEvents');
        event.initEvent('click', true, true);
        pom.dispatchEvent(event);
    }
    else {
        pom.click();
    }
}

