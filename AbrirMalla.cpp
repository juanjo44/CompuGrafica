#include "AbrirMalla.h"

AbrirMalla::AbrirMalla(char *malla) {
    objmodel_ptr = NULL;
    if (!objmodel_ptr)
    {
        objmodel_ptr = glmReadOBJ(malla);
        if (!objmodel_ptr)
            exit(0);

        glmUnitize(objmodel_ptr);
        glmFacetNormals(objmodel_ptr);
        glmVertexNormals(objmodel_ptr, 90.0);
    }
}
void AbrirMalla::DibujarMalla() {

    glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);

}