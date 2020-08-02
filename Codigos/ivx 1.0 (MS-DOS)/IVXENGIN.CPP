/*IVX ENGINE VERSION 1.0

	Esta es la tercera version del motor creado especificamente para el desarrollo
	del juego Invasion Marciana IVX creado como proyecto de semestre de la materia
	introduccion a la informatica de primer semestre de ingenieria de sistemas de
	la Universidad del Cauca (Colombia) por Manuel Alejandro Ceron pero se espera 
	que este motor grafico pueda servir para el desarrollo de otros futuros juegos.
	Esta desarrollado para el entorno Turbo C++ 3.0 pero no debe ser muy dificil de
	adaptarlo a otro entorno.
	Este motor NO esta desarrollado con la Interfaz Grafica de Borland (BGI) sino
	que esta desarrollado usando directamente la targeta de video (VGA) de forma
	estandar para todos los PC, la razon para no usar las BGI es que estas son muy
	lentas y no permiten la tecnica llamada "Duble Buffering" para evitar el parapdeo
	detallada mas abajo.
	Ademas el junto con el motor se ha desarrollado un tipo de archivos *.ivx el cual
	servira para obtener los graficos para el juego.

	Cambios desde la ultima version
		- Coregidos errores y mejor documentado el codigo.
 */
#include"ivxengin.h"
#include"teclado.h"
extern keys[128];
//contiene las declaraciones de funciones constantes y demas cosas

//******************************************************************
//** VARIABLES GLOBALES
//*****************************************************************
 COLOR *BUFFER = NULL ; //Pantalla Virtual donde se escribiran los datos antes
				 //de pasarlos a la pantalla real
 char *CARACTERES = NULL ; //Aqui se almacenaran las fuentes del juego que se cargan desde un archivo

 COLOR *_VGA = DIRECCION_MEMORIA_PANTALLA;//Puntero con la direccion de memoria
                                         //de la pantalla real

 RGB PALETA[256], BPALETA[256]; //Para almacenar las paletas de colores

//******************************************************************
//******************************************************************

//DEFINICION DE LAS FUNCIONES
  void Inicia_VGA()
  {
	FILE* Archivo_Fuentes;

        CARACTERES = new char[8*8*45];//pide memoria para 45 caracteres de 8*8
	BUFFER = new COLOR[ SIZE_PANTALLA ]; //Asigna la memoria necesaria para el buffer
													 //Equivalente a 320*200 bytes


	if (!( Archivo_Fuentes=fopen("IVXDATOS\\fuente.car","rb")) ) //Abre el archivo de fuentes
                {
		 cout<<"Error: no se encuntra el archivo de la fuente";
		 exit(1);
		}

	fread(CARACTERES,1,8*8*45,Archivo_Fuentes);  //Lee las imagenes de la letra del archivo

	if (BUFFER==NULL OR CARACTERES==NULL)
	  {
                cout<<"No hay memoria sufuciente para iniciar el modo grafico";
		exit(1);
	  }
	Limpiar_Pantalla(0);

	asm xor ax, ax;
	asm mov ax, 0x13;       //Entra en el modo grafico
	asm int 0x10;
  }

  //******************************************************************
  void Cierra_VGA()
        {
         delete BUFFER;    //libera la memoria
	 delete CARACTERES;
	 asm xor ax, ax;
	 asm mov ax, 0x03;  //vuelve al modo de texto
	 asm int 0x10;
	}

  //******************************************************************

  void Pixel(int iX, int iY, COLOR cColor)
	{
         if (iX < 0  OR  iX >= ANCHO_PANTALLA   OR   iY < 0  OR   iY  >= ALTO_PANTALLA) return;  //si no se sale de la pantalla
         else BUFFER[ ANCHO_PANTALLA *iY+iX ]=cColor;                   //pinta un punto
        }

  //******************************************************************

  SPRITE  Cargar_Imagen(char cRuta[])
	{
	 SPRITE sTemp;    // Variable temporal donde se guardan lo datos que se retornan
         FILE *fArchivo;  // Archivo
	 int Tamano=0;   // Variables

         fArchivo = fopen(cRuta, "rb");
         if (fArchivo == NULL)
             {                   //abre el archivo y si no se encuentra lanza un mensaje
                cout<<"error, no se encuentra el archivo: "<<cRuta;
		getch();
		return sTemp;
	     }
	 fread(&sTemp.Ancho,2,1,fArchivo); //Obtiene del archivo los valores
	 fread(&sTemp.Alto,2,1,fArchivo);  //del ancho y alto de la imagen

	 Tamano=sTemp.Ancho*sTemp.Alto; //establece el tama¤o de la imagen


         sTemp.Contenido=new COLOR[Tamano];  //reserva memoria para guardar
         if ( sTemp.Contenido==NULL )         //la imagen en memoria
            {
                cout<<"error, no hay memoria suficiente para cargar el archivo: "<<cRuta;
		getch();             //si no hay memoria lanza un mensaje
		return sTemp;
	    }
	 fread(sTemp.Contenido,1,Tamano,fArchivo); //lee el contenido de la imagen
	 fclose(fArchivo);
	 return sTemp;
	}

  //******************************************************************

  void Limpiar_Pantalla(COLOR cColor)
         {
	  memset(BUFFER,cColor,SIZE_PANTALLA);//llena toda la pantalla de un color en
	 }                                                                                                      //especial

  //******************************************************************

  void Poner_Sprite(SPRITE sMap, int CordX, int CordY, double dEscala_x, double dEscala_y)
	 {
          int ContadorX, ContadorY, Color=0; //variables necesarias para los ciclos

          CordX= (int) CordX - (sMap.Ancho / 2) * (dEscala_x / 100);
          CordY= (int) CordY - (sMap.Alto / 2) * (dEscala_y / 100);
          //Esto se hace para que las cordenadas sean en la mitad del dibujo

	  for (ContadorY = 0; ContadorY < sMap.Alto; ContadorY++)
	  {
		for (ContadorX = 0; ContadorX< sMap.Ancho; ContadorX++)
		{
		 if (sMap.Contenido[Color] != 0)
		  {
                        //Ciclo que sirve para poner un punto de acuerdo a como lo lea en
                        //Sprite excepto si es cero
                         Pixel(CordX + (ContadorX * (dEscala_x / 100)), //parametro x
                                         CordY + (ContadorY * (dEscala_y / 100)), //parametro y
                                         sMap.Contenido[Color]);                  //parametro color
		  }
		  //Pone el punto segun la escala y la posicion
		  Color++;
		}
	  }
	 }
  //******************************************************************
  void Pintar_Pantalla()
   {
    memcpy(_VGA,BUFFER,SIZE_PANTALLA); //Pasa el contenido de la pantalla
                                                                                                  //virtual a la pantalla real para
                                                                                                  //crear el efecto conocido como
												  //Double Buffering que hace que la
												  //imagen no parapadee.
   }
  //******************************************************************
  void Poner_Fondo(SPRITE sFondo)
  //simplemente pone un fondo en la pantalla, primero verifica que el Sprite
  //sea del tama¤o de la pantalla y luego copia su contenido a la pantalla virtual
  {
	if (sFondo.Ancho == ANCHO_PANTALLA  AND  sFondo.Alto==ALTO_PANTALLA)
        {
         memcpy(BUFFER,sFondo.Contenido,SIZE_PANTALLA);
        }
  }
  //******************************************************************
  void Cargar_Paleta(char cRuta[])
  {

	COLOR cRojo, cVerde, cAzul; //variables necesarias para el almacenamiento de
	int iNumero;                                    //los colores de la paleta
	FILE *fArchivo;      //archivo de donde se va a cargar la paleta
        fArchivo = fopen(cRuta, "rb"); //abre el archivo
	if (!fArchivo)
                {
                 printf("Imposible cargar la Paleta, no se encuentra el archivo");
		 getch();
		 return;
		}

        for (iNumero = 0; iNumero < 256; iNumero++) //comienza el ciclo son 256 colores
	 {
		outportb(0x3c8, iNumero); //se hace para seleccionar el color a editar en la paleta predeterminada
		cRojo  = getc(fArchivo) / 4; //extrae los colores del archivo y los
		cVerde = getc(fArchivo) / 4; //divide por cuatro por que los colores en
                cAzul  = getc(fArchivo) / 4; //la VGA son hasta 64

                PALETA[iNumero].cRojo  = cRojo;
		PALETA[iNumero].cVerde = cVerde;
		PALETA[iNumero].cAzul  = cAzul; //Guarda los colores en la paleta
		BPALETA[iNumero].cRojo = cRojo; // y la Paleta de reserva
		BPALETA[iNumero].cVerde = cVerde;
                BPALETA[iNumero].cAzul = cAzul;

		outportb(0x3c9, cRojo);
		outportb(0x3c9, cVerde); //Por ultimo le da la informacion de los colores
		outportb(0x3c9, cAzul);  // a la VGA
	 }
        fclose(fArchivo);
  }
  //******************************************************************
  BOOL Colision(SPRITE sMap1, int XMap1, int YMap1, SPRITE sMap2, int XMap2, int YMap2)
  //sencillisimo algoritmo para detectar colisiones cuadradas de SPRITES
  {
        if (abs(XMap1 - XMap2) < (sMap1.Ancho + sMap2.Ancho) / 2 AND
		 abs(YMap1 - YMap2) < (sMap1.Alto + sMap2.Alto) / 2)
	 {
                return (1);
	 }
	return (0);
  }
  //******************************************************************
  void Fundido(COLOR cRojo, COLOR cVerde, COLOR cAzul, int Duracion)
  {
	int off, color; //variables para ciclos

        cRojo /= 10; cVerde /= 10; cAzul /= 10;  //divide los porcentajes entre 10 para hacer mas facil el trabajo

	for (off = 0; off < 64; off++)
        {
         delay(Duracion); //espera de acuerdo al parametro
	 for (color = 0; color < 256; color++)
	 {
	 outportb(0x3c8, color); //selecciona el color modificar
	 if (BPALETA[color].cRojo < (PALETA[color].cRojo * cRojo) / 10 && BPALETA[color].cRojo < 63) {BPALETA[color].cRojo++;}
	 if (BPALETA[color].cAzul < (PALETA[color].cAzul * cAzul) / 10 && BPALETA[color].cAzul < 63) {BPALETA[color].cAzul++;}
	 if (BPALETA[color].cVerde < (PALETA[color].cVerde * cVerde) / 10 && BPALETA[color].cVerde < 63) {BPALETA[color].cVerde++;}
	 /* si el color actual es menor o mayor al color deseado deacuerdo
                 a los porcentajes de color entonces reduce (si es mayor) o aumenta
		 (si es menor) hasta conseguir el color deseado, gracias a este efectos
		 se logran la presentaciones*/
         if (BPALETA[color].cRojo > (PALETA[color].cRojo * cRojo) / 10 && BPALETA[color].cRojo > 0) {BPALETA[color].cRojo--;}
         if (BPALETA[color].cAzul > (PALETA[color].cAzul * cAzul) / 10 && BPALETA[color].cAzul > 0) {BPALETA[color].cAzul--;}
	 if (BPALETA[color].cVerde > (PALETA[color].cVerde * cVerde) / 10 && BPALETA[color].cVerde >0) {BPALETA[color].cVerde--;}

	 outportb(0x3c9, BPALETA[color].cRojo); //Edita los colores en la paleta
	 outportb(0x3c9, BPALETA[color].cVerde);
	 outportb(0x3c9, BPALETA[color].cAzul);
		 }
	 }
  }
  //******************************************************************
  void Libera_Sprite(SPRITE sMap)
        {
         delete sMap.Contenido; //libera la memoria otorgada a el contenido de la imagen.
	}

  //******************************************************************
  int Numero(char Letra) //sencilla funcion que devuelve el codigo
			//de cada una de las letras que se cargan desde
			//el archivo de fuentes.
  {
	Letra = tolower(Letra);
	switch(Letra)
	 {
	  case 'a': return 0;
	  case 'b': return 1;
	  case 'c': return 2;
	  case 'd': return 3;
	  case 'e': return 4;
	  case 'f': return 5;
	  case 'g': return 6;
	  case 'h': return 7;
	  case 'i': return 8;
	  case 'j': return 9;
	  case 'k': return 10;
	  case 'l': return 11;
	  case 'm': return 12;
	  case 'n': return 13;
	  case '¤': return 14;
	  case 'o': return 15;
	  case 'p': return 16;
	  case 'q': return 17;
	  case 'r': return 18;
	  case 's': return 19;
	  case 't': return 20;
	  case 'u': return 21;
	  case 'v': return 22;
	  case 'w': return 23;
	  case 'x': return 24;
	  case 'y': return 25;
	  case 'z': return 26;
	  case '0': return 27;
	  case '1': return 28;
	  case '2': return 29;
	  case '3': return 30;
	  case '4': return 31;
	  case '5': return 32;
	  case '6': return 33;
	  case '7': return 34;
	  case '8': return 35;
	  case '9': return 36;
	  case '#': return 37; //este es le simbolo de la peque¤a nave
	  case ' ': return 38;
	  case '-': return 39;
	  case '.': return 40;
	  case ',': return 41;
	  case ':': return 42;
	  case '?': return 43;
	  case '¨': return 44;
	  default : return 37;
	 }
  }
//******************************************************************
void Poner_Texto(char *Letra, int x, int y, COLOR cColor)
//simplemente coloca el texto en la pantalla virtual
{
 int i,j, cont; //tres contadores
 for(cont=0; cont< strlen(Letra); cont ++) //desde o hasta lo que mida la cadena
    {
     for (i=0;i<8;i++)//desde 0 hasta 8
	 {
	  for (j=0;j<8;j++)//otra vez desde 0 hasta 8 por que las fuentes miden 8x8
	      {
	       if (CARACTERES[64*Numero(Letra[cont]) +  (i*8+j) ] )
	       //si la poscicion del la letra + lo que valla del ciclo es 1
	       Pixel(x+j+cont*8,y+i,cColor); //pone pixel del color deseado
	      }
	 }
    }
}
//******************************************************************
char LeerKey()//como getch
{
 int cont;//contador
 char Tecla;//para saber que tecla se presion¢
 BOOL FIN=FALSE; //para saber cuando terminar el ciclo
 while(!FIN)//mientras no finalice
  {
   for (cont=1;cont<84;cont++)    //recorre todas las teclas
       if (keys[cont]) //si se presiono alguna
	  {
	   FIN=TRUE; //finaliza el proceso
	   Tecla=cont;
	  }
  }
 switch(Tecla) //examina la tecla
   {
    case KEY_A: return 'A';//y mira convierte los codigos de las
    case KEY_B: return 'B';//teclas y los convierte a ASCII
    case KEY_C: return 'C';
    case KEY_D: return 'D';
    case KEY_E: return 'E';
    case KEY_F: return 'F';
    case KEY_G: return 'G';
    case KEY_H: return 'H';
    case KEY_I: return 'I';
    case KEY_J: return 'J';
    case KEY_K: return 'K';
    case KEY_L:  return 'L';
    case KEY_M: return 'M';
    case KEY_N: return 'N';
    case KEY_O: return 'O';
    case KEY_P: return 'P';
    case KEY_Q: return 'Q';
    case KEY_R: return 'R';
    case KEY_S: return 'S';
    case KEY_T: return 'T';
    case KEY_U: return 'U';
    case KEY_V: return 'V';
    case KEY_W: return 'W';
    case KEY_X: return 'X';
    case KEY_Y: return 'Y';
    case KEY_Z: return 'Z';
    case KEY_0: return '0';
    case KEY_1: return '1';
    case KEY_2: return '2';
    case KEY_3: return '3';
    case KEY_4: return '4';
    case KEY_5: return '5';
    case KEY_6: return '6';
    case KEY_7: return '7';
    case KEY_8: return '8';
    case KEY_9: return '9';
    case KEY_SPACE: return ' ';
    case KEY_MINUS: return '-';
    case KEY_BAKSP: return 1;
    case KEY_ENTER: return 0;
    case KEY_F1: return '#';
   default: return -1;
  }
}
//******************************************************************
int Char_a_Int(char Caracter) //simple algoritmo que convierte de caracter a entero
{
 if ( isdigit (Caracter)  ) return Caracter-'0';
 else return -1;
}
//******************************************************************
void Leer_Cadena(char *Cadena, int x, int y, COLOR cColor)//lee una cadena de caracteres
{
int cont=0;//contador
char caracter=1;//para saber que tecla se presiono
char texto[5];//para convertir el numero a cadena
while (caracter!=0) //mientras caracter no sea 0 (osea nulo)
  {
   delay(300);//espera 300 milisegundos para que la cosa no sea tan rapida
   caracter=LeerKey();//lee un caracter
   if (caracter==1 AND BUFFER!=NULL) //si el caracter es backspace y todo esta ok
      {
       cont--;//regresa el conteo
       sprintf(texto,"%c",Cadena[cont]);
       Poner_Texto(texto,x+(8*(cont+1)),y,0); //tapa el caracter anterior
       Pintar_Pantalla();
      }
   if (caracter!=-1 AND caracter!=1 AND BUFFER!=NULL ) //si el caracter es diferente de enter
      {
       if (caracter==' ') caracter='-';
       Cadena[cont]=caracter; //lo graba en la cadena
       cont++;
       sprintf(texto,"%c",caracter);
       Poner_Texto(texto,x+(8*cont),y,cColor); //y lo imprime en la pantalla
       Pintar_Pantalla();
      }
   else Cadena[cont]=0;//sino termina en nulo
  }
}
//******************************************************************

