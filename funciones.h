#include <GL/glut.h>	//Windows, Linux //Compilar: gcc TestGL.c -c   //Enlazar: gcc TestGL.o -o test -lGL -lglut -lGLU
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define ANCHO 1300
#define ALTO 700
#define TOP_BAR 30
#define SIDE_BAR 30

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


//________________________________________________ Prototipos
//Callbacks
void display(void);
void PassiveMouse(int x, int y);
void Mouse(int button, int state, int x, int y);
void ActiveMouse(int x, int y);
//Figuras
void Linea(LINEA *l);
void Cuadrado(CUADRADO *c);
void Rectangulo(RECTANGULO *r);
void PoligonoI(POLIGONOi *p);
void Circulo(CIRCULO *c);
void Elipse(ELIPSE *e);
void DibujarTexto(char *text, float x, float y);
//Extras
void AsignaColor(COLOR color);
void TopBar();
void SideBar();


