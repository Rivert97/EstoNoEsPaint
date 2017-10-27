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

void TopBar()
{
	int i;
	//__________________________ Fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,ANCHO,TOP_BAR);

	//_________________________Paleta colores
	for(i = 0; i < 14; i++)
	{
		AsignaColor(i);
		glRectf(SIDE_BAR+15*i, 0, SIDE_BAR+15*(i+1), 15);
	}
	for(i = 0; i < 14; i++)
	{
		AsignaColor(i+14);
		glRectf(SIDE_BAR+15*i, 15, SIDE_BAR+15*(i+1), 30);
	}
}

void SideBar()
{
	int i;
	//___________________________ fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,SIDE_BAR,ALTO);

	//___________________________ Figuras
	for(i = 0; i < 7; i++)
	{
		glColor3f(0.90, 0.90, 0.90);
		glRectf(5, TOP_BAR+20*i, 25, TOP_BAR+20*(i+1));
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