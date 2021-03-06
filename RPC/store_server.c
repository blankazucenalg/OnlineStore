/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "store.h"
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *server = "127.0.0.1";
char *user = "root";
char *password = "n0m3l0s3"; /* set me first */
char *database = "carritocompras";

void conectarBD(){
   conn = mysql_init(NULL);
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
}

void desconectarBD(){
   /* close connection */
   mysql_free_result(res);
   mysql_close(conn);
}

int *
iniciarsesion_1_svc(Usuario *argp, struct svc_req *rqstp)
{
	static int  result;

	char *aux = (char * )malloc(sizeof(char)*200);
   conectarBD();
   char query[500];
   sprintf(query,"select * from usuario where tx_login='%s' and tx_password='%s'",argp->login,argp->pass);
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   if ((row = mysql_fetch_row(res)) != NULL) {
      sprintf(aux,"%s",row[0]);
      printf("Inicia sesión\n");
      desconectarBD();
      result = atoi(aux);
   } else {
      printf("No se encuentra el usuario\n");
      desconectarBD();
      result = 0;
   }
	return &result;
}

char **
consultarproductos_1_svc(char **argp, struct svc_req *rqstp)
{
	static char * result;

	conectarBD();
   char query[500];
   char *header,*aux;
   char *resultado = (char *)malloc(sizeof(char)*BUFSIZ);
   header = "Id\tProducto\tPrecio\tExistencia\tDescripcion\n";
   aux = (char *)malloc(sizeof(char)*1024);

   sprintf(query,"select * from producto");
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   sprintf(resultado,"%s", header);
   while ((row = mysql_fetch_row(res)) != NULL) {
      sprintf(aux,"%s\t%s\t$%s\t%s\t\t%s\n", row[0],row[2],row[3],row[4],row[5]);
      //printf("%s",aux);
      strncat(resultado,aux,1024);
   }
   desconectarBD();
   return &resultado;
}

char **
obtenerproducto_1_svc(char **argp, struct svc_req *rqstp)
{
	static char * result;

	conectarBD();
   char query[500];
   char *header,*aux;
   char *resultado = (char *)malloc(sizeof(char)*BUFSIZ);
   header = "Id\tProducto\tPrecio\tExistencia\tDescripcion\n";
   aux = (char *)malloc(sizeof(char)*1024);

   sprintf(query,"select * from producto where nb_producto like '%%%s%%' or dx_descripcion like '%%%s%%'",*argp,*argp);
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   sprintf(resultado,"%s", header);
   while ((row = mysql_fetch_row(res)) != NULL) {
      sprintf(aux,"%s\t%s\t$%s\t%s\t\t%s\n", row[0],row[2],row[3],row[4],row[5]);
      //printf("%s",aux);
      strncat(resultado,aux,1024);
   }
   desconectarBD();
   return &resultado;
}

int *
comprarproducto_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *
quitarproducto_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

int*
agregarproducto_1_svc(Producto *argp, struct svc_req *rqstp)
{
	static int  result;

	conectarBD();
   char query[500];
   sprintf(query,"insert into producto (id_categoria, nb_producto, nu_precio, nu_existencia, dx_descripcion) values (%d,'%s',%f,%d,'%s')",argp->idCategoria,argp->producto, argp->precio, argp->existencia, argp->descripcion);
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   //if ((row = mysql_fetch_row(res)) != NULL) {
   //   printf("Insertado\n");
   //} else {
    //  printf("No insertado\n");
   //}
   desconectarBD();
	return &result;
}
