#include "funciones.h"

//_________________________________________________ Variables globales
LISTA *cabeza, *actual;
char tipo;
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
	glutKeyboardFunc(&Keyboard);
	glutSpecialFunc(&SpecialKeyboard);

	//Inicialización de variables
	cabeza = NULL;
	tipo = 's';
	op.color = NEGRO;
	op.tipo_linea = L_LINE;
	op.llenado = GL_FILL;
	op.ancho_linea = 1;
	op.factor_linea = 2;

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
	LISTA* aux;
	if(state == GLUT_DOWN)
	{
		if(x >= SIDE_BAR && y >= TOP_BAR)	//Click dentro de pantalla de dibujo
		{
			if(button == GLUT_LEFT_BUTTON)
			{
				aux = (LISTA*)malloc(sizeof(LISTA));
				aux->tipo = tipo;
				aux->s = NULL;

				switch(tipo){
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
						aux->figura = (void*)CrearPentagono(x, y, op);
						break;

					case 'h':
						aux->figura = (void*)CrearHexagono(x, y, op);
						break;

					case 'd':
						aux->figura = (void*)CrearPunto(x, y, op);
						break;

					case 't':
						aux->figura = (void*)CrearTriangulo(x, y, op);
						break;

					case 'f':
						aux->figura = (void*)CrearFreeForm(x, y, op);
						break;

					default:
						break;
				}

				Push(&cabeza, &aux);
				actual = aux;
				glutPostRedisplay();
			}
		}
		else if(x < SIDE_BAR && y > TOP_BAR)	//Click en barra de la izquierda
		{
			int index;
			index = ClickBar(sideBarB, NSIDE_BAR_B, x, y);
			if(index >= 0)
			{
				tipo = sideBarB[index].id;
			}
		}
		else 	//Click en la barra de arriba
		{
			int index;
			index = ClickBar(topBarB, NTOP_BAR_B, x, y);
			if(index >= 0)
			{
				if(index < 28)
				{
					op.color = topBarB[index].id;
				}
				else if(index < 31)
				{
					op.llenado = topBarB[index].id;
				}
				else if(index < 36)
				{
					op.tipo_linea = topBarB[index].id;
				}
			}
		}
	}
	else if(state == GLUT_UP)
	{
		actual = NULL;
	}
}

void ActiveMouse(int x, int y)
{
	if(actual!=NULL)
	{
		FREEFORM* aux;
		switch(actual->tipo){
			case 's':
				((CUADRADO*)(actual->figura))->l =  Min(abs(x - ((CUADRADO*)(actual->figura))->x), abs(y - ((CUADRADO*)(actual->figura))->y));
				if(y < ((CUADRADO*)(actual->figura))->y)
					((CUADRADO*)(actual->figura))->direcciony = -1;
				else
					((CUADRADO*)(actual->figura))->direcciony = 1;

				if(x < ((CUADRADO*)(actual->figura))->x)
					((CUADRADO*)(actual->figura))->direccionx = -1;
				else
					((CUADRADO*)(actual->figura))->direccionx = 1;
				break;
			case 'r':
				((RECTANGULO*)(actual->figura))->ancho = x - ((RECTANGULO*)(actual->figura))->x;
				((RECTANGULO*)(actual->figura))->alto = y - ((RECTANGULO*)(actual->figura))->y;
				break;
			
			case 'c':
				((CIRCULO*)(actual->figura))->r =  Min(abs(x - ((CIRCULO*)(actual->figura))->x0), abs(y - ((CIRCULO*)(actual->figura))->y0));
				break;

			case 'l':
				((LINEA*)(actual->figura))->xf = x;
				((LINEA*)(actual->figura))->yf = y;
				break;

			case 'e':
				((ELIPSE*)(actual->figura))->a = x - ((ELIPSE*)(actual->figura))->x0;
				((ELIPSE*)(actual->figura))->b = y - ((ELIPSE*)(actual->figura))->y0;
				break;
				
			case 'p':
				CalcularPentagono(((POLIGONOi*)(actual->figura))->v, Min(x - ((POLIGONOi*)(actual->figura))->v[0].x, y - ((POLIGONOi*)(actual->figura))->v[0].y));
				break;

			case 'h':
				CalcularHexagono(((POLIGONOi*)(actual->figura))->v, Min(x - ((POLIGONOi*)(actual->figura))->v[0].x, y - ((POLIGONOi*)(actual->figura))->v[0].y));
				break;

			case 't':
				((TRIANGULO*)(actual->figura))->lado = x - ((TRIANGULO*)(actual->figura))->x;
				if(y > ((TRIANGULO*)(actual->figura))->y)
					((TRIANGULO*)(actual->figura))->direccion = -1;
				else
					((TRIANGULO*)(actual->figura))->direccion = 1;
				break;

			case 'f':
				aux = (FREEFORM*)(actual->figura);
				while(aux->s != NULL)
					aux = aux->s;

				aux->s = (FREEFORM*)malloc(sizeof(FREEFORM));
				aux->s->p = (PUNTO*)malloc(sizeof(PUNTO));
				aux->s->p->x = x;
				aux->s->p->y = y;
				aux->s->s = NULL;
				break;

			default:
				break;
		}
		glutPostRedisplay();
	}
}


void PassiveMouse(int x, int y)
{
	
}

void Keyboard(unsigned char key, int x, int y)
{
	LISTA* aux;
	switch(key)
	{
		case '+':	//Aumentar ancho de linea
			if(op.ancho_linea < 10)
			{
				if(actual != NULL)
				{
					PonerAnchoLinea(actual, op.ancho_linea++);
					glutPostRedisplay();
				}
				else
				{
					op.ancho_linea++;
				}
			}
			break;

		case '-':	//Disminuir ancho de linea
			if(op.ancho_linea > 0)
			{
				if(actual != NULL)
				{
					PonerAnchoLinea(actual, op.ancho_linea--);
					glutPostRedisplay();
				}
				else
				{
					op.ancho_linea--;
				}
			}
			break;

		case 'z':	//Deshacer
			Pop(&cabeza);
			glutPostRedisplay();
			break;

		case 27:
		case 'c':	//limpiar pantalla
			while(cabeza != NULL)
			{
				aux = cabeza;
				cabeza = cabeza->s;

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

					case 'f':
						free(((FREEFORM*)(aux->figura))->p);
						free((FREEFORM*)(aux->figura));
						break;

					default:
						break;
				}
				free(aux);
			}
			glutPostRedisplay();

			if(key == 27)
				exit(0);
			break;

		default:
			break;
	}
}

void SpecialKeyboard(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if(op.factor_linea < 10)
			{
				if(actual != NULL)
				{
					PonerFactorLinea(actual, op.factor_linea++);
					glutPostRedisplay();
				}
				else
				{
					op.factor_linea++;
				}
			}
			break;

		case GLUT_KEY_DOWN:
			if(op.factor_linea > 0)
			{
				if(actual != NULL)
				{
					PonerFactorLinea(actual, op.factor_linea--);
					glutPostRedisplay();
				}
				else
				{
					op.factor_linea--;
				}
			}
			break;

		default:
			break;
	}
}
