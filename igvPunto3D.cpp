#include <stdio.h>
#include <math.h>

#include "igvPunto3D.h"

// Constructores
igvPunto3D::igvPunto3D() {
	c[X] = c[Y] = c[Z] = 0.0;
}

igvPunto3D::igvPunto3D (const double& x, const double& y, const double& z ) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;	
}

// Constructor de copia
igvPunto3D::igvPunto3D (const igvPunto3D& p ) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
}

// Operador de asignación
igvPunto3D& igvPunto3D::operator = (const igvPunto3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	return(*this);
}

int igvPunto3D::operator == (const igvPunto3D& p) {
	return ((fabs(c[X]-p[X])<IGV_EPSILON) && (fabs(c[Y]-p[Y])<IGV_EPSILON) && (fabs(c[Z]-p[Z])<IGV_EPSILON));
}

int igvPunto3D::operator != (const igvPunto3D& p) {
	return ((fabs(c[X]-p[X])>=IGV_EPSILON) || (fabs(c[Y]-p[Y])>=IGV_EPSILON) || (fabs(c[Z]-p[Z])>=IGV_EPSILON));
}

igvPunto3D& igvPunto3D::operator+(const igvPunto3D& p)
{
	igvPunto3D res(c[0] + p.c[0], c[1] + p.c[1], c[2] + p.c[2]);
	return res;
}

igvPunto3D& igvPunto3D::operator-(const igvPunto3D& p)
{
	igvPunto3D* res = new igvPunto3D(c[0] - p.c[0], c[1] - p.c[1], c[2] - p.c[2]);
	return *res;
}

igvPunto3D& igvPunto3D::operator-=(const igvPunto3D& p) {
	c[X] -= p.c[X];
	c[Y] -= p.c[Y];
	c[Z] -= p.c[Z];
	return *this;
}

igvPunto3D& igvPunto3D::operator+=(const igvPunto3D& p) {
	c[X] += p.c[X];
	c[Y] += p.c[Y];
	c[Z] += p.c[Z];
	return *this;
}

igvPunto3D& igvPunto3D::operator*(const double& n)
{
	igvPunto3D* res = new igvPunto3D(c[X] * n, c[Y] * n, c[Z] * n);
	return *res;
}

igvPunto3D& igvPunto3D::productoVectorial(const igvPunto3D& a, const igvPunto3D& b)
{
	 
	double x = a[Y] * b[Z] - a[Z] * b[Y];
	double y = a[2] * b[X] - a[X] * b[Z];
	double z = a[X] * b[Y] - a[Y] * b[X];
	return *(new igvPunto3D(x,y,z));
}

void igvPunto3D::normalizar(igvPunto3D& v)
{
	double mod = sqrt(pow(v[X],2) + pow(v[Y] , 2) + pow(v[Z],2));
	v[X] /= mod;
	v[Y] /= mod;
	v[Z] /= mod;
}

// Destructor
igvPunto3D::~igvPunto3D() {
}

// Operadores

void igvPunto3D::set( const double& x, const double& y, const double& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}

std::ostream& operator<<(std::ostream& os, const igvPunto3D& p)
{
	os << "(" << p[X] << ", " << p[Y] << ", " << p[Z] << ")";
	return os;
}