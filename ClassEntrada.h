#pragma once


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "glsl.h"


class ClassEntrada
{
public:
	ClassEntrada();
	void DibujarEntrada(GLfloat x, GLfloat y, GLfloat z);  //Las cordenadas de un objeto se dan en tipo float
};

