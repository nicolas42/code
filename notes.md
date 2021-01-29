
Interesting Sources of Software
--------------------------------------------------------------
no mixer configi n /var/lib/alsa/asound.state, you have to unmute your card!
 
stb
https://github.com/nothings/stb
image loader: stb_image.h
image writer: stb_image_write.h
image resizer: stb_image_resize.h
font text rasterizer: stb_truetype.h
typesafe containers: stb_ds.h
 
SDL
suckless
tinygl
beej
lemoda.net
opencv
 
soso
wyos
 
 
Alpine Linux on Virtualbox Notes
--------------------------------------------------------------

IMPORTANT: I have not been able to get audio working on alpine linux in virtualbox 
on a macos host.

 
in system boot order, set hard drive to be the first item
root
setup-alpine
 
vi /etc/apk/repositories # add community repo
apk update
 
adduser nick
visudo # add nick to sudoers
 
install suckless dwm as per this guide
https://wiki.alpinelinux.org/wiki/Dwm
alt+p is used for the search bar in dwm
 
xrandr -s 1440x900
# The option --size/-s can be used with randr version 1.1 or newer
 
xrandr -s 1440x900
 
alt+shift+q quits dwm
startx starts it again
alt+shift+c closes a window
alt+p opens the "start" menu
 
 
 
 

 
 
Alpine Linux on Virtualbox with XFCE
--------------------------------------------------------------
https://wiki.alpinelinux.org/wiki/Xfce_Setup
 
root
setup-alpine
 
vi /etc/apk/repositories
apk update
 
adduser nick
visudo
 
setup-xorg-base 
apk add xfce4 faenza-icon-theme 
exec startxfce4
 
sudo dbus-x11 st chromium 
 
 
To Do
change resolution in dwm -xrandr?
get copy and paste working for virtualbox guest additions



 

 
c++ features to use;
--------------------------------------------------------------
auto
static_cast
auto thing = 0;
static_cast<templated_type*>(the_thing_were_casting);
 
 
tiny unix-like operating system
https://github.com/ozkl/soso
https://github.com/akkartik/mu can run on soso






monitor network traffic
--------------------------------------------------------------
sudo /usr/local/sbin/iftop
wireshark?




 
Beej's Guide to Socket Programming in C
--------------------------------------------------------------
there's stream sockets and datagram sockets.  they correspond to TCP and UDP respectively
when your program does stuff it'll specify application logic and TCP or UDP or something.  This goes on a header to the Then other systems can take care of the IP layer and the physical layer.
[ ethernet / wifi [ IP (routing) [ TCP [ application_protocol [ THE_ACTUAL_DATA ]  ] ] ] ]
IPv4 addresses have 32 bits  128.0.0.1/30  
CIDR side note: The number can be split up into network and host numbers using the CIDR /30 bit which specifies that the first 30 bits are the network and the last 2 are for the computers on that network.  I suppose this effectively increases the number of network addresses by about 2X.
IPv6 have 128 bits: abc0:ff00::51 
Zeroes can be left out with the double colon notation.
 
Port numbers specify the program or the class of program.  There's established conventions as to which port numbers different programs use.  Ports under 1024 are often considered special, and usually require special OS privileges to use.
 
Big endian is how regular numbers are written
Network Byte Order is big endian
Host Byte Order varies
 
There are functions that convert between these byte orders
short (2 bytes).  long (4 bytes)
htons()  host to network short
 



 
nginx - getting started on macos
--------------------------------------------------------------
static server
Hussein Nasser
http://nginx.org/en/docs/beginners_guide.html
 
On macos put this into /usr/local/etc/nginx/nginx.conf.  
 
http {
    server {
        listen 8080;
        root /Users/nick/Downloads/code/nginx/;
 
    }
}
 
events { }
 
Change the root directory and put an index.html file in there as well as whatever else you might want.  
 
then run "nginx"
 
then go to "localhost:8080" in a browser
 
:)
 
to stop "nginx -s stop"
to reload the config file "nginx -s reload"
there's plenty of other signals and config files can be much more complicated than this
 






Write your own Operating System in 1 hour
--------------------------------------------------------------
https://www.youtube.com/watch?v=1rnA6wpF0o4
http://github.com/nicolas42/wyoos

interesting os stuff

http://wyoos.org
http://mikeos.sourceforge.net/write-your-own-os.html
http://wiki.osdev.org
http://www.linuxfromscratch.org/
https://www.amazon.com/Modern-Operating-Systems-Andrew-Tanenbaum/dp/013359162X
https://os.phil-opp.com/
https://www.youtube.com/user/WhatsACreel x64 programming tutorials
https://github.com/includeos/IncludeOS minimal unikernel operating system for C++ services


