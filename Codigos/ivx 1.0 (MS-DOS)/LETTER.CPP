/***************************************************************************
		      PROGRAMA PARA LA CREACION DE FUENTES
			      DEL PROYECTO IVX
****************************************************************************/
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>

int x=3,y=16; //cordenadas para hacer el dibujo
int i,j;//para ciclos
int numero;//para saber el indicie de la letra
char *letra=NULL;//contiendra las letras

void main()
{
 FILE *Archivo;//ARCHIVO DESDE DONDE SE CARGAN
 char *Nombre_Archivo;//Nombre del achivo
 int horiz=0, vert=0; //para ubicarse en el cuadro
 char tecla; //para saber que tecla se presiono
 void pintar(); //funcion para pitar el cuadro en pantalla
 textmode(C40); //cambia a modo de letras grandes
 clrscr();//limpia la pantalla
 letra=new char[8*8*45];//reserva la memoria necesaria
 if (!letra)
   {
    printf("ERROR: No hay memoria sufuciente para cargar el archivo de fuentes");
    getch();
    exit(-1);
   }
 printf("INVAXION MARICIANA IVX \n"); //pone el texto
 printf("=======================\n\n");
 printf("Archivo de creacion de fuentes \n");
 printf("Intruduzca el archivo a modificar:\n");
 scanf("%s",Nombre_Archivo);//lee el nombre del archivo
 printf("\nSe mueve con las FLECHAS y con ESPACIO\n");
 printf("Se cambia de letra con 'S' y 'N'\n");
 printf("Se graba con ESC\n");
 printf("Presione Cualquier tecla para continuar\n");
 getch();
 textbackground(BLUE);
 textcolor(YELLOW);
 _setcursortype(_SOLIDCURSOR);//quita el cursor

 if (!( Archivo=fopen(Nombre_Archivo,"rb")) )  //abre el archivo
    {
     printf("ERROR: no se encuentra el archivo");
     getch();
     exit(-1);
    }
 fread(letra,1,8*8*45,Archivo);//coloca el contenido del archivo en memoria
 fclose(Archivo);
 pintar();//pinta el cuadro
 gotoxy(1,14);
 cprintf("Numero: %2d",numero);
 tecla=getch(); //espera a que presione una tecla
 if (tecla==0) tecla=getch();
 while(tecla!=27)
  {
	switch(tecla)
	 {
	  case 72: if (vert>0) { y--; vert--;} break;
	  case 80: if (vert<7) { y++; vert++;} break; //ARRIBA 72 DERE 77 ABAJO 80 IZQ 75 ESC 27
	  case 77: if (horiz<7) { x++; horiz++;} break;
	  case 75: if (horiz>0) { x--; horiz--;} break;
	  case 's': if (numero < 44) { numero++; horiz=0; vert=0; x=3; y=16; pintar(); } break;
	  case 'a': if (numero > 0) { numero--; horiz=0; vert=0; x=3; y=16; pintar(); } break;
	  case ' '://si presiona espacion
				  if (letra[(8*vert+horiz)+64*numero]==0)
						  {
							letra[(8*vert+horiz)+64*numero]=1;
							cprintf("²");
						  }
				  else
						 {
						  letra[(8*vert+horiz)+64*numero]=0;
						  cprintf(" ");
						 }
				  break;
	 }
	gotoxy(1,14);
	cprintf("Numero: %2d",numero);
	gotoxy(x,y);
	tecla=getch();
	if (tecla==0) tecla=getch();
  }
gotoxy(12,22);
if (!( Archivo=fopen(Nombre_Archivo,"wb+")) )
 {
  cprintf("ERROR: NO SE PUEDO GRABAR EL ARCHIVO");
  getch();
  exit(-1);
 }
if (fwrite(letra,1,8*8*45,Archivo)) cprintf("Grabando... ok.\n");
gotoxy(12,23); cprintf("Presione una tecla para salir");
getch();
fclose(Archivo);
delete letra;
}

void pintar()
{
 gotoxy(x,y);
 for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
		{
		 gotoxy(x+j,y+i);
		 if (letra[ (i*8+j) + 64*numero] ) cprintf("²");
		 else cprintf(" ");
		}
	}
  gotoxy(x,y);
}
