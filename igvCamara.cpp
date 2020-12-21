
#include <math.h>
#include <stdio.h>
#include <iostream>
#define PI 3.14159265358979323846
#include "igvCamara.h"

// Metodos constructores

igvCamara::igvCamara() {}

igvCamara::~igvCamara() {}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;

	tipo = _tipo;
}


// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
}
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	xwmin = _xwmin;
	xwmax = _xwmax;
	ywmin = _ywmin;
	ywmax = _ywmax;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
	double _angulo, double _raspecto, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	angulo = _angulo;
	raspecto = _raspecto;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::aplicar(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (tipo == IGV_PARALELA) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_FRUSTUM) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo == IGV_PERSPECTIVA) {
		gluPerspective(angulo, raspecto, znear, zfar);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X], P0[Y], P0[Z], r[X], r[Y], r[Z], V[X], V[Y], V[Z]);
	//gluLookAt(P0[X], P0[Y], P0[Z], P0[X] + r[X], P0[Y] + r[Y], P0[Z] + r[Z], V[X], V[Y], V[Z]);
}

double igvCamara::distPuntoVision()
{
	return sqrt((pow(r[X]-P0[X],2) + pow(r[Y] - P0[Y], 2) + pow(r[Z] - P0[Z], 2)));
}

void igvCamara::mirar(double incAlfa, double incBeta)
{
	beta += incBeta * vel;
	alfa += incAlfa * vel;
	if (beta > 89.0) {
		beta = 89.0;
	}
	else if (beta < -89.0) {
		beta = -89.0;
	}
	double dist = distPuntoVision();
	double alfaRad = alfa * PI / 180;
	double betaRad = beta * PI / 180;
	double rxz = dist * cos(betaRad);

	r[X] = P0[X] + sin(alfaRad) * rxz;
	r[Y] = P0[Y] + sin(betaRad) * dist;
	r[Z] = P0[Z] - cos(alfaRad) * rxz;

}

void igvCamara::moverAdelante(double dt)
{
	igvPunto3D dir;
	dir = r - P0;
	igvPunto3D::normalizar(dir);
	P0 += dir * (vel * dt);
	r += dir * (vel * dt);

}

void igvCamara::moverAtras(double dt)
{
	igvPunto3D dir;
	dir = r - P0;
	igvPunto3D::normalizar(dir);
	P0 -= dir * (vel * dt);
	r -= dir * (vel * dt);

}

void igvCamara::moverIzquierda(double dt)
{
	igvPunto3D dir = igvPunto3D::productoVectorial(V, (r - P0));
	igvPunto3D::normalizar(dir);
	P0 += dir * (vel * dt);
	r += dir * (vel * dt);
}

void igvCamara::moverDerecha(double dt)
{
	igvPunto3D dir = igvPunto3D::productoVectorial((r - P0), V);
	igvPunto3D::normalizar(dir);
	P0 += dir * (vel * dt);
	r += dir * (vel * dt);
}

void igvCamara::seguir(double dt)
{
	igvPunto3D dir;
	dir = r - P0;
	dir[Y] = 0;
	P0 += dir * (vel * dt);
	r += dir * (vel * dt);
	
}


