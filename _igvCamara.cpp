//#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265358979323846
#include "igvCamara.h"

// Metodos constructores

igvCamara::igvCamara () {}

igvCamara::~igvCamara () {}

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
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	if (tipo==IGV_PARALELA) {
		glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo==IGV_FRUSTUM) {
		glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
	}
	if (tipo==IGV_PERSPECTIVA) {
		gluPerspective(angulo,raspecto,znear,zfar);
	}
	
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(P0[X],P0[Y],P0[Z], r[X], r[Y], r[Z], V[X],V[Y],V[Z]);
}

void igvCamara::setDx(double x)
{
	dx = x - dx;
}

void igvCamara::setDy(double angy)
{
	double limiteY = 90.0 * 180 / PI;
	double nuevody = angy - dy;
	if (nuevody > limiteY) {
		nuevody = limiteY;
	}
	else if (nuevody < -limiteY) {
		nuevody = -limiteY;
	}
	dy = nuevody;
}

void igvCamara::resetDif()
{
	dx = dy = 0;
}

void igvCamara::rotate() {
	double rad = sqrt(pow(r[X]-P0[X],2) + pow(r[Y]-P0[Y],2) + pow(r[Z]-P0[Z],2));
	double xAng = dx * 180.0 / PI;
	double yAng = dy * 180.0 / PI;
	//double x = cos(xAng);
	double y = sin(yAng);
	//double z = -sin(xAng);

	//r[X] += x * rad * 0.1;
	//r[Z] += z * rad * 0.1;
	r[Y] += y * rad * 0.05;
}

void igvCamara::mover(char tipo)
{
	igvPunto3D aux(r[X] - P0[X], 0, r[Z] - P0[Z]);
	igvPunto3D aux2(-r[X] + P0[X], 0, -r[Z] + P0[Z]);
	switch (tipo) {
	case 'w':
		P0[Z]-= aux[X] * 0.5;
		P0[X] -= aux[Z] * 0.5;
		break;
	case 's':
		P0[Z] += aux2[X] * 0.5;
		P0[X] += aux2[Z] * 0.5;
		break;

	}
}
