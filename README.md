# One Light
This is my Ludem Dare 28 entry. The theme is 'You only get one', so I designed and amde a game in which the character is lost in a cae and must find their way out. You only have one lamp with a finite amount of oil, the brighter you make the lamp, the more you can see of the level but the quicker the oil runs out. Also bumbing into walls casuses oil to spil.

## Implementation

I write this using my 2D rendering engine [Flux](https://github.com/baggyn/Flux), which uses [emscripten](https://github.com/kripken/emscripten) to compile C++ to JavaScript.

[You can play it here](https://dl.dropboxusercontent.com/u/4998298/ld/onelight.html)

## Requirements

Latest version of Chrome or Firefox (works best in Chrome).

## Controls

* WASD / Arrows - Move
* Q E - Grow/Shrink light

## Concepts

* Find the blue exit
* If the exit is grey then it is locked
* If it is locked then you must collect all the green keys
* Avoid the walls
* Shrink the light to use less oil.

