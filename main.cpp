//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "ClassArbol.h"
#include "ClassEntrada.h"
#include "AbrirMalla.h"
#define NUM_ARBOLES 2

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   ClassArbol Jardin[NUM_ARBOLES];
   ClassEntrada Entrada1;
   //GLMmodel* objmodel_ptr;
   AbrirMalla *mallas[4];



public:
	myWindow(){}

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      if (shader) shader->begin();
      //glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
      glPushMatrix();
      glTranslatef(-1.0, 1.0, 0.0);
      mallas[0]->DibujarMalla();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(1.0, 1.0, 0.0);
        mallas[1]->DibujarMalla();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(1.0, -1.0, 0.0);
      mallas[2]->DibujarMalla();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-1.0, -1.0, 0.0);
      mallas[3]->DibujarMalla();
      glPopMatrix();
      //glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL);
         
         //glutSolidTeapot(0.5);
         //glutSolidCube(0.5);

      //Jardin[0].DibujarArbol(0.0f, 0.0f, 0.0f);
      //Jardin[1].DibujarArbol(-0.5f, 0.0f, -0.5f);
      //Entrada1.DibujarEntrada(0.0f, 0.0f, 0.0f);
      /*glTranslatef(0.0, 0.0, -3);

      glBegin(GL_TRIANGLES);
      glVertex3f(-0.5, 0.0, 0.0);
      glVertex3f(0.5, 0.0, 0.0);
      glVertex3f(0.0, 0.5, 0.0);
      glEnd();


      glPushMatrix();
      glTranslatef(0, 2.0, 0.0);
      glutSolidTeapot(0.3);
      glPopMatrix();

         //Dibujar cubito a la derecha
         glPushMatrix();
            glRotatef(30, 0.0, 0.0, 0.1);
            glTranslatef(0.5, -1.0, 0.0);
            glutSolidCube(0.5);
         glPopMatrix();

         //Dibujar cubito a la izquierda
         glPushMatrix();
            glRotatef(-30, 0.0, 0.0, 0.1);

            glTranslatef(-0.5, -1.0, 0.0);
            glutSolidCube(0.5);
         glPopMatrix();

         //Dibujar cubito abajito
         glPushMatrix();
            glTranslatef(0.0, -0.75, 0.0);
            glutSolidCube(0.5);
         glPopMatrix();



         //Ojos
         glPushMatrix();
         glTranslatef(0.6, 1.0, 0.0);
         glutSolidSphere(0.3, 20,20);
         glPopMatrix();

         glPushMatrix();
         glTranslatef(-0.6, 1.0, 0.0);
         glutSolidSphere(0.3, 20, 20);
         glPopMatrix();


         //Dibujar cubito a la izquierda
         glPushMatrix();
         glRotatef(-50, 0.0, 0.0, 0.1);

         glTranslatef(-1, -1.0, 0.0);
         glutSolidCube(0.5);
         glPopMatrix();

         glPushMatrix();
         glRotatef(50, 0.0, 0.0, 0.1);

         glTranslatef(1, -1.0, 0.0);
         glutSolidCube(0.5);
         glPopMatrix();*/

      if (shader) shader->end();
      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
    virtual void OnInit()
    {
        for (int i = 0; i < NUM_ARBOLES; i++) {
            Jardin[i] = ClassArbol();
        }

        //Entrada1 = ClassEntrada();
        mallas[0] = new AbrirMalla("./mallas/untitled.obj");
        mallas[1] = new AbrirMalla("./mallas/dragon.obj");
        mallas[2] = new AbrirMalla("./mallas/porcelana.obj");
        mallas[3] = new AbrirMalla("./mallas/persona.obj");
        /*objmodel_ptr = NULL;

        if (!objmodel_ptr)
        {
            objmodel_ptr = glmReadOBJ("./mallas/buddha.obj");
            if (!objmodel_ptr)
                exit(0);

            glmUnitize(objmodel_ptr);
            glmFacetNormals(objmodel_ptr);
            glmVertexNormals(objmodel_ptr, 90.0);
        }*/
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

      DemoLight();

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

