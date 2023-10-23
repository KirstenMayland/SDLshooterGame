# sdl2Dshooter - "ForagerDefense"

## Team Members (team of 1)
- Kirsten Mayland (@KirstenMayland)

## shooter

*shooter* is a program that runs a 2D 80s style, autumn-coded videogame using C and SDL (Simple DirectMedia Layer) libraries

[![Alternate Text]({image-url})]({video-url} "Link Title")
/home/kirstenm/DALI/sdl2Dshooter/video/ForagerDefense.mp4

## Usage

To initialize:
``` bash
$ ./shooter
```

When running:


## Files

* `Makefile` - compilation procedure
* `common.h` - collection of widely used header files
* `defs.h` - collection of 
* `draw.c` -
* `draw.h` -
* `init.c` -
* `init.h` -
* `input.c` -
* `input.h` -
* `main.c` - the implementation
* `main.h` -
* `shooter` -
* `sounds.c` -
* `sounds.h` -
* `stage.c` -
* `stage.h` -
* `structs.h` -
* `util.c` -
* `util.h` -


* `common.h` - the interface of the common module
* `common.c` - the implementation of the common module
* `solve.h` - the interface of the solve module
* `solve.c` - the implementation of the solve module
* `create.h` - the interface of the create module
* `create.c` - the implementation fo the create module
* `testing.sh` - runs script containing many test cases
* `testing.out` - contains the output of the testing script

## Compilation
To build, run `make set`.

To clean up, run `make clean`

To valgrind, run `make valgrind`


## Credit
Followed this tutorial bc new to game dev:
https://www.parallelrealities.co.uk/tutorials/#rogue


great tutorial bc it gives you mostly correct code and then you need to bring it all the way to completion,
forcing you to actually understand it
(got better at makefiles, typedef structs, general SDL, refresher on pointers, function pointers)
so so many hours of debugging, trying to conceptualize it and get it to work


Using SDL libraries:
- installed on linux using the command
```
sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev fcitx-libs-dev
```