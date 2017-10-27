#include <GL/glut.h>	//Windows, Linux //Compilar: gcc TestGL.c -c   //Enlazar: gcc TestGL.o -o test -lGL -lglut -lGLU
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define ANCHO 1200
#define ALTO 600
#define TOP_BAR 30
#define SIDE_BAR 40


typedef enum{			//Enumeración de colores
	NEGRO,
	AZUL_FUERTE,
	AZUL,
	CIAN,
	AZUL_CLARO,
	AZUL_OPACO,
	VERDE_AZUL,
	VERDE,
	VERDE_FUERTE,
	MARRON,
	ROJO,
	MORADO_FUERTE,
	VIOLETA,
	MORADO,
	MAGENTA,
	ORO,
	ANARANJADO,
	VERDE_CLARO,
	AMARILLO,
	GRIS,
	GRIS_CLARO,
	ROSA_MEXICANO,
	VERDE_PASTEL,
	AZUL_PASTEL,
	CIAN_CLARO,
	ROSA,
	AMARILLO_MOSTAZA,
	BLANCO
}COLOR;


//__________________________________________________Estructuras
typedef struct{			//Estructura punto (x,y)
	float x;
	float y;
	COLOR color;
	int tamano;
}PUNTO;

typedef struct{			//Estructura línea (Pi,Pf)
	float xi;
	float xf;
	float yi;
	float yf;
	COLOR color;
	int ancho;
	char tipo;
}LINEA;

typedef struct{
	float x;
	float y;
	float l;
	COLOR color;
	char tipo_linea;
	char tipo;
	int ancho_linea;
}CUADRADO;

typedef struct 
{
	float x;
	float y;
	float ancho;
	float alto;
	COLOR color;
	char tipo_linea;
	char tipo;
	int ancho_linea;
}RECTANGULO;

typedef struct 
{
	unsigned char numL;
	PUNTO *v;
	COLOR color;
	char tipo_linea;
	char tipo;
	int ancho_linea;
}POLIGONOi;

typedef struct               //Estructura círculo
{
	float x0;
	float y0;
	float r;
	COLOR color;
	char tipo_linea;
	char tipo;
	int ancho_linea;
}CIRCULO;

typedef struct				//Estructura elipse
{
	float x0;
	float y0;
	float a;
	float b;
	float th;
	COLOR color;
	char tipo_linea;
	char tipo;
	int ancho_linea;
}ELIPSE;

//Lista enlazada
typedef struct LISTA 
{
	void* figura;
	char tipo;			//s->cuadrado, e->elipse, c->circulo, p->poligono, r->rectangulo, l->linea, d->punto
	struct LISTA* s;
}LISTA;

typedef struct OPCIONES	//Opciones con las que se puede dibujar cada figura
{
	COLOR color;	//PaletaColor
	int tipo_linea;
	char tipo;		//f->Fill, p->Point, l->Line
	int ancho;
}OPCIONES;

//________________________________________________ Prototipos
//Callbacks
void display(void);
void PassiveMouse(int x, int y);
void Mouse(int button, int state, int x, int y);
void ActiveMouse(int x, int y);
//Figuras
void Dibujar(LISTA* l);
void Linea(LINEA *l);
void Cuadrado(CUADRADO *c);
void Rectangulo(RECTANGULO *r);
void PoligonoI(POLIGONOi *p);
void Circulo(CIRCULO *c);
void Elipse(ELIPSE *e);
void Punto(PUNTO *p);
void DibujarTexto(char *text, float x, float y);
//Extras
void AsignaColor(COLOR color);
void TopBar();
void SideBar();
void Push(LISTA** lista, LISTA** elemento);
//Creacion de figuras
CUADRADO* CrearCuadrado(int x, int y, OPCIONES op);
RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op);
CIRCULO* CrearCirculo(int x, int y, OPCIONES op);
LINEA* CrearLinea(int x, int y, OPCIONES op);
ELIPSE* CrearElipse(int x, int y, OPCIONES op);
POLIGONOi* CrearPoligonoi(int x, int y, OPCIONES op);
PUNTO* CrearPunto(int x, int y, OPCIONES op);

