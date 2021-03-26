
#include <GL/gl.h>
#include<string>
#include<math.h>
#include <GL/glut.h> 
using namespace std;
int triangleAmount = 400, A =  -1, color=1;
float x = -0.5, y = -0.5, radius=0.2, i=0, direction=0, spacecounter=0;
#define PI 3.141592
GLfloat twicePi = 2.0f * PI;
GLfloat hu[3] = {-0.5, 0, +0.5}, hi[] = {-0.5, +0.5, -0.5};


void display()
{ 

glClearColor(0.4f,0.4f,1.0f, 0.5f); 
glClear(GL_COLOR_BUFFER_BIT);


  if(A>=0)
{       x = hu[0];
        y = hi[0];
        glColor4f(color,0.5,0,1);
        glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	    glEnd();
}
if(A>=1)

{       x = hu[1];
        y = hi[1];
        glColor4f(color,0.5,0,1);
        glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	    glEnd();
}


glColor4f(1,1,0,1);
string s="500065719 | ABHIRUP KUMAR";
glRasterPos2f(0.3,-0.9);
int n=s.size();
for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);

 glEnd();
// glFlush();
  glutSwapBuffers(); 

}


void mouse(int button, int state, int x, int y) 
{
   
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        A++;   
       glutPostRedisplay();
   }
  
   
}

void keyboard(unsigned char key, int x, int y) {
   if(key == 27) //exit code
        exit(0);

   if(key != 32)
    return;
    
    if(spacecounter == 0)
        {
            direction = 0;
            spacecounter = 1;
        }
    else if(spacecounter == 1)
        {
            direction = 1;
            spacecounter = 0;
        }
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer,0); //60 fps , In a second 60 frames shown, 1000milisec is in the code.
    if(direction == 1)
    radius += 0.001;
    else if(direction == 0)
    radius -= 0.001;
}

int main( int argc, char** argv ) 
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(800,525);
   glutInitWindowPosition(00,00);   
   glutCreateWindow("LAB2 Event Handling"); 
   glutDisplayFunc(display);  
   glutTimerFunc(0,timer, 0);  
   glutMouseFunc(mouse); // i see same behaviour if this statement is placed above Displayfunc or below this displayfunc function?
   glutKeyboardFunc(keyboard);
   glutMainLoop();
    
   return 0;
}

