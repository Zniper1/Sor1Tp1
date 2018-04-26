#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // para castear de puntero a entero
#include <pthread.h>
#include <string.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////
// Info de grupos
///////////////////////////////////////////////////////////////////////////
#define CANTIDAD_GRUPOS 8
char* grupos_labels[] = {"A", "B", "C", "D", "E", "F", "G", "H"};

pthread_t A;
pthread_t B;
pthread_t C;
pthread_t D;
pthread_t E;
pthread_t F;
pthread_t G;
pthread_t H;

char* grupo_A[] = {"Rusia", "Arabia Saudita", "Egipto", "Uruguay"};
int grupo_A_favoritos[] = {1, 0, 0, 1};
int grupo_A_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} };

char* grupo_B[] = {"Portugal", "España", "Marruecos", "Irán"};
int grupo_B_favoritos[] = {1, 1, 0, 0};
int grupo_B_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
              		  	{0,0,0,0,0,0,0,0} ,
              		 	{0,0,0,0,0,0,0,0} ,
              			{0,0,0,0,0,0,0,0} };

char* grupo_C[] = {"Francia", "Australia", "Peru", "Dinamarca"};
int grupo_C_favoritos[] = {1, 0, 0, 0};
int grupo_C_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
              			{0,0,0,0,0,0,0,0} ,
              			{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} };

char* grupo_D[] = {"Argentina", "Islandia", "Croacia", "Nigeria"};
int grupo_D_favoritos[] = {1, 0, 0, 0};
int grupo_D_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} };

char* grupo_E[] = {"Brasil","Suiza", "Costa Rica", "Serbia"};
int grupo_E_favoritos[] = {1, 0, 0, 0};
int grupo_E_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} };

char* grupo_F[] = {"Alemania", "Mexico", "Suecia", "Korea del Sur"};
int grupo_F_favoritos[] = {1, 1, 0, 0};
int grupo_F_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} };

char* grupo_G[] = {"Belgica", "Panama", "Tunez", "Inglaterra"};
int grupo_G_favoritos[] = {0, 0, 0, 1};
int grupo_G_puntos[4][8] = { 	{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
               			{0,0,0,0,0,0,0,0} ,
                 		{0,0,0,0,0,0,0,0} };

char* grupo_H[] = {"Polonia", "Senegal", "Colombia", "Japón"};
int grupo_H_favoritos[] = {0, 0, 1, 0};
int grupo_H_puntos[4][8] = {	{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} ,
                		{0,0,0,0,0,0,0,0} };

void print_tabla_grupo(char* grupo_data[], int tabla[][8]){
  int i, j;
  for (i = 0; i < 4; i++){
    printf ("%s ,",grupo_data[i]);

    for (j = 0; j < 8; j++){
      printf ("%d ,",tabla[i][j]);
    }
    printf("\n");
  }
}

///////////////////////////////////////////////////////////////////////////
// End Info de grupos
///////////////////////////////////////////////////////////////////////////

void llenar_tabla(int tabla[][8], int equipo_1, int equipo_2, int goles_equipo_1, int goles_equipo_2)
{
  //columna 2 = PJ(Partidos Jugados)
  tabla[equipo_1][1] = tabla[equipo_1][1]+1;
  tabla[equipo_2][1] = tabla[equipo_2][1]+1;

  if(goles_equipo_1 > goles_equipo_2){
    //gano el equipo 1
    //columna 1 = Pts(Puntos)
    tabla[equipo_1][0] = tabla[equipo_1][0]+3;
    //columna 3 = PG(Partidos Ganados)
    tabla[equipo_1][2] = tabla[equipo_1][2]+1;
    //columna 5 = PP(Partidos Perdidos)
    tabla[equipo_2][4] = tabla[equipo_2][4]+1;

  }else if (goles_equipo_1 == goles_equipo_2){
    //empataron
    tabla[equipo_1][0] = tabla[equipo_1][0]+1;
    tabla[equipo_2][0] = tabla[equipo_2][0]+1;
    //columna 4 = PE(Partidos Empatados)
    tabla[equipo_1][3] = tabla[equipo_1][3]+1;
    tabla[equipo_2][3] = tabla[equipo_2][3]+1;
  }else{
    //gano el equipo 2
    tabla[equipo_2][0] = tabla[equipo_2][0]+3;
    tabla[equipo_2][2] = tabla[equipo_2][2]+1;
    //columna 5 = PP(Partidos Perdidos)
    tabla[equipo_1][4] = tabla[equipo_1][4]+1;
  }

  //columna 6 = GF(Goles a Favor)
  tabla[equipo_1][5] = tabla[equipo_1][5]+goles_equipo_1;
  tabla[equipo_2][5] = tabla[equipo_2][5]+goles_equipo_2;

  //columna 7 = GC(Goles en contra)
  tabla[equipo_1][6] = tabla[equipo_1][6]+goles_equipo_2;
  tabla[equipo_2][6] = tabla[equipo_2][6]+goles_equipo_1;

  //columna 8 = Dif(Diferencia de Gol)
  tabla[equipo_1][7] = 0; //TODO:revisar
  tabla[equipo_2][7] = 0; //TODO:revisar
}

void jugar_partido (int equipo_1, int equipo_2, int instancia, char* grupo_data[] , int grupo_puntos[][8], int grupo_favoritos[] ){
  char * nombre_equipo_1;
  char * nombre_equipo_2;
  int goles_equipo_1;
  int goles_equipo_2;

  nombre_equipo_1=grupo_data[equipo_1];
  nombre_equipo_2=grupo_data[equipo_2];

  /* random int entre 0 y 10 */
  int rango_gol_equipo1 = 1;
  int rango_gol_equipo2 = 1;
  int base=0;
  if(grupo_favoritos[equipo_1]){
    rango_gol_equipo1 = 7;
    base=3;
  }

  if(grupo_favoritos[equipo_2]){
    rango_gol_equipo2 = 7;
    base=3;
  }

  goles_equipo_1 = (rand() % rango_gol_equipo1)+base;
  goles_equipo_2 = (rand() % rango_gol_equipo2)+base;

  printf("Resultado %s %d -- %s %d \n", nombre_equipo_1, goles_equipo_1, nombre_equipo_2, goles_equipo_2);

  switch(instancia) {
  case 0 :
    //es instancia de grupos
    llenar_tabla(grupo_puntos, equipo_1, equipo_2, goles_equipo_1, goles_equipo_2);
    break;
  default :
    printf("Invalid instancia\n" );
  }
}

void PartidosGrupoA (){
    printf("\nJugando grupo A \n");
    jugar_partido(0,1, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(0,2, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(2,1, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(2,3, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(3,1, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
    jugar_partido(3,0, 0, grupo_A, grupo_A_puntos, grupo_A_favoritos);
}
void PartidosGrupoB (){
    printf("\nJugando grupo B \n");
    jugar_partido(0,1, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(0,2, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(2,1, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(2,3, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(3,1, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
    jugar_partido(3,0, 0, grupo_B, grupo_B_puntos, grupo_B_favoritos);
}
void PartidosGrupoC (){
    printf("\nJugando grupo C \n");
    jugar_partido(0,1, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(0,2, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(2,1, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(2,3, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(3,1, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
    jugar_partido(3,0, 0, grupo_C, grupo_C_puntos, grupo_C_favoritos);
}
void PartidosGrupoD (){
    printf("\nJugando grupo D \n");
    jugar_partido(0,1, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(0,2, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(2,1, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(2,3, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(3,1, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
    jugar_partido(3,0, 0, grupo_D, grupo_D_puntos, grupo_D_favoritos);
}
void PartidosGrupoE (){
    printf("\nJugando grupo E \n");
    jugar_partido(0,1, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(0,2, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(2,1, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(2,3, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(3,1, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
    jugar_partido(3,0, 0, grupo_E, grupo_E_puntos, grupo_E_favoritos);
}
void PartidosGrupoF (){
    printf("\nJugando grupo F \n");
    jugar_partido(0,1, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(0,2, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(2,1, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(2,3, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(3,1, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
    jugar_partido(3,0, 0, grupo_F, grupo_F_puntos, grupo_F_favoritos);
}
void PartidosGrupoG (){
    printf("\nJugando grupo G \n");
    jugar_partido(0,1, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(0,2, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(2,1, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(2,3, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(3,1, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
    jugar_partido(3,0, 0, grupo_G, grupo_G_puntos, grupo_G_favoritos);
}
void PartidosGrupoH (){
    printf("\nJugando grupo H \n");
    jugar_partido(0,1, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(0,2, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(2,1, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(2,3, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(3,1, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
    jugar_partido(3,0, 0, grupo_H, grupo_H_puntos, grupo_H_favoritos);
}

void jugar_grupos ()
{
  printf("***************************************** \n");

    pthread_create(&A, NULL, PartidosGrupoA, NULL);
    pthread_join(A,NULL);
    pthread_create(&B, NULL, PartidosGrupoB, NULL);
    pthread_join(B,NULL);
    pthread_create(&C, NULL, PartidosGrupoC, NULL);
    pthread_join(C,NULL);
    pthread_create(&D, NULL, PartidosGrupoD, NULL);
    pthread_join(D,NULL);
    pthread_create(&E, NULL, PartidosGrupoE, NULL);
    pthread_join(E,NULL);
    pthread_create(&F, NULL, PartidosGrupoF, NULL);
    pthread_join(F,NULL);
    pthread_create(&G, NULL, PartidosGrupoG, NULL);
    pthread_join(G,NULL);
    pthread_create(&H, NULL, PartidosGrupoH, NULL);
    pthread_join(H,NULL);
}

char* winer_octavos[] = {"Wp49", "Wp50", "Wp51", "Wp52", "Wp53", "Wp54", "Wp55", "Wp56"};

void jugar_partido_winners(char * nombre_equipo_1, char * nombre_equipo_2, int index_partido, char* data_winners[]){
  printf("Jugando partido entre %s y %s \n", nombre_equipo_1, nombre_equipo_2);
  int goles_equipo_1;
  int goles_equipo_2;
  /* random int entre 0 y 10 */
  goles_equipo_1 = rand() % 10;
  goles_equipo_2 = rand() % 10;
  if(goles_equipo_1 > goles_equipo_2){
    data_winners[index_partido]=nombre_equipo_1;
  }else{
    data_winners[index_partido]=nombre_equipo_2;
  }
}

int obtener_primero(int grupo_puntos[][8]){
  int i;
  int puntaje_maximo=-1;
  int index_maximo=-1;
  for (i = 0; i < 4; i++){
    if(grupo_puntos[i][0]>=puntaje_maximo){
      index_maximo=i;
      puntaje_maximo=grupo_puntos[i][0];
    }
  }
  return index_maximo;
}

int obtener_segundo(int grupo_puntos[][8]){
  int i;
  int puntaje_maximo=-1;
  int index_segundo=-1;

  int index_primero=obtener_primero(grupo_puntos);
  for (i = 0; i < 4; i++){
    if(grupo_puntos[i][0]>=puntaje_maximo && i!=index_primero){
      index_segundo=i;
      puntaje_maximo=grupo_puntos[i][0];
    }
  }
  return index_segundo;
}

void PartidoOctavosAB(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
//partido 49: A1 vs B2
  index_1=obtener_primero(grupo_A_puntos);
  nombre_equipo_1=grupo_A[index_1];
  index_2=obtener_segundo(grupo_B_puntos);
  nombre_equipo_2=grupo_B[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 0, winer_octavos);
  }
void PartidoOctavosBA(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
  //partido 51: B1 vs A2
  index_1=obtener_primero(grupo_B_puntos);
  nombre_equipo_1=grupo_B[index_1];
  index_2=obtener_segundo(grupo_A_puntos);
  nombre_equipo_2=grupo_A[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 2, winer_octavos);
  }
void PartidoOctavosCD(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
   //partido 50: C1 vs D2
  index_1=obtener_primero(grupo_C_puntos);
  nombre_equipo_1=grupo_C[index_1];
  index_2=obtener_segundo(grupo_D_puntos);
  nombre_equipo_2=grupo_D[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 1, winer_octavos);
  }
void PartidoOctavosDC(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
   //partido 52: D1 vs C2
  index_1=obtener_primero(grupo_D_puntos);
  nombre_equipo_1=grupo_D[index_1];
  index_2=obtener_segundo(grupo_C_puntos);
  nombre_equipo_2=grupo_C[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 3, winer_octavos);
  }
void PartidoOctavosEF(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
  //partido 53: E1 vs F2
  index_1=obtener_primero(grupo_E_puntos);
  nombre_equipo_1=grupo_E[index_1];
  index_2=obtener_segundo(grupo_F_puntos);
  nombre_equipo_2=grupo_F[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 4, winer_octavos);
  }
void PartidoOctavosFE(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
   //partido 55: F1 vs E2
  index_1=obtener_primero(grupo_F_puntos);
  nombre_equipo_1=grupo_F[index_1];
  index_2=obtener_segundo(grupo_E_puntos);
  nombre_equipo_2=grupo_E[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 6, winer_octavos);
  }
void PartidoOctavosGH(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
  //partido 54: G1 vs H2
  index_1=obtener_primero(grupo_G_puntos);
  nombre_equipo_1=grupo_G[index_1];
  index_2=obtener_segundo(grupo_H_puntos);
  nombre_equipo_2=grupo_H[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 5, winer_octavos);
  }
void PartidoOctavosHG(){
  int index_1;
  char * nombre_equipo_1;
  int index_2;
  char * nombre_equipo_2;
 //partido 56: H1 vs G2
  index_1=obtener_primero(grupo_H_puntos);
  nombre_equipo_1=grupo_H[index_1];
  index_2=obtener_segundo(grupo_G_puntos);
  nombre_equipo_2=grupo_G[index_2];
  jugar_partido_winners(nombre_equipo_1, nombre_equipo_2, 7, winer_octavos);
  }

void jugar_octavos ()
{
  printf("***************************************** \n");
  printf("Jugando octavos \n");

  pthread_create(&A, NULL, PartidoOctavosAB, NULL);
  pthread_create(&B, NULL, PartidoOctavosBA, NULL);
  pthread_create(&C, NULL, PartidoOctavosCD, NULL);
  pthread_create(&D, NULL, PartidoOctavosDC, NULL);
  pthread_create(&E, NULL, PartidoOctavosEF, NULL);
  pthread_create(&F, NULL, PartidoOctavosFE, NULL);
  pthread_create(&G, NULL, PartidoOctavosGH, NULL);
  pthread_create(&H, NULL, PartidoOctavosHG, NULL);
  pthread_join(A, NULL);
  pthread_join(B, NULL);
  pthread_join(C, NULL);
  pthread_join(D, NULL);
  pthread_join(E, NULL);
  pthread_join(F, NULL);
  pthread_join(G, NULL);
  pthread_join(H, NULL);
}

char* winer_cuartos[] = {"Wp57", "Wp58", "Wp59", "Wp60"};

void PartidoCuartosA(){
    //partido 57: Wp49 vs Wp50
  jugar_partido_winners(winer_octavos[0], winer_octavos[1], 0, winer_cuartos);
}
void PartidoCuartosB(){
 //partido 59: Wp51 vs Wp52
  jugar_partido_winners(winer_octavos[2], winer_octavos[3], 2, winer_cuartos);
}
void PartidoCuartosC(){
  //partido 58: Wp53 vs Wp54
  jugar_partido_winners(winer_octavos[4], winer_octavos[5], 1, winer_cuartos);
}
void PartidoCuartosD(){
  //partido 60: Wp55 vs Wp56
  jugar_partido_winners(winer_octavos[6], winer_octavos[7], 3, winer_cuartos);
}

void jugar_cuartos ()
{
  printf("***************************************** \n");
  printf("Jugando cuartos \n");

  pthread_create(&A, NULL, PartidoCuartosA, NULL);
  pthread_create(&B, NULL, PartidoCuartosB, NULL);
  pthread_create(&C, NULL, PartidoCuartosC, NULL);
  pthread_create(&D, NULL, PartidoCuartosD, NULL);

  pthread_join(A, NULL);
  pthread_join(B, NULL);
  pthread_join(C, NULL);
  pthread_join(D, NULL);
}

char* winer_semis[] = {"Wp61", "Wp62"};
char* champion[] = {"Wfinal"};

void PartidoSemiA(){
 //partido 61: Wp57 vs Wp58
  jugar_partido_winners(winer_cuartos[0], winer_cuartos[1], 0, winer_semis);
}
void PartidoSemiB(){
  //partido 62: Wp59 vs Wp60
  jugar_partido_winners(winer_cuartos[2], winer_cuartos[3], 1, winer_semis);
}

void jugar_semis ()
{
  printf("***************************************** \n");
  printf("Jugando semis \n");

  pthread_create(&A, NULL, PartidoSemiA, NULL);
  pthread_create(&B, NULL, PartidoSemiB, NULL);
  pthread_join(A, NULL);
  pthread_join(B, NULL);
}

void jugar_final ()
{
  printf("***************************************** \n");

  printf("Jugando final \n");
  //final: Wp91 vs Wp62
  jugar_partido_winners(winer_semis[0], winer_semis[1], 0, champion);
  printf("***************************************** \n");
  printf("El nuevo campeon del mundo es %s \n", champion[0]);
  printf("***************************************** \n");
}

int main ()
{
  //////////////////////////////////////////////////////////////////////
  // start mundial
  //////////////////////////////////////////////////////////////////////
  srand(time(NULL));

  jugar_grupos();
  jugar_octavos();
  jugar_cuartos();
  jugar_semis();
  jugar_final();

  /////////////////////////////////////////////////////////////////////
  // end mundial
  //////////////////////////////////////////////////////////////////////
}
