#include <stdlib.h>
#include <sstream>
#include "parts.h"
#include "textglut.h"

//Hide the Console Window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")



int main( void )
{
	

	//DeltaTime variable and two useful booleans for 
	//controling the game states.
	bool game = 0;
	bool gameover = 0;
	float DT;


	int SCORE=0;//to keep score...

	//The three following variables will hold time intervals
	// to use with left-right and downward movement.
	float time=0;
	float t=0;
	float tm=0;
	float f=1;
	float sec=0;

	//This boolean is used for rotation, to only rotate once when 
	//the key is pressed.
	bool Alpha=1;

	//Declare and Initialise the tetris world. Make the Walls and 
	//release the first tetromino.
	world *tet;
	tet = new world;
	tet->init();
	tet->walls();
	tet->newblock();
		
	//Some strings used for making a simple menu
	string s = "GAME OVER";
	string d = "PRESS 'Z' TO START THE GAME";
	string a = "SCORE:";
	string c = "CONTROLS:";
	string c1 = "A : MOVE LEFT";
	string c2 = "D : MOVE RIGHT";
	string c3 = "S : DROP";
	string c4 = "W : ROTATE";

	//I use stringstream to update the score and pass it to a string to display on screen.
	string score;
	stringstream ss;
		


	int running = GL_TRUE;
	// Initialize GLFW
	if( !glfwInit() )
	{
		exit( EXIT_FAILURE );
	}
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE ) ;

	// Open an OpenGL window
	if( !glfwOpenWindow( 750,500, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}
	glfwSetWindowTitle( "''It's Raining Tetrominos''" );  
	
	glOrtho(0.0, 1.5, 0.0, 1.0, -1.0, 1.0);

// Main loop
	while( running )
	{
		//Calculate the DeltaTime
		//The function is in "vector.h" and it uses the clock() function.
		DeltaTime(DT);
		t+=DT;
		tm+=DT;
		sec+=DT;
		if(sec>1)
		{
			
			sec=0;
			time++;

			//Increase the speed gradually
			f=1-(time/300.0f);
		}


		//And now to Draw everything.				
		glClear( GL_COLOR_BUFFER_BIT );
		tet->draw();
		
		

		//Check Game State:
		//The first time the game starts:
	    if (game==0&&gameover==0)
		{
			text(d,200,250,GLUT_BITMAP_TIMES_ROMAN_24);
			if(glfwGetKey('Z'))
		    {
				game = 1;
			}	
		}
		//Game Over screen
		else if (game==0&&gameover==1)
		{
			text(s,300,300,GLUT_BITMAP_TIMES_ROMAN_24);
			text(d,200,250,GLUT_BITMAP_TIMES_ROMAN_24);

			//Press Z to restart the game
			if(glfwGetKey('Z'))
		    {
				time=0;
				SCORE=0;
				delete tet;
				tet=new world;
				tet->init();
				tet->walls();
				tet->newblock();
				game = 1;
			}	
		}
		//Run the Game:
		else
		{

		//Controls:
		//With the use of 'tm'  i move the block down every second.
		
		if(tm>f)
		{
			tet->movedown();
			tm = 0;
	    }

		//Using 't'and pressing the keys 'A' and 'D' i move the block left and right,
		//allowing movement only every tenth of a second. This way it doesnt move too fast.
		if(glfwGetKey('A')&& t>0.1)
		{
			tet->moveleft();
			t=0;			
		}		
		if(glfwGetKey('D')&& t>0.1)
		{
			tet->moveright();			
			t=0;			
		}	

		//I rotate the tetromino using 'W' and a boolean to see make sure it only rotates once
		//every time the key is pressed.
		if(glfwGetKey('W')&&Alpha)
		{
			tet->rotate();
			Alpha = 0;
		}	
		if(!glfwGetKey('W')&&Alpha==0)Alpha=1;

		
		//To drop the tetromino press 'S'. It moves the block downwards
		//every 0.05 seconds,while 'S' is pressed.
		if(glfwGetKey('S')&&t>0.05)
		{
			tet->movedown();
			t=0;				
		}	

		//Check for full lines and adjust the Score.
		SCORE+=tet->check();


		//If the any block goes over 18 game is over.
		for(int i = 1 ; i<19 ; i++)
		{
			
			if(tet->board[i][18].status==1)
			{
			
				gameover=1;
				game = 0;
			}
		}

		
		}



		//Side Menu
		ss<<SCORE;
	    score=ss.str();
		ss.str("");
		text(score,640,450,GLUT_BITMAP_TIMES_ROMAN_24);
		text(a,550,450,GLUT_BITMAP_TIMES_ROMAN_24);
		text(c,550,430,GLUT_BITMAP_9_BY_15);
		text(c1,550,410,GLUT_BITMAP_9_BY_15);
		text(c2,550,390,GLUT_BITMAP_9_BY_15);
		text(c3,550,370,GLUT_BITMAP_9_BY_15);
		text(c4,550,350,GLUT_BITMAP_9_BY_15);


		// Swap front and back rendering buffers
		glfwSwapBuffers();



		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) &&
		glfwGetWindowParam( GLFW_OPENED );
	}
	
	
	// Close window and terminate GLFW
	glfwTerminate();
	// Exit program
	exit( EXIT_SUCCESS );
}

