extern i;
extern keys[128];
extern SPRITE ENEMIGO[3];
extern SPRITE IVX_LOGO;
extern SPRITE GANASTE;
extern SPRITE PERDISTE;
extern char MENSAJES[50];
extern PUNTUACION;
extern NIVEL;
extern char PASSWORD[6];
extern CONTINUES;
extern BOOL ESTRELLAS_ACTIVADAS;
extern BOOL MENSAJES_ACTIVADOS;
extern BOOL APOYO_ACTIVADO;
extern BOOL PRIMERA_VEZ;
extern BOOL CONTINUE_USADO;
extern BOOL PASSWORD_OK;
extern DIFICULTAD;
extern BOOL GANO_NIVEL;
extern BOOL SALIR;
extern time_t Tiempo_Inicial;
extern time_t Tiempo_Final;
extern float TIEMPO;
extern MAX_TIEMPO;
extern MAX_ACELERACION;
extern MAX_MALOS;
extern MAX_RESISTENCIA;
extern MAX_TITILANDO;
extern TURBO;
extern RETRAZO;
extern  struct {
	  int X, Y;
	  int Aceleracion;
	  BOOL Presionado;
	  int Vidas;
	  BOOL Kill;
	  BOOL Disparo;
	  BOOL Explosion;
	  int Aceleracion_Explosion;
	  int Escala;
	  int Disparo_X, Disparo_Y, Aceleracion_Disparo, Lado_Disparo;
	  int Arma_Actual;
	  int Titilando;
	  int Frame;
	  SPRITE Imagen[8], Imagen_Disparo[3];
      } Nave;
extern  struct {
	  int X,Y;
	  int Kill;
	  int Escala;
	  BOOL Explosion;
	  int Aceleracion_Explosion;
	  int Frame;
	  int Posicion_Horizontal, Posicion_Vertical;
	  BOOL Suicidio;
	  int Resistencia;
	  int  Direccion_Suicidio;
    } Malo[10];
extern  struct {
	  int X[MAX_ESTRELLAS], Y[MAX_ESTRELLAS], Z[MAX_ESTRELLAS];
      } Estrellas;
extern  struct {
	  int X, Y;
	  BOOL Activado;
	  SPRITE Imagen[2];
	  int Tipo;
       }Disparo_Enemigo;
extern   struct {
	  int X,Y;
	  SPRITE Imagen, Imagen_Bonus;
	  BOOL Activado, Bonus_Activado;
	  int Bonus_X, Bonus_Y;
	 }Nave_Apoyo;
