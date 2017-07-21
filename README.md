# LinuxTerminalGameEngine8
LinuxTerminalGameEngine8Test1

Command Line Options:

-h, --help:
help

1st Argument - Screen Width (1-24 for standard Terminal size)

2nd Argument - Screen Height (1-80 for standard Teminal size)

3rd Argument - Game Speed (100-500 larger numbers are slower)

4th Argument - GameMap On/Off (Turn Game Map on(1) or off(0)

You can leave the command line arguments empty, and the default parameters are (0, 0, 500, 0),
which is maximum screen size, slow speed, and no GameMap:

Sample Syntax:

$ ./TerminalGameEngineTest1

For a screen size of 40 width x 20 height , slow speed and GameMap:

Sample Syntax:



$ ./TerminalGameEngine8Test1 20, 40, 500, 1

for help:


Sample Syntax:

$ ./TerminalGameEngine8Test1 -h

or 

$ ./TerminalGameEngine8Test1 --help


To include in C++ programm include the screen.cpp file at the top of the code:

<include screen.cpp>

Then initialize the screen class object with the name of the class screen and the name of the object you select. 
Example text:

screen S;

Then call the funcion you want with the parameters of the function:
Example text:
Ex 1.


S.Start(24, 80, 500, 1) // screen height, screen width, game speed, gamemap on


Ex 2. 

S.DrawHorzLine(5, 5, 10) // startY position, startX position, line length

