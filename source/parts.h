#ifndef PARTS_H
#define PARTS_H
#define GLFW_DLL
#include <GL/glfw.h>
#include "vector.h"


/*This is the basic square block that i will use to make 
the game world and the moving tetromino. It is a simple square with the lower 
left corner at (X,Y) , a side 0f 0.05f and a color i can choose via the constructor.
*/
class square
{
public:

	//The status boolean will be used for drawing the square and for collision detection.
	bool status;

	//Position
	int X;
	int Y;

	//Color
	float R;
	float G;
	float B;


	square(int x = 0 , int y = 0, bool st=0,float r=0.5,float g=0.5 , float b=0.5)
	{
		X=x;
		Y=y;
		status = st;
		R=r;
		G=g;
		B=b;
	
	}

	
	void draw()
	{
		if(status)
		{
		
		glColor3f (R, G, B);
		glLineWidth(3.0);
		glBegin(GL_POLYGON);
		glVertex3f(X*0.05f,Y*0.05f,0);
		glVertex3f(X*0.05f+0.05f,Y*0.05f,0);
		glVertex3f(X*0.05f+0.05f,Y*0.05f+0.05f,0);
		glVertex3f(X*0.05f,Y*0.05f+0.05f,0);
		glVertex3f(X*0.05f,Y*0.05f,0);
		glEnd();
		glColor3f (0, 0, 0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(X*0.05f,Y*0.05f,0);
		glVertex3f(X*0.05f+0.05f,Y*0.05f,0);
		glVertex3f(X*0.05f+0.05f,Y*0.05f+0.05f,0);
		glVertex3f(X*0.05f,Y*0.05f+0.05f,0);
		glVertex3f(X*0.05f,Y*0.05f,0);
		glEnd();


		}
	}

};



/*The game world consists of a board of squares 20 by 20 and a tetromino of 4 squares.*/

class world
{
public:

	/*When moving,  the Tetromino check's the status of the board's squares. Only if the status =1 
	it can move to that square. When  the tetromino freezes, the status of the squares it is on turns to 1 
	and the tetromino is then placed back at the top of the board.*/
	square board[20][20];
	square tetromino[4];


	/*I initialise the world by arranging the squares of the board to form a 20by20 rectangle
	and setting their status to 0*/
	void init()
	{
		for(int i=0 ; i<20 ;i++)
		{
			for(int j=0;j<20;j++)
			{
				board[i][j].X=i;
				board[i][j].Y=j;
				board[i][j].status=0;

			}

		}
	}


	//Simple Draw Functions 
	void draw()
	{
		for(int i=0 ; i<20 ;i++)
		{
			for(int j=0;j<20;j++)board[i][j].draw();
		}
		drawtetromino();
	}
	void drawtetromino()
	{
		tetromino[0].draw();
		tetromino[1].draw();
		tetromino[2].draw();
		tetromino[3].draw();
	}



	/* I randomly create a new tetromino using rand(). In the future i will use a 
	better random number generator , as rand() always returs the same numbers.*/
	void newblock()
	{

		switch (rand()%7)
		{
		case 0:
			{
				//line
				tetromino[0]=square(5,19,1,1,0,0);
				tetromino[1]=square(6,19,1,1,0,0);
				tetromino[2]=square(7,19,1,1,0,0);
				tetromino[3]=square(8,19,1,1,0,0);
			} break;
		case 1 :
			{
				//lamda
				tetromino[0]=square(5,18,1,0,1,0);
				tetromino[1]=square(5,19,1,0,1,0);
				tetromino[2]=square(6,19,1,0,1,0);
				tetromino[3]=square(7,19,1,0,1,0);
			} break ;
		case 2:
			{
				//tau
				tetromino[0]=square(5,18,1,0,0,1);
				tetromino[1]=square(6,18,1,0,0,1);
				tetromino[2]=square(6,19,1,0,0,1);
				tetromino[3]=square(7,18,1,0,0,1);
			} break ;
		case 3:
			{
				//square
				tetromino[0]=square(5,18,1,1,1,0);
				tetromino[1]=square(5,19,1,1,1,0);
				tetromino[2]=square(6,18,1,1,1,0);
				tetromino[3]=square(6,19,1,1,1,0);
			} break ;
		case 4:
			{
				//snake
				tetromino[0]=square(5,17,1,0,1,1);
				tetromino[1]=square(5,18,1,0,1,1);
				tetromino[2]=square(6,18,1,0,1,1);
				tetromino[3]=square(6,19,1,0,1,1);
			} break ;
		case 5:
			{
				//gamma
				tetromino[0]=square(7,18,1,1,0,1);
				tetromino[1]=square(7,19,1,1,0,1);
				tetromino[2]=square(6,19,1,1,0,1);
				tetromino[3]=square(5,19,1,1,0,1);
			} break ;
		case 6:
			{
				//sigma
				tetromino[0]=square(6,17,1,1,1,0);
				tetromino[1]=square(6,18,1,1,1,0);
				tetromino[2]=square(5,18,1,1,1,0);
				tetromino[3]=square(5,19,1,1,1,0);
			} break ;
		}


	}


	/* A simple rotation function.It uses the second square as a center
	and rotates all other squares 90 degrees around it, clockwise. */
	void rotate()
	{

		/*To avoid overlapping squares after rotation, i save a copy of the tetromino
		before rotation */
		square before[4];
		for(int j=0 ; j<4;j++)
		{
			before[j]=tetromino[j];
		}


		// I do the Rotation
		for(int i=0 ; i<4 ; i++)
		{
				int A = tetromino[i].X-tetromino[1].X;
				int B = tetromino[i].Y-tetromino[1].Y;

				
					tetromino[i].X+=B-A;
					tetromino[i].Y-=A+B;
					
		}
		

		//And if any of the squares is in illegal space ,the whole tetromino
		//goes back to the way it was before.
		for(int a = 0 ;a<4 ;a++)
		{
			if(board[tetromino[a].X][tetromino[a].Y].status==1) 
			{
				for(int f=0 ; f<4;f++)
				{
					tetromino[f]=before[f];
				}
			}
		}




	}




		//Check for collision and then move left.
	void moveleft()
	{
		
		 
			if(board[tetromino[0].X-1][tetromino[0].Y].status==0
				&& board[tetromino[1].X-1][tetromino[1].Y].status==0
				&& board[tetromino[2].X-1][tetromino[2].Y].status==0
				&& board[tetromino[3].X-1][tetromino[3].Y].status==0
				)
			{
				for(int i = 0 ; i<4 ;i++) tetromino[i].X -- ;
			}
		}

	//Check for collision and then move right.
	void moveright()
	{
		
		 
			if(board[tetromino[0].X+1][tetromino[0].Y].status==0
				&& board[tetromino[1].X+1][tetromino[1].Y].status==0
				&& board[tetromino[2].X+1][tetromino[2].Y].status==0
				&& board[tetromino[3].X+1][tetromino[3].Y].status==0
				)
			{
				for(int i = 0 ; i<4 ;i++) tetromino[i].X ++ ;
			}
		}


	/*First check for collision. If it is clear then Move Down. If not, freeze the tetromino
	into place by turning the board status to 1 in the squares where the tetromino is standing.*/
	void movedown()
	{
		if(board[tetromino[0].X][tetromino[0].Y-1].status==0
				&& board[tetromino[1].X][tetromino[1].Y-1].status==0
				&& board[tetromino[2].X][tetromino[2].Y-1].status==0
				&& board[tetromino[3].X][tetromino[3].Y-1].status==0
				)
		{
				for(int i = 0 ; i<4 ;i++) tetromino[i].Y -- ;
		}
		else 
		{
			for(int j = 0 ; j<4 ;j++)
			{
				board[tetromino[j].X][tetromino[j].Y].status=1;
				board[tetromino[j].X][tetromino[j].Y].R=tetromino[j].R;
				board[tetromino[j].X][tetromino[j].Y].G=tetromino[j].G;
				board[tetromino[j].X][tetromino[j].Y].B=tetromino[j].B;

			}
			newblock();
		}




	}



	//Left , Right and Bottom Walls.

	void walls()
	{
		for (int i = 0 ; i<20 ; i++)
		{
			board[0][i].status=1;
			board[19][i].status=1;
			board[i][0].status=1;


		}
	}


	
	/*Check if a line is filled. If so, score++ and move all the above 
	lines one position downwards.Return score.*/

	int check()
	{
		int score=0;
		int check = 0;
		for(int i = 1 ; i<20 ; i++)
		{ 
			check = 0;
			for(int j = 1 ; j<19; j++)
			{
				if(board[j][i].status==1) check++;
			}
			if(check==18)
			{
				score++;

				for( int a = i ; a <19 ; a++)
				{
					for ( int b = 1 ; b<19 ; b++)
					{
						board[b][a].status=board[b][a+1].status;
					}
				}
			}
		}

		

		return score;
	}




};











#endif