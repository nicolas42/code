// Import Math object into global namespace
a = Object.getOwnPropertyNames(Math)
for(i=0; i<a.length; i+=1) {
	eval(a[i] + "=" + "Math." + a[i]);
}

// for convenience
const e = Math.E
const pi = Math.PI

