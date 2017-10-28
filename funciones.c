#include "funciones.h"

//_______________________________________________________________________ Paleta de colores (CORREGIR)
const float PaletaColor[28][3] = {0,0,0,/**/0,0,0.5,/**/0,0,1,/**/
								0,1,1,/**/0,0.5,1,/**/0,0.5,0.5,/**/
								0,1,0.5,/**/0,1,0,/**/0,0.5,0,/**/
								0.5,0,0,/**/1,0,0,/**/0.5,0,0.5,/**/
								1,0,0.5,/**/0.5,0,1,/**/1,0,1,/**/
								0.5,0.5,0,/**/1,0.5,0,/**/0.5,1,0,/**/
								1,1,0,/**/0.5,0.5,0.5,/**/0.75,0.75,0.75,/**/1,0.5,0.5,/**/
								0.5,1,0.5,/**/0.5,0.5,1,/**/0.5,1,1,/**/
								1,0.5,1,/**/1,1,0.5,/**/1,1,1};					//27 combinaciones


void Push(LISTA** lista, LISTA** elemento)
{
	LISTA* aux;

	if(*lista == NULL)
	{
		*lista = *elemento;
	}
	else
	{
		aux = *lista;

		while(aux->s != NULL)
			aux = aux->s;
		
		aux->s = *elemento;
	}
}

//____________________________________________________________ Funciones extras
void AsignaColor(COLOR color)
{
	glColor3f(PaletaColor[color][0],PaletaColor[color][1],PaletaColor[color][2]);
}

void TopBar(BOTON* topBarB)
{
	int i;
	//__________________________ Fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,ANCHO,TOP_BAR);

	//_________________________Paleta colores
	for(i = 0; i < 14; i++)
	{
		//_______________________ llenar caracteriasticas de los botones
		topBarB[i].xl = SIDE_BAR+15*i;
		topBarB[i].yl = 0;
		topBarB[i].xr = SIDE_BAR+15*(i+1);
		topBarB[i].yr = 15;
		topBarB[i].id = i;

		topBarB[i+14].xl = SIDE_BAR+15*i;
		topBarB[i+14].yl = 15;
		topBarB[i+14].xr = SIDE_BAR+15*(i+1);
		topBarB[i+14].yr = 30;
		topBarB[i+14].id = i+14;

		//_______________________ dibujar cuadros
		AsignaColor(i);
		glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);
		AsignaColor(i+14);
		glRectf(topBarB[i+14].xl, topBarB[i+14].yl, topBarB[i+14].xr, topBarB[i+14].yr);
	}
}

void SideBar(BOTON* sideBarB)
{
	int i;
	float th, x, y;
	//___________________________ fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,SIDE_BAR,ALTO);

	//___________________________ Figuras
	for(i = 0; i < 8; i++)
	{
		//______________________________ Llenando caracteriasticas del boton
		sideBarB[i].xl = 5;
		sideBarB[i].yl = TOP_BAR+20*i+(i*10);
		sideBarB[i].xr = 25;
		sideBarB[i].yr = TOP_BAR+20*(i+1)+(i*10);

		//_________________________________ Dibujar fondo
		glColor3f(0.90, 0.90, 0.90);
		glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);

		AsignaColor(NEGRO);
		glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
		
		//________________________________ Dibujar figuras internas
		switch(i)
		{
			case 0: //punto
				sideBarB[i].id = 'd';
				glPointSize(3);
				glBegin(GL_POINTS);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + (sideBarB[i].yr - sideBarB[i].yl)/2);
				glEnd();
				glPointSize(1);
				glEnd();
				break;
			case 1://Cuadrado
				sideBarB[i].id = 's';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 3);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yr - 3);
				glEnd();
				break;

			case 2://Rectangulo
				sideBarB[i].id = 'r';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 6);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yl + 6);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 6);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yr - 6);
				glEnd();
				break;

			case 3:	//Triangulo
				sideBarB[i].id = 't';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, TOP_BAR+20*(i+1)+(i*10)-3);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 3);
				glEnd();
				break;

			case 4:	//Circulo
				sideBarB[i].id = 'c';
				glBegin(GL_LINE_LOOP);
				for(th=0;th<=360; th+=1)
				{
					x = 9 * cos(th/180.0 * PI) + sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2;
					y = 9 * sin(th/180.0 * PI) + sideBarB[i].yl + (sideBarB[i].yr - sideBarB[i].yl)/2;
					glVertex2f(x,y);
				}
				glEnd();
				break;

			case 5:	//Elipse
				sideBarB[i].id = 'e';
				glBegin(GL_LINE_LOOP);
				for(th=0; th<360; th+=1)
				{
					x = 9*cos(th/180.0*PI) + sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2;
					y = 6*sin(th/180.0*PI) + sideBarB[i].yl + (sideBarB[i].yr - sideBarB[i].yl)/2;
					glVertex2f(x,y);
				}
				glEnd();
				break;

			case 6:	//Pentagono
				sideBarB[i].id = 'p';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + 2);
				glVertex2f(sideBarB[i].xr - 2, sideBarB[i].yl + 8);
				glVertex2f(sideBarB[i].xr - 6, sideBarB[i].yr - 2);
				glVertex2f(sideBarB[i].xl + 6, sideBarB[i].yr - 2);
				glVertex2f(sideBarB[i].xl + 2, sideBarB[i].yl + 8);
				glEnd();
				break;

			case 7:	//Hexágono
				sideBarB[i].id = 'h';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 6, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 6, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 2, sideBarB[i].yl + (sideBarB[i].yr - sideBarB[i].yl)/2);
				glVertex2f(sideBarB[i].xr - 6, sideBarB[i].yr - 2);
				glVertex2f(sideBarB[i].xl + 6, sideBarB[i].yr - 2);
				glVertex2f(sideBarB[i].xl + 2, sideBarB[i].yl + (sideBarB[i].yr - sideBarB[i].yl)/2);
				glEnd();
				break;
		}
		glPolygonMode(GL_BACK, GL_FILL);
	}
}

//_______________________________________________ Creacion de figuras
CUADRADO* CrearCuadrado(int x, int y, OPCIONES op)
{
	CUADRADO *aux;

	aux = (CUADRADO*)malloc(sizeof(CUADRADO));
	aux->x = x;
	aux->y = y;
	aux->l = 10;

	return aux;
}

RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op)
{
	RECTANGULO *aux;

	aux = (RECTANGULO*)malloc(sizeof(RECTANGULO));
	aux->x = x;
	aux->y = y;
	aux->ancho = 20;
	aux->alto = 50;

	return aux;
}

CIRCULO* CrearCirculo(int x, int y, OPCIONES op)
{
	CIRCULO *aux;

	aux = (CIRCULO*)malloc(sizeof(CIRCULO));
	aux->x0 = x;
	aux->y0 = y;
	aux->r = 10;

	return aux;
}

LINEA* CrearLinea(int x, int y, OPCIONES op)
{
	LINEA *aux;

	aux = (LINEA*)malloc(sizeof(LINEA));
	aux->xi = x;
	aux->yi = y;
	aux->xf = x+10;
	aux->yf = y+10;

	return aux;
}

ELIPSE* CrearElipse(int x, int y, OPCIONES op)
{
	ELIPSE *aux;

	aux = (ELIPSE*)malloc(sizeof(ELIPSE));
	aux->x0 = x;
	aux->y0 = y;
	aux->a = 10;
	aux->b = 20;
	aux->th = 0;

	return aux;
}

POLIGONOi* CrearPoligonoi(int x, int y, OPCIONES op)
{
	POLIGONOi *aux;

	aux = (POLIGONOi*)malloc(sizeof(POLIGONOi));
	aux->numL = 5;
	aux->v = (PUNTO*)malloc(sizeof(PUNTO)*aux->numL);
	aux->v[0].x = x;
	aux->v[0].y = y;
	aux->v[1].x = x+10;
	aux->v[1].y = y+10;
	aux->v[2].x = x+20;
	aux->v[2].y = y;
	aux->v[3].x = x+15;
	aux->v[3].y = y-10;
	aux->v[4].x = x+5;
	aux->v[4].y = y-10;

	return aux;
}

PUNTO* CrearPunto(int x, int y, OPCIONES op)
{
	PUNTO *aux;

	aux = (PUNTO*)malloc(sizeof(PUNTO));
	aux->x = x;
	aux->y = y;

	return aux;
}


//___________________________________________________________ Dibujado de objetos
void Dibujar(LISTA* l)
{
	switch(l->tipo){
		case 's':
			Cuadrado((CUADRADO*)(l->figura));
			break;
		
		case 'r':
			Rectangulo((RECTANGULO*)(l->figura));
			break;
		
		case 'c':
			Circulo((CIRCULO*)(l->figura));
			break;

		case 'l':
			Linea((LINEA*)(l->figura));
			break;

		case 'e':
			Elipse((ELIPSE*)(l->figura));
			break;

		case 'p':
			PoligonoI((POLIGONOi*)(l->figura));
			break;

		case 'd':
			Punto((PUNTO*)(l->figura));
			break;

		default:
			break;
	}
}

void Punto(PUNTO *p)
{
	glBegin(GL_POINTS);
	glVertex2f(p->x, p->y);
	glEnd();	
}

void Linea(LINEA *l)
{
	glBegin(GL_LINES);
	glVertex2f(l->xi, l->yi);
	glVertex2f(l->xf, l->yf);
	glEnd();
}

void Cuadrado(CUADRADO *c)
{
	glRectf(c->x, c->y, c->x+c->l, c->y+c->l);
}

void Rectangulo(RECTANGULO *r)
{
	glRectf(r->x, r->y, r->x+r->ancho, r->y+r->alto);
}

void PoligonoI(POLIGONOi *p)
{
	unsigned char i;
	glBegin(GL_LINE_LOOP);
	for(i=0;i<p->numL;i++)
	{
		glVertex2f(p->v[i].x, p->v[i].y);
	}
	glEnd();
}

void Circulo(CIRCULO *c)
{
	/*float x,y;
	glBegin(GL_LINE_STRIP);
	for(x=-1*(c->r+c->x0); x <= c->r+c->x0; x+=0.1)
	{
		y = sqrt(c->r*c->r - (x-c->x0)*(x-c->x0))+c->y0;
		glVertex2f(x,y);
	}
	for(x=c->r+c->x0; x > -1*(c->r+c->x0); x-=0.1)
	{
		y = -sqrt(c->r*c->r - (x-c->x0)*(x-c->x0))+c->y0;
		glVertex2f(x,y);
	}
	glEnd();*/

	float th, x, y;
	glBegin(GL_LINE_LOOP);
	for(th=0;th<=360; th+=1)
	{
		x = c->r * cos(th/180.0 * PI) + c->x0;
		y = c->r * sin(th/180.0 * PI) + c->y0;
		glVertex2f(x,y);
	}
	glEnd();
}

void Elipse(ELIPSE *e)
{
	float x,y,th, xr, yr;

	glBegin(GL_LINE_LOOP);
	for(th=0; th<360; th+=1)
	{
		x = e->a*cos(th/180.0*PI);
		y = e->b*sin(th/180.0*PI);
		xr = x*cos(e->th/180.0*PI)-y*sin(e->th/180.0*PI) + e->x0;
		yr = x*sin(e->th/180.0*PI)+y*cos(e->th/180.0*PI) + e->y0;
		glVertex2f(xr,yr);
	}
	glEnd();
}

void DibujarTexto(char *text, float x, float y)
{
	char* c;
	glRasterPos2f(x,y);

	for(c=text; *c!='\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
}