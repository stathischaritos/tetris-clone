#include <string>
#include <glut.h>
using namespace std;



//Text function
void text(string s, float x, float y,void * font)
{
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 750, 0.0, 500);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0); // Green
	glRasterPos2i(x, y);
	//void * font = GLUT_BITMAP_TIMES_ROMAN_24;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}