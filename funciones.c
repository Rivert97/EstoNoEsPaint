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

void TopBar(BOTON* topBar)
{
	int i;
	//__________________________ Fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,ANCHO,TOP_BAR);

	//_________________________Paleta colores
	for(i = 0; i < 14; i++)
	{
		//_______________________ llenar caracteriasticas del boton
		topBar[i].xl = SIDE_BAR+15*i;
		topBar[i].yl = 0;
		topBar[i].xr = SIDE_BAR+15*(i+1);
		topBar[i].yr = 15;
		topBar[i].id = i;

		topBar[i+14].xl = SIDE_BAR+15*i;
		topBar[i+14].yl = 15;
		topBar[i+14].xr = SIDE_BAR+15*(i+1);
		topBar[i+14].yr = 30;
		topBar[i+14].id = i+14;

		//_______________________ dibujar cuadro
		AsignaColor(i);
		glRectf(topBar[i].xl, topBar[i].yl, topBar[i].xr, topBar[i].yr);
		AsignaColor(i+14);
		glRectf(topBar[i+14].xl, topBar[i+14].yl, topBar[i+14].xr, topBar[i+14].yr);
	}
}

void SideBar(BOTON* sideBar)
{
	int i;
	float th, x, y;
	//___________________________ fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,SIDE_BAR,ALTO);

	//___________________________ Figuras
	for(i = 0; i < 8; i++)
	{
		glColor3f(0.90, 0.90, 0.90);
		glRectf(5, TOP_BAR+20*i+(i*10), 25, TOP_BAR+20*(i+1)+(i*10));

		AsignaColor(NEGRO);
		glPolygonMode(GL_BACK, GL_LINE);
		switch(i)
		{
			case 0: //punto
				glPointSize(3);
				glBegin(GL_POINTS);
				glVertex2f(15, TOP_BAR+20*i+(i*10)+10);
				glEnd();
				glPointSize(1);
				glEnd();
				break;
			case 1://Cuadrado
				glBegin(GL_POLYGON);
				glVertex2f(8, TOP_BAR+20*i+(i*10)+3);
				glVertex2f(23, TOP_BAR+20*i+(i*10)+3);
				glVertex2f(23, TOP_BAR+20*(i+1)+(i*10)-3);
				glVertex2f(8, TOP_BAR+20*(i+1)+(i*10)-3);
				glEnd();
				break;

			case 2://Rectangulo
				glBegin(GL_POLYGON);
				glVertex2f(8, TOP_BAR+20*i+(i*10)+6);
				glVertex2f(23, TOP_BAR+20*i+(i*10)+6);
				glVertex2f(23, TOP_BAR+20*(i+1)+(i*10)-6);
				glVertex2f(8, TOP_BAR+20*(i+1)+(i*10)-6);
				glEnd();
				break;

			case 3:	//Triangulo
				glBegin(GL_POLYGON);
				glVertex2f(8, TOP_BAR+20*(i+1)+(i*10)-3);
				glVertex2f(15, TOP_BAR+20*i+(i*10)+3);
				glVertex2f(23, TOP_BAR+20*(i+1)+(i*10)-3);
				glEnd();
				break;

			case 4:	//Circulo
				glBegin(GL_LINE_LOOP);
				for(th=0;th<=360; th+=1)
				{
					x = 9 * cos(th/180.0 * PI) + 15;
					y = 9 * sin(th/180.0 * PI) + TOP_BAR+20*i+(i*10)+10;
					glVertex2f(x,y);
				}
				glEnd();
				break;

			case 5:	//Elipse
				glBegin(GL_LINE_LOOP);
				for(th=0; th<360; th+=1)
				{
					x = 9*cos(th/180.0*PI) + 15;
					y = 6*sin(th/180.0*PI) + TOP_BAR+20*i+(i*10)+10;
					glVertex2f(x,y);
				}
				glEnd();
				break;

			case 6:
				glBegin(GL_POLYGON);

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