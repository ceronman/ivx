//*************************************************************************
//                            MODULO NAVE.CPP
//		Este modulo es el encargado de todo lo referente a la nave
//		Desde sus movimientos, sus disparos, sus explosiones etc.
//*************************************************************************

#include "ivxengin.h"
#include "main.h"


#include "globales.h"
//incluye las variables globales (declaradas en modulo MAIN) nescesarias para funcionar
//*************************************************************************
//Funciones Globales del Modulo
//*************************************************************************
int MAX_ACELERACION=5;//aceleracion maxima que puede alcanzar la nave
int MAX_TITILANDO=30;//El numero de cuadros que estara titilando la nave
//*************************************************************************
//DEFINICION DE LAS FUNCIONES
//*************************************************************************

void Activar_Disparo()
{
 if (!Nave.Explosion AND !Nave.Kill)
    //si la nave no esta explotando ni esta muerta
  {
	Nave.Disparo=TRUE; //activa
	Nave.Disparo_X = Nave.X + Nave.Lado_Disparo; //inicializa cordenada
	Nave.Disparo_Y = Nave.Y;
	Nave.Lado_Disparo*=-1; //cambia el lado del disparo para el proximo disparo
  }
}
//*************************************************************************
void Disparar()
{
  Poner_Sprite(Nave.Imagen_Disparo[Nave.Arma_Actual],Nave.Disparo_X,Nave.Disparo_Y);
  //coloca la imagen del disparo en su posicion
  switch(Nave.Arma_Actual)
  //si el arma es el misil, este tiene aceleracion sino  va a velocidad constante
    {
     case 0: Nave.Disparo_Y -= Nave.Aceleracion_Disparo*TURBO;
	     //sube, deacuerdo a la aceleracion y al TURBO que controla la velocidad
	    break;
     case 1: Nave.Disparo_Y -= 10*TURBO;
	     //si es el laser sube a diez espacios por cuadro constantemente
	   break;
     case 2: Nave.Disparo_Y -= 1*TURBO;
	    //si es la bola de fuego va lentamente
	   break;
    }
    //la cordenada Y va disminuyendo lo que quiere decir que el disparo sube.

  if ( i%2 == 0) Nave.Aceleracion_Disparo++; //la aceleracion sube cada 2 cuadros

  if ( Nave.Disparo_Y<0) //si llega al final de la pantalla termina el disparo
			{
			 Desactivar_Disparo();
			 if (Nave.Arma_Actual==2) Nave.Arma_Actual=0;
			}
}
//*************************************************************************
void Mover_Nave()
	{
	 if (Nave.Titilando>0) //si es mayor que cero quiere decir que esta titilando
	       {
		Nave.Titilando++;
		//la variable va aumentando hasta que sea 120 es decir solo por unos segundos
		if (Nave.Titilando>120) Nave.Titilando=0;
	       }
	 if (!Nave.Kill AND (Nave.Titilando%2==0)) //si la nave no esta muerta o titilando es multiplo de 2 (da el efecto de titilar)
			//coloca su imagen en pantalla virtual segun su posicion
	 Poner_Sprite(Nave.Imagen[Nave.Frame],Nave.X,Nave.Y,Nave.Escala,Nave.Escala);
	 Nave.Presionado=FALSE; //a menos de que se presione una tecla esta varialble esta a falso

	 if(keys[KEY_LEFT])//izquierda
			  {
				Nave.Aceleracion--; //reduce la aceleracion para que valla hacia la izquierda
				Nave.Frame--; //el frame se reduce para que muestre la imagen de cuando la nave esta hacia la izquierda
				Nave.Presionado=TRUE; //se ha presionado una tecla
			  }

	 if(keys[KEY_RIGHT]) //derecha
			  {
				Nave.Aceleracion++;
				Nave.Frame++;        //lo mismo anterior pero invertido
				Nave.Presionado=TRUE;
			  }

	 if (Nave.Aceleracion<-MAX_ACELERACION) Nave.Aceleracion=-MAX_ACELERACION;
	 if (Nave.Aceleracion>MAX_ACELERACION) Nave.Aceleracion=MAX_ACELERACION;
	  //esto es para que no acelere demasiado,MAX_ACELERACION es la constante de aceleracion maxima
	 if (Nave.Frame>7) Nave.Frame=7;
	 if (Nave.Frame<1) Nave.Frame=1;
	  //para que no se sobrepase el frame, es decir no ponga una imagen que no existe
	 if (!Nave.Presionado) //si no se ha presionado una tecla
		  {
			if (Nave.Aceleracion!=0)   //y si no esta completamente quieto
			 {                                                            			  if (Nave.Aceleracion<0) Nave.Aceleracion++;
			  else Nave.Aceleracion--; //reduce o aumenta la aceleracion deacuerdo a como este
			  if (Nave.Frame>4) Nave.Frame--;
			  else if (Nave.Frame<4) Nave.Frame++; //lo mismo hace con el frame para que se ponga en la imagen normal
			}
		  }
	 Nave.X += Nave.Aceleracion*TURBO; //la cordenada x cambia deacuerdo a la aceleracion
	 if ( Nave.X < 25 ) Nave.X=25;
	 if ( Nave.X > 245) Nave.X=245; //si se pasa de los bordes se detiene
  }
//*************************************************************************
void Desactivar_Disparo()
{
 Nave.Disparo=FALSE; //simplemente reinicia los valores
 Nave.Aceleracion_Disparo=-3;
}
//*************************************************************************
void Explotar_Nave()
{
  Nave.Y+=Nave.Aceleracion_Explosion; //la nave baja deacuerdo a su aceleracion
  if (i%5==0) Nave.Aceleracion_Explosion++; //cada 10 cuadros la aceleracion aumenta
  Nave.Escala+=5; //tambien se va agrandando la imagen (en realidad el efecto de sobre escalamiento lo agranda pero lo divide)
  if (Nave.Y>600) //si ya esta muy abajo
	{
	 Nave.Explosion=FALSE; //termina la explosion
	 Nave.Escala=100;
	 Nave.X=160; // las variables se reinicializan
	 Nave.Y=175;
	 Nave.Vidas--;//y le quita una vida
	 if (Nave.Vidas< 0) Nave.Kill=TRUE;
	 Nave.Aceleracion_Explosion=-3;
	 Nave.Titilando++; //comienza a titilar
       }
}
//*************************************************************************
