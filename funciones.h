#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define MAX_CUADROS 5
#define TOTAL_PUNTOS 500

//__________________________________________________Estructuras
typedef struct{			//Estructura punto (x,y)
	float x;
	float y;
}PUNTO;

typedef struct{			//Estructura línea (Pi,Pf)
	float xi;
	float xf;
	float yi;
	float yf;
}LINEA;

typedef struct{
	float x;
	float y;
	float l;
}CUADRADO;

typedef struct 
{
	float x;
	float y;
	float ancho;
	float alto;
}RECTANGULO;

typedef struct 
{
	unsigned char numL;
	PUNTO *v;
}POLIGONOi;

typedef struct               //Estructura círculo
{
	float x0;
	float y0;
	float r;
}CIRCULO;

typedef struct				//Estructura elipse
{
	float x0;
	float y0;
	float a;
	float b;
	float th;
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
	ROSA_MEXICANO,
	VERDE_PASTEL,
	AZUL_PASTEL,
	CIAN_CLARO,
	ROSA,
	AMARILLO_MOSTAZA,
	BLANCO
}COLOR;


//________________________________________________ Prototipos
void display(void);
void AsignaColor(COLOR color);
void Linea(LINEA *l);
void Cuadrado(CUADRADO *c);
void Rectangulo(RECTANGULO *r);
void PoligonoI(POLIGONOi *p);
void Circulo(CIRCULO *c);
void Elipse(ELIPSE *e);
void Mouse(int button, int state, int x, int y);
void ActiveMouse(int x, int y);
void DibujarTexto(char *text, float x, float y);
void PassiveMouse(int x, int y);

//_______________________________________________________________________ Paleta de colores
const float PaletaColor[27][3] = {0,0,0,/**/0,0,0.5,/**/0,0,1,/**/
								0,1,1,/**/0,0.5,1,/**/0,0.5,0.5,/**/
								0,1,0.5,/**/0,1,0,/**/0,0.5,0,/**/
								0.5,0,0,/**/1,0,0,/**/0.5,0,0.5,/**/
								1,0,0.5,/**/0.5,0,1,/**/1,0,1,/**/
								0.5,0.5,0,/**/1,0.5,0,/**/0.5,1,0,/**/
								1,1,0,/**/0.5,0.5,0.5,/**/1,0.5,0.5,/**/
								0.5,1,0.5,/**/0.5,0.5,1,/**/0.5,1,1,/**/
								1,0.5,1,/**/1,1,0.5,/**/1,1,1};				//27 combinaciones