My awesome tampermonkey script

This chrome extension is basically a simple version of tampermonkey.

Currently, it injects code into chatgpt to get rid of an error that was occuring on my old macbook. It's equivalent to pasting the injection code into the javascript console.

It'll run on websites defined in the "matches" field of the manifest.json file

The code that actually runs is in content.js.  Its setup to create a script element so that the javascript code actually runs within the window.  Otherwise it apparently doesn't interact with the webpage directly.  At least, not the code that I wanted to run below.

/*
   if (!Array.prototype.toSorted) {
     Array.prototype.toSorted = function(compareFn) {
       return Array.from(this).sort(compareFn);
     };
   }
*/


This code should be easy to modify.  Simply change the matches field in manifest.json and change codeToInject string in content.js and it should be good to go.  You can use alert("hello world") or console.log(...) or something to confirm that the script is running.


