/***************************************************************************
		 PROGRAMA PARA LA CREACION DE ESCENARIOS
			      DEL PROYECTO IVX
****************************************************************************/
#include<stdio.h>
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>

void main()
{
 FILE *Archivo;
 char Nombre_Archivo[40];
 int Cordx[10]= {4,6,8,10,12,4,6,8,10,12};
 int Cordy[10]= {11,11,11,11,11,13,13,13,13,13};
 char tipo=0;
 int numero;
 int ciclo=1;
 int i,j;
 int cont=0;
 clrscr();
 cout<<"INVAXION MARCIANA IVX \n";
 cout<<"===================== \n\n";
 cout<<"Programa de Creacion de Escenarios \n\n";
 cout<<"Introduzca el numero del Mundo \n";
 cin>>numero;
 sprintf(Nombre_Archivo,"mundo%d.imd",numero);
 Archivo=fopen(Nombre_Archivo,"w");
 if (Archivo==NULL)
    {
    printf("ERROR: no se puedo cargar el archivo");
    getch();
    exit(-1);
   }
 cout<<"Cual es la velocidad del escenario (0,1,2):  ";
 while (ciclo)
    {
     tipo=getch();
     switch (tipo)
       {
	case '0': tipo=0; ciclo=0; break;
	case '1': tipo=1; ciclo=0; break;
	case '2': tipo=2; ciclo=0; break;
	}
     }
 ciclo=1;
 printf("%d",tipo);
 fprintf(Archivo,"%1d\n",tipo);
 for (i=0;i<2;i++)
  {
	for (j=0;j<5;j++)
	 {
	  gotoxy(Cordx[cont],Cordy[cont]);
	  printf("?");
	  cont++;
	 }
	}
 cont=0;
 for (i=0;i<2;i++)
  {
	for (j=0;j<5;j++)
	 {
	  gotoxy(Cordx[cont],Cordy[cont]);
	  while (ciclo)
	    {
	     tipo=getch();
	     switch (tipo)
	       {
		case '0': tipo=0; ciclo=0; break;
		case '1': tipo=1; ciclo=0; break;
		case '2': tipo=2; ciclo=0; break;
	       }
	    }
	  ciclo=1;
	  printf("%d", tipo);
	  fprintf(Archivo, "%2d %1d %1d\n",j,i,tipo);
	  cont++;
	 }
	}
 fclose(Archivo);
 cout<<"\n\n Grabando.. ok.";
 getch();
}
