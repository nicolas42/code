--------------------------------------------------------------------------
What is Bricklayer for Windows ?
--------------------------------------------------------------------------
Bricklayer for Windows is a port of Steve Chamberlin's popular fast-paced
falling blocks game for the Macintosh.  The Macintosh version was honorably 
mentioned in the 1993 MacUser Shareware Awards, and favorably reviewed in 
numerous books and magazines.  Guaranteed to get you addicted, Bricklayer 
for Windows features beautiful 256-color artwork, an original music 
soundtrack, terrific sound effects, and more.  Systems which are not 
256-color or sound-capable are also supported.

Version 1.5 adds a host of new features described at the end if this
document.

--------------------------------------------------------------------------
Contents
--------------------------------------------------------------------------
- System Requirements
- Background Music
- Comments, Suggestions, Bug Reports
- Registration
- Controls
- New Features

--------------------------------------------------------------------------
System Requirements
--------------------------------------------------------------------------
Bricklayer has been beta tested on i386, i486, and Pentium systems with
4-8MB of memory.  The memory requirements may be quite steep because 
Bricklayer needs to load close to 1MB of music files.  To enjoy the
background music and sound effects, you will need to have a sound card
with wave playing ability supported by Windows (such as Microsoft Sound
System, or Creative Labs Sound Blaster).  

* If you cannot make Bricklayer even start up, try creating a file called 
  BRICKLYR.INI in your WINDOWS directory and putting the following lines 
  there:
                [Settings]
                LoadMusic=0

  This will force Bricklayer to ignore the music and sound settings and
  not load any music files.  You will be able to play, but will have no
  music or sound effects.

* Some users have encountered faults when Bricklayer displays its "Loading"
  window.  Try running Bricklayer with the -F command-line option
  (bricklyr.exe -F)  This will force Bricklater to skip the 
  initialization screen on startup.

--------------------------------------------------------------------------
Background Music
--------------------------------------------------------------------------
This version of Bricklayer, 1.50, uses the Microsoft WAVEMIX.DLL sound 
mixing library.  You may notice that the background music has stopped 
playing after six or seven minutes (in rare instances, even less) of 
continuous music.  If this occurs, press the <TAB> key to restart the 
music.

For those systems which are not sound capable, unselecting the 
"Load Music" check box in the preferences dialog will prevent 
Bricklayer from loading the music files and decrease load time.

The music WAV files are Copyright Opinicus Microtechnologies, and may 
be freely distributed only as part of the Bricklayer for Windows game 
for use by the Bricklayer executable.  See the distribution information 
for more details.

--------------------------------------------------------------------------
Comments, Suggestions, Bug Reports
--------------------------------------------------------------------------
I look forward to hearing from you.  If you encounter problems while 
playing Bricklayer, I would appreciate any information that you can
provide, such as your system configuration and a detailed description of
the problem.  Suggestions for improvements are also welcome.  Contact
me at the address listed below, or send email to:
        yevg@aol.com 

--------------------------------------------------------------------------
Registration
--------------------------------------------------------------------------
Bricklayer is $10 shareware (free for those people who've paid for previous 
versions).  If you enjoy and play Bricklayer, PLEASE send in the $10 
shareware fee.  It is not very much compared to the cost of a commercial 
game, and it motivates me to keep improving Bricklayer as well as to work on 
new games.  If you play, please pay.  Upgrades to new versions of Bricklayer 
are always free for registered users.  Those who register will also be kept 
informed of new version releases, as well as the releases of any new 
products.  

To register Bricklayer, please send a US$10 check payable to 
Yevgeny Gurevich to the address listed below.  If you live outside of 
the U.S., please send an international money order (preferred) or cash, 
since checks drawn on foreign banks are sometimes difficult to clear.

Site licenses are available - please contact me for more details.

Yevgeny Gurevich
Vanilla-Extract Software
129 Franklin Street #112
Cambridge, MA 02139
email: yevg@aol.com

--------------------------------------------------------------------------
Controls
--------------------------------------------------------------------------
Keyboard control is customizable with the [Change Keys...] Options menu 
item.  The numeric keypad keys are active as control keys in addition to 
any user-selectable settings.  The default user-selectable keyboard 
settings are the 'j', 'k', and 'l' keys for left, rotate, and right 
motion, and the spacebar for the drop.  The 'a' key controls the push.
On the numeric keypad, the 4, 5, 6, and 0 act the same as the 
j, k, l, and space.

--------------------------------------------------------------------------
New Features
--------------------------------------------------------------------------
Version 1.50 of Bricklayer for Windows introduces event recording, a
computer player feature, and support for external background modules.

* Event recording allows you to record your own games for future playback.
  To record your game, check the [Record] Event Recording menu item.
  The games that you play will then be recorded.  Only the last game played 
  is stored in the event buffer.  You can replay that game, using the 
  [Replay] Event Recording menu item, or save it to disk for future loading 
  and replay - using the [Save Event] and [Read Event] File menu items, 
  respectively.

* The computer player options in the file menu let the computer play a
  game on its own.  The fast player thinks quickly but is not as good
  at playing the game as the slower and smarter player, which uses the
  Next Piece for lookahead.  On fast systems like i486DX2-66's, the smart
  player is faster than the dumb player on an i486SX-33.

        For programmers:
        I may release a programming interface and guidelines to allow 
        you to write your own Bricklayer players in the form of DLLs.
        Please write me if you are interested.

* Alternate background modules may be used with Bricklayer for Windows -
  select New Graphics from the File menu.  Select an appropriate .BLR file
  from the available choices.  The unregistered distribution of Bricklayer
  comes only with the default (DEFAULT.BLR) backgrounds file.  Registered
  users of Bricklayer can order a "goodies" disk with extra backgrounds.

