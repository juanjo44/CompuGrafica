#pragma once

#include <iostream>
#include "./glm/glm.h"
class AbrirMalla
{
public:
	GLMmodel* objmodel_ptr;
	AbrirMalla(char*);
	void DibujarMalla();
};

