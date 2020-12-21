#include "igvMaterial.h"

// Metodos constructores 

igvMaterial::igvMaterial () {
	
}

igvMaterial::~igvMaterial () {

}

igvMaterial::igvMaterial (const igvMaterial& p) {	//de copia
	Ka = p.Ka;
	Kd = p.Kd;
	Ks = p.Ks;
	Ns = p.Ns;
}

igvMaterial::igvMaterial(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Metodos publicos 

void igvMaterial::aplicar(void) {

// APARTADO C
// Aplicar los valores de los atributos del objeto igvMaterial:
// - coeficiente de reflexión de la luz ambiental
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.cloneToFloatArray());
// - coeficiente de reflexión difuso
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.cloneToFloatArray());
// - coeficiente de reflesión especular
	glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.cloneToFloatArray());
// - exponente de Phong
	glMaterialf(GL_FRONT, GL_SHININESS, Ns);

// establecer como color de emisión (0.0, 0.0, 0.0) (el objeto no es una fuente de luz)
	glMaterialfv(GL_FRONT, GL_EMISSION, igvColor(0, 0, 0).cloneToFloatArray());


}

void igvMaterial::set(igvColor _Ka, igvColor _Kd, igvColor _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



