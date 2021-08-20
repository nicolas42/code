/*
How to do modules in node reasonably easily

Run this to demo

var demo_module = require('./demo_module.js');
demo_module.hello();

*/

exports.hello = function(){ console.log("I don't know why you say goodbye, I say hello.  Hello, hello"); }

exports.goodbye = function(){ console.log('goodbye\n'); }
