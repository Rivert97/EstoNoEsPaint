#include "funciones.h"

//_________________________________________________ Variables globales
unsigned int NumDeCuadros=0;
unsigned int NumDePuntos=0;
CUADRADO Vcuad[5];
COLOR selectColor=ROJO;
PUNTO Vpuntos[TOTAL_PUNTOS];
char txCoordenadas[40] = "(0,0)";
LINEA l1;
unsigned char primerPunto = 1;

int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("MOVIMIENTO DEL RATON");
	glClearColor(0.8,0.8,0.8,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,400,400,0);		//Se deben cambiar

	//ASIGNACIÓN DE CALLBACKS
	glutDisplayFunc(&display);
	//glutMouseFunc(&Mouse);
	glutMotionFunc(&ActiveMouse);
	glutPassiveMotionFunc(&PassiveMouse);

	AsignaColor(VERDE_FUERTE);

	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	unsigned int i;

	glClear(GL_COLOR_BUFFER_BIT);

	/*AsignaColor(AMARILLO);
	glRectf(-10,10,-9,9);
	AsignaColor(ROJO);
	glRectf(-9,10,-8,9);*/

	//_______________________________ Dibujar cuadrados
	AsignaColor(selectColor);
	for(i=0;i<NumDeCuadros; i++)
		Cuadrado(&Vcuad[i]);

	//_____________________________ Dibujar puntos
	/*AsignaColor(selectColor);
	glBegin(GL_POINTS);
	for(i = 0; i<NumDePuntos; i++)
	{
		glVertex2f(Vpuntos[i].x, Vpuntos[i].y);
	}
	glEnd();*/

	DibujarTexto(txCoordenadas, 10,10);

	//_____________________________ Linea interactiva
	AsignaColor(selectColor);
	if(!primerPunto)
		Linea(&l1);

	glFlush();
}

void Mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(y<=20 && y>=0)
		{
			if(x<=20 && x>=0)
				selectColor = AMARILLO;
			else if(x<=40 && x>=21)
				selectColor = ROJO;
		}
		else if(NumDeCuadros < MAX_CUADROS)
		{
			NumDeCuadros++;
			Vcuad[NumDeCuadros-1].x = (x-200)/20.0;
			Vcuad[NumDeCuadros-1].y = -(y-200)/20.0;
			Vcuad[NumDeCuadros-1].l = 1;
		}
		glutPostRedisplay();
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		exit(0);
	}
}

/*void ActiveMouse(int x, int y)
{
	if(NumDePuntos<TOTAL_PUNTOS)
	{
		NumDePuntos++;
		Vpuntos[NumDePuntos-1].x = x;
		Vpuntos[NumDePuntos-1].y = y;
		glutPostRedisplay();
	}
}*/

void ActiveMouse(int x, int y)
{
	if(primerPunto)
	{
		l1.xi = x;
		l1.yi = y;
		l1.xf = x;
		l1.yf = y;
		primerPunto = 0;
	}
	else
	{
		l1.xf = x;
		l1.yf = y;
	}
	glutPostRedisplay();
}



void PassiveMouse(int x, int y)
{
	sprintf(txCoordenadas,"(%i,%i)",x,y);
	glutPostRedisplay();
}


