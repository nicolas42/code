# Get started

Run this

    go run serve.go

then this

    localhost:8080

Then click stuff

# Notes

The go default http server has quite a nice habit of displaying links to all files in a directory if there's no index.html file.  It's neat.
That way you can try all the different stuff quite conveniently.

Also in the future it'd be nice to make a markdown server.  So when a markdown (.md) file is requested it can be dynamically transformed into html.

woo.

There's also a server in node scripts that you could copy to this directory then run but it sucks more.


## AWS Javascript SDK

https://docs.aws.amazon.com/sdk-for-javascript/index.html

version 2 API reference seems handiest


## AWS Credentials

make a json file that looks like this

{ "accessKeyId": "<accessKeyId>", "secretAccessKey": "<secretAccessKey>", "region": "<region>" }

then load it like this

AWS.config.loadFromPath(<the_file.json>);



## Promises

A good page on promises / asynchronous stuff 
https://javascript.info/async



promises seem to be syntactic sugar on callbacks.

callback
do_something(arg, function(){ } );

sugar 1
promise.then( do_other_stuff() )

sugar 2
async function(){
    var response = await do_something()
}


## ArcGIS Mapping

Hussein Nasser - ArcGIS Javascript API Video Playlist
https://www.youtube.com/watch?v=rft4ZecPQcI&list=PLQnljOFTspQUppK8iiIuoQJTAj436IWQz


arcgis examples
https://developers.arcgis.com/javascript/latest/sample-code/
