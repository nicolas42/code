# Web Shit

go run serve.go

localhost:8080


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
