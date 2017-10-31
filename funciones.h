#include <GL/glut.h>	//Windows, Linux //Compilar: gcc TestGL.c -c   //Enlazar: gcc TestGL.o -o test -lGL -lglut -lGLU
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define ANCHO 800
#define ALTO 600
#define TOP_BAR 30
#define SIDE_BAR 30
#define NSIDE_BAR_B 11
#define NTOP_BAR_B 36  
#define NCOLORES 28
#define L_LINE 0xFFFF
#define L_DOT 0xAAAA
#define L_DOTDASH 0xC9C9
#define L_DASH 0x6666
#define L_LONGDOTDASH 0xBEBE


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
	int ancho_linea;
	int tipo_linea;
	int factor_linea;
}LINEA;

typedef struct FREEFORM{
	PUNTO* p;
	struct FREEFORM* s;
	COLOR color;
	int tipo_linea;
	int ancho_linea;
	int factor_linea;
}FREEFORM;

typedef struct{
	float x;
	float y;
	float l;
	float direccionx;
	float direcciony;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}CUADRADO;

typedef struct 
{
	float x;
	float y;
	float ancho;
	float alto;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}RECTANGULO;

typedef struct 
{
	unsigned char numL;	//+1, el primero es el centro (en regular)
	float radio;
	PUNTO *v;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}POLIGONOi;

typedef struct               //Estructura círculo
{
	float x0;
	float y0;
	float r;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}CIRCULO;

typedef struct				//Estructura elipse
{
	float x0;
	float y0;
	float a;
	float b;
	float th;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}ELIPSE;

typedef struct 				//Estructura triangulo
{
	float x;
	float y;
	float lado;
	float direccion;
	COLOR color;
	int tipo_linea;
	int tipo;
	int ancho_linea;
	int factor_linea;
}TRIANGULO;

//Lista enlazada
typedef struct LISTA
{
	void* figura;
	char tipo;			//s->cuadrado, e->elipse, c->circulo, p->pentagono, h->hexagono, r->rectangulo, l->linea, d->punto, i->irregular
	struct LISTA* s;
}LISTA;

typedef struct OPCIONES	//Opciones con las que se puede dibujar cada figura
{
	COLOR color;	//PaletaColor
	int tipo_linea;
	int llenado;		//fill, line, point
	int ancho_linea;
	int factor_linea;
}OPCIONES;

typedef struct BOTON
{
	float xl;
	float yl;
	float xr;
	float yr;
	int id;
	int checked;
}BOTON;

//________________________________________________ Prototipos
//Callbacks
void display(void);
void PassiveMouse(int x, int y);
void Mouse(int button, int state, int x, int y);
void ActiveMouse(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
//Figuras
void Dibujar(LISTA* l);
void Linea(LINEA *l);
void Cuadrado(CUADRADO *c);
void Rectangulo(RECTANGULO *r);
void PoligonoI(POLIGONOi *p);
void Circulo(CIRCULO *c);
void Elipse(ELIPSE *e);
void Punto(PUNTO *p);
void Triangulo(TRIANGULO* t);
void FreeForm(FREEFORM* f);
void DibujarTexto(char *text, float x, float y);
//Extras
void AsignaColor(COLOR color);
void TopBar(BOTON* topBarB, OPCIONES* op);
void SideBar(BOTON* sideBarB, char tipo);
void Push(LISTA** lista, LISTA** elemento);
void Pop(LISTA** lista);
int ClickBar(BOTON* botones, int size, int x, int y);
int ClickBoton(BOTON boton, int x, int y);
float Min(int a, int b);
void ResetOptions();
void PonerAnchoLinea(LISTA* actual, int ancho);
void PonerFactorLinea(LISTA* actual, int factor);
//Creacion de figuras
CUADRADO* CrearCuadrado(int x, int y, OPCIONES op);
RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op);
CIRCULO* CrearCirculo(int x, int y, OPCIONES op);
LINEA* CrearLinea(int x, int y, OPCIONES op);
ELIPSE* CrearElipse(int x, int y, OPCIONES op);
POLIGONOi* CrearPoligonoi(int x, int y, OPCIONES op);
POLIGONOi* CrearPentagono(int x, int y, OPCIONES op);
void CalcularPentagono(PUNTO* v, float radio);
POLIGONOi* CrearHexagono(int x, int y, OPCIONES op);
void CalcularHexagono(PUNTO* v, float radio);
PUNTO* CrearPunto(int x, int y, OPCIONES op);
TRIANGULO* CrearTriangulo(int x, int y, OPCIONES op);
FREEFORM* CrearFreeForm(int x, int y, OPCIONES op);

