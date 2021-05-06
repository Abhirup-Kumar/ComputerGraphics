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
int refchoice=0;

struct position{
    double x;
    double y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 CompositeMat;//Composite matrix
vector<position> xy;
position tmp;
void DrawPolygon();
void dragmouse(int x,int y);
void mymouse(int button,int state,int x,int y);
void myKeyboard(unsigned char key,int x,int y);
void myKeyboardUp(unsigned char key,int x,int y);

void SetIdentity(Matrix3x3 mat){
    GLint row,col;
    for(row=0;row<3;row++){
        for(col=0;col<3;col++)
            mat[row][col]=(row==col);
    }
}

void init(){
     glClearColor(1.0,0.411,0.705,1.0);
    //glClearColor(1.0,0.613,0.657,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,winwidth,winheight,0);//L R T B
    SetIdentity(CompositeMat);
}

 

void MultiplyMat(Matrix3x3 m1,Matrix3x3 m2){
    GLint row,col;
    Matrix3x3 tmp;
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            tmp[row][col]=m1[row][0]*m2[0][col]+m1[row][1]*
                m2[1][col]+m1[row][2]*m2[2][col];
        }
    }

    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            m2[row][col]=tmp[row][col];
        }
    }
}

void translation(GLfloat tx,GLfloat ty){
    Matrix3x3 matTransl;
    SetIdentity(matTransl);
    matTransl[0][2]=tx;
    matTransl[1][2]=ty;
    MultiplyMat(matTransl,CompositeMat); 
}

//Rotation about arbitrary point
void rotation(int x,int y,float theta){
    theta=theta/180*PI;
    Matrix3x3 matRot;
    SetIdentity(matRot);
    matRot[0][0]=cos(theta); //this matrot is T  = T*R*T , we do before 
    matRot[0][1]=-sin(theta);//multiply it with point.
    matRot[0][2]=x*(1-cos(theta))+y*sin(theta);
    matRot[1][0]=sin(theta);
    matRot[1][1]=cos(theta);
    matRot[1][2]=y*(1-cos(theta))-x*sin(theta);
    MultiplyMat(matRot,CompositeMat); //matcomposite it is identity mat, we are passing 
}                                       // value of matrot to composite by * by it
                    //since it is indentity, it happens without us writing extra code in every func.
                        //matcomposite then * with P to get new P` in transforverts2d()

                        
void scaling(GLfloat sx,GLfloat sy,int x,int y){//Arbitrary 
    Matrix3x3 matScale;
    SetIdentity(matScale);
    matScale[0][0]=sx;
    matScale[0][2]=(1-sx)*x;
    matScale[1][1]=sy;
    matScale[1][2]=(1-sy)*y;
    MultiplyMat(matScale,CompositeMat);
}


void reflection()  //about X axis
{
    float m,ic;
		m=0;//slope
		ic=winheight/2;//intercept
		
		float a1=(1-m*m)/(1+m*m);
		float b=2*m/(m*m+1);
		float c=-2*ic*m/(m*m+1);
		float d=2*ic/(m*m+1);
    Matrix3x3 matrefl={{a1,b,c},{b,-a1,d},{0,0,1}};
    MultiplyMat(matrefl,CompositeMat);
}

void Shearing(GLfloat sx,GLfloat sy,int x,int y)//simultaneous shearing
{
    Matrix3x3 matShear ={{sx,0,0},{0,sy,0},{0,0,1}};
    MultiplyMat(matShear,CompositeMat);
}


void transformedPoints(){
    GLfloat tmp;
    for(int i=0;i<xy.size();i++)
    {
        tmp=CompositeMat[0][0]*xy[i].x+CompositeMat[0][1]*xy[i].y+CompositeMat[0][2];//here T*P is happening
        xy[i].y=CompositeMat[1][0]*xy[i].x+CompositeMat[1][1]*xy[i].y+CompositeMat[1][2];//T is matcomp
        xy[i].x=tmp;                                                                     //P is xy[]
    }
    DrawPolygon();
    SetIdentity(CompositeMat);
}
 

void DrawPolygon(){

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable( GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    for(unsigned int i=0;i<xy.size();i++){
        glVertex2f(xy[i].x,xy[i].y);
    }
    glEnd();

     glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex2f(0,winheight/2);
			glVertex2f(winwidth,winheight/2);
			glVertex2f(winwidth/2,0);
			glVertex2f(winwidth/2,winheight);
		glEnd();

    glColor3f(1.0,1.0,1.0);
   	glRasterPos2f(40,40);
   	string s="Abhirup Kumar | 500065719";
   	int n=s.size();
   	for(int i=0;i<n;i++)
     	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);

        glFlush();
}

void dragmouse(int x,int y){
   
    float ssx=1,ssy=1;
    switch (mode)
    {
        case DRAWPOLYGON:               
            break;
        case TRANSLATE:
            translation(x-tran_x,y-tran_y); //as it is recieved by tx and ty, they are translation factors.
            transformedPoints(); //this finds the new points, plots it and resets compositemat
            tran_x=x;
            tran_y=y;
            break;
        case ROTATE:
            if(x<=_xtmp&&y>=_ytmp)
                rotation(tran_x,tran_y,-8);
            else
                rotation(tran_x,tran_y,8);
            transformedPoints();
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

            scaling(ssx,ssy,tran_x,tran_y);
            transformedPoints();
            _xtmp=x;
            _ytmp=y;
            break;
        
        case REFLECT:
            reflection();
            transformedPoints();
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
            Shearing(ssx,ssy,tran_x,tran_y);
            transformedPoints();
            _xtmp=x;
            _ytmp=y;
            break;
        default:
            break;
    } 
} 


void mymouse(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON &&state==GLUT_DOWN){
        switch (mode)
        {
        case TRANSLATE:
            tran_x=x;
            tran_y=y;
            break;
        case DRAWPOLYGON:      
            tmp.x=x;
            tmp.y=y;
            xy.push_back(tmp);
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
 
int main(int argc,char**argv){
    glutInit(&argc,argv);//initialization
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);//Set the drawing mode
    glutInitWindowPosition(500,300);
    glutInitWindowSize(winwidth,winheight);
    glutCreateWindow("Experiment-9  2-D Transformations");//Create window 
    init();
    int id=glutCreateMenu(Menu);   
    glutAddMenuEntry("Polygon",0);
    glutAddMenuEntry("Translate",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Scale",3);
    glutAddMenuEntry("Reflect",4);
    glutAddMenuEntry("Shear",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutDisplayFunc(Display);
    glutMouseFunc(mymouse);//Mouse monitor callback function
    glutMotionFunc(dragmouse);//Mouse drag 

    glutMainLoop();
}