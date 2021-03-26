#include <GL/gl.h>
#include<string>
#include <GL/glut.h> 
using namespace std;

void display()
{ 
glClearColor(0.4f,0.4f,1.0f, 0.5f); 
glClear(GL_COLOR_BUFFER_BIT);

//Ground
	glColor3f(0.0,0.5,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(-1.0,-1.0);
		glVertex2f(-1.0,-0.4);
		glVertex2f(1.0,-0.4);
		glVertex2f(1.0,-1.0);
	glEnd();

//hutbase
glColor4f(1,1,0,1); //if polygon not given color, why it took white as a color
glBegin(GL_POLYGON); 
glVertex2f(0.3,-0.5);
glVertex2f(0.5, -0.5);  
glVertex2f(0.5,-0.2); 
glVertex2f(0.3,-0.2); 
glEnd(); 

//door
glColor4f(0,0,0,1);
glBegin(GL_POLYGON); 
glVertex2f(0.35,-0.5);
glVertex2f(0.45, -0.5);  
glVertex2f(0.45,-0.3); 
glVertex2f(0.35,-0.3); 
glEnd(); 

//topcone
glColor4f(1,0,0,1);
glBegin(GL_TRIANGLES); 
glVertex2f(0.3,-0.2);
glVertex2f(0.5, -0.2);  
glVertex2f(0.4,0.05);  
glEnd(); 

//top hut roof
glColor4f(0.255, 0.0, 0.102,1);
glBegin(GL_POLYGON);  
glVertex2f(0.4,0.05);
glVertex2f(0.6,0.05);
glVertex2f(0.7,-0.2);
glVertex2f(0.5,-0.2);  
glEnd();

//below base
glColor4f(1,0.5,0,1);
glBegin(GL_POLYGON);  
glVertex2f(0.7,-0.2);
glVertex2f(0.5,-0.2); 
glVertex2f(0.5,-0.5);
glVertex2f(0.7,-0.45);   
glEnd();

string s="ABHIRUP KUMAR - 500065719";
glRasterPos2f(-0.3,-0.5);

int n=s.size();
for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);

glEnd();
glFlush();
glutSwapBuffers(); 

}

int main( int argc, char** argv ) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE);
   glutInitWindowSize(800,525);
   glutInitWindowPosition(00,00);   
   glutCreateWindow("Village Scene"); 
   glutDisplayFunc(display);    

   glutMainLoop();
    
   return 0;
}
