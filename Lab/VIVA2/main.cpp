#include<GL/gl.h>
#include<GL/glut.h>
#include<string>

using namespace std;

typedef unsigned int regcode;
enum{TOP=1,BOTTOM=2,RIGHT=4,LEFT=8};
int mainwindow;

int ww = 640, wh = 480;  
int xi, yi, xf, yf,x11,y11,x22,y22; 
float xd1,yd1,xd2,yd2;
int xmin,ymin,xmax,ymax;

void setPixel(int x, int y) 
{
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}
	
	
regcode ComputeCode(int x, int y)
{
    regcode code=0;
    if(y>ymax)
        code|=TOP;
    if(y<ymin)
        code|=BOTTOM;
    if(x>xmax)
        code|=RIGHT;
    if(x<xmin)
        code|=LEFT;
    return code;
}	

void CohenSutherland(int xi, int yi, int xf, int yf)
{
	int x0, y0, x1, y1;
	x0 = xi;
	y0 = yi;
	x1 = xf;
	y1 = yf;
    regcode regcode0,regcode1,regcodeout;
    int accept = 0, done = 0;
    regcode0=ComputeCode(xi,yi);
    regcode1=ComputeCode(xf,yf);
    do
    {
        if(regcode0==0 && regcode1==0)
        {
            accept=1;
            done=1;
        }
        else if(regcode0 & regcode1)
            {
                done=1;
            }
            else
            {
              	int x,y;
                int ocd=regcode0 ? regcode0:regcode1;
                if(ocd & TOP)
                {
                    x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                    y=ymax;
                }
                else if(ocd & BOTTOM)
                {
                    x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                    y=ymin;
                }
                else if(ocd & LEFT)
                {
                    y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                    x=xmin;
                }
                else
                {
                    y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                    x=xmax;
                }
                if(ocd==regcode0)
                {
                    x0=x;
                    y0=y;
                    regcode0=ComputeCode(x0,y0);
                }
                else
                {
                    x1=x;
                    y1=y;
                    regcode1=ComputeCode(x1,y1);
                }
            }

    }while(done==0);

    if(accept==1)
    {
        	glColor3f(1.0, 1.0, 0.0);
			    glPointSize(8);
			    glBegin(GL_LINES);
    			glVertex2f(x0,y0);
    			glVertex2f(x1,y1);
    			glEnd();
          glFlush();
    }
}

void radomWindowcohen()
{
	int flag=0;
	while(flag==0)
	{
		int randomX=(rand()%ww);
		int randomY=(rand()%wh);
				glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(3);
				glColor3f(0.0,0.0,0.0);
				glFlush();
				glBegin(GL_LINES);
    			glVertex2f(xi,yi);
    			glVertex2f(xf,yf);
    			glEnd();
        glBegin(GL_LINES);
    			glVertex2f(x11,y11);
    			glVertex2f(x22,y22);
    			glEnd();
				xmin=randomX;
				xmax=randomX+130;
				ymin=randomY;
				ymax=randomY+150;
				glColor3f(1.0 , 0.0, 0.0);
				glBegin(GL_LINE_LOOP);
				glVertex2i(xmin, ymin);
				glVertex2i(xmax, ymin);
				glVertex2i(xmax, ymax);
				glVertex2i(xmin, ymax);
				glEnd();
				glFlush();
				CohenSutherland(xi, yi, xf, yf); 
        CohenSutherland(x11, y11, x22, y22);
				flag=1;
	}
}

void keyboardkeycohen(unsigned char key,int x,int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(key==32)
    {
        radomWindowcohen();
    }
    
}

void drawcohen(void)
{
  
  glColor3f(0.644f, 0.164f, 0.164f); 
  string s="500065719 | ABHIRUP";
  glRasterPos2f(160.0,0);
  int n=s.size();
  for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
    
    glColor3f(1.0f, 0.0f, 1.0f); 
   s="CohenSutherland";
  glRasterPos2f(260.0,wh-10);
   n=s.size();
  for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);


  glutSwapBuffers();
  glutPostRedisplay();
}
 

void initcohen() 
{  
  glutCreateSubWindow(mainwindow,ww/2,0,ww/2,wh);
  glClearColor(0.0,0.996,0,0.0);
  glColor3f(1.0,1.0,0.0);

gluOrtho2D(0,ww,0,wh);
} 

void displaycohen()
{
	glColor3f(1.0f, 1.0f, 1.0f); 
	xi=0;
	yi=480;
	xf=640;
	yf=0;
  x11=ww/2;
  y11=wh/2;
  x22=-ww;
  y22=wh/2;
}

int xcbox = 0, ycbox = 0, rcbox = 0;
int xminl=0,yminl=0,xmaxl=0,ymaxl=0;

float maximum(float arr[],int n) {
  float m = 0;
  for (int i = 0; i < n; ++i)
    if (m < arr[i])
      m = arr[i];
  return m;
}

float minimum(float arr[], int n) {
  float m = 1;
  for (int i = 0; i < n; ++i)
    if (m > arr[i])
      m = arr[i];
  return m;
}

void square(int x, int y, int change)
{
    int a = x-change;
    int b = y-change;
    int c = x+change;
    int d = y+change;
    glColor3f(0.644,0.164,0.164);
    glBegin(GL_LINE_LOOP);
        glVertex2f(a, b);
        glVertex2f(c, b);
        glVertex2f(c, d);
        glVertex2f(a, d);
    glEnd();
}

int newx1[2] = {0}, newy1[2] = {0}, newx2[2] = {0}, newy2[2] = {0};
void Liang(int x1,int y1,int x2,int y2, int line)
{
  float p1 = -(x2 - x1);
  float p2 = -p1;
  float p3 = -(y2 - y1);
  float p4 = -p3;

  float q1 = x1 - xminl;
  float q2 = xmaxl - x1;
  float q3 = y1 - yminl;
  float q4 = ymaxl - y1;

  float positive[5], negative[5];
  int posindex = 1, negindex = 1;
  positive[0] = 1;
  negative[0] = 0;

  if ((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0)) {
    return;
  }
  if (p1 != 0) {
    float r1 = q1 / p1;
    float r2 = q2 / p2;
    if (p1 < 0) {
      negative[negindex++] = r1; 
      positive[posindex++] = r2; 
    } else {
      negative[negindex++] = r2;
      positive[posindex++] = r1;
    }
  }
  if (p3 != 0) {
    float r3 = q3 / p3;
    float r4 = q4 / p4;
    if (p3 < 0) {
      negative[negindex++] = r3;
      positive[posindex++] = r4;
    } else {
      negative[negindex++] = r4;
      positive[posindex++] = r3;
    }
  }

  float xn1, yn1, xn2, yn2;
  float rn1, rn2;
  rn1 = maximum(negative, negindex); 
  rn2 = minimum(positive, posindex); 

  if (rn1 > rn2)  { 
    return;
  }

  xn1 = x1 + p2 * rn1;
  yn1 = y1 + p4 * rn1; 

  xn2 = x1 + p2 * rn2;
  yn2 = y1 + p4 * rn2;

  glColor3f(0,0,0);

  if(line == 1)
  {
  newx1[0] = xn1;
  newy1[0] = yn1;
  newx2[0] = xn2;
  newy2[0] = yn2;

  }

  if(line == 2)
  {
  newx1[1] = xn1;
  newy1[1] = yn1;
  newx2[1] = xn2;
  newy2[1] = yn2;

  }
  glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 1.0f); 
    string s="Liang Barsky";
    glRasterPos2f(100.0,wh-10);
    int n=s.size();
    for(int i=0;i<n;i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,s[i]);
    glColor3f(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(ww/2,wh);
    glVertex2f(ww/4,wh/2);
    glVertex2f(ww/2,wh/2);
    glEnd();

    square(xcbox, ycbox, rcbox);
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2f(newx1[0],newy1[0]);
    glVertex2f(newx2[0],newy2[0]);
    glVertex2f(newx1[1],newy1[1]);
    glVertex2f(newx2[1],newy2[1]);
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x= rand()%ww/2;
        y = rand()%wh;
        xcbox = x;
        ycbox = y;
        rcbox = 50;
        xminl = x-rcbox;
        yminl = y-rcbox;
        xmaxl = x+rcbox;
        ymaxl = y+rcbox;
        Liang(0,0,ww/2,wh, 1);
        Liang(ww/4,wh/2,ww/2,wh/2, 2);
        glutPostRedisplay();
    }
    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glutPostRedisplay();
    }
}

int main(int argc, char **argv) 
{
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(ww, wh);
    mainwindow = glutCreateWindow("Viva 2 - Linag Barsky and CohenSutherland");
   glClearColor(1,1,1,0);
    gluOrtho2D(0, ww, 0, wh);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

  initcohen();
  glutDisplayFunc(drawcohen);
  displaycohen();
  glutKeyboardFunc(keyboardkeycohen); 

  glutMainLoop();
  return 0;
}

