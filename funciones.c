#include "funciones.h"

//_______________________________________________________________________ Paleta de colores (CORREGIR)
const float PaletaColor[28][3] = {0,0,0,/**/0,0,0.5,/**/0,0,1,/**/
								0,1,1,/**/0,0.5,1,/**/0,0.5,0.5,/**/
								0,1,0.5,/**/0,1,0,/**/0,0.5,0,/**/
								0.5,0,0,/**/1,0,0,/**/0.5,0,0.5,/**/
								1,0,0.5,/**/0.5,0,1,/**/1,0,1,/**/
								0.5,0.5,0,/**/1,0.5,0,/**/0.5,1,0,/**/
								1,1,0,/**/0.5,0.5,0.5,/**/0.95,0.95,0.95,/**/1,0.5,0.5,/**/
								0.5,1,0.5,/**/0.5,0.5,1,/**/0.5,1,1,/**/
								1,0.5,1,/**/1,1,0.5,/**/1,1,1};					//27 combinaciones

//____________________________________________________________ Funciones extras
void AsignaColor(COLOR color)
{
	glColor3f(PaletaColor[color][0],PaletaColor[color][1],PaletaColor[color][2]);
}

void TopBar()
{
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,ANCHO,TOP_BAR);
}

void SideBar()
{
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,SIDE_BAR,ALTO);
}

//___________________________________________________________ Dibujado de objetos

void Linea(LINEA *l)
{
	glBegin(GL_LINES);
	glVertex2f(l->xi, l->yi);
	glVertex2f(l->xf, l->yf);
	glEnd();
}

void Cuadrado(CUADRADO *c)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(c->x,c->y);
	glVertex2f(c->x+c->l,c->y);
	glVertex2f(c->x+c->l,c->y-c->l);
	glVertex2f(c->x,c->y-c->l);
	glEnd();
}

void Rectangulo(RECTANGULO *r)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(r->x,r->y);
	glVertex2f(r->x+r->ancho,r->y);
	glVertex2f(r->x+r->ancho,r->y-r->alto);
	glVertex2f(r->x,r->y-r->alto);
	glEnd();
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