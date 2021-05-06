//#include<windows.h>
#include <GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

void init()
{
    glClearColor(0.7,0.7,0.7,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600);
}

void writeOnScreen(float x, float y, float z, char *str) {
  glRasterPos3f(x, y, z);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void writeSmaller(float x, float y, float z, char *str) {
  glRasterPos3f(x, y, z);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

void circle(float x, float y, float radius){
	int i;
	int triangleAmount = 100;
	float twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
                x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

void hollowCircle(float x, float y, float radius){
	int i;
	int lineAmount = 100;
	float twicePi = 2.0f * 3.14;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

class Point {
public:
    float x, y;
    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }

    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }
};

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}

int clicks = 4;
void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
      glVertex2f(p1.x, p1.y);
      glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}

Point drawBezierGeneralized(Point PT[], double t) {
    Point P;
    P.x = 0; P.y = 0;
    for (int i = 0; i<clicks; i++)
    {
        P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
    }
    return P;
}
void drawCurve(Point x[])
{
    Point p1 = x[0];
    for(double t = 0.0;t <= 1.0; t += 0.02)
    {
        Point p2 = drawBezierGeneralized(x,t);
        drawLine(p1, p2);

        p1 = p2;
    }
    glColor3f(0.0,0.0,0.0);
}
void shapeCoordinates()
{
    glColor3f(0,0.8,1);
    circle(325, 375, 150);

    glColor3f(0.9,0.9,0.9);
    glBegin(GL_LINES);
    glVertex2f(240,400);
    glVertex2f(250,325);
    glVertex2f(400,325);
    glVertex2f(410,400);
    glEnd();

    glColor3f(0.9,0.9,0.9);
    Point mask[3]={{250,325},{325,225},{403,330}};
    clicks=3;
    drawCurve(mask);

    glColor3f(0.9,0.9,0.9);
    Point mask1[5]={{240,400},{310,410},{325,470},{340,410},{415,398}};
    clicks=5;
    drawCurve(mask1);

    glLineWidth(3);
    glColor3f(0,0.5,1);
    Point mask2[5]={{240,385},{310,395},{325,455},{340,395},{415,383}};
    clicks=5;
    drawCurve(mask2);

    glLineWidth(3);
    glColor3f(0,0.5,1);
    Point mask3[5]={{265,365},{310,375},{325,410},{340,375},{390,365}};
    clicks=5;
    drawCurve(mask3);

    glColor3f(0,0.5,1);
    Point mask4[3]={{269,350},{325,330},{388,350}};
    clicks=3;
    drawCurve(mask4);

    glColor3f(0,0.5,1);
    Point mask5[3]={{269,325},{325,305},{388,325}};
    clicks=3;
    drawCurve(mask5);

    glLineWidth(4);
    glColor3f(0.7,0.7,0.7);
    Point left[5]={{238,395},{140,400},{220,350},{157,360},{254,325}};
    clicks=5;
    drawCurve(left);

    glColor3f(0.7,0.7,0.7);
    Point right[5]={{412,395},{515,400},{420,350},{490,360},{396,325}};
    clicks=5;
    drawCurve(right);
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}



int renderShape = 0;
int fillShape = 0;
void mainDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable( GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);

    shapeCoordinates();

    glColor3f(0,0,0);
    writeOnScreen(245,190,0,"WEAR MASK");
    writeOnScreen(270,160,0,"BE SAFE");
    writeOnScreen(10,20,0,"500065719 | Abhirup Kumar");
    glFlush();

    if(fillShape)
    {
        Color newColor = {1,1,1} ;
        Color oldColor = {0,0.8,1};
        floodFill(325, 425, oldColor, newColor);
        floodFill(325, 410, oldColor, newColor);
    }

}

void mainMouse(int button, int state, int x, int y)
{
    y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        fillShape = 1;
}

void reshape(int w, int h)
{
    glClearColor(0.7,0.7,0.7,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode( GL_MODELVIEW );

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(400,100);
    glutInitWindowSize(600, 600);
    int mainWindow = glutCreateWindow("LAB 12 : Bezier Curve");
    init();
    glutDisplayFunc(mainDisplay);
    glutReshapeFunc(reshape);
    glutMouseFunc(mainMouse);
    glutMainLoop();
}
