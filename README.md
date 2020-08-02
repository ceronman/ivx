# Invaxion Marciana IVX

> UPDATE August 2 2020:

Here is a blast from the past, a game I wrote 18 years ago:

https://www.youtube.com/watch?v=XnLaDhkUyD4

This was a student project for my first semester of Systems Engineering.

It's a Space Invaders like shooter with cheesy story and graphics.

Some fun facts about this project:

It was originally written for MS-DOS in C using Turbo C++ 3.0 (That's what was used to teach us back then, barbaric!)

It had pretty much zero dependencies besides the standard C library. So I had to implement almost everything from scratch.

For the graphics I found some assembler snippets on the internet to enter into mode 13h  (320x200 256 colors).

I knew zero assembler but copy pasting the snippet did the trick. With that I was able to get a put_pixel(x, y, color)  function and I built everything on top of that.

I implemented my own graphics file format, font format and text rendering, sprite blitting, physics, collision detection, timers, keyboard interruption handler, etc.

The lemmings like explosion animation was inspired by my failed attempt to implement a sprite scaling algorithm.

For the graphics I used a shareware program called Strata 3D. The models were pre-rendered and later processed using the glorious Paint Shop Pro.

Because all my files were custom format, I had to use an HEX editor (UltraEdit) to manually put metadata into the files.

The video shows an awful frame rate, but the game was too fast! At full speed It was unplayable on my old Pentium. I didn't know about frame synchronization so I had to add some sleeps to make it playable. Of course this meant the game ran at different speeds on different computers.

I didn't know about version control systems back then so I used to manually create a zip file with the current state of the source code every now an then.

I still have 12 zip files with versions 0.1 to 1.1, but I did not add all the versions to this repo.

The official final version for the university project was 1.0. But a few months later, I ported the code to Win32 using MinGW and Allegro. I also updated the explosion animations to use an actual particle system explosion generator and fixed the frame rate.  That was version 1.1
