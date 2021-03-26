#include <iostream>
#include <vector>
#include <list>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define dimens 700

using namespace std;

typedef float Color[3]; //var of 3 floats.

struct Point
{
	int x, y;
};

typedef struct InterPoint
{
	int pointFlag;
	int index0, index1;
	Point p;
	bool inFlag;
	int dis;
}ipt;

class Polygon
{
public:
	vector<Point> pts;
	Polygon(void); //ctor
	~Polygon(void); //dtor
	void drawPolyLine(Color c);
};
Polygon::Polygon(void)
{
}
Polygon::~Polygon(void)
{
}
void Polygon::drawPolyLine(Color c)
{
	glColor3fv(c); //passing vector of floats
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	int size = pts.size();
	for (int i = 0; i < size; i++)
		glVertex2i(pts[i].x, pts[i].y);
	glEnd();
}

bool isPointInsidePoly(Point p, Polygon& py)
{
	int cnt = 0, size = py.pts.size();
	for (int i = 0; i < size; i++) {
		Point p1 = py.pts[i];
		Point p2 = py.pts[(i + 1) % size];
		if (p1.y == p2.y) continue;
		if (p.y < min(p1.y, p2.y)) continue;
		if (p.y >= max(p1.y, p2.y)) continue;
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if (x > p.x) cnt++;
	}
	return (cnt % 2 == 1);
}
int cross(Point& p0, Point& p1, Point& p2)
{
	return ((p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y));
}
bool onSegment(Point& p0, Point& p1, Point& p2)
{
	int minx = min(p0.x, p1.x), maxx = max(p0.x, p1.x);
	int miny = min(p0.y, p1.y), maxy = max(p0.y, p1.y);
	if (p2.x >= minx && p2.x <= maxx && p2.y >= miny && p2.y <= maxy) return true;
	return false;
}
bool segmentsIntersect(Point& p1, Point& p2, Point& p3, Point& p4)
{
	int d1 = cross(p3, p4, p1);
	int d2 = cross(p3, p4, p2);
	int d3 = cross(p1, p2, p3);
	int d4 = cross(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true;
	if (d1 == 0 && onSegment(p3, p4, p1)) return true;
	if (d2 == 0 && onSegment(p3, p4, p2)) return true;
	if (d3 == 0 && onSegment(p1, p2, p3)) return true;
	if (d4 == 0 && onSegment(p1, p2, p4)) return true;
	return false;
}

int flag=1;
vector<Point> figure1;
vector<Point>  figure2;

Point getintersectPoint(Point p1, Point p2, Point p3, Point p4)
{
	Point p;
	int b1 = (p2.y - p1.y) * p1.x + (p1.x - p2.x) * p1.y;
	int b2 = (p4.y - p3.y) * p3.x + (p3.x - p4.x) * p3.y;
	int D = (p2.x - p1.x) * (p4.y - p3.y) - (p4.x - p3.x) * (p2.y - p1.y);
	int D1 = b2 * (p2.x - p1.x) - b1 * (p4.x - p3.x);
	int D2 = b2 * (p2.y - p1.y) - b1 * (p4.y - p3.y);
	p.x = D1 / D;
	p.y = D2 / D;
	return p;
}
void generateIntersectPoints(Polygon& pyclip, Polygon& py, list<ipt>& iplist)
{
	int clipSize = pyclip.pts.size(), pySize = py.pts.size();

	for (int i = 0; i < clipSize; i++) {
		Point p1 = pyclip.pts[i];
		Point p2 = pyclip.pts[(i + 1) % clipSize];
		for (int j = 0; j < pySize; j++) {
			Point p3 = py.pts[j];
			Point p4 = py.pts[(j + 1) % pySize];
			if (segmentsIntersect(p1, p2, p3, p4)) {
				ipt ip;
				ip.index0 = j;
				ip.index1 = i;
				ip.p = getintersectPoint(p1, p2, p3, p4);
				iplist.push_back(ip);
			}
		}
	}
}
int getDistance(Point& p1, Point& p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool distanceComparator(ipt& ip1, ipt& ip2) {
	return ip1.dis < ip2.dis;
}
void generateList(Polygon& py, list<ipt>& iplist, list<ipt>& comlist, int index) {
	int size = py.pts.size();
	list<ipt>::iterator it;

	for (int i = 0; i < size; i++) {
		Point p1 = py.pts[i];
		ipt ip;
		ip.pointFlag = 0;
		ip.p = p1;
		comlist.push_back(ip);
		list<ipt> oneSeg;
		for (it = iplist.begin(); it != iplist.end(); it++) {
			if ((index == 0 && i == it->index0) ||
				(index == 1 && i == it->index1)) {
				it->dis = getDistance(it->p, p1);
				it->pointFlag = 1;
				oneSeg.push_back(*it);
			}
		}
		oneSeg.sort(distanceComparator);
		for (it = oneSeg.begin(); it != oneSeg.end(); it++)
			comlist.push_back(*it);
	}
}
void getPolyPointInOut(list<ipt>& Pglist, Polygon& pyclip) {
	bool inFlag;
	list<ipt>::iterator it;
	for (it = Pglist.begin(); it != Pglist.end(); it++) {
		if (it->pointFlag == 0) {
			if (isPointInsidePoly(it->p, pyclip))
				inFlag = true;
			else inFlag = false;
		}
		else {
			inFlag = !inFlag;
			it->inFlag = inFlag;
		}
	}
}
bool operator==(Point& p1, Point& p2) { //overloading == for point datatype
	return p1.x == p2.x && p1.y == p2.y;
}
void getClipPointInOut(list<ipt>& cliplist, list<ipt>& Pglist) {
	list<ipt>::iterator it, it1;
	for (it = cliplist.begin(); it != cliplist.end(); it++) {
		if (it->pointFlag == 0) continue;
		for (it1 = Pglist.begin(); it1 != Pglist.end(); it1++) {
			if (it1->pointFlag == 0) continue;
			if (it->p == it1->p) it->inFlag = it1->inFlag;
		}
	}
}
void generateClipArea(list<ipt>& Pglist, list<ipt>& cliplist) {
	list<ipt>::iterator it, it1;
	Polygon py;
	Color c = { 0.0, 0.0, 0.0 };

	for (it = Pglist.begin(); it != Pglist.end(); it++)
		if (it->pointFlag == 1 && it->inFlag) break;
	py.pts.clear();

	while (true) {

		if (it == Pglist.end()) break;
		py.pts.push_back(it->p);
		for (; it != Pglist.end(); it++) {
			if (it->pointFlag == 1 && !it->inFlag) break;
			py.pts.push_back(it->p);
		}
		for (it1 = cliplist.begin(); it1 != cliplist.end(); it1++)
			if (it1->p == it->p) break;

		for (; it1 != cliplist.end(); it1++) {
			if (it1->pointFlag == 1 && it1->inFlag) break;
			py.pts.push_back(it1->p);
		}
		if (py.pts[0] == it1->p) {
			py.drawPolyLine(c);
			py.pts.clear();
			for (; it != Pglist.end(); it++)
				if (it->pointFlag == 1 && it->inFlag) break;
			continue;
		}
		for (; it != Pglist.end(); it++)
			if (it->p == it1->p) break;
	}
}
void weilerAtherton(Polygon& pyclip, Polygon& py) {
	list<ipt> iplist, Pglist, cliplist;
	generateIntersectPoints(pyclip, py, iplist);

	generateList(py, iplist, Pglist, 0);
	generateList(pyclip, iplist, cliplist, 1);

	getPolyPointInOut(Pglist, pyclip);

	getClipPointInOut(cliplist, Pglist);

	generateClipArea(Pglist, cliplist);
}

void init()
{
	glClearColor(1, 0.450, 0, 0.0); // 0.270 is orange BG.
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, dimens - 1, 0.0, dimens - 1);
}

void GenerateRandomSimplePg(Polygon &G, int M)
{
	Point P;
	G.pts.clear();
	for (int i = 0; i < M; ++i)
	{
		bool flag;
		do
		{
			P.x = rand() % dimens;
			P.y = rand() % dimens;
			flag = true;
			for (int j = 1; j < i - 1; ++j)
				if (segmentsIntersect(G.pts[j - 1], G.pts[j], G.pts[i - 1], P))
				{
					flag = false;
					break;
				}
			if (flag && i == M - 1)
			{
				for (int j = 2; j < i; ++j)
					if (segmentsIntersect(G.pts[j - 1], G.pts[j], P, G.pts[0]))
					{
						flag = false;
						break;
					}
			}
		} while (!flag);
		G.pts.push_back(P);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable( GL_LINE_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  	
	glColor3f(1.0,1.0,1.0);
   	glRasterPos2f(400,30);
   	string s="Abhirup Kumar | 500065719";
   	int n=s.size();
   	for(int i=0;i<n;i++)
     	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);

	Polygon pyclip, py;

	int s_f1=figure1.size();
	int s_f2=figure2.size();

	for(int i=0;i<s_f1;i++)
        py.pts.push_back(figure1[i]);

    for(int i=0;i<s_f2;i++)
        pyclip.pts.push_back(figure2[i]);

	int size = pyclip.pts.size();
	for (int i = 0; i < size; ++i)
		cout << pyclip.pts[i].x << " " << pyclip.pts[i].y << endl;
	cout << endl;
	size = py.pts.size();
	for (int i = 0; i < size; ++i)
		cout << py.pts[i].x << " " << py.pts[i].y << endl;

	Color a = { 0, 0.0, 1.0 };
	Color b = { 0.0, 1.0, 0.0 };
	py.drawPolyLine(a);
	pyclip.drawPolyLine(b);
	weilerAtherton(pyclip, py);

	glFlush();
}

void KeyboardAction(unsigned char key, int x, int y)
{
    if(key==32)
    	flag=0;
}

void mouse(int button, int state, int x, int y)
{
    y=dimens-y;
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point temp;
        temp.x=x; temp.y=y;

		if(flag)
            figure1.push_back(temp);
        else
            figure2.push_back(temp);
		
		glutPostRedisplay();
    }

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(dimens, dimens);
	glutInitWindowPosition(0,0);
	glutCreateWindow("EXP-8 Weiler Atherton Polygon Clipping");

	glutKeyboardFunc(KeyboardAction);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 0;
}