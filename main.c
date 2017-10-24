#include "funciones.h"

//_________________________________________________ Variables globales


int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1300,700);
	glutCreateWindow("Esto no es PAINT");
	glClearColor(1,1,1,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,1300,700,0);		//Se deben cambiar

	//ASIGNACIÓN DE CALLBACKS
	glutDisplayFunc(&display);
	//glutMouseFunc(&Mouse);
	glutMotionFunc(&ActiveMouse);
	glutPassiveMotionFunc(&PassiveMouse);


	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	

	glFlush();
}

void Mouse(int button, int state, int x, int y)
{
	
}

void ActiveMouse(int x, int y)
{
	
}


void PassiveMouse(int x, int y)
{
	
}


