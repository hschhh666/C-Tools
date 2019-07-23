#include "CoordinateTransfer.h"


//这段注释非常重要，请仔细阅读
/***************************************
原作者：赵卉菁老师
修改者：胡少驰 hushch@pku.edu.cn

代码解释：本代码继承自赵老师的程序，做了一些坐标系上的统一工作。
本代码是基于欧拉角的三维坐标变换，在这里定义
1. 坐标系采用右手系
2. 自坐标轴正方向向原点看去，定义正旋转方向为绕该坐标轴顺时针方向旋转
3. 本代码提供了若干旋转顺序，如先绕X轴转再绕Y轴转再绕Z轴转，具体可看下面的代码注释
4. 一定注意，本代码旋转的是坐标轴，根据旋转后的坐标轴再来计算相应点的坐标

****************************************/


//创建3x3的单位阵
void rMatrixInit (MATRIX &rt)
{
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			if (i==j) rt[i][j] = 1;
			else rt[i][j] = 0;
}


//两个3x3的方阵相乘，一定注意矩阵相乘顺序。本函数中 r = r*rt
void rMatrixmulti (MATRIX &r, MATRIX &rt)
{
	double	rin[3][3];	 
	int		i, j;

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			rin[i][j] = r[i][j];

	for (i=0; i<3; i++) 
		for (j=0; j<3; j++) { 
			r[i][j] = rin[i][0]*rt[0][j] +
					  rin[i][1]*rt[1][j] +
					  rin[i][2]*rt[2][j];
		}
}



//创建旋转矩阵。本旋转矩阵为坐标轴先绕X轴转rotateX弧度，再绕Y轴转rotateY弧度，再绕Z轴转rotateZ弧度
//旋转角度的正方向详见代码开头处注释。自轴正方向看去，顺时针旋转为正方向。
//注意旋转角度为弧度制
//旋转矩阵保存在rt这个3x3的矩阵中
//定义坐标轴绕X轴、Y轴、Z轴旋转的旋转矩阵分别为Rx,Ry,Rz，则本函数中rt = Rz*Ry*Rx
//设原坐标轴的基向量为(x0,y0,z0)T， 则旋转后的坐标轴基向量为 (x1,y1,z1)T = rt * (x0,y0,z0)T = Rz*Ry*Rx * (x0,y0,z0)T，其中T为转置，即用列向量表示基向量
//设在旋转后的坐标轴(x1,y1,z1)T下点A坐标为(a1,b1,c1)，则点A在原坐标轴(x0,y0,z0)T的坐标为(a0,b0,c0) = (a1,b1,c1)*rt
void createRotMatrix_ZYX (MATRIX &rt, double rotateX, double rotateY, double rotateZ)
{
	double	sinx, siny, sinz, cosx, cosy, cosz;
	double	rr[3][3];
	int		i, j;

	sinx = sin(rotateX);
	siny = sin(rotateY);
	sinz = sin(rotateZ);
	cosx = cos(rotateX);
	cosy = cos(rotateY);
	cosz = cos(rotateZ);

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			if (i==j) rt[i][j] = 1;
			else rt[i][j] = 0;

	if (rotateZ!=0.0) {
		/*	Rz :   cosz  -sinz   0.0
				   sinz  cosz   0.0
				   0.0   0.0   1.0
		*/
		rr[0][0] = cosz;
		rr[0][1] = -sinz;
		rr[0][2] = 0.0;
		rr[1][0] = sinz;
		rr[1][1] = cosz;
		rr[1][2] = 0.0;
		rr[2][0] = 0.0;
		rr[2][1] = 0.0;
		rr[2][2] = 1.0;
		rMatrixmulti (rt, rr);
	}

	if (rotateY!=0.0) {
		/*	Ry :   cosy   0.0  siny
			 		0.0   1.0   0.0
				  -siny   0.0  cosy
		*/
		rr[0][0] = cosy;
		rr[0][1] = 0.0;
		rr[0][2] = siny;
		rr[1][0] = 0.0;
		rr[1][1] = 1.0;
		rr[1][2] = 0.0;
		rr[2][0] = -siny;
		rr[2][1] = 0.0;
		rr[2][2] = cosy;
		rMatrixmulti (rt, rr);
	}

	if (rotateX!=0.0) {
		/*	Rx :	1.0   0.0   0.0
					0.0  cosx  -sinx
					0.0  sinx  cosx
		*/
		rr[0][0] = 1.0;
		rr[0][1] = 0.0;
		rr[0][2] = 0.0;
		rr[1][0] = 0.0;
		rr[1][1] = cosx;
		rr[1][2] = -sinx;
		rr[2][0] = 0.0;
		rr[2][1] = sinx;
		rr[2][2] = cosx;
		rMatrixmulti (rt, rr);
	}
}


//参看函数createRotMatrix_ZYX的注释
void createRotMatrix_ZXY (MATRIX &rt, double rotateX, double rotateY, double rotateZ)
{
	double	sinx, siny, sinz, cosx, cosy, cosz;
	double	rr[3][3];
	int		i, j;

	sinx = sin(rotateX);
	siny = sin(rotateY);
	sinz = sin(rotateZ);
	cosx = cos(rotateX);
	cosy = cos(rotateY);
	cosz = cos(rotateZ);

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			if (i==j) rt[i][j] = 1;
			else rt[i][j] = 0;

	if (rotateZ!=0.0) {
		/*	Rz :   cosz  -sinz   0.0
				   sinz  cosz   0.0
				   0.0   0.0   1.0
		*/
		rr[0][0] = cosz;
		rr[0][1] = -sinz;
		rr[0][2] = 0.0;
		rr[1][0] = sinz;
		rr[1][1] = cosz;
		rr[1][2] = 0.0;
		rr[2][0] = 0.0;
		rr[2][1] = 0.0;
		rr[2][2] = 1.0;
		rMatrixmulti (rt, rr);
	}


	if (rotateX!=0.0) {
		/*	Rx :	1.0   0.0   0.0
					0.0  cosx  -sinx
					0.0  sinx  cosx
		*/
		rr[0][0] = 1.0;
		rr[0][1] = 0.0;
		rr[0][2] = 0.0;
		rr[1][0] = 0.0;
		rr[1][1] = cosx;
		rr[1][2] = -sinx;
		rr[2][0] = 0.0;
		rr[2][1] = sinx;
		rr[2][2] = cosx;
		rMatrixmulti (rt, rr);
	}

	if (rotateY!=0.0) {
		/*	Ry :   cosy   0.0  siny
			 		0.0   1.0   0.0
				  -siny   0.0  cosy
		*/
		rr[0][0] = cosy;
		rr[0][1] = 0.0;
		rr[0][2] = siny;
		rr[1][0] = 0.0;
		rr[1][1] = 1.0;
		rr[1][2] = 0.0;
		rr[2][0] = -siny;
		rr[2][1] = 0.0;
		rr[2][2] = cosy;
		rMatrixmulti (rt, rr);
	}

}


//参看函数createRotMatrix_ZYX的注释
void createRotMatrix_XYZ (MATRIX &rt, double rotateX, double rotateY, double rotateZ)
{
	double	sinx, siny, sinz, cosx, cosy, cosz;
	double	rr[3][3];
	int		i, j;

	sinx = sin(rotateX);
	siny = sin(rotateY);
	sinz = sin(rotateZ);
	cosx = cos(rotateX);
	cosy = cos(rotateY);
	cosz = cos(rotateZ);

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			if (i==j) rt[i][j] = 1;
			else rt[i][j] = 0;

	if (rotateX!=0.0) {
		/*	Rx :	1.0   0.0   0.0
					0.0  cosx  -sinx
					0.0  sinx  cosx
		*/
		rr[0][0] = 1.0;
		rr[0][1] = 0.0;
		rr[0][2] = 0.0;
		rr[1][0] = 0.0;
		rr[1][1] = cosx;
		rr[1][2] = -sinx;
		rr[2][0] = 0.0;
		rr[2][1] = sinx;
		rr[2][2] = cosx;
		rMatrixmulti (rt, rr);
	}

	if (rotateY!=0.0) {
		/*	Ry :   cosy   0.0 siny
			 		0.0   1.0   0.0
				   -siny   0.0  cosy
		*/
		rr[0][0] = cosy;
		rr[0][1] = 0.0;
		rr[0][2] = siny;
		rr[1][0] = 0.0;
		rr[1][1] = 1.0;
		rr[1][2] = 0.0;
		rr[2][0] = -siny;
		rr[2][1] = 0.0;
		rr[2][2] = cosy;
		rMatrixmulti (rt, rr);
	}

	if (rotateZ!=0.0) {
		/*	Rz :   cosz  -sinz   0.0
				   sinz cosz   0.0
					0.0   0.0   1.0
		*/
		rr[0][0] = cosz;
		rr[0][1] = -sinz;
		rr[0][2] = 0.0;
		rr[1][0] = sinz;
		rr[1][1] = cosz;
		rr[1][2] = 0.0;
		rr[2][0] = 0.0;
		rr[2][1] = 0.0;
		rr[2][2] = 1.0;
		rMatrixmulti (rt, rr);
	}
}


void shiftPoint3d (Point3d &pt, Point3d &sh)
{
	Point3d		p;

	p.x = pt.x + sh.x;
	p.y = pt.y + sh.y;
	p.z = pt.z + sh.z;
	pt.x = p.x;
	pt.y = p.y;
	pt.z = p.z;
}

//认为点pt是行向量，行向量左乘旋转矩阵a
void rotatePoint3d (Point3d &pt, MATRIX &a)
{
	Point3d	p;
	p.x = a[0][0] * pt.x + a[1][0] * pt.y + a[2][0] * pt.z;
	p.y = a[0][1] * pt.x + a[1][1] * pt.y + a[2][1] * pt.z;
	p.z = a[0][2] * pt.x + a[1][2] * pt.y + a[2][2] * pt.z;
	pt.x = p.x;
	pt.y = p.y;
	pt.z = p.z;

}

void INVshiftPoint3d (Point3d &pt, Point3d &sh)
{
	pt.x = pt.x - sh.x;
	pt.y = pt.y - sh.y;
	pt.z = pt.z - sh.z;
}

//认为点pt是行向量，行向量左乘旋转矩阵a
//注意观察这里面访问a的顺序，正好是rotatePoint3d中a的转置。这相当于把坐标轴转回到原来.
void INVrotatePoint3d (Point3d &pt, MATRIX &a)
{
	Point3d	p;
	p.x = a[0][0]*pt.x + a[0][1]*pt.y + a[0][2]*pt.z;
	p.y = a[1][0]*pt.x + a[1][1]*pt.y + a[1][2]*pt.z;
	p.z = a[2][0]*pt.x + a[2][1]*pt.y + a[2][2]*pt.z;
	pt.x = p.x;
	pt.y = p.y;
	pt.z = p.z;
}

//认为点pt是行向量，行向量左乘旋转矩阵a
void rotatePoint3fi (Point3fi &pt, MATRIX &a)
{
	Point3d	p;
	p.x = a[0][0] * pt.x + a[1][0] * pt.y + a[2][0] * pt.z;
	p.y = a[0][1] * pt.x + a[1][1] * pt.y + a[2][1] * pt.z;
	p.z = a[0][2] * pt.x + a[1][2] * pt.y + a[2][2] * pt.z;
	pt.x = p.x;
	pt.y = p.y;
	pt.z = p.z;
}


double ppDistance2d (Point2d *p1, Point2d *p2)
{
	return sqrt(sqr(p1->x-p2->x)+sqr(p1->y-p2->y));
}

double innerProduct2d (Point2d *v1, Point2d *v2)
{
	return (v1->x*v2->x+v1->y*v2->y);
}

double normVector2d (Point2d *p)
{
	return (sqrt(sqr(p->x)+sqr(p->y)));
}

double normalize2d (Point2d *p)
{
	const   double NORM_EPS = 1.0e-10;
	double	norm;

	norm = normVector2d (p);
	if (norm) {
		p->x /= (norm + NORM_EPS);
		p->y /= (norm + NORM_EPS);
	}
	return norm;
}

double ppDistance3fi (Point3fi *pt1, Point3fi *pt2)
{
	return (sqrt(sqr(pt1->x-pt2->x)+sqr(pt1->y-pt2->y)+sqr(pt1->z-pt2->z)));
}

double p2r (Point3fi *pt1)
{
	return (sqrt(sqr(pt1->x)+sqr(pt1->y)+sqr(pt1->z)));
}
