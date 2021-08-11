function mandelbrot(canvas) {
	"use strict";

	// This mandelbrot takes all its parameters from the url and also updates the url which is neat
	// but this prevents it from being embedded in a larger website with other items

	// optionally take arguments from url
	// draws mandelbrot image
	// register event handlers for left and right mouse clicks
	// left click zooms in right click zooms out

	var m; // mandelbrot entity

	function main() {

		// default parameters
		m = { x: 0, y: 0, zoom: 1, img: -1 }
		get_parameters_from_url(m, window.location.href)
	
		canvas.width = 500;
		canvas.height = 500;
		// get image from canvas
		m.img = canvas.getContext("2d").getImageData(0, 0, canvas.width, canvas.height);
	
		
		draw_mandelbrot(true);
		update_url_without_refreshing_page();
		// respond to left and right mouse clicks
		canvas.addEventListener("mousedown", on_mousedown, false);
		// disable context menu
		canvas.addEventListener("contextmenu", (e) => { e.preventDefault(); });

	}

	function draw_mandelbrot(max_iterations_supplied = false) {

		var img = m.img;

		// the first time the page is loaded max_iterations can be overrided with m url parameter
		if (max_iterations_supplied === false || typeof m.max_iterations === "undefined") {
			m.max_iterations = (255 + (20 * Math.log2(m.zoom)));
		}
		

		var black = [0, 0, 0, 255];
		var stride = 4;

		var x, y, zx, zxtemp, zy, cx, cy, rgb, i, in_set, pos;
		var math_height = 4 / m.zoom;
		var math_width = 4 / m.zoom;

		// make black image
		for (i = 0; i < img.data.length; i += stride) {
			img.data[i + 0] = black[0];
			img.data[i + 1] = black[1];
			img.data[i + 2] = black[2];
			img.data[i + 3] = black[3];
		}

		// main loop
		for (y = 0; y < img.height; y += 1) {
			for (x = 0; x < img.width; x += 1) {
				// get math point from image point
				cx = (m.x - math_width / 2) + x * (math_width / img.width);
				cy = (m.y - math_height / 2) + y * (math_width / img.width);
				// image is flipped vertically. numbers go up, pixels go down. who cares
				zx = 0;
				zy = 0;

				in_set = true;
				for (i = 1; i <= m.max_iterations; i += 1) {
					zxtemp = zx * zx - zy * zy + cx;
					zy = 2 * zx * zy + cy;
					zx = zxtemp;
					if (zx * zx + zy * zy > 4) {
						in_set = false;
						break;
					}
				}

				if (in_set === false) {
					pos = y * img.width * stride + x * stride;
					rgb = hsl_to_rgb((i % 255) / 255, 1, 0.5);
					img.data[pos + 0] = rgb[0];
					img.data[pos + 1] = rgb[1];
					img.data[pos + 2] = rgb[2];
					// img.data[pos + 3] = rgb[3]; // don't mess with opacity
				}
			}
		}
		canvas.getContext("2d").putImageData(img, 0, 0);
		console.log(m.max_iterations)
	}


	var on_mousedown = function (e) {
		if (e.which === 1) {
			// get clicked position of mouse cursor
			var rect = e.currentTarget.getBoundingClientRect();
			var x_pixel = e.clientX - rect.left;
			var y_pixel = e.clientY - rect.top;

			var math_height = 4 / m.zoom;
			var math_width = 4 / m.zoom;

			// update globals
			m.x = (m.x - math_width / 2) + x_pixel / (m.img.width / math_width);
			m.y = (m.y - math_height / 2) + y_pixel / (m.img.height / math_height);
			m.zoom *= 2;

		} else if (e.which === 3) { // right click
			// update global
			m.zoom /= 2;
		}

		draw_mandelbrot();
		update_url_without_refreshing_page();
	}


	function get_parameters_from_url(vars, url) {
		// from https://html-online.com/articles/get-url-parameters-javascript/
		var parts = url.replace(/[?&]+([^=&]+)=([^&]*)/gi, function (m, key, value) {
			vars[key] = value;
		});
		return vars;
	}

	function update_url_without_refreshing_page() {
		console.log(m)
		// https://computerrock.com/blog/html5-changing-the-browser-url-without-refreshing-page/
		window.history.replaceState("object or string", "Title", "?x=" + m.x + "&y=" + m.y + "&zoom=" + m.zoom+ "&w=" + m.img.width + "&h=" + m.img.height + "&max_iterations=" + m.max_iterations );
	}

	function hsl_to_rgb(h, s, l) {
		var r;
		var g;
		var b;
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

		var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		var p = 2 * l - q;

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

	main();
}
