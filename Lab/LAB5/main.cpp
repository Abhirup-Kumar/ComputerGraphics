#include<iostream>
#include<GL/glut.h>
#include<GL/gl.h>
#include<string>
#include<vector>

using namespace std;

int xc, yc;
int mainWindow, subWindow1,subWindow2,direction=0, spacecounter=0;;

vector<float> pointcir_x;
vector<float> pointcir_y;
vector<float> pointell_x;
vector<float> pointell_y;

void plot(int x, int y, int pntX1, int pntY1)
{
  glColor3f(0.8,0,0.7);
    glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(x+pntX1, y+pntY1);
	glEnd();
}
float r=50;
void displaycir(void)
{
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glPushMatrix();
  
  int x,y, cx, cy;
	float decision;

int length=pointcir_x.size();
for(int i=0;i<length;i++)
{
  x = 0;
	y = r;
  cx = pointcir_x[i];
  cy = pointcir_y[i];
  decision = 5/4 - r;
  plot(x, y, cx, cy);

	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2*x+3;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+5;
		}
		plot(x, y, cx, cy);
		plot(x, -y, cx, cy);
		plot(-x, y, cx, cy);
		plot(-x, -y, cx, cy);
		plot(y, x, cx, cy);
		plot(-y, x, cx, cy);
		plot(y, -x, cx, cy);
		plot(-y, -x, cx, cy);
	}
}

glPopMatrix();

glColor4f(1,0,0,1);

string s="500065719";
glRasterPos2f(270.0,1);
int n=s.size();
for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);

glColor4f(0,0,0,1);
s="|";
glRasterPos2f(350.0,1);
n=s.size();
for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);

glColor4f(0,0,1,1);
s="ABHIRUP KUMAR";
glRasterPos2f(360.0,1);
n=s.size();
for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);

glFlush();
}


void drawDot(int x, int y, float r, float g, float b)
{
	glColor3f(r,g,b);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void symmetricPixels(int x,int y,float r,float g, float b)
{
	drawDot(xc+x,yc+y,r,g,b);
	drawDot(xc-x,yc+y,r,g,b);
	drawDot(xc+x,yc-y,r,g,b);
	drawDot(xc-x,yc-y,r,g,b);	
}

float rx=30,ry=40; //using long type break animation with keyboard
void displayell(void)
{
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glPushMatrix();

int length=pointell_x.size();
 int x,y;float p;

for(int i=0;i<length;i++)
{
    xc = pointell_x[i];
    yc = pointell_y[i];
    p=ry*ry-rx*rx*ry+rx*rx/4; //P10
    x=0;y=ry;

    //region 1
    while(ry*ry*x <= rx*rx*y) //condition to be true to be in 1st region
   {
	if(p < 0)
	{
		x++; //did x+1 to fit in eqn
		p = p+2*ry*ry*x+ry*ry;// actual eqn is ry*ry(x+1), but already did x+1 in above line.
	}
	else
	{
		x++;y--;
		p = p+2*ry*ry*x-2*rx*rx*y-ry*ry;
	}
  symmetricPixels(x,y,1,1,1);
   }

  //Region 2
   p=ry*ry*(x+0.5)*(x+0.5)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry; //P20
   while(y > 0) //TILL WE REACH X-AXIS
   {
	if(p <= 0)
	{
		x++;y--;
		p = p+2*ry*ry*x-2*rx*rx*y+rx*rx;
	}
	else
	{
		y--;
		p = p-2*rx*rx*y+rx*rx;
	}
  symmetricPixels(x,y,1,1,1);
   }


}

glPopMatrix();

glFlush();

}



void mouseell(int button, int state, int xx, int yy)
{
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
          float px, py;
            px = xx;

          py = (500/2 - 10*3/2 - yy) ;
           pointell_x.push_back(px);
            pointell_y.push_back(py);
   }
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { 
   glutPostRedisplay();
   }
}

void initcir(void)
{
glClearColor(0.5,0.5,0.5,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,500,0,500);

}

void initell(void)
{
glClearColor(0.0,0.0,0.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,480,0,500/2 - 10*3/2);

}
 
void mousecir(int button, int state, int xx, int yy)
{
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
          float px, py;
            px = xx;

          py = (500 - yy) ;
           pointcir_x.push_back(px);
            pointcir_y.push_back(py);
   }
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { 
   
   glutPostRedisplay();
   }
}

void timercir(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/400, timercir,0);
    if(direction == 1)
    r += 0.01;
    else if(direction == 0)
    r -= 0.01; //when r was int , minus 0.01 slash r by 1 and when it reached 0, doing +0.01 to int only kept r at 0 so circle never grew back.
}

void keyboardcir(unsigned char key, int x, int y) {
   if(key == 27)
        exit(0);

   if(key != 32)
    return;
    
	glutTimerFunc(0,timercir, 0);
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

void timerell(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/400, timerell,0);
    if(direction == 1)
    {
		rx += 0.01; //using long type instead of float for rx and ry, breaks animation with keyboard
		ry += 0.01;
	}
    else if(direction == 0)
    {
		rx -= 0.01;
		ry -= 0.01;
	} 
}

void keyboardell(unsigned char key, int x, int y) {
   if(key == 27)
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
	glutTimerFunc(0,timerell, 0);
}


int main(int argc, char** argv) {
 
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100,100);
mainWindow = glutCreateWindow ("LAB-5 CIRCLE AND ELLIPSE");

glutDisplayFunc(displaycir);
glutMouseFunc(mousecir);
glutKeyboardFunc(keyboardcir);
initcir();

subWindow1 = glutCreateSubWindow(mainWindow, 10,10,500-2*10, 500/2 - 10*3/2);
glutDisplayFunc(displayell);
glutMouseFunc(mouseell);
glutKeyboardFunc(keyboardell);
initell();
glutMainLoop();
 
return 0;
}
