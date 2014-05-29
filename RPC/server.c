/* Simple C program that connects to MySQL Database server*/
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Usuario{
   char login[15];
   char pass[15];
}Usuario;

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

int iniciarSesion(Usuario* u){
   conectarBD();
   char query[500];
   sprintf(query,"select * from usuario where tx_login='%s' and tx_password='%s'",u->login,u->pass);
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   if ((row = mysql_fetch_row(res)) != NULL) {
      desconectarBD();
      return 1;
   } else {
      desconectarBD();
      return 0;
   }
}

char* consultarProductos(){
   conectarBD();
   char query[500];
   char* resultado,*aux;
   sprintf(query,"select * from producto");
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   *resultado = "Id\tProducto\tPrecio\tExistencia\tDescripcion\n";
   while ((row = mysql_fetch_row(res)) != NULL)
      sprintf(aux,"%s\t%s\t\t$%s\t%s\t\t%s\n", row[0],row[2],row[3],row[4],row[5]);
      strcat(resultado,aux);
   desconectarBD();
      return resultado;
}


main() {
   Usuario* yo = malloc(sizeof(Usuario));
   printf("Usuario: ");
   scanf("%15s",yo->login);
   printf("Contraseña: ");
   scanf("%15s",yo->pass);
   conectarBD();
   if(iniciarSesion(yo)){
      printf("%s",consultarProductos());
   } else {
      printf("No se encuentra el usuario\n");
   }
     
}

