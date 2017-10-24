#include "funciones.h"

//_________________________________________________ Variables globales


int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(ANCHO,ALTO);
	glutCreateWindow("Esto no es PAINT");
	glClearColor(1,1,1,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,ANCHO,ALTO,0);		//Se deben cambiar

	//ASIGNACIÓN DE CALLBACKS
	glutDisplayFunc(&display);
	glutMouseFunc(&Mouse);
	glutMotionFunc(&ActiveMouse);
	glutPassiveMotionFunc(&PassiveMouse);


	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);

	TopBar();
	SideBar();

	for(i=0;i<28;i++)
	{
		AsignaColor(i);
		glRectf(40+5*i,40,100+5*i,100);
	}

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


