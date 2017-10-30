#include "funciones.h"

//_______________________________________________________________________ Paleta de colores (CORREGIR)
const float PaletaColor[NCOLORES][3] = {0,0,0,/**/0,0,0.5,/**/0,0,1,/**/
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

void Pop(LISTA** lista)
{
	LISTA* aux = *lista;
	LISTA* aux2 = aux;

	if(*lista == NULL)
		return;
	else if((*lista)->s == NULL)
	{
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
		*lista = NULL;
	}
	else
	{
		while(aux->s != NULL)
		{
			aux2 = aux;
			aux = aux->s;
		}

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

		aux2->s = NULL;
	}
}

//____________________________________________________________ Funciones extras
void AsignaColor(COLOR color)
{
	glColor3f(PaletaColor[color][0],PaletaColor[color][1],PaletaColor[color][2]);
}

void TopBar(BOTON* topBarB, OPCIONES* op)
{
	int i;
	//__________________________ Fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,ANCHO,TOP_BAR);

	//_________________________Paleta colores
	for(i = 0; i < NCOLORES/2; i++)
	{
		//_______________________ llenar caracteriasticas de los botones
		topBarB[i].xl = SIDE_BAR+15*i;
		topBarB[i].yl = 0;
		topBarB[i].xr = SIDE_BAR+15*(i+1);
		topBarB[i].yr = 15;
		topBarB[i].id = i;
		if(op->color == topBarB[i].id)
			topBarB[i].checked = 1;
		else
			topBarB[i].checked = 0;


		topBarB[i+14].xl = SIDE_BAR+15*i;
		topBarB[i+14].yl = 15;
		topBarB[i+14].xr = SIDE_BAR+15*(i+1);
		topBarB[i+14].yr = 30;
		topBarB[i+14].id = i+14;
		if(op->color == topBarB[i+14].id)
			topBarB[i+14].checked = 1;
		else
			topBarB[i+14].checked = 0;

		//_______________________ dibujar cuadros
		AsignaColor(i);
		glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);
		AsignaColor(i+14);
		glRectf(topBarB[i+14].xl, topBarB[i+14].yl, topBarB[i+14].xr, topBarB[i+14].yr);
	}

	//____________________________________ tipos de llenado
	for(i = 28; i < NCOLORES + 3; i++)
	{
		//______________________________ Llenando caracteriasticas del boton
		topBarB[i].xl = SIDE_BAR+20*(i-28) + 250 + (i-28)*10;
		topBarB[i].yl = 5;
		topBarB[i].xr = SIDE_BAR+20*(i-27) + 250 + (i-28)*10;
		topBarB[i].yr = 25;
		/*if(op->llenado == topBarB[i].id)
			topBarB[i].checked = 1;
		else
			topBarB[i].checked = 0;

		//_________________________________ Dibujar fondo
		if(topBarB[i].checked == 1)
			glColor3f(0.75, 0.75, 0.75);
		else
			glColor3f(0.90, 0.90, 0.90);
		glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);*/
		
		
		switch(i)
		{
			case 28: //GL_FILL
				//______________________________ Fondo
				if(op->llenado == GL_FILL)
					glColor3f(0.60, 0.60, 0.60);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);
				//
				glPolygonMode(GL_BACK, GL_FILL);
				topBarB[i].id = GL_FILL;
				break;

			case 29:	//GL_LINE
				//______________________________ Fondo
				if(op->llenado == GL_LINE)
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);
				//
				glPolygonMode(GL_BACK, GL_LINE);
				topBarB[i].id = GL_LINE;
				break;

			case 30:	//GL_POINT
				//______________________________ Fondo
				if(op->llenado == GL_POINT)
					glColor3f(0.60, 0.60, 0.60);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);
				//
				glPolygonMode(GL_BACK, GL_POINT);
				topBarB[i].id = GL_POINT;
				break;

			default:
				break;
		}

		//__________________________ Dibujar figura
		AsignaColor(AZUL_FUERTE);
		glRectf(topBarB[i].xl + 3, topBarB[i].yl + 3, topBarB[i].xr - 3, topBarB[i].yr - 3);
		glPolygonMode(GL_BACK, GL_FILL);
	}

	//______________________________________ tipos de linea
	for(i = NCOLORES + 3; i < NTOP_BAR_B; i++)
	{
		//______________________________ Llenando caracteriasticas del boton
		topBarB[i].xl = SIDE_BAR+20*(i-31) + 370 + (i-31)*10;
		topBarB[i].yl = 5;
		topBarB[i].xr = SIDE_BAR+20*(i-30) + 370 + (i-31)*10;
		topBarB[i].yr = 25;

		glEnable(GL_LINE_STIPPLE);
		switch(i)
		{
			case 31:	//Continua
				glLineStipple(1, L_LINE);
				topBarB[i].id = L_LINE;
				break;

			case 32:	//Punteada
				glLineStipple(1, L_DOT);
				topBarB[i].id = L_DOT;
				break;

			case 33:	//Punto-Gion
				glLineStipple(1, L_DOTDASH);
				topBarB[i].id = L_DOTDASH;
				break;

			case 34:	//Guiones
				glLineStipple(1, L_DASH);
				topBarB[i].id = L_DASH;
				break;

			case 35:	//Punto_guion largo
				glLineStipple(1, L_LONGDOTDASH);
				topBarB[i].id = L_LONGDOTDASH;
				break;

			default:
				glLineStipple(1, L_LINE);
				topBarB[i].id = L_LINE;
				break;
		}

		if(op->tipo_linea == topBarB[i].id)
			topBarB[i].checked = 1;
		else
			topBarB[i].checked = 0;

		//_________________________________ Dibujar fondo
		if(topBarB[i].checked == 1)
			glColor3f(0.65, 0.65, 0.65);
		else
			glColor3f(0.90, 0.90, 0.90);
		glRectf(topBarB[i].xl, topBarB[i].yl, topBarB[i].xr, topBarB[i].yr);

		//__________________________________ Dibujar figura
		AsignaColor(AZUL_FUERTE);
		glBegin(GL_LINES);
		glVertex2f(topBarB[i].xl + 3, topBarB[i].yl + 3);
		glVertex2f(topBarB[i].xr - 3, topBarB[i].yr - 3);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);
}

void SideBar(BOTON* sideBarB, char tipo)
{
	int i;
	float th, x, y;
	//___________________________ fondo
	AsignaColor(GRIS_CLARO);
	glRectf(0,0,SIDE_BAR,ALTO);

	//___________________________ Figuras
	for(i = 0; i < NSIDE_BAR_B; i++)
	{
		//______________________________ Llenando caracteriasticas del boton
		sideBarB[i].xl = 5;
		sideBarB[i].yl = TOP_BAR+20*i+(i*10);
		sideBarB[i].xr = 25;
		sideBarB[i].yr = TOP_BAR+20*(i+1)+(i*10);		
		
		//________________________________ Dibujar figuras internas
		switch(i)
		{
			case 0: //punto
				//_________________________ Dibujar fondo
				if(tipo == 'd')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);

				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
				sideBarB[i].id = 'd';
				glPointSize(3);
				glBegin(GL_POINTS);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + (sideBarB[i].yr - sideBarB[i].yl)/2);
				glEnd();
				glPointSize(1);
				glEnd();
				break;

			case 1:	//Linea
				//_________________________ Dibujar fondo
				if(tipo == 'l')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
				sideBarB[i].id = 'l';
				glBegin(GL_LINES);
				glVertex2f(sideBarB[i].xl + 2, sideBarB[i].yl + 2);
				glVertex2f(sideBarB[i].xr - 2, sideBarB[i].yr - 2);
				glEnd();
				break;

			case 2:	//Linea libre (freeform)
				//_________________________ Dibujar fondo
				if(tipo == 'f')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
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
				//_________________________ Dibujar fondo
				if(tipo == 's')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
				sideBarB[i].id = 's';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 3);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yr - 3);
				glEnd();
				break;

			case 4://Rectangulo
				//_________________________ Dibujar fondo
				if(tipo == 'r')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
				sideBarB[i].id = 'r';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yl + 6);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yl + 6);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 6);
				glVertex2f(sideBarB[i].xl + 3, sideBarB[i].yr - 6);
				glEnd();
				break;

			case 5:	//Triangulo
				//_________________________ Dibujar fondo
				if(tipo == 't')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
				sideBarB[i].id = 't';
				glBegin(GL_POLYGON);
				glVertex2f(sideBarB[i].xl + 3, TOP_BAR+20*(i+1)+(i*10)-3);
				glVertex2f(sideBarB[i].xl + (sideBarB[i].xr - sideBarB[i].xl)/2, sideBarB[i].yl + 3);
				glVertex2f(sideBarB[i].xr - 3, sideBarB[i].yr - 3);
				glEnd();
				break;

			case 6:	//Circulo
				//_________________________ Dibujar fondo
				if(tipo == 'c')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
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
				//_________________________ Dibujar fondo
				if(tipo == 'e')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
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
				//_________________________ Dibujar fondo
				if(tipo == 'p')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
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
				//_________________________ Dibujar fondo
				if(tipo == 'h')
					glColor3f(0.65, 0.65, 0.65);
				else
					glColor3f(0.90, 0.90, 0.90);
				glRectf(sideBarB[i].xl, sideBarB[i].yl, sideBarB[i].xr, sideBarB[i].yr);
				
				//__________________________ Dibujar figura
				AsignaColor(NEGRO);
				glPolygonMode(GL_BACK, GL_LINE);//OJO AQUI!!!!!! normalmente es front
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
	aux->direccionx = 1;
	aux->direcciony = 1;
	aux->color = op.color;
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

	return aux;
}

RECTANGULO* CrearRectangulo(int x, int y, OPCIONES op)
{
	RECTANGULO *aux;

	aux = (RECTANGULO*)malloc(sizeof(RECTANGULO));
	aux->x = x;
	aux->y = y;
	aux->ancho = 50;
	aux->alto = 20;
	aux->color = op.color;
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

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
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

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
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

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
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

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
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

	return aux;
}

/*POLIGONOi* CrearPoligonoi(int x, int y, int numL, OPCIONES op)
{
	PUNTO* aux;

	aux->v = (PUNTO*)malloc(sizeof(PUNTO)*numL);
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
}*/

POLIGONOi* CrearPentagono(int x, int y, OPCIONES op)
{
	POLIGONOi *aux;
	int i;

	aux = (POLIGONOi*)malloc(sizeof(POLIGONOi));
	aux->numL = 6;	//+1 para el centro
	aux->radio = 10.0;
	aux->v = (PUNTO*)malloc(sizeof(PUNTO)*aux->numL);
	aux->v[0].x = x;	//El primero es el centro
	aux->v[0].y = y;
	aux->color = op.color;
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

	CalcularPentagono(aux->v, aux->radio);

	return aux;
}

void CalcularPentagono(PUNTO* v, float radio)
{
	int i;
	for(i = 1; i < 6; i++)	//El primero es el centro
	{
		v[i].x = v[0].x + radio*cos(((18.0+i*72.0)*PI)/180.0);
		v[i].y = v[0].y - radio*sin(((18.0+i*72.0)*PI)/180.0);
	}
}

POLIGONOi* CrearHexagono(int x, int y, OPCIONES op)
{
	POLIGONOi *aux;
	int i;

	aux = (POLIGONOi*)malloc(sizeof(POLIGONOi));
	aux->numL = 7;	//+1 para el centro
	aux->radio = 10.0;
	aux->v = (PUNTO*)malloc(sizeof(PUNTO)*aux->numL);
	aux->v[0].x = x;	//El primero es el centro
	aux->v[0].y = y;
	aux->color = op.color;
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;

	CalcularHexagono(aux->v, aux->radio);

	return aux;
}

void CalcularHexagono(PUNTO* v, float radio)
{
	int i;
	for(i = 1; i < 7; i++)	//El primero es el centro
	{
		v[i].x = v[0].x + radio*cos((i*60.0*PI)/180.0);
		v[i].y = v[0].y - radio*sin((i*60.0*PI)/180.0);
	}
}

PUNTO* CrearPunto(int x, int y, OPCIONES op)
{
	PUNTO *aux;

	aux = (PUNTO*)malloc(sizeof(PUNTO));
	aux->x = x;
	aux->y = y;
	aux->color = op.color;
	aux->tamano = op.ancho_linea;

	return aux;
}

TRIANGULO* CrearTriangulo(int x, int y, OPCIONES op)
{
	TRIANGULO* aux;

	aux = (TRIANGULO*)malloc(sizeof(TRIANGULO));
	aux->x = x;
	aux->y = y;
	aux->lado = 10;
	aux->direccion = 1;
	aux->color = op.color;
	aux->tipo = op.llenado;
	aux->tipo_linea = op.tipo_linea;
	aux->factor_linea = op.factor_linea;
	aux->ancho_linea = op.ancho_linea;
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
	glPointSize(p->tamano);
	glBegin(GL_POINTS);
	glVertex2f(p->x, p->y);
	glEnd();

	glPointSize(1);
}

void Triangulo(TRIANGULO* t)
{
	AsignaColor(t->color);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(t->factor_linea, t->tipo_linea);
	glLineWidth(t->ancho_linea);
	glPointSize(t->ancho_linea);

	if((t->direccion < 0 && t->lado > 0) || (t->direccion > 0 && t->lado < 0))
		glPolygonMode(GL_FRONT, t->tipo);
	else
		glPolygonMode(GL_BACK, t->tipo);

	glBegin(GL_POLYGON);
	glVertex2f(t->x, t->y);
	glVertex2f(t->x + t->lado/2, t->y - t->direccion*sqrt(3*(t->lado*t->lado)/4));
	glVertex2f(t->x + t->lado, t->y);
	glEnd();

	ResetOptions();
}

void Linea(LINEA *l)
{
	AsignaColor(l->color);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(l->factor_linea, l->tipo_linea);
	glLineWidth(l->ancho_linea);
	glPointSize(l->ancho_linea);
	
	glBegin(GL_LINES);
	glVertex2f(l->xi, l->yi);
	glVertex2f(l->xf, l->yf);
	glEnd();

	ResetOptions();
}

void FreeForm(FREEFORM* f)
{
	AsignaColor(f->color);
	
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(f->factor_linea, f->tipo_linea);
	glLineWidth(f->ancho_linea);
	glPointSize(f->ancho_linea);

	glBegin(GL_LINE_STRIP);
	while(f!=NULL)
	{
		glVertex2f(f->p->x, f->p->y);
		f = f->s;
	}
	glEnd();

	ResetOptions();
}

void Cuadrado(CUADRADO *c)
{
	AsignaColor(c->color);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(c->factor_linea, c->tipo_linea);
	glLineWidth(c->ancho_linea);
	glPointSize(c->ancho_linea);

	if((c->direccionx == 1 && c->direcciony == 1) || (c->direccionx == -1 && c->direcciony == -1))
	{
		glPolygonMode(GL_BACK, c->tipo);
	}
	else
	{
		glPolygonMode(GL_FRONT, c->tipo);
	}

	glRectf(c->x, c->y, c->x+c->direccionx*c->l, c->y+c->direcciony*c->l);
	
	ResetOptions();
}

void Rectangulo(RECTANGULO *r)
{
	AsignaColor(r->color);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(r->factor_linea, r->tipo_linea);
	glLineWidth(r->ancho_linea);
	glPointSize(r->ancho_linea);

	if((r->ancho > 0 && r->alto > 0) || (r->ancho < 0 && r->alto < 0))
	{
		glPolygonMode(GL_BACK, r->tipo);
	}
	else
	{
		glPolygonMode(GL_FRONT, r->tipo);
	}

	glRectf(r->x, r->y, r->x+r->ancho, r->y+r->alto);
	
	ResetOptions();
}

void PoligonoI(POLIGONOi *p)
{
	unsigned char i;
	AsignaColor(p->color);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(p->factor_linea, p->tipo_linea);
	glLineWidth(p->ancho_linea);
	glPointSize(p->ancho_linea);

	glPolygonMode(GL_FRONT, p->tipo);

	glBegin(GL_POLYGON);
	for(i=1;i<p->numL;i++)
	{
		glVertex2f(p->v[i].x, p->v[i].y);
	}
	glEnd();
	
	ResetOptions();
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

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(c->factor_linea, c->tipo_linea);
	glLineWidth(c->ancho_linea);
	glPointSize(c->ancho_linea);

	if(c->tipo == GL_POINT)
		glBegin(GL_POINTS);
	else
		glBegin(GL_LINE_LOOP);

	if(c->tipo == GL_LINE || c->tipo == GL_POINT)	//Circunferencia
	{
		for(th=0;th<=360; th+=1)
		{
			x = c->r * cos(th/180.0 * PI) + c->x0;
			y = c->r * sin(th/180.0 * PI) + c->y0;
			glVertex2f(x,y);
		}
	}
	else if(c->tipo == GL_FILL) 	//Circulo
	{
		for(x=-1*(c->r+c->x0); x <= c->r+c->x0; x+=0.1)
		{
			y = sqrt(c->r*c->r - (x-c->x0)*(x-c->x0))+c->y0;
			glVertex2f(x,y);
			y = -sqrt(c->r*c->r - (x-c->x0)*(x-c->x0))+c->y0;
			glVertex2f(x,y);
		}
	}	
	glEnd();

	ResetOptions();
}

void Elipse(ELIPSE *e)
{
	float x,y,th, xr, yr, th2,a,b;
	AsignaColor(e->color);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(e->factor_linea, e->tipo_linea);
	glLineWidth(e->ancho_linea);
	glPointSize(e->ancho_linea);
	
	if(e->tipo == GL_POINT)
		glBegin(GL_POINTS);
	else
		glBegin(GL_LINE_LOOP);

	if(e->tipo == GL_POINT || e->tipo == GL_LINE)	//Contorno
	{
		for(th=0; th<360; th+=1)
		{
			x = e->a*cos(th/180.0*PI);
			y = e->b*sin(th/180.0*PI);
			xr = x*cos(e->th/180.0*PI)-y*sin(e->th/180.0*PI) + e->x0;
			yr = x*sin(e->th/180.0*PI)+y*cos(e->th/180.0*PI) + e->y0;
			glVertex2f(xr,yr);
		}
	}
	else if(e->tipo == GL_FILL)	//Relleno
 	{
 		a = e->a;
 		b = e->b;
 		if(abs(a) < abs(b))
 		{
	 		for(a = e->a; a >=0; a--)
	 		{
				for(th=0; th<360; th++)
				{
					x = a*cos(th/180.0*PI);
					y = b*sin(th/180.0*PI);
					xr = x*cos(e->th/180.0*PI)-y*sin(e->th/180.0*PI) + e->x0;
					yr = x*sin(e->th/180.0*PI)+y*cos(e->th/180.0*PI) + e->y0;
					glVertex2f(xr,yr);
				}
			}
		}
		else
		{
			for(b = e->b; b >=0; b--)
	 		{
				for(th=0; th<360; th++)
				{
					x = a*cos(th/180.0*PI);
					y = b*sin(th/180.0*PI);
					xr = x*cos(e->th/180.0*PI)-y*sin(e->th/180.0*PI) + e->x0;
					yr = x*sin(e->th/180.0*PI)+y*cos(e->th/180.0*PI) + e->y0;
					glVertex2f(xr,yr);
				}
			}
		}
	}
	glEnd();

	ResetOptions();
}

void DibujarTexto(char *text, float x, float y)
{
	char* c;
	glRasterPos2f(x,y);

	for(c=text; *c!='\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
}

void ResetOptions()
{
	glPolygonMode(GL_BACK, GL_FILL);
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1);
	glPointSize(1);
}

void PonerAnchoLinea(LISTA* actual, int ancho)
{
	switch(actual->tipo){
		case 's':
			((CUADRADO*)(actual->figura))->ancho_linea = ancho;
			break;
		
		case 'r':
			((RECTANGULO*)(actual->figura))->ancho_linea = ancho;
			break;
		
		case 'c':
			((CIRCULO*)(actual->figura))->ancho_linea = ancho;
			break;

		case 'l':
			((LINEA*)(actual->figura))->ancho_linea = ancho;
			break;

		case 'e':
			((ELIPSE*)(actual->figura))->ancho_linea = ancho;
			break;

		case 'p':
			((POLIGONOi*)(actual->figura))->ancho_linea = ancho;
			break;

		case 'h':
			((POLIGONOi*)(actual->figura))->ancho_linea = ancho;
			break;

		case 'd':
			((PUNTO*)(actual->figura))->tamano= ancho;
			break;

		case 't':
			((TRIANGULO*)(actual->figura))->ancho_linea = ancho;
			break;

		case 'f':
			((FREEFORM*)(actual->figura))->ancho_linea = ancho;
			break;

		default:
			break;
	}
}

void PonerFactorLinea(LISTA* actual, int factor)
{
	switch(actual->tipo){
		case 's':
			((CUADRADO*)(actual->figura))->factor_linea = factor;
			break;
		
		case 'r':
			((RECTANGULO*)(actual->figura))->factor_linea = factor;
			break;
		
		case 'c':
			((CIRCULO*)(actual->figura))->factor_linea = factor;
			break;

		case 'l':
			((LINEA*)(actual->figura))->factor_linea = factor;
			break;

		case 'e':
			((ELIPSE*)(actual->figura))->factor_linea = factor;
			break;

		case 'p':
			((POLIGONOi*)(actual->figura))->factor_linea = factor;
			break;

		case 'h':
			((POLIGONOi*)(actual->figura))->factor_linea = factor;
			break;

		case 't':
			((TRIANGULO*)(actual->figura))->factor_linea = factor;
			break;

		case 'f':
			((FREEFORM*)(actual->figura))->factor_linea = factor;
			break;

		default:
			break;
	}
}