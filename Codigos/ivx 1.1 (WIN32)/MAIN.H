/*
============================================================================
			ARCHIVO DE CABECERA DEL MODULO MAIN.CPP

Este archivo contienen todas las constantes, macros, y prototipos de funciones
necesarios para el funcionamiento de este modulo
============================================================================
*/
#ifndef _MAIN_H
#define _MAIN_H

#define MAX_ESTRELLAS 150
//el numero maxion de estrella

#define AMARILLO 	166
#define ROJO_OSCURO 	52
#define ROJO		149
#define AMARILLO_CLARO  195
#define VERDE_OSCURO    96
#define VERDE_CLARO	103
#define BLANCO		255
#define NEGRO		0
#define GRIS		112
#define MORADO		92
//Constantes que significan los colores en la paleta principal


#define Poner_Texto_Sombra(texto,x,y,color,colors) Poner_Texto(texto,x+1,y+1,colors); Poner_Texto(texto,x,y,color);
//Macro para crear texto con sombra, utiliza la funcion Poner_Texto() de IVXENGINE
//*******************************************************************
//FUNCIONES UTILIZADAS

  void Inicializar(); //inicializa cargando todo lo necesario para el juego
  void Finalizar();   //Libera memoria y finaliza con otras operaciones
  void Activar_Disparo(); //Activa el disparo inicializandolo en las cordenadas especificas
  void Disparar(); //Realiza la rutina del disparo, el movimiento y aceleracion
  void Mover_Nave(); //Coloca en pantalla y mueve la nave deacuerdo a las teclas que
		     //se presionen, tambien controla la ACELERACION
  void Detectar_Impactos();//Detecta si el disparo choco con algun enemigo, y de ser asi
			//activa la explosion del enemigo en cuestion
  void Desactivar_Disparo();//Desactiva el disparo de la nave
  void Explotar_Malo(int Num_Malo); //Explota el malo numero "Num_Malo"
  void Poner_Estrellas();//su nombre lo dice todo
  void Cargar_Mundo(int Numero);//carga un mundo, es decir la posicion de cada malo, y su tipo que esta almacenado
				       //en un archivo, retorna FALSE si no se puedo cargar el mundo
  void Enemigo_Disparar();//dispara las bolitas rojas
  void Activar_Disparo_Enemigo(int Enemigo);//activa el disparo del enemigo
  void Mover_Malos(); //mueve los enemigos en una especie de circulos
  void Explotar_Nave(); //esplota la nave!!!
  void Suicidar_Malo(int Numero);//Hace que los malos amarillos se tiren en espiral y se suiciden
  void Poner_Panel();//Coloca la barra vertical de la derecha con la informacion del juego.
  void Apoyo();//sirve para lanzar la nave de apoyo que aparece arriba y va de izquierda a derecha
  void Bonus();//sirve para lanzar de la nave de apoyo la bola verde del bonus
  void Obtener_Bonus();//sirve para obtener un beneficio del bonus como una vida etc.
  void Ganar();//Mustra la pantalla de triunfo.
  void Perder();//Muestra la pantalla de derrota
  void Inicializar_Datos();//inicializa los datos
  void Pantalla_Inicio();//muestra la pantalla inicial
  void Cambiar_Mensajes();//Cambia los mensajes de la parte superior
  void Menu_Opciones();//Crea el menu de opciones
  int  Menu_Principal();//Crea el menu principal
  void Configurar_Dificultad();//configura el juego deacuerdo a la dificultad escojida
  void Ayuda(int Tipo_Ayuda);//muestra la ayuda que aparece al precionar ESC
  void Creditos();//muestra los creditos
  void Iniciar_Escenario(); //muestra el nombre del nivel al inicio del escenario
  void Obtener_Password(); //capta un password de pantalla
  void Revisar_Records();// Revisa si hizo un nuevo record despues de perder
  void Mostrar_Records();//Muestra los actuales records en pantalla
  void Presentacion();//Muestra la presentacion del juego
  void Historia();//Muestra la historia
  void Final();//Despues de que se pase los 90 Mundos muestra el funal
  void Configurar_Password();//Configura el juego deacuerdo al password.
#endif
