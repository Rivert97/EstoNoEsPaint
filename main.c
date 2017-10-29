#include "funciones.h"

//_________________________________________________ Variables globales
LISTA *cabeza, *actual;
OPCIONES op;
BOTON topBarB[NTOP_BAR_B];
BOTON sideBarB[NSIDE_BAR_B];

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
	op.color = NEGRO;
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

	//________________________________ Dibujar figuras del usuario
	AsignaColor(ROJO);
	while(aux != NULL)
	{
		Dibujar(aux);
		aux = aux->s;
	}

	//__________________________________ Barras de herramientas
	TopBar(topBarB);
	SideBar(sideBarB);

	

	glFlush();
}

void Mouse(int button, int state, int x, int y)
{
	if(x >= SIDE_BAR && y >= TOP_BAR)	//Click dentro de pantalla de dibujo
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

				case 'h':
					aux->figura = (void*)CrearPoligonoi(x, y, op);
					break;

				case 'd':
					aux->figura = (void*)CrearPunto(x, y, op);
					break;

				case 't':
					aux->figura = (void*)CrearTriangulo(x, y, op);
					break;

				default:
					break;
			}

			Push(&cabeza, &aux);
			actual = aux;
			glutPostRedisplay();
		}
		else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			LISTA* aux;
			while(cabeza != NULL)
			{
				aux = cabeza;
				cabeza = cabeza->s;
				/*if(aux->tipo == 'p' || aux->tipo == 'h')	//Si es poligono eliminar v
					free(((POLIGONOi*)(aux->figura))->v);
				free(aux->figura);*/

				switch(aux->tipo){
					case 's':
						free((CUADRADO*)(aux->figura));
						break;
					
					case 'r':
						free((RECTANGULO*)(aux->figura));
						break;
					
					case 'c':
						free((CIRCULO*)(aux->figura));
						break;

					case 'l':
						free((LINEA*)(aux->figura));
						break;

					case 'e':
						free((ELIPSE*)(aux->figura));
						break;

					case 'p':
						free(((POLIGONOi*)(aux->figura))->v);
						free((POLIGONOi*)(aux->figura));
						break;

					case 'h':
						free(((POLIGONOi*)(aux->figura))->v);
						free((POLIGONOi*)(aux->figura));
						break;

					case 'd':
						free((PUNTO*)(aux->figura));
						break;

					case 't':
						free((TRIANGULO*)(aux->figura));
						break;

					default:
						break;
				}
				free(aux);
			}
			glutPostRedisplay();
		}
	}
	else if(x < SIDE_BAR && y > TOP_BAR)	//Click en barra de la izquierda
	{
		int index;
		index = ClickBar(sideBarB, NSIDE_BAR_B, x, y);
		op.tipo = sideBarB[index].id;
	}
	else 	//Click en la barra de arriba
	{
		int index;
		index = ClickBar(topBarB, NTOP_BAR_B, x, y);
		op.color = topBarB[index].id;
	}
}

void ActiveMouse(int x, int y)
{
	if(x >= SIDE_BAR && y >= TOP_BAR)
	{
		if(actual!=NULL)
		{
			switch(actual->tipo){
				case 's':
					((CUADRADO*)(actual->figura))->l =  Min(x - ((CUADRADO*)(actual->figura))->x, y - ((CUADRADO*)(actual->figura))->y);
					break;
				case 'r':
					((RECTANGULO*)(actual->figura))->ancho = x - ((RECTANGULO*)(actual->figura))->x;
					((RECTANGULO*)(actual->figura))->alto = y - ((RECTANGULO*)(actual->figura))->y;
					break;
				
				case 'c':
					((CIRCULO*)(actual->figura))->r =  Min(x - ((CIRCULO*)(actual->figura))->x0, y - ((CIRCULO*)(actual->figura))->y0);
					break;

				case 'l':

					break;

				case 'e':

					break;

				case 'p':

					break;

				case 'h':

					break;

				case 'd':

					break;

				case 't':

					break;

				default:
					break;
			}
			glutPostRedisplay();
		}
	}
}


void PassiveMouse(int x, int y)
{
	
}


