/*
Invasion Marciana IVX
Version 1.1 WINDOWS VERSION

Esta es la version 1.0 del juego creado como proyecto de semestre de la materia
introduccion a la informatica de primer semestre de ingenieria de sistemas de
la Universidad del Cauca (Colombia) por Manuel Alejandro Ceron.

Esta version del juego se ha adaptado para usarse con la libreria ALLEGRO
puede encontrar informacion al respecto en http://alleg.sourceforge.net

Esta version requiere de un compilador de 32 bits para poder correr.
La version 1.0 puede correr en un compilador de 16 bits como Turbo C++

Para obtener IVX para otros sistemas operativos como linux BeOS o Mac
Escriba a rdceron@emtel.net.co

La documentacion de la version 1.0 se puede encontrar en el archivo "documentacion.doc"
------------------------------
Cambios desde la ultima version
	- Se ha adaptado todo el codigo a la libreria Allegro
	- Ahora el codigo es portable y existen versiones para varios
      sistemas operativos
	- Mejorado el sistema de explosiones de los enemigos
	- Mejorado el sistema de fuente (texto) gracias a allegro.
    - Ahora el juego corre a la misma velocidad en casi cualquier computador
    - Corregidos fallos en el sistema de records
    - Ahora el juego tiene licencia GPL
*/
#include "ivxengin.h"
//Contiene los tipos y funciones necesarias para el aspecto grafico

// por Dhonn Lushine, para controlar el teclado.
#include "main.h"
//Constantes, Macros, y funciones del proyecto
#include "globales.h"
//incluye los datos globales del proyecto
volatile int contador=0; //contador para controlar la velocidad
void incrementar_conteo() //funcion para controlar la velocidad
{
 contador++;
}
void decrementar_tiempo()
{
 TIEMPO--;
}

//********************************************************************
//FUNCION PRINCIPAL
//*******************************************************************
int main()
{
 int temp_tiempo;
 int temp_contador;
 Inicializar();//carga todas las imagenes e inicia modo grafico
 LOCK_VARIABLE(contador);
 LOCK_FUNCTION(incrementar_conteo);
 LOCK_VARIABLE(TIEMPO);
 LOCK_FUNCTION(decrementar_tiempo);
 install_int_ex(incrementar_conteo, BPS_TO_TIMER(30));
 install_int(decrementar_tiempo,1000);

 Presentacion();//realiza la presentacion con el logo de ucauca y el de ivx software
 Historia();//Muestra la historia del juego.
 //BUCLE PRINCIPAL

 while(!SALIR) //Mientras no se de la opcion de salir
  {
   if (PRIMERA_VEZ) Pantalla_Inicio(); //La primera vez que se ejecuta el ciclo  coloca la pantalla de inicio
   Cambiar_Mensajes();//coloca un mensaje aleatorio en la variable MENSAJES
   Configurar_Password();//Raliza la configuracion de los datos que se cargan si se ingresa un password
   Cargar_Mundo(NIVEL); //carga el mundo indicado por la variable NIVEL (comienza en 1)
   Configurar_Dificultad();//Configura el juego deacuerdo a la dificultad escojida en el menu de opciones
   Configurar_Password();//Denuevo configura el password
   
   PRIMERA_VEZ=TRUE;//Es para que se inicie el escenaria cada ciclo
   RETRAZO=15;//Cambiar esta variable para controlar la velocidad en diferentes PC
   contador=0;
   TIEMPO=MAX_TIEMPO;
   while(!Nave.Kill AND !GANO_NIVEL AND !SALIR)
   //Mientras no este muerto ni halla ganado el nivel  ni tenga la opcion de salir
	 {
      while(contador>0)
     {
	  Limpiar_Pantalla(0); //Pone la pantalla a negro
	  if (ESTRELLAS_ACTIVADAS) Poner_Estrellas(); //si la opcion de estrellas esta activada las pone
	  if (MENSAJES_ACTIVADOS)  Poner_Texto(MENSAJES,0,0,ROJO);
	  //coloca los mensajes de arriba si esta activada la opcion

	  Detectar_Impactos();
	  //detecta si el disparo de la nave choca con algun enemigo
	  //o si el disparo del enemigo choca con la nave, etc..;

	  if (Nave.Explosion) Explotar_Nave(); //esto se explica por si solo
	  if (Nave_Apoyo.Activado) Apoyo();
	  if (Nave_Apoyo.Bonus_Activado) Bonus();
	  if (Nave.Disparo) Disparar();
	  if (Disparo_Enemigo.Activado) Enemigo_Disparar();
      Mover_Malos();//pone los enemigos y cambia las cordenadas en rebotes
      Mover_Nave();//mueve la nave deacuerdo a las teclas

	  if(keys[KEY_SPACE] AND !Nave.Disparo) Activar_Disparo();
	  //si presiona espacio y no esta disparando actualmente Dispara;
	  if (i%200==0) Cambiar_Mensajes(); //cada 200 cuadros cambia el mensaje de arriba
	  if (i%100==0 AND !Nave_Apoyo.Activado AND !Nave_Apoyo.Bonus_Activado AND APOYO_ACTIVADO)
	   {
	    Nave_Apoyo.Activado=TRUE;
	    //Cada 500 cuadros, si la nave de apoyo no esta activada ni el bonus tampoco activa el bonus
	   }
	  Poner_Panel();//coloca la barra de informacion
      contador--;
      if (TIEMPO<=0) Nave.Kill=true;
      if (PRIMERA_VEZ) {
             temp_tiempo=TIEMPO;
             temp_contador=contador;
             Iniciar_Escenario();//si es el primer cuadro inicia el escemario mostrando el numero de nivel
             contador=temp_contador;
             TIEMPO=temp_tiempo;
      }
    }
   	  Pintar_Pantalla(); //Pone la informacion en la pantalla (ver IVXENGINE)


	  if (keys[KEY_ESC] OR keys[KEY_F1]) Ayuda(0); //si presiona escape o F1 va a la ayuda.
   	  i++; //aumenta un cuadro o un ciclo;
      if (keys[KEY_P]) {
         temp_tiempo=TIEMPO;
         temp_contador=contador;
         delay(200);
         clear_keybuf();
         readkey();
         TIEMPO=temp_tiempo;
         contador=temp_contador;
      }
	}
   if (Nave.Kill) Perder(); //si la nave fue muerta pone la pantalla de perder
   if (GANO_NIVEL) Ganar();// si gano el juego pone la pantalla de ganar
  }
 Finalizar(); //libera memoria y cierra modo grafico
 return 0;
}
END_OF_MAIN();
//***********************************************************************
//DECLARACION DE FUNCIONES
//*************************************************************************
void Detectar_Impactos()
{
 if(Colision(Disparo_Enemigo.Imagen[Disparo_Enemigo.Tipo],Disparo_Enemigo.X,Disparo_Enemigo.Y,Nave.Imagen[Nave.Frame],Nave.X,Nave.Y)
    AND Disparo_Enemigo.Activado
    AND !Nave.Titilando)
   {
 //Si detecta una colision entre el disparo del enemigo y la nave
 //y fue por un disparo, y la nave no esta titilado (invulnerable)
	   Nave.Explosion=TRUE; //la nave explota
	   Nave.Arma_Actual=0; //y el arma se vuelve el misil
   }

  if ( Colision(Nave.Imagen_Disparo[Nave.Arma_Actual],Nave.Disparo_X,Nave.Disparo_Y, Nave_Apoyo.Imagen,Nave_Apoyo.X,Nave_Apoyo.Y)
       AND Nave_Apoyo.Activado
       AND Nave.Disparo)
  //si chocan la imagen del disparo y la imagen de la nave de apoyo
    {
	   Nave_Apoyo.Bonus_Activado=TRUE; //activa el bonus
	   Nave_Apoyo.Bonus_X=Nave_Apoyo.X; //con cordenadas iguales a las de la nave de apoyo.
	   Nave_Apoyo.Bonus_Y=Nave_Apoyo.Y;
	   Nave_Apoyo.Activado=FALSE;//y la nave de apoyo se desactiva
	   Nave_Apoyo.X=0;//y su cordenada se vuelve a 0 osea el principio de la pantalla
	   PUNTUACION+=15;//y el puntaje sube 15 puntos.
    }
 if ( Colision(Nave.Imagen[Nave.Frame],Nave.X,Nave.Y,Nave_Apoyo.Imagen_Bonus,Nave_Apoyo.Bonus_X,Nave_Apoyo.Bonus_Y)
      AND Nave_Apoyo.Bonus_Activado)
 //si la imagen del bonus choca con la nave
    {
	    Obtener_Bonus(); //se le da un bonus a la nave.
    }

 for (int cont=0;cont<MAX_MALOS;cont++) //recorre cada uno de los enemigos
    {
     if (Colision(ENEMIGO[ Malo[cont].Frame ],
		  Malo[cont].X , Malo[cont].Y,
		  Nave.Imagen_Disparo[Nave.Arma_Actual] , Nave.Disparo_X ,
		  Nave.Disparo_Y)
		  //si el disparo colisiona con el malo
	 AND Nave.Disparo //y fue por un disparo
	 AND !Malo[cont].Explosion //y no esta explotando todavia
	 AND !Malo[cont].Kill) // y no lo han matado ya
	{
	    if (Nave.Arma_Actual!=2) Desactivar_Disparo();
	    //si el arma es diferente al DEVASTATOR
	    //desactiva el disparo
	    Malo[cont].Resistencia--;
	    if (Malo[cont].Resistencia<1) //si la resistencia es menor que 1 osea ya le dieron todos los disparos necesarios
		Malo[cont].Explosion=TRUE; //Activa la explosion!!

	    PUNTUACION+=15*(Malo[cont].Frame+1)*(DIFICULTAD+1);
	    //la puntuacion aumenta deacuerdo al tipo de enmigo.
	}

     if (Colision(Nave.Imagen[Nave.Frame],Nave.X,Nave.Y,
		  ENEMIGO[Malo[cont].Frame],Malo[cont].X,Malo[cont].Y)
		  //si colisiona un enemigo con la nave
	 AND !Malo[cont].Explosion //y el malo no esta explotando
	 AND !Malo[cont].Kill//y el malo no esta muerto
	 AND !Nave.Titilando) //y la nave no esta titilando (invulnerable)
	{
	  Nave.Explosion=TRUE; //la nave explota.
	  Nave.Arma_Actual=0;
	}
    }
}
//*************************************************************************

void Poner_Estrellas()
{
 for(int cont=0;cont<MAX_ESTRELLAS;cont++) //recorre
   {
    Estrellas.Y[cont]+=Estrellas.Z[cont];
    if (Estrellas.Y[cont]>200) //si llegan al final
       {
	Estrellas.Y[cont]=0; //vuelven y comienzan
	Estrellas.X[cont]=random(319); //pero en un lugar aleatorio
       }
    switch(Estrellas.Z[cont]) //dependiendo de Z coloca el pixel de un determinado color para dar efecto de profundidad
       {
	case 1: { Pixel(Estrellas.X[cont],Estrellas.Y[cont],78); break;}//gris oscuro;
	case 2: { Pixel(Estrellas.X[cont],Estrellas.Y[cont],126); break;} //gris claro;
	case 3: { Pixel(Estrellas.X[cont],Estrellas.Y[cont],255); break;} //BLANCO;
       }
   }
}
//*************************************************************************
void Poner_Panel()
{
 int cont;//simple contador para las vidas
 char Texto[30]; //sirve para convertir datos enteros en cadenas

 Poner_Sprite(IVX_LOGO,290,10);//pone el logo de IVX

 for(cont=0;cont<200;cont++) //pone la linea vertical que separa el panel
 Pixel(263,cont,MORADO);

 Poner_Texto_Sombra("VIDAS",270,35,AMARILLO,ROJO_OSCURO);
 //escribe vidas con sombra en las cordenadas 270,35 de color amarillo y con sombra rojo oscuro
 //Poner_Texto_Sombra es un MACRO declarado en MAIN.H

 for(cont=0; cont<Nave.Vidas; cont++)
     {
      //pone tantas "navecitas" como vidas tenga el jugador
      if (cont<4) Poner_Texto("#",270+cont*10,45,BLANCO);
      else Poner_Texto("#",230+cont*10,55,BLANCO);
      //el caracter "#" signigica el caracter con la forma de la nave
      //ver IVXENGIN
     }
 Poner_Texto_Sombra("ARMA ",270,70,AMARILLO,ROJO_OSCURO);
 if (Nave.Arma_Actual!=2)
 //si el arma es el misil o el laser
     {
      Poner_Sprite(Nave.Imagen_Disparo[Nave.Arma_Actual],290,90);
      //lo pone de forma normal
     }
 else Poner_Sprite(Nave.Imagen_Disparo[Nave.Arma_Actual],290,90,30,30);
      //si es la bola de fuego lo pone en escala de 30%

 Poner_Texto_Sombra("NIVEL ",270,110,AMARILLO,ROJO_OSCURO);
 sprintf(Texto,"%d",NIVEL);
 Poner_Texto(Texto,285,120,BLANCO);
 sprintf(Texto,"%06d",PUNTUACION);
 //convierte el numero entero del puntaje en una cadena de caracteres
 //y la guarda en la variable Texto_Puntaj
 Poner_Texto_Sombra("PUNTOS",267,140,AMARILLO,ROJO_OSCURO);
 Poner_Texto(Texto,267,150,BLANCO); //escribe el puntaje

 Poner_Texto_Sombra("TIEMPO",267,170,AMARILLO,ROJO_OSCURO); //coloca el tiempo
 //Tiempo_Final=time(NULL);//toma un segundo tiempo como referencia
 //TIEMPO=MAX_TIEMPO-difftime(Tiempo_Final,Tiempo_Inicial);//la diferencia es el tiempo
 sprintf(Texto,"%d",TIEMPO);//convierte el numero en texto
 Poner_Texto(Texto,280,180,BLANCO);//e imprime
}
//*************************************************************************
void Apoyo()
{
 Poner_Sprite(Nave_Apoyo.Imagen, Nave_Apoyo.X, Nave_Apoyo.Y);
 //pone la imagen de la nave de apoyo en sus cordenadas
 Nave_Apoyo.X+=1*TURBO;
 //la variable x de la nave de apoyo va aumentando (o dirigiendose a la derecha)
 if (Nave_Apoyo.X>320)//si llega al final de la pantalla
    {
     Nave_Apoyo.X=0;//la cordenada vuelve al principio
     Nave_Apoyo.Activado=FALSE;//y se desactiva la nave de apoyo.
    }
}
//*************************************************************************
void Bonus()
{
 Poner_Sprite(Nave_Apoyo.Imagen_Bonus,Nave_Apoyo.Bonus_X,Nave_Apoyo.Bonus_Y);
 //Pone la imagen del bonus en sus cordenadas
 Nave_Apoyo.Bonus_Y+=1*TURBO;
 //su cordenada y aumenta (osea baja),
 if (Nave_Apoyo.Bonus_Y>200) //si llego al final de la pantalla
     Nave_Apoyo.Bonus_Activado=FALSE; //se desactiva
}
//*************************************************************************
void Obtener_Bonus()
{
 int Cual_Bonus;//variable para decidir que premio otorgar

 Nave_Apoyo.Bonus_Activado=FALSE; //desactiva el bonus
 Cual_Bonus=random(4);//se asigna aleatoriamente cual bonus escojer
 switch(Cual_Bonus)//dependiendo del bonus
  {
    //si es 0 le da una nueva arama o le da 100 puntos
    case 0:
	  if (Nave.Arma_Actual==0)   {  Nave.Arma_Actual=1; strcpy(MENSAJES,"#: LASER ACTIVADO"); }
	  else { PUNTUACION+=1000; strcpy(MENSAJES,"#: OBTENIDOS 1000 PUNTOS"); }
    break;
    //si es uno le da el arma 1 o si ya la tiene le pone la mejor arma
    case 1:
	  if (Nave.Arma_Actual!=1)   {  Nave.Arma_Actual=1; strcpy(MENSAJES,"#: LASER ACTIVADO");}
	  else { Nave.Arma_Actual=2; strcpy(MENSAJES,"#: DEVASTATOR ACTIVADO"); }
    break;
    //si es 2 le aumenta una vida o lo pone invensible por unos segundos
    case 2:
	   if (Nave.Vidas<8) { Nave.Vidas++; strcpy(MENSAJES,"#: VIDA EXTRA");}
	   else { Nave.Titilando=1; strcpy(MENSAJES,"#: MODO INVENSIBLE ACTIVADO");}
    break;
    //si es le pone las vidas al maximo o le resta vidas
    case 3: if (Nave.Vidas==0) { Nave.Vidas=4; strcpy(MENSAJES,"#: VIDAS EXTRA"); }
	    else { Nave.Vidas++; strcpy(MENSAJES,"#: VIDA EXTRA"); }
    break;
  }
}
//*************************************************************************
void Cambiar_Mensajes()
{
 char *Msg[10]=  //mensajes que puede tomar la variable mensajes
	{
  "TIERRA: Alerta Comandante","TIERRA: Enemigos a la vista",
  "TIERRA: Comandante Salve la Tierra","TIERRA: Marcianos destruidos",
  "TIERRA: ¨Conquistaran la Tierra?","TIERRA: Al Ataque",
  "MARTE: RINDANSE TERRICOLAS", "MARTE: Acabaremos con ustedes",
  "MARTE: la tierra es nuestra", "MARTE: Destruiremos tu #"};
 int numero; //para seleccionar cual mensaje
 numero=random(10); //se selecciona aleatoriamente
 strcpy(MENSAJES,Msg[numero]); //se copia el mensaje aleatoria a la variable global
}
//*************************************************************************
void Configurar_Dificultad()
{
 switch(DIFICULTAD) //dependiendo de que dificultad se haya escojido en el menu de opciones
   {
     case 0: //si es facil
	   if (PRIMERA_VEZ OR CONTINUE_USADO) //si es la primera iteracion del cilco de arriba o acaba de gastar un continue
	       {
		Nave.Vidas=8; //tiene 4 vidas
	       }
	   if (PRIMERA_VEZ) CONTINUES=9;//10 continues
	   Nave.Arma_Actual=1; //emipeza con el arma laser;
	   TURBO+=1;//la velocidad es 1;
	   MAX_ACELERACION=5;//la aceleracion maxima es 5 osea es facil de controlar
	   MAX_TITILANDO=60;//la nave titilara durante 60 cuadros
	   APOYO_ACTIVADO=TRUE; //la nave de apoyo esta activado
	   MAX_MALOS=5; //y solo hay 5 malos
	   MAX_TIEMPO=90; //solo tiene 90 segundos por mundo
     break;
     case 1: //en la dificultad normal
	   if (PRIMERA_VEZ OR CONTINUE_USADO)
	      {
	       Nave.Vidas=4; //emipieza con 2 vidas
	       Nave.Arma_Actual=0; //el arma con el que comieza es el misil
	      }
	   if (PRIMERA_VEZ) CONTINUES=9;//10 continues
	   TURBO+=2; //la velocidad es un poco mas rapida
	   MAX_TITILANDO=30;//la nave titilara durante 30 cuadros
	   MAX_ACELERACION=5; //la aceleracion maxima es
	   APOYO_ACTIVADO=TRUE; //hay apoyo
	   MAX_MALOS=10;//y hay 3 malos
	   MAX_TIEMPO=60; //solo tiene 60 segundos por mundo
     break;
     case 2://en el modo dificil
	   if (PRIMERA_VEZ OR CONTINUE_USADO)
	      {
	       Nave.Vidas=2; //empieza con una vida
	       Nave.Arma_Actual=0; //con el misil
	      }
	   if (PRIMERA_VEZ) CONTINUES=7;//4 continues
	   APOYO_ACTIVADO=FALSE;//sin nave de apoyo
	   MAX_TITILANDO=10;//la nave titilara durante 10 cuadros
	   MAX_ACELERACION=15;//la aceleracion maxima es 15 osea que es bastante dificil controlar la nave
	   TURBO+=2; //y la velocida es muy alta
	   MAX_MALOS=10;//hay 10 malos
	   MAX_TIEMPO=30; //solo tiene 30 segundos por mundo
     break;
   }
 CONTINUE_USADO=FALSE;
}
//*************************************************************************
void Iniciar_Escenario()
{
 char Mundo[20];//variable para escribir el texto del mundo.
 sprintf(Mundo,"Nivel %d",NIVEL);//convierte el numero del nivel en texto con formato
 Poner_Texto(Mundo,120,100,AMARILLO); //coloca el nombre del mundo
 Pintar_Pantalla();//y pinta la pantalla
 Fundido(100,100,100,5);//realiza un fundido para encender la pantalla
 PRIMERA_VEZ=FALSE;//y pone la variable a false para no hacerlo en cada cuadro
 clear_keybuf();
 readkey();
 delay(100);
 clear_keybuf();
}
//*************************************************************************
void Configurar_Password()
{
 if (PRIMERA_VEZ AND PASSWORD_OK) //si es la primera vez del ciclo y el password fue correcto
  {
   NIVEL=(PASSWORD[3])*10+1; //el nivel es el campo 3 del password decodigicado por 10
   DIFICULTAD=PASSWORD[0]; //la dificultad es el campo 0
   CONTINUES=PASSWORD[2];//los continues es el campo 2
   Nave.Vidas=PASSWORD[1];//Las vidas el campo 1
   PUNTUACION=NIVEL*225*(DIFICULTAD+1); //y se hace una aproximacion de la puntuacion
  }
}
//*************************************************************************
//Eso es todo amigos!!!!!!!!!!!!


