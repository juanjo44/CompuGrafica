#include "ClassEntrada.h"

ClassEntrada::ClassEntrada() {}

void ClassEntrada::DibujarEntrada(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();

		//Dibujar columna1
		glPushMatrix();
			glTranslatef(x + 1.0, y, z);
			glRotatef(90, 1, 0, 0);
			glutSolidCylinder(0.2f, 1.8f, 20, 20);
		glPopMatrix();

		//Dibujar colomna2
		glPushMatrix();
			glTranslatef(x - 1.0, y, z);
			glRotatef(90, 1, 0, 0);
			glutSolidCylinder(0.2f, 1.8f, 20, 20);
		glPopMatrix();

		//Dibujar parte arriba
		glPushMatrix();
			glTranslatef(x-1.2, y+0.2, z);
			glRotatef(90, 0, 1, 0);
			glutSolidCylinder(0.2f, 2.4f, 20, 20);
		glPopMatrix();

	glPopMatrix();
}