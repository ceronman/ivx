//*****************************************************************************
//				MODULO INTERFAZ.CPP
//		Este modulo es el encargado de todo lo que tiene que ver con
//		la interfaz del juego como los menus, las opciones, los cre-
//		ditos etc...
//*****************************************************************************
#include "ivxengin.h"
#include "main.h"
#include "teclado.h"

#include "globales.h"
//incluye las variables globales (declaradas en modulo MAIN) nescesarias para funcionar
//*****************************************************************************
//VARIABLES GLOBALES DEL MODULO
//*****************************************************************************
 SPRITE IVX_LOGO, GANASTE, PERDISTE;//imagenes del logo, y para el triunfo o la derrota
 SPRITE Fondo;//fondo de la presentacion
//*****************************************************************************
//DEFINICION DE FUNCIONES
//*****************************************************************************
void Perder()
{
 BOOL MENU=TRUE;//varibale para la seleccion de men£
 char Texto[30];

 if(CONTINUES<1) Revisar_Records(); //si ya perdio examina si rompio algun record
 
 Fundido(100,20,20,5);//realiza un fundido a rojo para dar dramatismo
 Poner_Sprite(PERDISTE,160,100); //pone la imagen de perder
 
 sprintf(Texto,"CONTINUES : %d",CONTINUES); //imprime cuantos
 Poner_Texto(Texto,50,140,BLANCO);	    //Continues le quedan	
 if (CONTINUES>0) //si todavia le quedan
    {
     Poner_Texto("¨Desea Continuar?",50,150,BLANCO);//pregunta si quiere continuar
     Poner_Texto("S : Si",90,160,BLANCO);
     Poner_Texto("N : No",90,170,BLANCO);
    }
  else Poner_Texto("Presiona ESCAPE para SALIR",90,170,BLANCO); //de lo contrario
 //escribe si se quiere salir
 Pintar_Pantalla();
 while (MENU)//hasta que escoja una opcion
   {
    if (keys[KEY_N] OR keys[KEY_ESC])
       {
	NIVEL=1; //si es "N" se sale
	PRIMERA_VEZ=TRUE; //y vuelve y comienza todo
	MENU=FALSE; //se termina el menu
       }

    if (keys[KEY_S] AND CONTINUES>0) //si es "s"
       {
	MENU=FALSE; //se sale del menu
	CONTINUES--;//se le resta un continue
	CONTINUE_USADO=TRUE; //y la variable continue usado se pone a VERDADERO para renovar la vidas
       }
    //si es "S" y si tiene sufucionetes continues sigue tranquilamente
   }
}
//*************************************************************************
void Ganar()
{
 char Texto_Password[30];
 if (NIVEL%10==0) //cada 10 niveles;
    {
     PASSWORD[0]=9-DIFICULTAD; //|
     PASSWORD[1]=9-Nave.Vidas; //|
     PASSWORD[2]=9-CONTINUES;  //crea una contrase¤a
     PASSWORD[3]=9-NIVEL/10;   //para continuar en otro momento
     PASSWORD[4]=DIFICULTAD+2; //|
     PASSWORD[5]=NIVEL-1;  //|
     sprintf(Texto_Password,"Password: %d%d%d%d%d%d",PASSWORD[0],PASSWORD[1],PASSWORD[2],PASSWORD[3],PASSWORD[4],PASSWORD[5]);
     Poner_Texto_Sombra(Texto_Password,100,140,BLANCO,ROJO); //escribe texto
    }
 Poner_Sprite(GANASTE,160,100);//pone la imagen de triunfo
 Poner_Texto_Sombra("Presiona ENTER para Continuar",50,180,BLANCO,ROJO); //escribe texto
 Pintar_Pantalla();//pinta la pantalla
 while(!keys[KEY_ENTER]); //espera a que presione enter.
 if (NIVEL==90) Final();
 if (NIVEL<90) NIVEL++;
 Fundido(0,0,0,5);
}
//*************************************************************************
void Pantalla_Inicio()
{
 BOOL MENU=FALSE; //una variable para el menu
 //Carga el fondo del disco.

 PUNTUACION=0;
 Fondo=Cargar_Imagen("IVXGRAF\\presenta.ivx");
 Cargar_Paleta("IVXGRAF\\paleta2.pal");//carga una nueva paleta
 Fundido(0,0,0,0);
 Poner_Fondo(Fondo);
 Pintar_Pantalla();//pinta la pantalla
 Fundido(100,100,100,5);
 while (!MENU) //mientras el menu este falso
    {
     switch( Menu_Principal() ) //examina el resultado del menu principal
       {
	case 0:
	      MENU=TRUE; //si es 0 se va al juego
	break;
	case 1://si escojio la opcion 1 se va al menu de opciones
	      Menu_Opciones();
	break;
	case 2://si es 2 se va a las opciones
	      Creditos();
	break;
       }
    }
 Fundido(0,0,0,5); //realiza un fundido a negro
 Limpiar_Pantalla(0);//limpia la pantalla
 Pintar_Pantalla();//Pinta la pantalla negra con el fin de que no se vean cosas feas
 Cargar_Paleta("IVXGRAF\\paleta.pal"); //cambia a la paleta principal
 Fundido(0,0,0,0);//realiza con la paleta principal un fundido a negro.
		  //que se volvera al color normal gracias a la variable FUNDIR
 Libera_Sprite(Fondo);
}
//*************************************************************************
void Menu_Opciones()
{
 BOOL Menu=FALSE; //para saber cuando se acaba el menu
 int Opcion=0; //para saber cual opcion se escojio
 int Color[6]; //Para pintar diferente la opcion necesitada
 int cont; //simple contador
 BOOL Presionado=FALSE;
 BOOL Fundir=TRUE;

 char *Dificul[3]={"Facil","Medio","Dificil"}; //Las diferentes clases de dificultades

 int Indice_Dificultad=DIFICULTAD, Indice_Estrellas=ESTRELLAS_ACTIVADAS,Indice_Mensajes=MENSAJES_ACTIVADOS;
 //las diferentes opciones que se pueden escojer

 char *On_OFF[2]={"OFF","ON"}; //las posiblilidades que tienen algunas opciones

 char *Mensaje_Ayuda[6]={"Selecciona que tan dificl es el juego",
			 "Prende o apaga las estrellas del fondo",
			 "Poner o quitar los mensajes de arriba",
			 "Ingresa el codigo de un mundo anterior ",
			 "Mira las mejores puntuaciones",
			 "Regresa al menu principal"};

 Fundido(0,0,0,5);
 while(!Menu AND !SALIR) //mientras no termine el menu (se escoja la opcion de salir)
   {
    Limpiar_Pantalla(0); //Limpia la pantalla
    for(cont=0;cont<6;cont++) Color[cont]=122; //y pone todos los colores a verde
    Color[Opcion]=219; //la opcion seleccionada tiene color amarillo
    i=0;Poner_Estrellas(); //pone las estrellas y pone i a 0 para que se muevan (solo un adorno)

    Poner_Texto(Mensaje_Ayuda[Opcion],10,190,AMARILLO);
    Poner_Texto("Presiona F1 para Ayuda",10,5,AMARILLO);

    Poner_Texto("Menu de Opciones",100,20,BLANCO); //Pone el titulo
    Poner_Texto("Dificultad",80,60,Color[0]); //dificultad
    Poner_Texto(Dificul[Indice_Dificultad],250,60,AMARILLO);//y al lada el tipo de dificultad actual
    Poner_Texto("Estrellas de fondo",80,80,Color[1]);//Estrellas de fondo
    Poner_Texto(On_OFF[Indice_Estrellas],250,80,AMARILLO);//y al lado las opciones ON OFF que puede tener las estrellas de fondo
    Poner_Texto("Mensajes",80,100,Color[2]); //mensajes
    Poner_Texto(On_OFF[Indice_Mensajes],250,100,AMARILLO);//y al lado el modo
    Poner_Texto("Ingresar Password",80,120,Color[3]); //para ingresar un password
    Poner_Texto("Ver Records",80,140,Color[4]); //para ingresar un password
    Poner_Texto("Volver a Pricipal",80,160,Color[5]); //por ultimo la opcion de volver al menu principal
    if (keys[KEY_ENTER]) //si presiona enter
       {
	switch(Opcion)//Examina la opcion actual
	  {
	   case 0://si es la de dificultad
		 delay(100);
		 Indice_Dificultad++;//sube el indice solo si es menor que 3 por que solo hay 3 opciones
		 if (Indice_Dificultad>2) Indice_Dificultad=0;
	   break;
	   case 1://si es el de estrellas
		 delay(100);
		 Indice_Estrellas++;//sube el indice si es menor que 2
		 if (Indice_Estrellas>1) Indice_Estrellas=0;
	   break;
	   case 2://si es el de mensajes
		 delay(100);
		 Indice_Mensajes++;//sube el indice si es menor que 2
		 if (Indice_Mensajes>1) Indice_Mensajes=0;
	   break;
	   case 3://si es el de ingresar el password
		  Obtener_Password();
	   break;
	   case 4://si es el de volver a la pantalla principal se sale del menu
		 Mostrar_Records();
		 delay(100);
	   break;
	   case 5://si es el de volver a la pantalla principal se sale del menu
		 Menu=TRUE;
	   break;
	  }
       }
     if (keys[KEY_UP]) { Opcion--; Presionado=TRUE;  }//si presiona arriba la opcion disminuye
     if (keys[KEY_DOWN]) { Opcion++; Presionado=TRUE; } //si presiona abajo la opcion aumenta
     if (keys[KEY_F1] OR keys[KEY_ESC]) Ayuda(1);
     if (Opcion<0) Opcion=0; //la opcion no puede ser menor que 0
     if (Opcion>5) Opcion=5; //o mayor que 3
     if (Presionado)
	{
	 delay(200);//espera un tiempo para que el teclado no sea tan sencible
	 Presionado=FALSE;
	}
     Pintar_Pantalla();  //pinta la pantalla
     if (Fundir) Fundido(100,100,100,5);
     Fundir=FALSE;
  }
 MENSAJES_ACTIVADOS=Indice_Mensajes; //las variables de control se cambian de acuerdo a las opciones escojidas
 ESTRELLAS_ACTIVADAS=Indice_Estrellas;
 DIFICULTAD=Indice_Dificultad;
 Fundido(0,0,0,5);
 Poner_Fondo(Fondo);
 Pintar_Pantalla();//pinta la pantalla
 Fundido(100,100,100,5);
}
//*************************************************************************
int Menu_Principal()
{
 SPRITE Jugar, Opciones, Creditos; //Estas son las imagenes de las opciones del menu principal
 int Escala[3];//3 escalas para las 3 opciones diferentes
 BOOL MENU=FALSE; //variable para controlar el menu
 int Opcion=0;//para saber que opcion se escojio
 int cont;//simple contador
 BOOL Presionado=FALSE;
 char *Mensaje_Ayuda[3]={"Comienza el juego", "Configura la dificultad y otras cosas", "Los creadores de este juego tan bacano"};

 Jugar=Cargar_Imagen("IVXGRAF\\jugar.ivx");
 Opciones=Cargar_Imagen("IVXGRAF\\opciones.ivx");//Carga las imagenes de las
 Creditos=Cargar_Imagen("IVXGRAF\\creditos.ivx");//opciones del menu

 while (!MENU AND !SALIR) //mientras no se haya seleccionado ninguna opcion
    {
     Poner_Fondo(Fondo);//coloca la pantalla de fondo
     for (cont=0;cont<3;cont++) Escala[cont]=60;//primero todas las escalas son 60
     Escala[Opcion]=100;//la escala de la opcion es 100 osea mas grande;
     Poner_Sprite(Jugar,240,80,Escala[0],Escala[0]);
     Poner_Sprite(Opciones,240,100,Escala[1],Escala[1]); //coloca las imagens de
     Poner_Sprite(Creditos,240,120,Escala[2],Escala[2]);//las opciones
     Poner_Texto("Presiona F1 para Ayuda",10,5,BLANCO);
     Poner_Texto(Mensaje_Ayuda[Opcion],10,190,BLANCO);
     if (keys[KEY_ENTER]) MENU=TRUE; //si presiona enter se termina el menu
     if (keys[KEY_UP]) { Opcion--;  Presionado=TRUE; }//si presiona arriba la opcion disminuye
     if (keys[KEY_DOWN]) { Opcion++; Presionado=TRUE; } //si presiona abajo la opcion aumenta
     if (Opcion<0) Opcion=0; //controla que la opcion no se salga de los limites
     if (Opcion>2) Opcion=2;
     if (keys[KEY_ESC] OR keys[KEY_F1])
	{
	 MENU=TRUE;
	 Ayuda(1);//si presiona escape o F1 se va a la ayuda
	 Opcion=3;
	}
     Pintar_Pantalla();//pone  la informacion en la pantalla
     if (Presionado)
	{
	 delay(200);//espera un tiempo para que el teclado no sea tan sencible
	 Presionado=FALSE;
	}
    }
 Libera_Sprite(Jugar);//libera la memoria de los graficos
 Libera_Sprite(Opciones);
 Libera_Sprite(Creditos);
 return Opcion; //regresa la opcion seleccionada
}
//*************************************************************************
void Ayuda(int Tipo_Ayuda)
{
 BOOL MENU=TRUE;//variable para el menu
 BOOL Fundir=TRUE;
 Fundido(0,0,0,5);
 while (MENU)
   { //hasta que escoja una opcion
    Limpiar_Pantalla(0);//limpia la pantalla
    i=0;Poner_Estrellas();
    Poner_Texto("Ayuda",120,15,219); //coloca el titulo

    switch(Tipo_Ayuda)
      {
       case 0:
	  Poner_Texto("Uso de la Nave:",30,40,AMARILLO); //coloca la ayuda
	  Poner_Texto("Se mueve con las flechas y dispara",40,50,BLANCO); //coloca la ayoda
	  Poner_Texto("con espacio.",40,60,BLANCO);
	  Poner_Texto("disparandole a la nave que sale por",40,70,BLANCO);
	  Poner_Texto("arriba se obtiene un bonus, que ",40,80,BLANCO);
	  Poner_Texto("que puede ser vidas extras o una" ,40,90,BLANCO);
	  Poner_Texto("arma mas poderosa",40,100,BLANCO);
	  Poner_Texto("USA -P- Para poner PAUSA",40,110,BLANCO);
       break;
       case 1:
	  Poner_Texto("Uso del MENU:",30,40,122); //coloca la ayuda
	  Poner_Texto("Utiliza arriba y abajo",40,50,BLANCO); //coloca la ayoda
	  Poner_Texto("para moverte en el menu",40,60,BLANCO);
	  Poner_Texto("y usa enter para seleccionar",40,70,BLANCO);
	  Poner_Texto("Una opcion.",40,80,BLANCO);
	  Poner_Texto("En la parte inferior hay",40,90,BLANCO);
	  Poner_Texto("una descripcion de cada item",40,100,BLANCO);
       break;
    }
    Poner_Texto("Durante cualquier momento presionar",30,130,AMARILLO);
    Poner_Texto("ESC o F1 para Ayuda",30,140,AMARILLO); //coloca la ayuda
    Poner_Texto("¨Desea Salir del Juego?",50,160,BLANCO); //pregunta si quiere salir
    Poner_Texto("S : Si",90,170,BLANCO);
    Poner_Texto("N : No",90,180,BLANCO);

    Pintar_Pantalla(); //pinta la pantalla
    if (Fundir) Fundido(100,100,100,5);
    Fundir=FALSE;
    if (keys[KEY_S])
       {
	SALIR=TRUE; //si es "s" se sale
	MENU=FALSE;
       }
    if (keys[KEY_N]) MENU=FALSE; //si es "N" sigue tranquilamente
   }
 Tiempo_Inicial=time(NULL)-(60-TIEMPO);
 Fundido(0,0,0,5);
 Limpiar_Pantalla(0);
 Pintar_Pantalla();
 Fundido(100,100,100,0);
}
//*************************************************************************
void Creditos()
{
 int x=40,y=230; //Posiciones iniciales
 int ESP=15;//espaciado entre letras
 BOOL FIN=FALSE; //para saber cuando se termina el ciclo

 Fundido(0,0,0,10);
 while (!FIN)//mientras no termine
  {
   Limpiar_Pantalla(0);//limpia la pantalla
   i=0;Poner_Estrellas();//pone estrellas de fondo
   Poner_Texto("#   INVAXION MARICIANA IVX   # "  ,x,y-2*ESP,BLANCO); //creditos
   Poner_Texto("Dise¤o y programacion:"       ,x,y+ESP,122);
   Poner_Texto("Manuel Alejandro Ceron"       ,x+40,y+2*ESP,219);
   Poner_Texto("Dise¤o Grafico:"              ,x,y+6*ESP,122);
   Poner_Texto("Manuel Alejandro Ceron"       ,x+40,y+7*ESP,219);
   Poner_Texto("Die¤o de escenarios"          ,x,y+9*ESP,122);
   Poner_Texto("Manuel Alejandro Ceron"       ,x+40,y+10*ESP,219);
   Poner_Texto("Juan Camilo Ceron"            ,x+40,y+11*ESP,219);
   Poner_Texto("Carlos Andres Bernal"         ,x+40,y+12*ESP,219);
   Poner_Texto("Edwin Fernando Lara "         ,x+40,y+13*ESP,219);
   Poner_Texto("Historia:"                    ,x,y+15*ESP,122);
   Poner_Texto("Manuel Alejandro Ceron"       ,x+40,y+16*ESP,219);
   Poner_Texto("Carlos Andres Bernal"         ,x+40,y+17*ESP,219);
   Poner_Texto("Edwin Fernando Lara "         ,x+40,y+18*ESP,219);
   Poner_Texto("Idea Original:"               ,x,y+20*ESP,122);
   Poner_Texto("SPACE INVADERS"               ,x+40,y+21*ESP,219);
   Poner_Texto("Toshihiro Nishikado"          ,x+40,y+22*ESP,219);
   Poner_Texto("Taito 1978"                   ,x+40,y+23*ESP,219);
   Poner_Texto("Agradecimientos:"             ,x,y+25*ESP,122);
   Poner_Texto("Dhonn Lushine"                ,x+40,y+26*ESP,219);
   Poner_Texto("Por su libreria de teclado"   ,x+50,y+27*ESP,AMARILLO);
   Poner_Texto("Benjamin Moreno Placios"      ,x+40,y+28*ESP,219);
   Poner_Texto("Jesus Angel Sanchez Mena"     ,x+40,y+29*ESP,219);
   Poner_Texto("Por su Curso de Programacion" ,x+50,y+30*ESP,AMARILLO);
   Poner_Texto("de Videojuegos"               ,x+50,y+31*ESP,AMARILLO);
   Poner_Texto("PabloSoft Entertaiment"       ,x+40,y+32*ESP,219);
   Poner_Texto("Por su curso de juegos en c"  ,x+50,y+33*ESP,AMARILLO);
   Poner_Texto("Juan Camilo Ceron"            ,x+40,y+34*ESP,219);
   Poner_Texto("Por su apoyo e ideas"         ,x+50,y+35*ESP,AMARILLO);
   Poner_Texto("#       IVX SOFTWARE 2002       # " ,x,y+37*ESP,BLANCO);
   Poner_Texto("# todos los derechos reservados # " ,x,y+38*ESP,BLANCO);
   y--; //y va disminuyendo para que los textos suban
   if (y<-(38*ESP)-8) FIN=TRUE; //si termino se acaba
   if (keys[KEY_ENTER]) FIN=TRUE;//si presiona enter tambien
   Pintar_Pantalla();//pinta la pantalla;
   if (y==229) Fundido(100,100,100,10);
   delay(RETRAZO);
  }
 Limpiar_Pantalla(0);
 Pintar_Pantalla();//pinta la pantalla
 Fundido(100,100,100,0);
}
//*************************************************************************
void Obtener_Password()
{
 int cont; //contador
 char Digito; //digito leido
 char Texto[10];//texto para converisones
 BOOL FIN=FALSE;//para controlar el ciclo

 for (cont=0;cont<6;cont++) PASSWORD[cont]=0; //incializa a 0
 sprintf(Texto,"%d%d%d%d%d%d",PASSWORD[0],PASSWORD[1],PASSWORD[2],PASSWORD[3],PASSWORD[4],PASSWORD[5]);
 Poner_Texto(Texto,250,120,AMARILLO); //coloca el password en 000000
 Pintar_Pantalla();
 for (cont=0;cont<6;cont++)//recorre el password
   {
     delay(500); //controla la velocidad
     while(!FIN)
      {
       Digito=Char_a_Int(LeerKey()); // va leyendo cada una de los digitos
       if (Digito>=0) FIN=TRUE;
      }
     FIN=FALSE;
     Poner_Texto(Texto,250,120,NEGRO); //de nuevo coloca el texto
     PASSWORD[cont]=Digito;
     sprintf(Texto,"%d%d%d%d%d%d",PASSWORD[0],PASSWORD[1],PASSWORD[2],PASSWORD[3],PASSWORD[4],PASSWORD[5]);
     Poner_Texto(Texto,250,120,AMARILLO); //y lo va actualizando
     //muestra en pantalla lo digitado;
     Pintar_Pantalla();
    }
  for (cont=0;cont<4;cont++)
      {
       PASSWORD[cont] = 9-PASSWORD[cont]; //decodifica el password
	      }
  if ( (PASSWORD[4]-2)==PASSWORD[0] AND	  //y lo examina para saber si es correcto
       (PASSWORD[5]+1)==PASSWORD[3]  )
     {
      Poner_Texto("OK",300,120,AMARILLO);//si es correcto escribe OK
      PASSWORD_OK=TRUE;
     }
  else
    {
     Poner_Texto("NO",300,120,AMARILLO); //Si es incorrecto escribe NO
     PASSWORD_OK=FALSE;
    }
  Pintar_Pantalla();
  delay (1000);
}
//*************************************************************************
void Revisar_Records()
{
 FILE *Archivo;		//Archivo de records
 char *Nombres[10];	//Donde se guardan los nombres
 long int Puntos[10];	//Los puntos
 int cont, cont2;	//contadores
 int Fin_Archivo;	//controla el fin del archivo
 char Texto[50];	//para conversiones
 BOOL RECORD=FALSE;	//para saber si hizo un nuevo record

 for (cont=0;cont<10;cont++) //recorre los nombres
     {
      if (  (Nombres[cont]=new char[50]) == NULL )  //reserva memoria
	 {
	  Finalizar();
	  cout<<"No hay memoria suficiente para cargar los records";
	 }
     }
 Archivo=fopen("IVXDATOS\\records.dat","r"); //abre el archivo
 if (Archivo==NULL)
     {
      Finalizar();
      cout<<"No se pudo cargar los records";
     }
 cont=0;
 while(!feof(Archivo)) //mientras no se termine
   {
    fscanf(Archivo,"%s",Nombres[cont]); //leer los datos
    fscanf(Archivo,"%d",&Puntos[cont]);
    if (cont<10) cont++;
   }
 Fin_Archivo=cont;//se guarda el fin del archivo
 fclose(Archivo);//se sierra el archivo
 for (cont=0;cont<10;cont++) //recorre los puntos
     {
      if (PUNTUACION>Puntos[cont]) //examina cada uno de los puntajes
	 {
	  for(cont2=9;cont2>cont;cont2--) //si rompio un record baja los demas records
	     {
	      strcpy(Nombres[cont2],Nombres[cont2-1]);
	      Puntos[cont2]=Puntos[cont2-1];
	     }
	  Poner_Texto_Sombra("has consegido un nuevo record",20,70,AMARILLO,ROJO);
	  Poner_Texto("ingresa tu nombre:",20,80,AMARILLO);
	  Pintar_Pantalla();
	  Leer_Cadena(Texto,170,80,ROJO); //lee el nombre si rompio un record
	  if (Texto[0]==0) strcpy(Texto,"#"); //si no escribio nada pone una navecita
	  strcpy(Nombres[cont],Texto); //copia el texto y la puntuacion
	  Puntos[cont]=PUNTUACION;
	  RECORD=TRUE;
	  cont=9;
	 }
     }
 Archivo=fopen("IVXDATOS\\records.dat","w"); //abre otra vez
 if (Archivo==NULL)
     {
      Finalizar();
      cout<<"No hay se pudo cargar los records";
     }
 for(cont=0;cont<Fin_Archivo;cont++) //escribe los nuevos datos en el archivo
   {
    fprintf(Archivo,"%10s\n",Nombres[cont]);
    fprintf(Archivo,"%d\n",Puntos[cont]);
   }
 fclose(Archivo); //cierra
 if (RECORD) Mostrar_Records(); //y si hizo un nuevo record muestra los records
 for (cont=0;cont<10;cont++) delete Nombres[cont]; //libera la memoria
}
//*************************************************************************
void Mostrar_Records()
{
 FILE *Archivo; //archivo
 char *Nombres[10]; //donde se guardan los nombres
 long int Puntos[10]; //los puntos
 int cont; //contador
 char Texto[10]; //variable para guardar texto
 int Fin_Archivo;// variable para saber cuando se finaliza el archivo
 BOOL Fundir=TRUE; //variable para realizar un fundido

 Fundido(0,0,0,5); //funde a negro

 for (cont=0;cont<10;cont++)//asigna memoria
     {
      if (  (Nombres[cont]=new char[50]) == NULL )
	 {
	  Finalizar();
	  cout<<"No hay memoria suficiente para cargar los records";
	 }
     }
 Archivo=fopen("IVXDATOS\\records.dat","r");//abre el archivo
 if (Archivo==NULL)
     {
      Finalizar();
      cout<<"No se pudo cargar los records";
     }
 cont=0;
 while(!feof(Archivo)) //mientras no termine el archivo
   {
    fscanf(Archivo,"%s",Nombres[cont]); //lee los nombres
    fscanf(Archivo,"%d",&Puntos[cont]); //y los puntajes de los records
    if (cont<10) cont++; //si es menor que 10 el contador aumenta
   }
 Fin_Archivo=cont;//el archivo tiene tantas lineas como indica el contador
 fclose(Archivo);//cierra el archivo
 Limpiar_Pantalla(0);
 delay(500);//espera un tiempo para que no sea tan largo el proceso
 while (!keys[KEY_ENTER])//mientras no presione enter
    {
     Limpiar_Pantalla(0); //limpia
     i=0;Poner_Estrellas();//y pone las estrellas
     Poner_Texto_Sombra("RECORDS",120,40,AMARILLO,ROJO); //pone el titulo
     Poner_Texto_Sombra("Presiona Enter Para Continuar",60,180,AMARILLO,ROJO);
     //y pone el mensaje para que continue
     for (cont=0;cont<Fin_Archivo;cont++)//mientras no termine el archivo
	{
	 Poner_Texto(Nombres[cont],80,60+(cont*10),AMARILLO); //pone los nombres
	 sprintf(Texto,"%d",Puntos[cont]);
	 Poner_Texto(Texto,180,60+(cont*10),ROJO); //y pone los puntos en pantalla
	}
     Pintar_Pantalla(); //pinta para que todo se vea
     if (Fundir) Fundido(100,100,100,5); //y si es la primera vez del ciclo prende la pantalla
     Fundir=FALSE;
    }
 for (cont=0;cont<10;cont++) delete Nombres[cont]; //libera la memoria
}
//*************************************************************************
void Presentacion()
{
 SPRITE Logo_Ucauca, Logo_Ivx_Software; //el logo de ucauca y el de ivx software

 int Escala=100; //variable para sobreescalar el logo y dar la impresion de explosion
 BOOL Explosion=FALSE; //para saber cuando debe explotar
 int Logo_Aceleracion=-8; //para saber cuanta es la aceleracion de la explosion
 int Logo_Y=50; //posicion y del logo
 int Nave_X=-20; //posicion x de la nave
 int Nave_Frame=7; //imagen de la nave
 BOOL FIN=FALSE; //para saber cuando terminar el ciclo
 int cont=0; //simple contador

 Logo_Ucauca=Cargar_Imagen("IVXGRAF\\ucauca.ivx");//carga el logo de ucauca
 Logo_Ivx_Software=Cargar_Imagen("IVXGRAF\\logo.ivx");//carga el logo de ivxsoftware
 Limpiar_Pantalla(0);
 Pintar_Pantalla();
 Fundido(0,0,0,0);//apaga la pantalla
 Limpiar_Pantalla(BLANCO);
 Poner_Sprite(Logo_Ucauca,160,100);//coloca el logo de ucauca
 Poner_Texto("Universidad del Cauca 2002",55,10,GRIS);
 Poner_Texto("Presione Una tecla para Continuar",30,190,GRIS);
 Pintar_Pantalla();
 Fundido(100,100,100,20);//apaga
 LeerKey();//espera a que se presione una tecla
 Fundido(0,0,0,20);
 Limpiar_Pantalla(0);
 Poner_Sprite(Logo_Ivx_Software,160,50);
 Pintar_Pantalla();
 Fundido(100,100,100,20);
 Inicializar_Datos();
 delay(500);
 while(!FIN)
   {
    Limpiar_Pantalla(0);
    Poner_Sprite(Logo_Ivx_Software,160,Logo_Y,Escala,Escala);
    Poner_Sprite(Nave.Imagen[Nave_Frame],Nave_X,175);
    if (Nave_X<160) Nave_X+=3;
    else
      {
       if (!Nave.Disparo AND !Explosion) Activar_Disparo();
       if (Nave.Disparo) Disparar();
       if (Nave_Frame>4) Nave_Frame--;
      }
    if (  Colision(Nave.Imagen_Disparo[0],Nave.Disparo_X,Nave.Disparo_Y,Logo_Ivx_Software,160,Logo_Y)  )
       {
	Explosion=TRUE;
       }

    if (Explosion)
       {
	delay(5);
	if (cont%5==0) Logo_Aceleracion+=2;
	if (Logo_Y<600)
	   {
	    Escala+=2;
	    Logo_Y+=Logo_Aceleracion;
	   }
	else FIN=TRUE;
       }

    cont++;
    Pintar_Pantalla();
   }
 Fundido(0,0,0,20);
 Limpiar_Pantalla(0);
 Pintar_Pantalla();
 Libera_Sprite(Logo_Ucauca);
 Libera_Sprite(Logo_Ivx_Software);
}
///*************************************************************************
void Historia()
{
 int x=20,y=230; //Posiciones iniciales
 int ESP=15;//espaciado entre letras
 BOOL FIN=FALSE; //para saber cuando se termina el ciclo

 while (!FIN)//mientras no termine
  {
   Limpiar_Pantalla(0);//limpia la pantalla
   i=0;Poner_Estrellas();//pone estrellas de fondo
   Poner_Texto("En el a¤o 2084 Todo era pacifico"  ,x,y-2*ESP,AMARILLO);
   Poner_Texto("en el planeta tierra, hasta que el"  ,x,y-1*ESP,AMARILLO);
   Poner_Texto("17 de octubre la sonda espacial MAC"  ,x,y,AMARILLO);
   Poner_Texto("detecto una enorme masa verde que"  ,x,y+1*ESP,AMARILLO);
   Poner_Texto("provenia de marte.   Antes que los"  ,x,y+2*ESP,AMARILLO);
   Poner_Texto("cientificos pudieran averiguar que"  ,x,y+3*ESP,AMARILLO);
   Poner_Texto("era,  salieron de ella millones de"  ,x,y+4*ESP,AMARILLO);
   Poner_Texto("criaturas extra¤as que inmediata-"  ,x,y+5*ESP,AMARILLO);
   Poner_Texto("mente empezaron a destruir todo lo"  ,x,y+6*ESP,AMARILLO);
   Poner_Texto("que en contraron a su camino.  "  ,x,y+7*ESP,AMARILLO);
   Poner_Texto("poco a poco se iban acercando ca-"  ,x,y+8*ESP,AMARILLO);
   Poner_Texto("da vez mas a la tierra. rapidamen-"  ,x,y+9*ESP,AMARILLO);
   Poner_Texto("destruyeron los ejercitos de las"  ,x,y+10*ESP,AMARILLO);
   Poner_Texto("potencias mas poderosas del mundo."  ,x,y+11*ESP,AMARILLO);
   Poner_Texto("desde el espacio lanzaban enormes"  ,x,y+12*ESP,AMARILLO);
   Poner_Texto("bolas rojas de fuego que empezaron"  ,x,y+13*ESP,AMARILLO);
   Poner_Texto("a destruir la ciudades mas grandes"  ,x,y+14*ESP,AMARILLO);
   Poner_Texto("del mundo."  ,x,y+15*ESP,AMARILLO);
   Poner_Texto("la tierra entera estaba llena de"  ,x,y+16*ESP,AMARILLO);
   Poner_Texto("panico, todos creian que era el fin"  ,x,y+17*ESP,AMARILLO);
   Poner_Texto("del planeta tierra."  ,x,y+18*ESP,AMARILLO);
   Poner_Texto("Hasta que depronto surgio una es-"  ,x,y+19*ESP,AMARILLO);
   Poner_Texto("peranza,  el coronel IVX,  consi-"  ,x,y+20*ESP,AMARILLO);
   Poner_Texto("derado como el mejor piloto del "  ,x,y+21*ESP,AMARILLO);
   Poner_Texto("mundo, a bordo de la nueva super"  ,x,y+22*ESP,AMARILLO);
   Poner_Texto("nave de combate espacial creada por"  ,x,y+23*ESP,AMARILLO);
   Poner_Texto("la O.N.U. la #F-413."  ,x,y+24*ESP,AMARILLO);
   Poner_Texto("El coronel IVX acepto la mision y"  ,x,y+25*ESP,AMARILLO);
   Poner_Texto("despego hacia la orbita de la tie-"  ,x,y+26*ESP,AMARILLO);
   Poner_Texto("rra para destruir  a los marcianos"  ,x,y+27*ESP,AMARILLO);
   Poner_Texto("y devolverle la paz a la tierra..."  ,x,y+28*ESP,AMARILLO);

   y--; //y va disminuyendo para que los textos suban
   if (y<-(28*ESP)-8) FIN=TRUE; //si termino se acaba
   if (keys[KEY_ENTER]) FIN=TRUE;//si presiona enter tambien
   Pintar_Pantalla();//pinta la pantalla;
   if (y==229) Fundido(100,100,100,10);
   delay(RETRAZO);
  }
 Limpiar_Pantalla(0);
 Pintar_Pantalla();//pinta la pantalla
 Fundido(100,100,100,0);
}
///*************************************************************************
void Final()
{
 SPRITE Final;
 Final=Cargar_Imagen("IVXGRAF\\final.ivx");
 Fundido(0,0,0,20);
 Limpiar_Pantalla(0);
 Poner_Sprite(Final,160,100);
 Pintar_Pantalla();
 Fundido(100,100,100,20);
 LeerKey();
 Creditos();
 Libera_Sprite(Final);
 SALIR=TRUE;
}
