#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include<vector>
using namespace std;
int mainWindow, subWindow1;

int counter=0;
vector<float> pointflood_x;
vector<float> pointflood_y;

vector<float> pointbound_x;
vector<float> pointbound_y;

void displayflood(){
    glLineWidth(3);
    glPointSize(2);
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glPushMatrix();
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
      for(int indexx=0; indexx< 3; indexx++)
        {
          glVertex2f(pointflood_x[indexx],pointflood_y[indexx]);
          indexx++;
          glVertex2f(pointflood_x[indexx],pointflood_y[indexx]);
          indexx++;
          glVertex2f(pointflood_x[indexx],pointflood_y[indexx]);
        }
    glEnd();
    glBegin(GL_LINE_LOOP);
      for(int indexx=3; indexx< pointflood_y.size(); indexx++)
        {
          glVertex2f(pointflood_x[indexx],pointflood_y[indexx]);
          indexx++;
          glVertex2f(pointflood_x[indexx],pointflood_y[indexx]);
          indexx++;
          glVertex2f(pointflood_x[indexx],pointflood_y[indexx]);
        }
    glEnd();
    glPopMatrix();
    glFlush();
}

void init_displayflood()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void floodFill(int x,int y,float* oldcolor,float* newcolor)
{
  float color[3];
  glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
	if((color[0]==oldcolor[0] && color[1]==oldcolor[1] && color[2]==oldcolor[2]))
  {
		glColor3f(newcolor[0],newcolor[1],newcolor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
    floodFill(x+1,y,oldcolor,newcolor);
		floodFill(x,y+2,oldcolor,newcolor);
		floodFill(x-2,y,oldcolor,newcolor);
		floodFill(x,y-2,oldcolor,newcolor);
	}
}

void initflood(){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500/2);
}


void mouseflood(int btn, int state, int x, int y){
    float xx=x,yy;
    yy = 500.0/2-y;
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
            pointflood_x.push_back(xx);
            pointflood_y.push_back(yy);
            counter++;
            if(counter % 3 == 0)
            {
              displayflood();
              
            }

    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
              float oldCol[] = {1.0,1.0,1.0};
              float newcolor[] = {0,1,1};
              glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,oldCol);
              floodFill(x,yy,oldCol,newcolor);
    }
}








void initbound(){
    glClearColor(0.5,0.996,0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}

void boundaryFill(int x, int y, float* fillColor, float* boundcolor)
{
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=boundcolor[0] || color[1]!=boundcolor[1] || color[2]!=boundcolor[2])&&(
     color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
     {
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        // boundaryFill(x+1,y,fillColor,boundcolor);
        // boundaryFill(x-1,y,fillColor,boundcolor);
        // boundaryFill(x,y+1,fillColor,boundcolor);
        // boundaryFill(x,y-1,fillColor,boundcolor);

        boundaryFill(x+1,y,fillColor,boundcolor);
        boundaryFill(x-2,y,fillColor,boundcolor);
        boundaryFill(x,y+1,fillColor,boundcolor);
        boundaryFill(x,y-2,fillColor,boundcolor);
    }
}

void displaybound(){
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);

    for(int indexx=0; indexx< pointbound_y.size(); indexx++)
        {
          glVertex2f(pointbound_x[indexx],pointbound_y[indexx]);
        }
    
    glEnd();

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

glPopMatrix();
glFlush();
}

void init_displaybound()
{
  glClear(GL_COLOR_BUFFER_BIT);

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

void mousebound(int btn, int state, int x, int y){
    y = 500-y;
    float boundCol[] = {1,0,0};
    float color[] = {0,0,1};
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        pointbound_x.push_back(x);
        pointbound_y.push_back(y);
        displaybound();
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        boundaryFill(x,y,color,boundCol);
    }
}


int main(int argc, char** argv) {
 
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (500, 500);
glutInitWindowPosition (0,0);
mainWindow = glutCreateWindow ("LAB-6 Flood Fill - Boundary Fill Algorithm");

glutDisplayFunc(init_displaybound);
glutMouseFunc(mousebound);
initbound();

//mainWindow = glutCreateWindow ("LAB-6 Flood Fill - Boundary Fill Algorithm");
mainWindow = glutCreateSubWindow(mainWindow,0,0,500,500/2);
glutDisplayFunc(init_displayflood);
glutMouseFunc(mouseflood);
initflood();
glutMainLoop();
 
return 0;
}

