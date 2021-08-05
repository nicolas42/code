   0 sudo setup-xorg-base
   1 sudo nano /etc/apk/repositories
   2 sudo apk update
   3 apk install git make gcc
   4 apk add git make gcc
   5 sudo apk add git make gcc
   6 sudo apk add git make gcc g++ libx11-dev libxft-dev libxinerama-dev ncurses
   7 sudo apk add dbus-x11
   8 sudo apk add adwaita-gtk2-theme adwaita-icon-theme tff-dejavu
   9 sudo apk add adwaita-gtk2-theme adwaita-icon-theme ttf-dejavu
  10 cd /tmp
  11 git clone https://git.suckless.org/dwm
  12 cd dwm
  13 sudo make clean install
  14 cd ..
  15 git clone https://git.suckless.org/dmenu
  16 cd dmenu
  17 sudo make clean install
  18 cd ..
  19   git clone https://git.suckless.org/st
  20 cd st
  21 sudo make clean install
  22 cd /home/nick
  23 nano .xinitrc
  24 nano .profile
  25 exit
  26 apk add firefox-esr
  27 sudo apk add firefox
  28 sudo apk add firefox-esr
  29 apk -h
  30 apk del firefox
  31 sudo apk del firefox
  32 sudo apk add firefox-esr
  33 sudo apk add chromium
  34 xrandr
  35 sudo apk add xrandr
  36 xrandr
  37 xrandr -h
  38 xrandr --help
  39 apk add tldr
  40 sudo apk add tldr
  41 xrandr
  42 less
  43 xrandr --help | less
  44 xrandr
  45 xrandr --output Virtual-1 --mode 1400x900
  46 xrandr --output Virtual-1 --mode 1280x960
  47 cvt 976 600
  48 xrandr --newmode "976x600_60.00"   46.50  976 1016 1112 1248  600 603 613 624 -hsync +vsync
  49 xrandr
  50 xrandr --addmode Virtual-1 976x600_60.00
  51 xrandr
  52 xrandr --output Virtual-1 --mode 976x600_60.00 --set "scaling mode" Center
  53 xrandr --output Virtual-1 --mode 976x600_60.00
  54 cvt 1000 1000
  55 xrandr --newmode "1000x1000_60.00"   83.00  1000 1064 1168 1336  1000 1003 1013 1038 -hsync +vsync
  56 xrandr
  57 xrandr --addmode Virtual-1 1000x1000_60.00
  58 xrandr --output Virtual-1 --mode 1000x1000_60.00
  59 history
