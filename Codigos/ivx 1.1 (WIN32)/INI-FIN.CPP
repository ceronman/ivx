//*****************************************************************************
//				MODULO INI-FIN.CPP
//		Este modulo es el encargado de inicializar todas las variables
//		y estructuras globales del juego, tambien de liberar al final
//		la memoria utilizada por las mismas.
//*****************************************************************************
#include "ivxengin.h"
#include "main.h"

#include "globales.h"
//incluye las variables globales (declaradas en modulo MAIN) nescesarias para funcionar
//*****************************************************************************
//DEFINICION DE FUNCIONES
//*****************************************************************************
void Inicializar()
{
	int cont;

	Inicia_VGA(); //inicia modo grafico
	Nave.Imagen[4] = Cargar_Imagen("IVXGRAF\\nave1.pcx");
	Nave.Imagen[1]=Cargar_Imagen("IVXGRAF\\nave4.pcx");
	Nave.Imagen[2]=Cargar_Imagen("IVXGRAF\\nave3.pcx");
	Nave.Imagen[3]=Cargar_Imagen("IVXGRAF\\nave2.pcx"); //Carga las imagenes
	Nave.Imagen[5]=Cargar_Imagen("IVXGRAF\\nave5.pcx"); //de la nave, tine varias para
	Nave.Imagen[6]=Cargar_Imagen("IVXGRAF\\nave6.pcx"); //distintas posiciones
	Nave.Imagen[7]=Cargar_Imagen("IVXGRAF\\nave7.pcx");

	Nave.Imagen_Disparo[0] = Cargar_Imagen("IVXGRAF\\disparo.pcx");
	Nave.Imagen_Disparo[1] = Cargar_Imagen("IVXGRAF\\disparo2.pcx");
	Nave.Imagen_Disparo[2] = Cargar_Imagen("IVXGRAF\\bfuego.pcx");
	//Son las diferentes imagenes de los disparos LASER, MISIL y BOLA DE FUEGO

	ENEMIGO[0]= Cargar_Imagen("IVXGRAF\\malo1.pcx");
	ENEMIGO[1]= Cargar_Imagen("IVXGRAF\\malo2.pcx");
	ENEMIGO[2]= Cargar_Imagen("IVXGRAF\\malo3.pcx");

    Explosion[0] = Cargar_Imagen("IVXGRAF\\Expl01.pcx");
    Explosion[1] = Cargar_Imagen("IVXGRAF\\Expl02.pcx");
    Explosion[2] = Cargar_Imagen("IVXGRAF\\Expl03.pcx");
    Explosion[3] = Cargar_Imagen("IVXGRAF\\Expl04.pcx");
    Explosion[4] = Cargar_Imagen("IVXGRAF\\Expl05.pcx");
    Explosion[5] = Cargar_Imagen("IVXGRAF\\Expl06.pcx");
    Explosion[6] = Cargar_Imagen("IVXGRAF\\Expl07.pcx");
    Explosion[7] = Cargar_Imagen("IVXGRAF\\Expl08.pcx");
    Explosion[8] = Cargar_Imagen("IVXGRAF\\Expl09.pcx");
    Explosion[9] = Cargar_Imagen("IVXGRAF\\Expl10.pcx");
	//3 imagenes de 3 diferentes enemigos
	Disparo_Enemigo.Imagen[0] = Cargar_Imagen("IVXGRAF\\dis_malo.pcx");
	Disparo_Enemigo.Imagen[1] = Cargar_Imagen("IVXGRAF\\dis_malo2.pcx");
	//2 imagenes del, TRUENO y LA BOLA ROJA.

	IVX_LOGO=Cargar_Imagen("IVXGRAF\\ivxlogo.pcx");
	//Carga el logo que aparece en la parte superior derecha
	GANASTE=Cargar_Imagen("IVXGRAF\\ganaste.pcx");
	PERDISTE=Cargar_Imagen("IVXGRAF\\perdiste.pcx");

	Nave_Apoyo.Imagen=Cargar_Imagen("IVXGRAF\\napoyo.pcx");
	Nave_Apoyo.Imagen_Bonus=Cargar_Imagen("IVXGRAF\\Bonus.pcx");

	for (cont=0;cont<MAX_ESTRELLAS;cont++) //cada una de las estrellas
	{
	 Estrellas.X[cont]=random(ANCHO_PANTALLA-1);
	 Estrellas.Y[cont]=random(ALTO_PANTALLA-1); //asigna aleatoriamente una posicion para las estrellas
	 Estrellas.Z[cont]=random(3)+1;
	}
	install_keyboard();

	Cargar_Paleta("IVXGRAF\\malo1.pcx");
 }
//*************************************************************************
void Finalizar()
{
	int i; //variable para ciclos;
 	for(i=1;i<8;i++) Libera_Sprite( Nave.Imagen[i] );
	      //Libera los SPRITES de la nave

	Libera_Sprite(ENEMIGO[0]); //de los enemigos
	Libera_Sprite(ENEMIGO[1]);
	Libera_Sprite(ENEMIGO[2]);

	Libera_Sprite(Disparo_Enemigo.Imagen[0]); //de los disparos enemigos
	Libera_Sprite(Disparo_Enemigo.Imagen[1]);

	Libera_Sprite(Nave.Imagen_Disparo[0]); //de los disparos de la nave
	Libera_Sprite(Nave.Imagen_Disparo[1]);
	Libera_Sprite(Nave.Imagen_Disparo[2]);

	Libera_Sprite(Nave_Apoyo.Imagen);
	Libera_Sprite(Nave_Apoyo.Imagen_Bonus);

	Libera_Sprite(IVX_LOGO);
	Libera_Sprite(PERDISTE);
	Libera_Sprite(GANASTE);

	Cierra_VGA(); //cierra el modo grafico
}
//*************************************************************************
void Inicializar_Datos()
{
 int cont;

  //inicializa las variables
  GANO_NIVEL=FALSE;
  Nave.X=160; //en el centro
  Nave.Y=175; //abajo
  Nave.Aceleracion=0; //no se esta moviendo
  Nave.Kill=FALSE; //no esta muerto
  Nave.Disparo=FALSE; //no esta disparando
  Nave.Explosion=FALSE; //ni explotando
  Nave.Aceleracion_Explosion=-3; // " "
  Nave.Escala=100;//escala normal
  Nave.Frame=4; //en el frame donde la nave aparece defrente
  Nave.Lado_Disparo=12; //dipara hacia la derecha 12 puntos
  Nave.Titilando=1;// al comienzo esta titilado

  Nave_Apoyo.X=0;
  Nave_Apoyo.Y=20;
  Nave_Apoyo.Activado=FALSE;
  Nave_Apoyo.Bonus_Activado=FALSE;

  for (cont=0;cont<MAX_MALOS;cont++) //cada uno de los enemigos
  {
    Malo[cont].Kill=FALSE; //no esta muerto
    Malo[cont].Explosion=FALSE; //ni explotando
    Malo[cont].Escala=100; //esta en tama¤o real
    Malo[cont].Aceleracion_Explosion=-3; //la explosion comienza hacia arriba
    Malo[cont].Suicidio=FALSE; //no se estan suicidando
    Malo[cont].Resistencia=MAX_RESISTENCIA;
    Malo[cont].Direccion_Suicidio=3; //y se empieza suicidando hacia la izquierda
    Malo[cont].Frame_Explosion=0;
  }
}
