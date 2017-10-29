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

float Min(int a, int b)
{
	if(a <= b)
		return a;
	else
		return b;
}

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

			case 1:	//Linea
				sideBarB[i].id = 'l';
				glBegin(GL_LINES);
				glVertex2f(sideBarB[i].xl + 2, sideBarB[i].yl + 2);
				glVertex2f(sideBarB[i].xr - 2, sideBarB[i].yr - 2);
				glEnd();
				break;

			case 2:	//Linea libre (freeform)
				sideBarB[i].id = 'f';
				glBegin(GL_LINE_STRIP);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xl + 2, sideBarB[i].yl + 5);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 10);
				glVertex2f(sideBarB[i].xl + 10, sideBarB[i].yr - 3);
				glVertex2f(sideBarB[i].xr - 5, sideBarB[i].yr - 5);
				glVertex2f(sideBarB[i].xr - 2, sideBarB[i].yr - 10);
				glVertex2f(sideBarB[i].xr - 7, sideBarB[i].yr -15);
				glEnd();
				break;

			case 3://Cuadrado
				sideBarB[i].id = 's';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 3);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yr - 3);
				glEnd();
				break;

			case 4://Rectangulo
				sideBarB[i].id = 'r';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 6);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yl + 6);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 6);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yr - 6);
				glEnd();
				break;

			case 5:	//Triangulo
				sideBarB[i].id = 't';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, TOP_BAR+20*(i+1)+(i*10)-3);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 3);
				glEnd();
				break;

			case 6:	//Circulo
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

			case 7:	//Elipse
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

			case 8:	//Pentagono
				sideBarB[i].id = 'p';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + 2);
				glVertex2f(sideBarB[i].xr - 2, sideBarB[i].yl + 8);
				glVertex2f(sideBarB[i].xr - 6, sideBarB[i].yr - 2);
				glVertex2f(sideBarB[i].xl + 6, sideBarB[i].yr - 2);
				glVertex2f(sideBarB[i].xl + 2, sideBarB[i].yl + 8);
				glEnd();
				break;

			case 9:	//Hexágono
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

int ClickBoton(BOTON boton, int x, int y)
{
	if(x > boton.xl && x < boton.xr)
		if(y > boton.yl && y < boton.yr)
			return 1;

	return 0;
}

int ClickBar(BOTON* botones, int size, int x, int y)	//Retorna el indice del boton
{
	int i;

	for(i = 0; i < size; i++)
	{
		if(ClickBoton(botones[i], x, y) == 1)
			return i;
	}

	return -1;
}

//_______________________________________________ Creacion de figuras
CUADRADO* CrearCuadrado(int x, int y, OPCIONES op)
{
	CUADRADO *aux;

	aux = (CUADRADO*)malloc(sizeof(CUADRADO));
	aux->x = x;
	aux->y = y;
	aux->l = 10;
	aux->color = op.color;

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
	aux->color = op.color;

	return aux;
}

CIRCULO* CrearCirculo(int x, int y, OPCIONES op)
{
	CIRCULO *aux;

	aux = (CIRCULO*)malloc(sizeof(CIRCULO));
	aux->x0 = x;
	aux->y0 = y;
	aux->r = 10;
	aux->color = op.color;

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
	aux->color = op.color;

	return aux;
}

FREEFORM* CrearFreeForm(int x, int y, OPCIONES op)
{
	FREEFORM* aux;

	aux = (FREEFORM*)malloc(sizeof(FREEFORM));
	aux->p = (PUNTO*)malloc(sizeof(PUNTO));
	aux->p->x = x;
	aux->p->y = y;
	aux->s = NULL;
	aux->color = op.color;

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
	aux->color = op.color;

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
	aux->color = op.color;

	return aux;
}

PUNTO* CrearPunto(int x, int y, OPCIONES op)
{
	PUNTO *aux;

	aux = (PUNTO*)malloc(sizeof(PUNTO));
	aux->x = x;
	aux->y = y;
	aux->color = op.color;

	return aux;
}

TRIANGULO* CrearTriangulo(int x, int y, OPCIONES op)
{
	TRIANGULO* aux;

	aux = (TRIANGULO*)malloc(sizeof(TRIANGULO));
	aux->x = x;
	aux->y = y;
	aux->lado = 10;
	aux->color = op.color;
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

		case 't':
			Triangulo((TRIANGULO*)(l->figura));
			break;

		case 'h':
			PoligonoI((POLIGONOi*)(l->figura));
			break;

		case 'f':
			FreeForm((FREEFORM*)(l->figura));
			break;

		default:
			break;
	}
}

void Punto(PUNTO *p)
{
	AsignaColor(p->color);
	glBegin(GL_POINTS);
	glVertex2f(p->x, p->y);
	glEnd();	
}

void Triangulo(TRIANGULO* t)
{
	AsignaColor(t->color);
	glBegin(GL_POLYGON);
	glVertex2f(t->x, t->y);
	glVertex2f(t->x + t->lado/2, t->y - sqrt(3*(t->lado*t->lado)/4));
	glVertex2f(t->x + t->lado, t->y);
	glEnd();
}

void Linea(LINEA *l)
{
	AsignaColor(l->color);
	glBegin(GL_LINES);
	glVertex2f(l->xi, l->yi);
	glVertex2f(l->xf, l->yf);
	glEnd();
}

void FreeForm(FREEFORM* f)
{
	AsignaColor(f->color);
	glBegin(GL_LINE_STRIP);
	while(f!=NULL)
	{
		glVertex2f(f->p->x, f->p->y);
		f = f->s;
	}
	glEnd();
}

void Cuadrado(CUADRADO *c)
{
	AsignaColor(c->color);
	glRectf(c->x, c->y, c->x+c->l, c->y+c->l);
}

void Rectangulo(RECTANGULO *r)
{
	AsignaColor(r->color);
	glRectf(r->x, r->y, r->x+r->ancho, r->y+r->alto);
}

void PoligonoI(POLIGONOi *p)
{
	unsigned char i;
	AsignaColor(p->color);
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
	AsignaColor(c->color);
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
	AsignaColor(e->color);
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