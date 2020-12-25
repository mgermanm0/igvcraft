#include "igvColor.h"

// Constructures

igvColor::igvColor () {
}

igvColor::~igvColor () {
}

igvColor::igvColor (const double r, const double g, const double b) {
	color[R] = r;
	color[G] = g;
	color[B] = b;
}

igvColor::igvColor (const double r, const double g, const double b, const double a) {
	color[R] = r;
	color[G] = g;
	color[B] = b;
	color[A] = a;
}

igvColor::igvColor (const igvColor& p) {	//de copia
	color[R] = p.color[R];
	color[G] = p.color[G];
	color[B] = p.color[B];
	color[A] = p.color[A];
}

// Metodos publicos 

// Operadores de acceso a miembros
double& igvColor::operator[] ( const unsigned char idx ) {
	return color[idx];
}

double igvColor::operator[] (const unsigned char idx) const {
	return color[idx];
}

bool igvColor::operator==(const igvColor& a)
{
	return (color[R] == a[R] && color[G] == a[G] && color[B] == a[B]);
}

bool igvColor::less(const igvColor& a, const igvColor& b)
{
	float lb = 0.2126 * b[R] + 0.7152 * b[G] + 0.0722 * b[B];
	float la = 0.2126 * a[R] + 0.7152 * a[G] + 0.0722 * a[B];
	return la<lb;
}

void igvColor::aplicar (void) {
	glColor4dv(color);
}

float* igvColor::cloneToFloatArray() const
{
	float* res = new float[4]{ (float)color[0], (float)color[1], (float)color[2], (float)color[3] };
	return res;
}
