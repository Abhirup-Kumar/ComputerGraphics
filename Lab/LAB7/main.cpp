#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<string>
using namespace std;

int leftedge[600], rightedge[600], flag=0 ,m, counteri=0, counterj;

	void line(int x0, int y0, int x1, int y1)
	{
		if (y1<y0)
		{
			int tmp;
			tmp = y1;
			y1 = y0;
			y0 = tmp;
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		int x = x0;

		m = (y1 - y0) / (x1 - x0);
		for (int i = y0; i<y1; i++)
		{
			if (x<leftedge[i])
				leftedge[i] = x;
			if (x>rightedge[i])
				rightedge[i] = x;
			x += (1 / m);
		}
	}

	void plot(int x0, int y0, int x1, int y1, int x2, int y2)
	{
		glLineWidth(3);
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);

		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glEnd();

		for (int i = 0; i<600; i++)
		{
			leftedge[i] = 600;
			rightedge[i] = 0;
		} 
		line(x0, y0, x1, y1);
		line(x1, y1, x2, y2);
		line(x2, y2, x0, y0);

		if (flag == 1 && counterj == 1)
		{
			for (int i = 0; i < 600; i++)
			{
				if (leftedge[i] < rightedge[i])
				{
					for (int j = leftedge[i]; j < rightedge[i]; j++)
					{
						glColor3f(1, 0.753, 0.796);
						glBegin(GL_POINTS);
						glVertex2f(j, i);
						glEnd();
					}

				}
			}
		}
			counterj = 0;
	}

	void display()
	{
		glClearColor(0.5,0.996,0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		int x0[3], x1[3], y0[3], y1[3], x2[3], y2[3];
		
		x0[0] = 360;
		y0[0] = 460;
		x1[0] = 260;
		y1[0] = 360;
		x2[0] = 460;
		y2[0] = 360;

		x0[1] = 250;
		y0[1] = 350;
		x1[1] = 150;
		y1[1] = 250;
		x2[1] = 350;
		y2[1] = 250;

		x0[2] = 145;
		y0[2] = 245;
		x1[2] = 45;
		y1[2] = 145;
		x2[2] = 245;
		y2[2] = 145;

	if(counteri==1)
	plot(x0[0], y0[0], x1[0], y1[0], x2[0], y2[0]);

	if(counteri==2)
	plot(x0[1], y0[1], x1[1], y1[1], x2[1], y2[1]);

	if(counteri==3)
	plot(x0[2], y0[2], x1[2], y1[2], x2[2], y2[2]);


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


	

void mouse(int button, int state, int mousex, int mousey)
	{
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
          flag=1;
		  counteri++;
   	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
	{ 
   glutPostRedisplay();
   }
   if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
   { 
   counterj++;
   }
}


	int main(int argc, char **argv)
	{
		glutInit(&argc, argv);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(600, 600);
		glutCreateWindow("Experiment-7 Scanline");
		gluOrtho2D(0, 600, 0, 600);
		glutDisplayFunc(display);
		glutMouseFunc(mouse);
		glutMainLoop();
		return 0;
	}