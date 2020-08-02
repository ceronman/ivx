/*IVX ENGINE VERSION 1.0

  Esta es la version adaptada a la libreria ALLEGRO de IVXENGINE,
  el motor de juego utilizado en IVX 1.0 y versiones anteriores.
  Creado por Manuel Alejandro Ceron.


	Cambios desde la ultima version
         - El codigo se ha adaptado a Allegro y ahora es portable!!
 */
#include"ivxengin.h"
//------------------------------------------------------------------------
#define keys key
//contiene las declaraciones de funciones constantes y demas cosas

//******************************************************************
//** VARIABLES GLOBALES
//*****************************************************************
 BITMAP *BUFFER = NULL ; //Pantalla Virtual donde se escribiran los datos antes
				 //de pasarlos a la pantalla real
 PALETTE PALETA, BPALETA; //Para almacenar las paletas de colores

 DATAFILE *datos;
 FONT     *f;

//******************************************************************
//******************************************************************

//DEFINICION DE LAS FUNCIONES
  void Inicia_VGA()
  {
   // Initialize Allegro.
   allegro_init();

   set_color_depth(8);
   // Set the resolution to 640 by 480 with SAFE autodetection.
   if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 320, 200, 0, 0)!=0) {
      allegro_message("Error no se pudo iniciar el juego...");
   }
   install_timer();
   BUFFER=create_bitmap(SCREEN_W,SCREEN_H);
   datos = load_datafile("IVXDATOS\\fuente.dat");
   if (!datos) {
      allegro_message("Error no se puede abrir el archivo %s\n", "fuente.dat");
   }
   f = (FONT *) datos[0].dat;
 }
  //******************************************************************
  void Cierra_VGA()
        {
         destroy_bitmap(BUFFER);
         unload_datafile(datos);
         allegro_exit();
        }

  //******************************************************************

  void Pixel(int iX, int iY, COLOR cColor)
	{
       putpixel(BUFFER,iX,iY,cColor);
    }

  //******************************************************************

  SPRITE  Cargar_Imagen(char cRuta[])
	{
	 SPRITE sTemp;    // Variable temporal donde se guardan lo datos que se retornan
     sTemp.Contenido=load_bitmap(cRuta,NULL);
     if (!sTemp.Contenido) {
        allegro_message("Error no se pudo cargar el archivo %s",cRuta);
     }
     sTemp.Ancho = sTemp.Contenido->w;
     sTemp.Alto = sTemp.Contenido->h;
	 return sTemp;
	}

  //******************************************************************

  void Limpiar_Pantalla(COLOR cColor)
     {
      clear_to_color(BUFFER,cColor);
	 }                                                                                                      //especial

  //******************************************************************

  void Poner_Sprite(SPRITE sMap, int CordX, int CordY, double dEscala_x, double dEscala_y)
	 {
      double porcentaje_x, porcentaje_y;
      porcentaje_x = dEscala_x/100*sMap.Ancho;
      porcentaje_y = dEscala_y/100*sMap.Alto;
      CordX -= (int) porcentaje_x/2;
      CordY -= (int) porcentaje_y/2;

      stretch_sprite(BUFFER,sMap.Contenido,CordX,CordY,(int)porcentaje_x,(int)porcentaje_y);


     }
  //******************************************************************
  void Pintar_Pantalla()
   {
    blit(BUFFER,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    //Pasa el contenido de la pantalla
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
   blit(sFondo.Contenido,BUFFER,0,0,0,0,SCREEN_W,SCREEN_H);
  }
  //******************************************************************
  void Cargar_Paleta(char cRuta[])
  {
   BITMAP *algo;
   algo=load_bitmap(cRuta,PALETA);
   if (!algo) {
        allegro_message("Error no se pudo cargar el archivo %s",cRuta);
     }
   algo=load_bitmap(cRuta,BPALETA);
   if (!algo) {
        allegro_message("Error no se pudo cargar el archivo %s",cRuta);
     }
   set_palette(PALETA);
   destroy_bitmap(algo);
  }
  //******************************************************************
  BOOL Colision(SPRITE sMap1, int XMap1, int YMap1, SPRITE sMap2, int XMap2, int YMap2)
  //sencillisimo algoritmo para detectar colisiones cuadradas de SPRITES
  {
        if (abs(XMap1 - XMap2) < (sMap1.Ancho + sMap2.Ancho) / 2 AND
		 abs(YMap1 - YMap2) < (sMap1.Alto + sMap2.Alto) / 2)
	 {
                return (true);
	 }
	return (false);
  }
  //******************************************************************
  void Fundido(COLOR cRojo, COLOR cVerde, COLOR cAzul, int Duracion)
  {
   if (cRojo>1 && cVerde>1 && cAzul>1) fade_in(BPALETA,10);
   else fade_out(10);
  }
  //******************************************************************
  void Libera_Sprite(SPRITE sMap)
        {
         destroy_bitmap(sMap.Contenido); //libera la memoria otorgada a el contenido de la imagen.
	}

//******************************************************************
void Poner_Texto(char *Letra, int x, int y, COLOR cColor)
{
 text_mode(-1);
 textout(BUFFER,f,Letra,x,y,cColor);
}
//******************************************************************
char LeerKey()//como getch
{
 return (readkey() & 0xff);
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
int caracter=1;//para saber que tecla se presiono
char texto[5];//para convertir el numero a cadena
bool salir=false;
while (!salir) //mientras caracter no sea 0 (osea nulo)
  {
   caracter=readkey();//lee un caracter
   if (SCANCODE(caracter)==KEY_BACKSPACE AND BUFFER!=NULL) //si el caracter es backspace y todo esta ok
      {
       cont--;//regresa el conteo
       sprintf(texto,"%c",Cadena[cont]);
       Poner_Texto(texto,x+(8*(cont+1)),y,0); //tapa el caracter anterior
       Pintar_Pantalla();
      }
   if (SCANCODE(caracter)!=KEY_ENTER AND SCANCODE(caracter)==KEY_BACKSPACE AND BUFFER!=NULL ) //si el caracter es diferente de enter
      {
       if (scancode_to_ascii(SCANCODE(caracter))!=0){
          Cadena[cont]=caracter; //lo graba en la cadena
          cont++;
          sprintf(texto,"%c",caracter);
          Poner_Texto(texto,x+(8*cont),y,cColor); //y lo imprime en la pantalla
          Pintar_Pantalla();
       }
      }
   else Cadena[cont]='\0';//sino termina en nulo
  }
}
//******************************************************************

