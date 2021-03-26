#include<iostream>
#include<GL/glut.h>
#include<GL/gl.h>
#include<string>
#include<math.h>
#include <unistd.h>
#include<sstream>
#include<vector>
using namespace std;

float red=1.0;
float green=1.0;
float blue=1.0, slope;
int c=1;
vector<float> point_x;
vector<float> point_y;

void draw(int x, int y) {
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

}

//float x1,x2,yk1,y2;
// int A=0;

void display(void)
{
    // if(A < 3)
    // return;

 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glPushMatrix();

int length=point_x.size();
//printf(" %d ", length);
int p,x,x1,y1,y,inter,adx,ady;    
int incx, incy, inc1, inc2,i,e;
float dy,dx;
for(int i=0;i<length-1;i++,i++)
{
dx=point_x[i+1]-point_x[i];
dy=point_y[i+1]-point_y[i];

x= point_x[i];
y=point_y[i];
x1 = point_x[i+1];
y1 = point_y[i+1];
slope = dy/dx;

if(slope>1)
{red = 1;
green = 0;
blue = 0;}
else if(slope<0 && slope>-1)
{red = 0;
green = 1;
blue = 0;}
else if(slope>0 && slope<1)
{red = 0;
green = 0;
blue = 1;}
else if(slope<-1)
{red = 0;
green = 0;
blue = 0;}


if (dx < 0) 
dx = -dx;
if (dy < 0) 
dy = -dy;
incx = 1;
	
if (point_x[i+1]<point_x[i]) 
	incx = -1;
	incy = 1;
if (point_y[i+1]<point_y[i]) 
	incy = -1;
		
x = point_x[i]; y = point_y[i];
if (dx > dy) {
	draw(x, y);

	e = 2 * dy-dx;
	inc1 = 2*(dy-dx);
	inc2 = 2*dy;
	for (inter=0; inter<dx; inter++) {
		if (e >= 0) {
			y += incy;
			e += inc1;
			}
			else
			e += inc2;
			x += incx;
			draw(x, y);
		}

	} else {
		draw(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (inter=0; inter<dy; inter++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw(x, y);
		}
	}

}

glPopMatrix();
glColor4f(1,0,1,1);

std::ostringstream ss;
ss << slope; //converting float to string
std::string sq(ss.str());

string s="500065719 | ABHIRUP KUMAR";
glRasterPos2f(260.0,0);
int n=s.size();
for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);

    glColor4f(0.7,0,0.9,1);
   glRasterPos2f(420.8, 480.0);
   int m= sq.size();    //printing slope
   for(int i=0;i<m;i++)
   glutBitmapCharacter(GLUT_BITMAP_8_BY_13, sq[i]);

glFlush();
}
 
void init(void)
{
glClearColor(0.7,0.7,0.7,0.7);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,500,0,500);

}
 
void mouse(int button, int state, int xx, int yy)
{
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
          float px, py;
            px = xx;

          py = (500 - yy) ;
           point_x.push_back(px);
            point_y.push_back(py);
            //A++;
        //printf("mouse pressed at (%f,%f)\n", px, py);
   }
   if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { 
   //A++;
   glutPostRedisplay();
   }
}

int main(int argc, char** argv) {
 
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (100,100);
glutCreateWindow ("LAB-4 LINE DRAWING (BRESEMHAM)");
init();

glutDisplayFunc(display);
glutMouseFunc(mouse);
glutMainLoop();
 
return 0;
}
