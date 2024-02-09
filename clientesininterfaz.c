#include <stdio.h>
#include <atmi.h>
#include <fml32.h>	
#include <string.h>
#include "bib_proyecto.fml.h"	

typedef struct Autos{
   int autoID;
   char marca[50];
   char modelo[51];
   char anio[10];
   char color[50];
   double precio;
}Autos;

int main(int argc, char **argv){
   int opc;

   /* Menu de opciones que se pueden realizar en el codigo*/
   printf("\n*************************************************\n");
   printf("Menu de opciones\n");
   printf("\n*************************************************\n");
   printf("1. (SELECT - todos)\n");
   printf("2. (SELECT - Buscar)\n");
   printf("3. (INSERT)\n");
   printf("4. (UPDATE)\n");
   printf("5. (DELETE)\n");
   printf("\n*************************************************\n");
   printf("Opción: "); scanf("%d",&opc);
   switch(opc){
      case 1:
      	printf("(SELECT - todos).\n");
	clientSelect_todos_AgenciaAutos();
      	break;
      case 2:
      	printf("(SELECT - Buscar).\n");
	clientSelect_buscar_AgenciaAutos();
      	break;
      case 3:
      	printf("(INSERT)\n");
	clientInsert_AgenciaAutos();
      	break;
      case 4:
      	printf("(UPDATE).\n");
        clientUpdate_AgenciaAutos();
      	break;
      case 5:
      	printf("(DELETE).\n");
        clientDelete_AgenciaAutos();
      	break;

   }
   return 0;
}

int clientSelect_todos_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];
   Autos *autosRegis;
   Autos carro;
   int ivL_numOcurr;
   int ivl_iterador;

   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n");
   if (tpinit((TPINIT *) NULL) == -1){
       printf("Error en la conexion, tperrno = %d \n", tperrno);
       return (1);
   }

   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
       printf("Error Reservando espacio para Buffer fbfr\n");
       tpterm();
       return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
       printf("ErrorReservando espacio para Buffer recv\n");
       tpterm();
       return(1);
   }

   // Invocamos el servicio 
   printf("Llamada al servicio 'SELECT_TODOS_AgenciaAutos'\n");
   if(tpcall("SELECT_TODOS_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L)==-1){
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      tpfree((char *)fbfr);
      tpfree((char *)recv);
      tpterm();
      return (1);
   }

   if((ivL_numOcurr = Foccur32(recv, AUTOID)) < 0) {
      printf("Error en Foccur32\n");
      tpfree((char *)fbfr);
      tpfree((char *)recv);
      tpterm();
      return (1); 
   }

   printf("Numero de ocurrencias: %d\n", ivL_numOcurr);
   autosRegis = (Autos *) malloc(sizeof(Autos) * ivL_numOcurr);

  flen = sizeof(msgbuf);
  printf("***************************************************\n");
  for(ivl_iterador = 0;ivl_iterador < ivL_numOcurr; ivl_iterador++) {
      Fget32(recv, AUTOID, ivl_iterador, (char *)&autosRegis[ivl_iterador].autoID,0);
      printf("ID carro : %d\n", autosRegis[ivl_iterador].autoID);

      Fget32(recv, MARCA, ivl_iterador, (char *)autosRegis[ivl_iterador].marca,0);
      printf("Nombre de la marca : %s\n", autosRegis[ivl_iterador].marca);

      Fget32(recv, MODELO, ivl_iterador, (char *)autosRegis[ivl_iterador].modelo,0);
      printf("modelo: %s\n", autosRegis[ivl_iterador].modelo);

      Fget32(recv, ANIO, ivl_iterador, (char *)autosRegis[ivl_iterador].anio,0);
      printf("Anio del automovil : %s\n", autosRegis[ivl_iterador].anio);

      Fget32(recv, COLOR, ivl_iterador, (char *)autosRegis[ivl_iterador].color,0);
      printf("COlor del automovil : %s\n", autosRegis[ivl_iterador].color);

      Fget32(recv, PRECIO, ivl_iterador, (char *)&autosRegis[ivl_iterador].precio,0);
      printf("Precio del automovil : %lf\n", autosRegis[ivl_iterador].precio);

   }
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}



int clientSelect_buscar_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];
   int id_auto;
   Autos *autosRegis;
   Autos carro;
   int ivL_numOcurr;
   int ivl_iterador;

   printf("*************************************************\n");
   printf("Se imprimira el carro con el ID que escriba \n");
   printf("IDCarro : "); scanf("%d", &id_auto);
   printf("*************************************************\n");

   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n");
   if (tpinit((TPINIT *) NULL) == -1){
       printf("Error en la conexion, tperrno = %d \n", tperrno);
       return (1);
   }

   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
       printf("Error Reservando espacio para Buffer fbfr\n");
       tpterm();
       return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
       printf("ErrorReservando espacio para Buffer recv\n");
       tpterm();
       return(1);
   }
   /* Manejo del Buffer FML */
   if(Fadd32 (fbfr, AUTOID, (char *)&id_auto, 0) < 0) {
      printf ("\n\tError insertando campo FML (AUTOID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   // Invocamos el servicio 
   printf("Llamada al servicio 'SELECT_buscar_AgenciaAutos'\n");
   if(tpcall("SELECT_BUSCAR_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L)==-1){
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      tpfree((char *)fbfr);
      tpfree((char *)recv);
      tpterm();
      return (1);
   }

   if((ivL_numOcurr = Foccur32(recv, AUTOID)) < 0) {
      printf("Error en Foccur32\n");
      tpfree((char *)fbfr);
      tpfree((char *)recv);
      tpterm();
      return (1); 
   }

   printf("Numero de ocurrencias: %d\n", ivL_numOcurr);
   autosRegis = (Autos *) malloc(sizeof(Autos) * ivL_numOcurr);

  flen = sizeof(msgbuf);
  printf("Respuesta del servidor para EL autoID: %d\n", id_auto);
  printf("***************************************************\n");
  for(ivl_iterador = 0;ivl_iterador < ivL_numOcurr; ivl_iterador++) {
      Fget32(recv, AUTOID, ivl_iterador, (char *)&autosRegis[ivl_iterador].autoID,0);
      printf("ID carro : %d\n", autosRegis[ivl_iterador].autoID);

      Fget32(recv, MARCA, ivl_iterador, (char *)autosRegis[ivl_iterador].marca,0);
      printf("Nombre de la marca : %s\n", autosRegis[ivl_iterador].marca);

      Fget32(recv, MODELO, ivl_iterador, (char *)autosRegis[ivl_iterador].modelo,0);
      printf("modelo: %s\n", autosRegis[ivl_iterador].modelo);

      Fget32(recv, ANIO, ivl_iterador, (char *)autosRegis[ivl_iterador].anio,0);
      printf("Anio del automovil : %s\n", autosRegis[ivl_iterador].anio);

      Fget32(recv, COLOR, ivl_iterador, (char *)autosRegis[ivl_iterador].color,0);
      printf("COlor del automovil : %s\n", autosRegis[ivl_iterador].color);

      Fget32(recv, PRECIO, ivl_iterador, (char *)&autosRegis[ivl_iterador].precio,0);
      printf("Precio del automovil : %lf\n", autosRegis[ivl_iterador].precio);

   }
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}

int clientInsert_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Inicializamos una referencia bibliografica */
   Autos carro;
  
   printf("\n*************************************************\n");
   printf("Auto ID : "); scanf("%d", &carro.autoID);
   printf("Marca: "); scanf("%s", carro.marca);
   printf("Modelo : "); scanf("%s", carro.modelo);
   printf("Anio : "); scanf("%s", carro.anio);
   printf("Color : "); scanf("%s", carro.color);
   printf("Precio : "); scanf("%lf", &carro.precio);
   printf("\n*************************************************\n");


   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, AUTOID, (char *)&carro.autoID, 0) < 0) {
      printf ("\n\tError insertando campo FML (AUTOID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MARCA, (char *)&carro.marca, 0) < 0) {
      printf ("\n\tError insertando campo FML (MARCA)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MODELO, (char *)&carro.modelo, 0) < 0) {
      printf ("\n\tError insertando campo FML (MODELO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, ANIO, (char *)&carro.anio, 0) < 0) {
      printf ("\n\tError insertando campo FML (ANIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, COLOR, (char *)&carro.color, 0) < 0) {
      printf ("\n\tError insertando campo FML (COLOR)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, PRECIO, (char *)&carro.precio, 0) < 0) {
      printf ("\n\tError insertando campo FML (PRECIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }


   //Invocamos el servicio
   printf("Llamada al servicio 'INSERT_AgenciaAutos'\n");
   if (tpcall("INSERT_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}


int clientUpdate_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Inicializamos una referencia bibliografica */
   Autos carro;
  
   printf("\n*************************************************\n");
   printf("Ingrese su ID de cliente: "); scanf("%d", &carro.autoID);
   printf("Ingrese los valores 	que desea actualizar. ");
   printf("Marca: "); scanf("%s", carro.marca);
   printf("Modelo : "); scanf("%s", carro.modelo);
   printf("Anio : "); scanf("%s", carro.anio);
   printf("Color : "); scanf("%s", carro.color);
   printf("Precio : "); scanf("%lf", &carro.precio);
   printf("\n*************************************************\n");


   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, AUTOID, (char *)&carro.autoID, 0) < 0) {
      printf ("\n\tError insertando campo FML (AUTOID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MARCA, (char *)&carro.marca, 0) < 0) {
      printf ("\n\tError insertando campo FML (MARCA)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MODELO, (char *)&carro.modelo, 0) < 0) {
      printf ("\n\tError insertando campo FML (MODELO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, ANIO, (char *)&carro.anio, 0) < 0) {
      printf ("\n\tError insertando campo FML (ANIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, COLOR, (char *)&carro.color, 0) < 0) {
      printf ("\n\tError insertando campo FML (COLOR)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, PRECIO, (char *)&carro.precio, 0) < 0) {
      printf ("\n\tError insertando campo FML (PRECIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }

   //Invocamos el servicio
   printf("Llamada al servicio 'UPDATE_AgenciaAutos'\n");
   if (tpcall("UPDATE_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}


int clientDelete_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Inicializamos una referencia bibliografica */
   Autos carro;
  
   printf("\n*************************************************\n");
   printf("Ingrese su ID de la venta que desea eliminar: \n");
   printf("ID Venta: "); scanf("%d", &carro.autoID);
   printf("\n*************************************************\n");

   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, AUTOID, (char *)&carro.autoID, 0) < 0) {
      printf ("\n\tError insertando campo FML (CARRO ID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   
   //Invocamos el servicio
   printf("Llamada al servicio 'DELETE_AgenciaAutos'\n");
   if (tpcall("DELETE_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}
