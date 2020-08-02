//*****************************************************************************
//				MODULO GLOBALES.CPP
//
//			Modulo donde se declaran las variable globales
//			principales del juego
//*****************************************************************************
#include "ivxengin.h"
#include "main.h"
//*******************************************************************
//VARIABLES GLOBALES
//*******************************************************************
  int i=0; //variable para controlar los cuadros (FRAMES) y para algunos ciclos

  BOOL GANO_NIVEL=FALSE;//para saber si gano el nivel
  BOOL SALIR=FALSE;//para saber si se sale del juego.
  BOOL PRIMERA_VEZ=TRUE;//variable para saber si es la primera vez que se realiza el cilco
  BOOL CONTINUE_USADO=FALSE;//variable para saber si se activo un continue nuevo.
  BOOL ESTRELLAS_ACTIVADAS=TRUE;//variable para las opciones para saber si se ponen las estrellas
  BOOL MENSAJES_ACTIVADOS=TRUE;//variable para saber si se ponen los mensajes
  BOOL APOYO_ACTIVADO=TRUE;//variable para saber si sale la nave de apoyo
  char MENSAJES[50];//es el mensajes que salen en la parte de arriba
  volatile int TIEMPO; //el tiempo
  int MAX_TIEMPO=60; //el tiempo maximo;
  int DIFICULTAD=1;// la dificultad puede ser 0 1 ¢ 2
  int NIVEL=1;   //Nivel Actual
  int CONTINUES=2;//Numero de veces que puede continuar el jugador
  long int PUNTUACION=0; //variable que acumula la puntuacion;
  int PASSWORD[6];
  BOOL PASSWORD_OK=FALSE;
  int TURBO=1;
  int RETRAZO=0;
  //Variables para el manejo de la velocidad del juego.
  //TURBO es el factor de movimiento en pixeles de cada cuadro
  //mientras que retrazo es el retrazo adicional de cada cuadro, convinandolas
  //se puden obtener diferentes velocidades

  struct { //Esta es la estructura Nave que se usa para encapsular todo lo referente a la NAVE
	  int X, Y; //Posicion
	  int Aceleracion;
	  BOOL Presionado; //La variable presionado sirve para saber si se esta presionando una tecla
			//(el tipo BOOL se define en IVXENGINE)
	  int Vidas;
	  BOOL Kill; //Sirve para saber si le disparan y pierde una vida
	  BOOL Disparo; //para saber si se activo el disparo;
	  BOOL Explosion;//para saber si esta esplotando
	  int Aceleracion_Explosion; //que tan rapida es la explocion
	  int Escala;//que tama¤o tiene
	  int Disparo_X, Disparo_Y, Aceleracion_Disparo, Lado_Disparo;
	    //estas variabel son para todo lo referente al disparo
	    //Lado_Disparo sirve para que el disparo sala por diferentes lados
	  int Arma_Actual;//que arma tiene actualmente
	  int Titilando;//para saber si esta titilando y  cuando debe terminar
	  int Frame; //indica en que frame esta en la animacion (la nave se anima cuando gira)
	  SPRITE Imagen[8], Imagen_Disparo[3]; //los SPRITES o IMAGENES
      } Nave;

  struct { //esta es la estructura de cada enemigo
	  int X,Y;
	  int Kill;
	  int Escala; //Sirve para la explocion en donde esta no es mas que el sobredimencionado de la imagen
	  BOOL Explosion; //sirve para saber si fue impactado y tiene que explotar
	  int Aceleracion_Explosion; //para que la explosion se vea bacana
	  int Frame; //para saber que tipo de malo es
      int Frame_Explosion;//para que la explosion;
	  int Posicion_Horizontal, Posicion_Vertical;//para saber su posicion en el grupo
	  BOOL Suicidio; //para saber si se esta suicidando
	  int Resistencia;//para saber cuantos golpes resisten
	  int Direccion_Suicidio;  //hacia que lado se esta suicidando
    } Malo[10]; //por ahora solo hay 3 malos

  struct {
	  int X[MAX_ESTRELLAS], Y[MAX_ESTRELLAS], Z[MAX_ESTRELLAS];
      } Estrellas; //sirve para crear el campo de estrellas, cada estrella tiene 3 dimenciones}

  struct { //es la estructura de los disparos de los enemigos
	  int X, Y; //posicion
	  BOOL Activado;
	  SPRITE Imagen[2];//imagen
	  int Tipo; //para saber si es trueno o bola
       }Disparo_Enemigo;

  struct {
	  int X,Y;//ubicacion
	  SPRITE Imagen, Imagen_Bonus;//imagenes
	  BOOL Activado, Bonus_Activado;//si estan activados
	  int Bonus_X, Bonus_Y;//ubicacion del bonus
   }Nave_Apoyo;// La nave de apoyo

SPRITE Explosion[10];
