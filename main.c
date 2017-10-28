#include "funciones.h"

//_________________________________________________ Variables globales
LISTA *cabeza, *actual;
OPCIONES op;
BOTON topBar[28];
BOTON sideBar[8];

int main(int argc, char** argv)
{
	//CONFIGURACIONES INICIALES
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(ANCHO,ALTO);
	glutCreateWindow("Esto no es PAINT");
	glClearColor(1,1,1,0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,ANCHO,ALTO,0);

	//ASIGNACIÓN DE CALLBACKS
	glutDisplayFunc(&display);
	glutMouseFunc(&Mouse);
	glutMotionFunc(&ActiveMouse);
	glutPassiveMotionFunc(&PassiveMouse);

	//Inicialización de variables
	cabeza = NULL;
	op.color = BLANCO;
	op.tipo_linea = 0xFFFF;
	op.tipo = 's';
	op.ancho = 1;

	//ESTADO DE ESPERA DE EVENTOS
	glutMainLoop();
	return 0;
}

void display()
{
	LISTA* aux;
	aux = cabeza;

	glClear(GL_COLOR_BUFFER_BIT);

	//__________________________________ Barras de herramientas
	TopBar(topBar);
	SideBar(sideBar);

	//________________________________ Dibujar figuras del usuario
	AsignaColor(ROJO);
	while(aux != NULL)
	{
		Dibujar(aux);
		aux = aux->s;
	}

	glFlush();
}

void Mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		LISTA* aux;
		aux = (LISTA*)malloc(sizeof(LISTA));
		aux->tipo = op.tipo;
		aux->s = NULL;

		switch(op.tipo){
			case 's':
				aux->figura = (void*)CrearCuadrado(x, y, op);
				break;
			
			case 'r':
				aux->figura = (void*)CrearRectangulo(x, y, op);
				break;
			
			case 'c':
				aux->figura = (void*)CrearCirculo(x, y, op);
				break;

			case 'l':
				aux->figura = (void*)CrearLinea(x, y, op);
				break;

			case 'e':
				aux->figura = (void*)CrearElipse(x, y, op);
				break;

			case 'p':
				aux->figura = (void*)CrearPoligonoi(x, y, op);
				break;

			case 'd':
				aux->figura = (void*)CrearPunto(x, y, op);
				break;

			default:
				break;
		}

		Push(&cabeza, &aux);
		glutPostRedisplay();
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		LISTA* aux;
		while(cabeza != NULL)
		{
			aux = cabeza;
			cabeza = cabeza->s;
			if(aux->tipo == 'p')
				free(((POLIGONOi*)(aux->figura))->v);
			free(aux->figura);
			free(aux);
		}
		glutPostRedisplay();
	}
}

void ActiveMouse(int x, int y)
{
	
}


void PassiveMouse(int x, int y)
{
	
}


