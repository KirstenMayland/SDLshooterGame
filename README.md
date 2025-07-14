# sdl2Dshooter - "ForagerDefense"

## --------NOTE: Further development paused when I transitioned to working in Godot--------


## ForagerDefense

ForagerDefense is a program that runs a 2D 80s style, autumn-coded videogame using C and SDL (Simple DirectMedia Layer) libraries.

Video of playthrough documented here: [ForagerDefensePlaythrough](video/ForagerDefense.mp4).

Game play still: 
![Gameplay](images/Screenshot%20(57).png)

## Usage

To initialize:
``` bash
$ ./shooter
```

When running:

Use the `Arrow Keys` to move, and press `Left Ctrl` to shoot acorns


## Graphics and Audio Credit

Chipmunk and background drawn by me. The acorns and bear were obtained from Google images.

The music in the background is "In The Deep Woods" from the Stardew Valley OST by ConcernedApe aka Eric Barone.


## Files

* `Makefile` - compilation procedure
* `common.h` - collection of widely used header files
* `defs.h` - collection of program wide variables/values
* `draw.c` - the implementation of functions related to drawing
* `draw.h` - the interface of the draw module
* `init.c` - the implementation of functions related to initializing SDL
* `init.h` - the interface of the init module
* `input.c` - the implementation of functions related to keyboard inputs
* `input.h` - the interface of the input module
* `main.c` - the implementation of the main module
* `main.h` - the interface of the main module
* `shooter` - the executable file which when ran, runs the hame
* `sounds.c` - the implementation of functions related to sound and music
* `sounds.h` - the interface of the sound module
* `stage.c` - the implementation of functions related to general gameplay and interactions
* `stage.h` - the interface of the stage module
* `structs.h` - typedef structures needed for the program
* `util.c` - the implementation of functions related to needed math
* `util.h` - the interface of the util module

## Valgrind and Memory Errors/Leaks
After many hours trying to get rid of memory errors and leaks, I discovered that the SDL library itself was responsible for most of the memory errors (which is in part why I'm stepping away from it for Godot). I don't know if the apparent errors/leaks are the fault of Valgrind or
SDL2 or a combination, but at this point in time, it at least does not appear to be me.

When you compile and run the program below:
```c
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Quit();
	return 0;
}
```
Valgrind returns with:
```
==10260== LEAK SUMMARY:
==10260==    definitely lost: 21,610 bytes in 14 blocks
==10260==    indirectly lost: 113,752 bytes in 19 blocks
==10260==      possibly lost: 5,084,230 bytes in 784 blocks
==10260==    still reachable: 497,672 bytes in 5,277 blocks
==10260==                       of which reachable via heuristic:
==10260==                         newarray           : 418,080 bytes in 5 blocks
==10260==         suppressed: 0 bytes in 0 blocks
==10260== 
==10260== For lists of detected and suppressed errors, rerun with: -s
==10260== ERROR SUMMARY: 3172 errors from 1675 contexts (suppressed: 20 from 4)
```


## Compilation
To build, run `make`

To clean up, run `make clean`

To clean and then build, run `make set`

To use valgrind, run `make valgrind`


## Credit pt.2
Followed this tutorial bc new to game dev: https://www.parallelrealities.co.uk/tutorials/#shooter

It was a great tutorial bc it gave me mostly correct code and then I need to bring it all the way to completion, forcing me to actually understand it (got better at makefiles, typedef structs, general SDL, refresher on pointers, function pointers) All in all, so many hours of debugging, trying to conceptualize it and get it to work.

/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

SDL can be installed here:
```
sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev fcitx-libs-dev
```
