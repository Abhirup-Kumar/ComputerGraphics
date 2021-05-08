#include <cmath>
#include <vector>
#include <iostream>
#include <GL/glut.h>
using namespace std;

#define PI 3.14159265
#define ROOT3 1.73205081

#define RATIO 0.7 
#define ANGLE 108 

static int maxLevel = 0;

class Source; 

void writeOnScreen() {
   char *str = "500065719 | Abhirup Kumar";
   glRasterPos3f(-20.0, -45.0, 0.0);
   for (char* c = str; *c != '\0'; c++) 
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
   }

   char *str1 = "Forking";
   glRasterPos3f(-8.0, 45.0, 0.0);
   for (char* c = str1; *c != '\0'; c++) 
   {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
   }

}

class Sequel
{
public:
   Sequel()
   { 
      coords.clear();
      v.clear(); 
   }
   void drawTree(); 

   friend class Source;

private:
   vector<float> coords; 
   vector<Source> v; 
};

void Sequel::drawTree()
{
	glEnable( GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   float r = (rand()%100)/100.0;
   glColor3f(r,r,0);
   glBegin(GL_LINE_STRIP);
   for (int i=0; i < 3; i++)
      glVertex2f(coords[2*i], coords[2*i+1]);
   glEnd();
}

class Source
{
public:
   Source(){ }
   Source(float coordsVal[4])
   {
      for (int i=0; i < 4; i++) coords[i] = coordsVal[i];
   }

   void draw(); 

   Sequel sourceToSequelTree(); 
   void produceTree(int level); 

   friend class Sequel;

private:
   float coords[4];
};

void Source::draw()
{
   glBegin(GL_LINES);
   for (int i=0; i < 2; i++)
      glVertex2f(coords[2*i], coords[2*i+1]);
   glEnd();
}

Sequel Source::sourceToSequelTree()
{
   float x0, y0, x1, y1, coordsVal[10], coordsVal1[4];
   int i, j;
   Source s;
   Sequel seq = *new Sequel();

   x0 = coords[0]; y0 = coords[1]; x1 = coords[2]; y1 = coords[3];

   coordsVal[0] = x1 + RATIO*cos((PI/180.0)*ANGLE/2.0)*(x1-x0) - RATIO*sin((PI/180.0)*ANGLE/2.0)*(y1-y0);
   coordsVal[1] = y1 + RATIO*cos((PI/180.0)*ANGLE/2.0)*(y1-y0) + RATIO*sin((PI/180.0)*ANGLE/2.0)*(x1-x0);
   coordsVal[2] = x1;
   coordsVal[3] = y1;
   coordsVal[4] = x1 + RATIO*cos((PI/180.0)*ANGLE/2.0)*(x1-x0) + RATIO*sin((PI/180.0)*ANGLE/2.0)*(y1-y0);
   coordsVal[5] = y1 + RATIO*cos((PI/180.0)*ANGLE/2.0)*(y1-y0) - RATIO*sin((PI/180.0)*ANGLE/2.0)*(x1-x0);

   for (i=0; i < 6; i++) seq.coords.push_back(coordsVal[i]);

   for (i=0; i < 2; i++)
   {
	  coordsVal1[0] = coordsVal[2];
	  coordsVal1[1] = coordsVal[3];
      for (j=2; j < 4; j++)
	  {
	     coordsVal1[j] = coordsVal[4*i+j-2];
	  }
	  s = *new Source(coordsVal1);
	  seq.v.push_back(s);
   }

   return seq;
}

void Source::produceTree(int level)
{
   glColor3f(0.4, 0.5, 0.5);

   glLineWidth(1.5*(maxLevel - level));

   if (maxLevel == 0) this->draw();
   else if (maxLevel == 1) {this->draw(); this->sourceToSequelTree().drawTree();}
        else if (level < maxLevel)
		{
		   if (level == 0) this->draw();
		   this->sourceToSequelTree().drawTree();
	       for (int i=0; i < 2; i++) this->sourceToSequelTree().v[i].produceTree(level+1);
		}

   glLineWidth(1.0);
}

void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   float coordsVal1[4] = {-30.0, -15.0, 0.0, -15.0 + ROOT3*0.5*60.0};
   float coordsVal2[4] = {0.0, -15.0 + ROOT3*0.5*60.0, 30.0, -15.0};
   float coordsVal3[4] = {30.0, -15.0, -30.0, -15.0};
   float coordsVal4[4] = {0.0, -7.5, 0.0, 7.5};
   float coordsVal5[4] = {0.0, 7.5, 0.0, -7.5};


   Source src1 = *new Source(coordsVal1); 
   Source src2 = *new Source(coordsVal2); 
   Source src3 = *new Source(coordsVal3); 
   Source src4 = *new Source(coordsVal4); 
   Source src5 = *new Source(coordsVal5);

   writeOnScreen();

   src4.produceTree(0);
   src5.produceTree(0);

   glFlush();
}

void init(void)
{
   glClearColor(0.87, 0.89, 1.0, 0.0);
}

void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
   if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      maxLevel++;
   else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
      maxLevel--;
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(400, 100);
   glutCreateWindow("Viva-3  Fractals");
   init();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutMouseFunc(mouse);
   glutMainLoop();

   return 0;
}
