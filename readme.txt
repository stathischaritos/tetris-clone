“It’s Raining Tetrominos”


Description:

This is a clone of a very popular arcade game. It is basicaly a puzzle game , where you try to arrange tetrominos in order to fill the board without leaving empty spaces. Tetrominos are geometric shapes that are composed of 4 squares connected orthogonally.




Base Mechanics: 

Move the Tetromino  Left and Right  using ‘A’ and ‘D’.
Rotate the Tetromino using ‘W’
Drop the Tetromino using ‘S’



Gameplay Mechanics:

You cannot move the tetromino where there are other squares.
If a Horizontal line is filled with squares , it disappears and you get a score point.
If the wall gets too high you loose the game.



Features:

OpenGL window using GLFW.
Minimal text screen made with Glut.
Different Color Squares made by OpenGL .
Side Screen that shows Score and Controls.



 
Source Code :

The source code includes the following files:

main.cpp : Where the main() function is.
vector.h : My 3D vector class, plus a Delta Time Calculator using the clock() function.
textglut.h : Render a string using glut.The easiest way to use text with OpenGL.
parts.h : The Square and World classes I used to make the game.

To compile it needs a proper GLFW set-up,  and GLUT.




Release Build:

The Release Build includes the Tetrom.exe , the GLFW.dll  , and the glut32.dll.  I have tried it on 2  other computers , one running Windows 7 , and one running Windows XP as mine.