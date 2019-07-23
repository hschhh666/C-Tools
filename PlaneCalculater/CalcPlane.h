/*计算地面的方程*/
#pragma once

//根据输入点云计算平面方程
void Calculate_Plane(int Points_Total, double *X_Coord, double *Y_Coord, double *Z_Coord, int Origin_Flag, double Plane_Eq[4]);
//计算点到平面的距离
double disToPlane(double p[3], double Plane_Eq[4]);


void Find_Scatter_Matrix(double Centroid[3], int Points_Total,double *X_Coord, double *Y_Coord, double *Z_Coord,double Scatter_Matrix[3][3], int Order[3]);
void tred2(double a[3][3], double d[3], double e[3]);
void tqli(double d[3], double e[3], double z[3][3]);
void Calculate_Residuals(double *X, double *Y, double *Z, double Equation[4],double *Error, int PointsTotal);