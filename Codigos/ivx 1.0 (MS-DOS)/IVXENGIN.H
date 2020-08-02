/*
============================================================================
			ARCHIVO DE CABECERA DEL MODULO IVXENGINE.CPP

Este archivo contienen todas las constantes, macros, y prototipos de funciones
necesarios para el funcionamiento de este modulo
============================================================================
*/

	//DEFINICION DEL ARCHIVO DE CABECERA

#ifndef _IVXEngine_H
#define _IVXEngine_H

// LIBRERIAS NECESARIAS PARA EL FUNCIONAMIENTO DE IVXENGINE

#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

//Constantes

#define FALSE 0
#define TRUE  1
#define ANCHO_PANTALLA 320
#define ALTO_PANTALLA 200
#define SIZE_PANTALLA 64000
#define DIRECCION_MEMORIA_PANTALLA (unsigned char *) MK_FP(0xA000, 0)
#define AND &&
#define OR ||


//Tipo de datos necesarios para el manejo de colores;
typedef unsigned char COLOR;
//Tipo necesario para las variables booleanas
typedef unsigned char BOOL;

//Estructura necesaria para el manejo de sprites o bitmaps
typedef struct
  {
	int Ancho, Alto;
	COLOR *Contenido;
  }
  SPRITE;

//Estructura para almecenar colores divididos en ROJO VERDE y AZUL
typedef struct
  {
	COLOR cRojo, cVerde, cAzul;
  }
  RGB;

 //** DECALRACION DE FUNCIONES

 void    Inicia_VGA(); //inicia el modo Grafico
 void    Cierra_VGA();// Cierra el modo Grafico
 void    Pixel(int iX, int iY, COLOR cColor); //Pone un pixel en el buffer de memoria
 SPRITE  Cargar_Imagen(char cRuta[]); //Carga una imagen de un archivo en disco
 void    Limpiar_Pantalla(COLOR cColor); //llena la pantalla con un color determinado
 void    Poner_Sprite(SPRITE sMap, int CordX, int CordY, double dEscala_x=100, double dEscala_y=100);
			//Coloca un Sprite en el Buffer de memoria a una determinada escala
 void    Pintar_Pantalla(); //Copia el contenido del buffer de memoria en la pantalla
 void    Poner_Fondo(SPRITE sFondo);//pone un fondo de 320*200 en el buffer de memoria
 void    Libera_Sprite(SPRITE sMap);//libera la memoria de los sprites
 BOOL    Colision(SPRITE sMap1, int XMap1, int YMap1, SPRITE sMap2, int Xmap2, int YMap2); //detecta colisiones entre Sprites
 void    Cargar_Paleta(char cRuta[]); //Carga la paleta de colores de un archivo en el disco
 void    Fundido(COLOR cRojo, COLOR cVerde, COLOR cAzul, int Duracion);
			//Realiza un Fundido de acuerdo al porcentaje de color y aun retardo predeterminado
 int     Numero(char Letra); //retorna el numero correspondiente de cada letra para escribir;
 void    Poner_Texto(char *Letra, int x, int y, COLOR cColor);//coloca texto en pantalla
 char    LeerKey();//lee una tecla (como getch pero con el nuevo sistema de teclado)
 int     Char_a_Int(char Caracter);//convierte de caracter a entero
 void    Leer_Cadena(char *Cadena, int x, int y, COLOR cColor);//lee una cadena de caracteres;

#endif