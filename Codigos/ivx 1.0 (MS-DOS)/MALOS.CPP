//**************************************************************************
//				MODULO MALOS.CPP
//		Este modulo es el encargado de todo lo referente a los
//		Enemigos, como su ubicacion sus movimientos, sus disparos
//		explosiones etc..
//**************************************************************************
#include "ivxengin.h"
#include "main.h"
#include "teclado.h"

#include "globales.h"
//incluye las variables globales (declaradas en modulo MAIN) nescesarias para funcionar


//**************************************************************************
//Variables Globales del Modulo
//**************************************************************************
SPRITE ENEMIGO[3]; //Son las imagenes de los enemigos, como hay son iguales se declaran afuera de la
		   //estructura (el tipo SPRITE se define en IVXENGINE)
int BLOQUE_X, BLOQUE_Y, CAMBIO_BLOQUE_X=-TURBO, CAMBIO_BLOQUE_Y=TURBO;
int cont;//simple contador
int MAX_MALOS=10; //Numero de malos (no puede ser mayor que 10)
int MAX_RESISTENCIA=1; //Numero de Golpes que resisten los malos
//es para definir cuantos enemigos debe haber (ojo no puede haber mas de 10)

//**************************************************************************
//DEFINICION DE FUNCIONES
//**************************************************************************
void Activar_Disparo_Enemigo(int Numero)
{
 if ( !Disparo_Enemigo.Activado AND !Malo[Numero].Kill AND !Malo[Numero].Explosion )
	  //si no esta disparando actualmente, no esta muerto ni explotando
 {
  Disparo_Enemigo.X = Malo[Numero].X;  //inicializa las variables
  Disparo_Enemigo.Y = Malo[Numero].Y;
  Disparo_Enemigo.Activado = TRUE;
  Disparo_Enemigo.Tipo = Malo[Numero].Frame;
 }
}
//*************************************************************************
void Enemigo_Disparar()
{
  //coloca la imagen del disparo
  Poner_Sprite(Disparo_Enemigo.Imagen[Disparo_Enemigo.Tipo],Disparo_Enemigo.X,Disparo_Enemigo.Y);
  Disparo_Enemigo.Y+=Disparo_Enemigo.Tipo*3+2*TURBO; //va bajando
  if (Disparo_Enemigo.Y > ALTO_PANTALLA ) Disparo_Enemigo.Activado=FALSE;
   //si ya esta muy abajo detiene el disparo
}
//*************************************************************************
void Mover_Malos()
{
 BLOQUE_X+=CAMBIO_BLOQUE_X*TURBO; //las cordenadas del bloque de enemigos va cambiando
 BLOQUE_Y+=CAMBIO_BLOQUE_Y*TURBO; //deacuerdo a como la direccion que indica CAMBIO_BLOQUE_?

 if (BLOQUE_X>85 OR BLOQUE_X<10) CAMBIO_BLOQUE_X*=-1; //las direcciones X Y cambian cada
 if (BLOQUE_Y>60 OR BLOQUE_Y<10) CAMBIO_BLOQUE_Y*=-1; //vez que se llaga hasta un extremo

 GANO_NIVEL=TRUE;

 for (cont=0;cont<MAX_MALOS;cont++) //recorre todos los enemigos
		  {
		   if (!Malo[cont].Kill) GANO_NIVEL=FALSE;
		   if (!Malo[cont].Explosion AND !Malo[cont].Suicidio) //si no estan explotando
			 {
			  //establece las posiciones X y Y de cada malo deacuerdo a las variables BLOQUE_?
			  Malo[cont].X = BLOQUE_X + 40 * Malo[cont].Posicion_Horizontal;
			  Malo[cont].Y = BLOQUE_Y + 30 * Malo[cont].Posicion_Vertical;
			 }

		   if (cont==random(MAX_MALOS ) AND Malo[cont].Frame!=2)
			  //decidiendo de forma aleatoria y si el malo no es AMARILO (no disparan solo se suicidan)
				{
				 Activar_Disparo_Enemigo(cont);//activa el disparo
				}
		   if ( !random(100) AND Malo[cont].Frame==2)
			  //decide de forma aleatoria, y si el malo es un cangrejo se suicida
				 {
				 Malo[cont].Suicidio=TRUE; //se suicida
				 }
		   if (Malo[cont].Explosion)//si esta activada la explosion
			     Explotar_Malo(cont); //de ser asi explota!!
		   if (Malo[cont].Suicidio) //si esta activado el suicidio
			     Suicidar_Malo(cont);//si suicida

		   if (!Malo[cont].Kill AND 0<Malo[cont].Frame<3)   //si no esta muerto
			{
			  Poner_Sprite(ENEMIGO[Malo[cont].Frame], //simplemente coloca el enemigo
			  Malo[cont].X,Malo[cont].Y, //segun sus cordenadas
			  Malo[cont].Escala,Malo[cont].Escala); //y su escala
			}                                       //por si esta explotando
		  }
}
//*************************************************************************
void Suicidar_Malo(int Numero)
{
 if (!Malo[Numero].Kill AND !Malo[Numero].Explosion)
	 //si no esta muerto o explotando
 {
	Malo[Numero].Y+=2*TURBO;  //la cordenada y va aumentando lo que quiere decir que baja
	Malo[Numero].X+=Malo[Numero].Direccion_Suicidio; //y la cordenadax cambia de acuerdo a la direccion del suicidio
	if (i%20==0) Malo[Numero].Direccion_Suicidio*=-1; //la direccion del suicidio cambia cada 20 cuadros para crear el efecto de zig-zag
	if (Malo[Numero].Y>230) Malo[Numero].Suicidio=FALSE  ;//si llega muy abajo se termina el suicidio
 }
}
//*************************************************************************
void Explotar_Malo(int Num_Malo)
{
  Malo[Num_Malo].Y+=Malo[Num_Malo].Aceleracion_Explosion; //el malo se mueve deacuerdo a su aceleracion
  if (i%10==0) Malo[Num_Malo].Aceleracion_Explosion++; //cada 10 cuadros la aceleracion aumenta
  Malo[Num_Malo].Escala+=20; //tambien se va agrandando la imagen (en realidad el efecto de sobre escalamiento lo agranda pero lo divide)
  if (Malo[Num_Malo].Y>600) //si ya esta muy abajo
			{
			 Malo[Num_Malo].Explosion=FALSE; //termina la explosion
			 Malo[Num_Malo].Kill=TRUE;//y lo mata
			 Malo[Num_Malo].Aceleracion_Explosion=-3; //y reinicia su valor par uso posterior (­?)
			}
 }
//*************************************************************************
void Cargar_Mundo(int Numero)
{
 FILE *Archivo; //el archivo de donde se va a cargar
 int cont=0; //simple contador
 char Ruta[50];

 sprintf(Ruta,"IVXDATOS\\mundo%d.imd",Numero);
 if (NIVEL>0)  MAX_RESISTENCIA=1;
 if (NIVEL>30) MAX_RESISTENCIA=2;
 if (NIVEL>60) MAX_RESISTENCIA=3;

 BLOQUE_X=60;//inicializa las cordenadas del bloque de enemigos
 BLOQUE_Y=40;
 Inicializar_Datos();//inicializa los datos algunas variables globales

 if ( ! ( Archivo=fopen(Ruta,"r") ) ) //si no encuaentra el archivo
      {
	Finalizar();
	cout<<"Error no se puedo cargar el archivo de Nivel";//lanza error
	exit(-1);; //si no se puedo abrir el archivo retorna un error
      }
 fscanf(Archivo,"%1d\n",&TURBO);
 for (int i=0;i<2;i++) //los archivos tiene 2 filas
  {
	for (int j=0;j<5;j++) //y 5 columanas
	 {
	  if (!fscanf(Archivo, "%2d %1d %1d\n",&Malo[cont].Posicion_Horizontal, &Malo[cont].Posicion_Vertical, &Malo[cont].Frame) )
	  //lee cada uno de los datos, de cada malo, como su posicion vertical, horizontal, y el tipo de malo que es y los almacena en sus respectivas variables
	     { //si no pudo cargar el nivel lanza un error
	      Finalizar();
	      cout<<"Error no se puedo cargar el archivo de Nivel";//lanza error
	      exit(-1);; //si no se puedo abrir el archivo retorna un error
	     }
	  cont++;
	 }
  }
 fclose(Archivo);//cierra
}
//*************************************************************************