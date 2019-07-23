#pragma once
#include <math.h>

typedef double  MATRIX[3][3];
#define	sqr(x)			((x)*(x))


//注意，这里定义的数据结构可以搬出去，谨防重定义
//3个double
struct Point3d {
	double x;
	double y;
	double z;
};

//3个double + 1个unsigned char
struct Point3fi {
	float x;
	float y;
	float z;
	unsigned char i;
};

//2个double
struct Point2d
{
	double x;
	double y;
};

void rMatrixInit(MATRIX &rt);
void rMatrixmulti(MATRIX &r, MATRIX &rt);
void createRotMatrix_ZYX(MATRIX &rt, double rotateX, double rotateY, double rotateZ);
void createRotMatrix_ZXY(MATRIX &rt, double rotateX, double rotateY, double rotateZ);
void createRotMatrix_XYZ(MATRIX &rt, double rotateX, double rotateY, double rotateZ);
void shiftPoint3d(Point3d &pt, Point3d &sh);
void rotatePoint3d(Point3d &pt, MATRIX &a);
void INVshiftPoint3d(Point3d &pt, Point3d &sh);
void INVrotatePoint3d(Point3d &pt, MATRIX &a);
void rotatePoint3fi(Point3fi &pt, MATRIX &a);
double ppDistance2d(Point2d *p1, Point2d *p2);
double innerProduct2d(Point2d *v1, Point2d *v2);
double normVector2d(Point2d *p);
double normalize2d(Point2d *p);
double ppDistance3fi(Point3fi *pt1, Point3fi *pt2);
double p2r(Point3fi *pt1);
