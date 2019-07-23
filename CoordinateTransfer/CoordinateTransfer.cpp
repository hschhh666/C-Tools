#include "CoordinateTransfer.h"


//���ע�ͷǳ���Ҫ������ϸ�Ķ�
/***************************************
ԭ���ߣ��Ի�ݼ��ʦ
�޸��ߣ����ٳ� hushch@pku.edu.cn

������ͣ�������̳�������ʦ�ĳ�������һЩ����ϵ�ϵ�ͳһ������
�������ǻ���ŷ���ǵ���ά����任�������ﶨ��
1. ����ϵ��������ϵ
2. ����������������ԭ�㿴ȥ����������ת����Ϊ�Ƹ�������˳ʱ�뷽����ת
3. �������ṩ��������ת˳��������X��ת����Y��ת����Z��ת������ɿ�����Ĵ���ע��
4. һ��ע�⣬��������ת���������ᣬ������ת�������������������Ӧ�������

****************************************/


//����3x3�ĵ�λ��
void rMatrixInit (MATRIX &rt)
{
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			if (i==j) rt[i][j] = 1;
			else rt[i][j] = 0;
}


//����3x3�ķ�����ˣ�һ��ע��������˳�򡣱������� r = r*rt
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



//������ת���󡣱���ת����Ϊ����������X��תrotateX���ȣ�����Y��תrotateY���ȣ�����Z��תrotateZ����
//��ת�Ƕȵ�������������뿪ͷ��ע�͡�����������ȥ��˳ʱ����תΪ������
//ע����ת�Ƕ�Ϊ������
//��ת���󱣴���rt���3x3�ľ�����
//������������X�ᡢY�ᡢZ����ת����ת����ֱ�ΪRx,Ry,Rz���򱾺�����rt = Rz*Ry*Rx
//��ԭ������Ļ�����Ϊ(x0,y0,z0)T�� ����ת��������������Ϊ (x1,y1,z1)T = rt * (x0,y0,z0)T = Rz*Ry*Rx * (x0,y0,z0)T������TΪת�ã�������������ʾ������
//������ת���������(x1,y1,z1)T�µ�A����Ϊ(a1,b1,c1)�����A��ԭ������(x0,y0,z0)T������Ϊ(a0,b0,c0) = (a1,b1,c1)*rt
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


//�ο�����createRotMatrix_ZYX��ע��
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


//�ο�����createRotMatrix_ZYX��ע��
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

//��Ϊ��pt���������������������ת����a
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

//��Ϊ��pt���������������������ת����a
//ע��۲����������a��˳��������rotatePoint3d��a��ת�á����൱�ڰ�������ת�ص�ԭ��.
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

//��Ϊ��pt���������������������ת����a
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
