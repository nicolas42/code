// Import Math object into global namespace
a = Object.getOwnPropertyNames(Math)
for(i=0; i<a.length; i+=1) {
	eval(a[i] + "=" + "Math." + a[i]);
}

// Define some convenience
const e = Math.E
const pi = Math.PI
function degrees(a){ return a/pi*180 }
function radians(a) { return a*pi/180 }
// toFixed(n) rounds to that many decimal places


function addPolar(a,b,c,d) {

	b=radians(b);
	d=radians(d);
	
	// Add Polar Coordinates a,b and c,d
	x=a*cos(b)+c*cos(d);
	y=a*sin(b)+c*sin(d);
	m=sqrt(pow(x,2)+pow(y,2)); // magnitude
	d=degrees(atan(y/x));	// direction

	// fix quadrant ( atan() 
	if ( ( d < 0 && y > 0 ) || ( d > 0 && y < 0 ) ) {
		d += 180;
	}
	// Make positive
	if ( d < 0 ) {
		d += 360;
	}
	return [x, y]
}
// addPolar(5,140,3,70)

