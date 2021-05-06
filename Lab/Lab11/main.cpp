#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<iostream>
#include<cmath>
#include<vector>

#define PI 3.14159265358
#define DRAWPOLYGON 0
#define TRANSLATE 1
#define ROTATE 2
#define SCALE 3
#define REFLECT 4
#define SHEARING 5
int tran_x,tran_y;
int _xtmp,_ytmp;//Used as a zoom variable
int mode=DRAWPOLYGON;//The default 
using namespace std;
const int winwidth=800;
const int winheight=640;
GLfloat halfScreenWidth = winwidth / 2;
    GLfloat halfScreenHeight = winheight / 2;
int refchoice=0;
int sorta=0;
struct position{
    double x;
    double y;
    double z;
};
typedef GLfloat Matrix4x4[4][4];
typedef GLfloat Matrix3x3[3][3];
float xy[8][4];
void DrawCube();
// float centerPosX=halfScreenWidth, centerPosY=halfScreenHeight, edgeLength=200,centerPosZ=-500 ;
float centerPosX=0, centerPosY=0, edgeLength=100,centerPosZ=0 ;
//void SetIdentity(Matrix3x3 mat);
void SetIdentity4(Matrix4x4 mat);
int camx=0, camy=0,camz=5;

void reshape(int w, int h)
{
glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, 1000, -1000); //L R B T
    glMatrixMode( GL_MODELVIEW );

    
}

void init(){
      glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0f);
  //  glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -320, 320, 1000, -1000); //L R B T
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}


void mul(float a[][4], float b[][4], float c[][4]) //a is xy, b is transform_matrix
{
	int i, j, k;
	float sum;
	for (i = 0; i < 1; i++)
	{
		for (j = 0; j < 4; j++)
		{
			sum = 0;
			for (k = 0; k < 4; k++)
			{
				sum = sum + a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
}
void printcurr(char *str);
void DRAWW(float xy[][4])
{
    glClear(GL_COLOR_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable( GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex2f(0,-winheight);
			glVertex2f(0,winheight);
			glVertex2f(-winwidth,0);
			glVertex2f(winwidth,0);
            glVertex2f(-winwidth,winheight);
			glVertex2f(winwidth,-winheight);
		glEnd();
    
    glColor3f(1.0,1.0,1.0);
       glRasterPos2f(-winwidth/2,-winheight/3-20);
   	string s="Abhirup Kumar | 500065719";
   	int n=s.size();
   	for(int i=0;i<n;i++)
     	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);

    

    switch (mode)
        {
        case TRANSLATE:
        printcurr("TRANSLATION");
            break;
        case ROTATE:
        printcurr("ROTATION");
            break;
        case SCALE:
        printcurr("SCALING");
            break;
        case REFLECT:
        printcurr("REFLECTION");
            break;
        case SHEARING:
        printcurr("SHEARING");
            break;
        default:
            break;
        } 


    //glBegin(GL_QUADS);
    glBegin(GL_LINE_LOOP);
    //front
    glColor3f(1.0,0.0,0.0);
    glVertex3f(xy[0][0],xy[0][1],xy[0][2]);
    glVertex3f(xy[1][0],xy[1][1],xy[1][2]);
    glVertex3f(xy[2][0],xy[2][1],xy[2][2]);
    glVertex3f(xy[3][0],xy[3][1],xy[3][2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    // back
    glColor3f(0.0,0.0,1.0);
    glVertex3f(xy[4][0],xy[4][1],xy[4][2]);
    glVertex3f(xy[5][0],xy[5][1],xy[5][2]);
    glVertex3f(xy[6][0],xy[6][1],xy[6][2]);
    glVertex3f(xy[7][0],xy[7][1],xy[7][2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    // //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(xy[0][0],xy[0][1],xy[0][2]);
    glVertex3f(xy[3][0],xy[3][1],xy[3][2]);
    glVertex3f(xy[7][0],xy[7][1],xy[7][2]);
    glVertex3f(xy[4][0],xy[4][1],xy[4][2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    // //right

    glColor3f(0.0,1.0,1.0);
    glVertex3f(xy[1][0],xy[1][1],xy[1][2]);
    glVertex3f(xy[2][0],xy[2][1],xy[2][2]);
    glVertex3f(xy[6][0],xy[6][1],xy[6][2]);
    glVertex3f(xy[5][0],xy[5][1],xy[5][2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    // //top
    glColor3f(1.0,0.0,1.0);
    glVertex3f(xy[0][0],xy[0][1],xy[0][2]);
    glVertex3f(xy[1][0],xy[1][1],xy[1][2]);
    glVertex3f(xy[5][0],xy[5][1],xy[5][2]);
    glVertex3f(xy[4][0],xy[4][1],xy[4][2]);
glEnd();
    glBegin(GL_LINE_LOOP);
    //bottom
    glColor3f(0.0,1.0,0.0);
    glVertex3f(xy[3][0],xy[3][1],xy[3][2]);
    glVertex3f(xy[2][0],xy[2][1],xy[2][2]);
    glVertex3f(xy[6][0],xy[6][1],xy[6][2]);
    glVertex3f(xy[7][0],xy[7][1],xy[7][2]);
    glEnd();
    glFlush();

}

void transform(float mul_matrix[][4])
{
	float Pdash[][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	for (int i = 0; i < 8; i++)
		mul(xy + i, mul_matrix, Pdash + i);
	DRAWW(Pdash);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			xy[i][j] = Pdash[i][j];
		}
	}
}

void reset()
{
    centerPosX=0;
  centerPosY=0;
   edgeLength=100;
   centerPosZ=0 ;    
   DrawCube();
}

void DrawCube()
{
    float halfSideLength = edgeLength * 0.5f;
    float xytemp[8][4] = {{centerPosX - halfSideLength,centerPosY + halfSideLength,centerPosZ + halfSideLength,1},
        {centerPosX + halfSideLength,centerPosY + halfSideLength,centerPosZ + halfSideLength,1},
        {centerPosX + halfSideLength,centerPosY - halfSideLength,centerPosZ + halfSideLength,1},
        {centerPosX - halfSideLength,centerPosY - halfSideLength,centerPosZ + halfSideLength,1},
        
        {centerPosX - halfSideLength,centerPosY + halfSideLength,centerPosZ - halfSideLength,1},
        {centerPosX + halfSideLength,centerPosY + halfSideLength,centerPosZ - halfSideLength,1},
        {centerPosX + halfSideLength,centerPosY - halfSideLength,centerPosZ - halfSideLength,1},
        {centerPosX - halfSideLength,centerPosY - halfSideLength,centerPosZ - halfSideLength,1}
        };

    for(int i=0; i<8; i++)
        for(int j=0; j<4; j++)
            xy[i][j] = xytemp[i][j];

    DRAWW(xy);
}










position tmp;
void DrawPolygon();
void dragmouse(int x,int y);
void mymouse(int button,int state,int x,int y);
void myKeyboard(unsigned char key,int x,int y);
void myKeyboardUp(unsigned char key,int x,int y);


void SetIdentity4(Matrix4x4 mat){
    GLint row,col;
    for(row=0;row<4;row++){
        for(col=0;col<4;col++)
            mat[row][col]=(row==col);
    }
}




void MultiplyMat4(Matrix4x4 m1,Matrix4x4 m2){
    int row,col;
    Matrix4x4 tmp;
    for(row=0;row<4;row++){
        for(col=0;col<4;col++){
            tmp[row][col]=m1[row][0]*m2[0][col]+m1[row][1]*
                m2[1][col]+m1[row][2]*m2[2][col]+m1[row][3]*m2[3][col];
        }
    }

    for(row=0;row<4;row++){
        for(col=0;col<4;col++){
            m2[row][col]=tmp[row][col];
        }
    }
}

void translation(GLfloat tx,GLfloat ty, GLfloat tz){
    Matrix4x4 matTransl;
    SetIdentity4(matTransl);
    matTransl[3][0]=tx;
    matTransl[3][1]=ty;
    matTransl[3][2]=tz;
    transform(matTransl); 
}

void rotation(Matrix4x4 matRot)
{   
    transform(matRot);    
}
                        
void scaling(GLfloat sx,GLfloat sy,GLfloat sz)
{ 
    Matrix4x4 matScale = {{sx, 0, 0, 0}, {0, sy, 0, 0}, {0, 0, sz, 0}, {0, 0, 0, 1}};;
    transform(matScale);
}


void reflection(int a, int b, int c) 
{
    Matrix4x4 matrefl={{a,0,0,0},{0,b,0,0},{0,0,c,0},{0,0,0,1}};
    transform(matrefl);
}

void Shearing(Matrix4x4 matShear)
{
    transform(matShear);
}

 

void DrawPolygon(){

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable( GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(1.0,1.0,1.0);
    DrawCube();
    glFlush();
}

void dragmouse(int x,int y){
    float ssx=1,ssy=1;
     int tx=0, ty=0, tz=0,a=1,b=1,c=1;
    switch (mode)
    {
        case DRAWPOLYGON:               
            break;
        case TRANSLATE:
            if(x>_xtmp){
                tx += 10;
            }
            else if(x<_xtmp){
                tx -= 10;
            }
            if(y<_ytmp){
                ty += 10;
            }
            else if(y>_ytmp){
                ty -= 10;
            }
            translation(tx,ty,tz);
             _xtmp=x;
             _ytmp = y;
            glutPostRedisplay();
            break;
        case ROTATE:
            _xtmp=x;
            _ytmp=y; 
            break;
        case SCALE:  

            /*Unequal scaling*/
            if(x>_xtmp){
                ssx+=0.1f;
            }
            else if(x<_xtmp&&ssx>0){
                ssx-=0.1f;
            }
            if(y<_ytmp){
                ssy+=0.1f;
            }
            else if(y>_ytmp&&ssy>0){
                ssy-=0.1f;
            }

            _xtmp=x;
            _ytmp=y;
            break;
        
        case REFLECT:
            _xtmp=x;
            _ytmp=y;
            break;
        case SHEARING:
        if(x>_xtmp){
                ssx+=0.01f;
            }
            else if(x<_xtmp&&ssx>0){
                ssx-=0.01f;
            }
            if(y<_ytmp){
                ssy+=0.01f;
            }
            else if(y>_ytmp&&ssy>0){
                ssy-=0.01f;
            }
            //Shearing(ssx,ssy,tran_x,tran_y);
           // transformedPoints();
            _xtmp=x;
            _ytmp=y;
            break;
        default:
            break;
    } 
} 


void mymouse(int button,int state,int x,int y){
    if(button==GLUT_MIDDLE_BUTTON &&state==GLUT_DOWN){
        if(sorta == 0)
        {
            camx = -3;
            camy = 4;
            camz = 5;
            sorta =1;
            gluLookAt(camx, camy, camz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        }
        else
        {
            camx = 0;
            camy = 0;
            camz = 5;
            sorta =0;
            gluLookAt(camx, camy, camz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        }
    }
    int tx=0, ty=0, tz=0,a=1,b=1,c=1;
    if(button==GLUT_LEFT_BUTTON &&state==GLUT_DOWN){
        
        switch (mode)
        {
        case TRANSLATE:
            break;
        case DRAWPOLYGON:      
            tmp.x=x;
            tmp.y=y;
            //xy.push_back(tmp);
            DrawPolygon();
            break;
        case ROTATE:
            tran_x=x;
            tran_y=y;
            _xtmp=x;
            _ytmp=y;
            break;
        case SCALE:
            tran_x=x;
            tran_y=y;
            break;
        case REFLECT:
        tran_x=x;
            tran_y=y;
            _xtmp=x;
            _ytmp=y;
            break;
        case SHEARING:
        tran_x=x;
            tran_y=y;
            _xtmp=x;
            _ytmp=y;
            break;
        default:
            break;
        } 
    }
   
}
 
void printcurr(char *str) {
  glRasterPos2f(winwidth/6,winheight/3+70);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void Display(){
     glFlush();
}

void Menu(int id){
    if(id==0)
        mode=0;
    else if(id==1)
       mode=1;
    else if(id==2)
        mode=2;
    else if(id==3)
        mode=3;
    else if(id==4)
        mode=4;
    else if(id==5)
        mode=5;
}
 


void myKey(unsigned char key, int x, int y)
{
    int tx=0, ty=0, tz=0,a=1,b=1,c=1;
    float theta=10 * 3.14 / 180;

    float shx=0,shy=0,shz=0, sx=0, sy=0,sz=0;
    if(key == '6')
        { 
            tx += 10;
            translation(tx,ty,tz);
            tx = 0;
        }
    else if(key == '4')
        {   tx -= 10;
            translation(tx,ty,tz);
            tx=0;
        }
    else if(key == '8')
        {   ty += 10;
            translation(tx,ty,tz);
            ty=0;
        }
    else if(key == '2')
        {   ty -= 10;
            translation(tx,ty,tz);
            ty=0;
        }
    else if(key == '1')
        {   tz -= 10;
            translation(tx,ty,tz);
            tz=0;
        }
    else if(key == '3')
        {   tz += 10;
            translation(tx,ty,tz);
            tz=0;
        }
    else if(key == 'm') //shear in x
    {
        shy = 0.5;
        shz = 0.5;
        Matrix4x4 matShear = {{1,shy,shz,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        Shearing(matShear);
        shy = 0;
        shz = 0;
    }
    else if(key == 'n') //shear in y
    {
        shx = 0.5;
        shz = 0.5;
        Matrix4x4 matShear = {{1,0,0,0},{shx,1,shz,0},{0,0,1,0},{0,0,0,1}};
        Shearing(matShear);
        shx = 0;
        shz = 0;
    }
    else if(key == 'b') //shear in z
    {
        shx = 0.5;
        shy = 0.5;
        Matrix4x4 matShear = {{1,0,0,0},{0,1,0,0},{shx,shy,1,0},{0,0,0,1}};
        Shearing(matShear);
        shx = 0;
        shy = 0;
    }
    else if(key == 'i') //scaling big
    {
        sx=1.5;
        sy=1.5;
        sz=1.5;
        scaling(sx,sy,sz);
        sx=0;
        sy=0;
        sz=0;
    }
    else if(key == 'o') //scaling small
    {   sx=0.5;
        sy=0.5;
        sz=0.5;
        scaling(sx,sy,sz);
        sx=0;
        sy=0;
        sz=0;
    }
    else if (key == '9') // rotation in x
	{
		Matrix4x4 matrot = {{1, 0, 0, 0}, {0, cos(theta), sin(theta), 0}, {0, -sin(theta), cos(theta), 0}, {0, 0, 0, 1}};
		rotation(matrot);
        theta =0;
	}
	else if (key == '7') // rotation in y
	{
		Matrix4x4 matrot = {{cos(theta), 0, -sin(theta), 1}, {0, 1, 0, 0}, {sin(theta), 0, cos(theta), 0}, {0, 0, 0, 1}};
		rotation(matrot);
        theta =0;
	}
	else if (key == '5') // rotation in z
	{
		Matrix4x4 matrot = {{cos(theta), sin(theta), 0, 0}, { -sin(theta), cos(theta), 0,0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        rotation(matrot);
        theta =0;
	}
    else if (key == 's') //for reflection in yz plane
	{
		a=-1;
		reflection(a,b,c);
	}
    else if (key == 'd') //for reflection in zx plane
	{
		b=-1;
		reflection(a,b,c);
	}
    else if (key == 'a') //for reflection in xy plane
	{
		c=-1;
		reflection(a,b,c);
	}    
    else if (key == 'w') //for reflection about origin
	{
		c=-1;
        b=-1;
        a=-1;
		reflection(a,b,c);
	}
    glutPostRedisplay();

    if(key == 'r')
        reset();
}
int counter=0;

void timer(int)
{
  //  glutPostRedisplay();
    char str[] = "I am timed";
    glRasterPos2f(winwidth/4,winheight/3);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
  glutPostRedisplay();
}

int main(int argc,char**argv){
    glutInit(&argc,argv);//initialization
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);//Set the drawing mode
    glutInitWindowPosition(500,300);
    glutInitWindowSize(winwidth,winheight);
    glutCreateWindow("Experiment-11 CallBack Functions");//Create window 
    init();
    int id=glutCreateMenu(Menu);   
    glutAddMenuEntry("Polygon",0);
    glutAddMenuEntry("Translate",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Scale",3);
    glutAddMenuEntry("Reflect",4);
    glutAddMenuEntry("Shear",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutReshapeFunc(reshape);//1
    glutDisplayFunc(Display);
   glutMouseFunc(mymouse);
    glutMotionFunc(dragmouse);//2
    glutTimerFunc(1000,timer, 0);//3
    glutKeyboardFunc(myKey);
    glutMainLoop();
}