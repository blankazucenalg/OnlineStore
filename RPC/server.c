/* Simple C program that connects to MySQL Database server*/
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Usuario{
   char login[15];
   char pass[15];
}Usuario;

typedef struct Producto
{
   int idCategoria;
   char *producto;
   float precio;
   int existencia;
   char *descripcion;
}Producto;

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
   char *aux = (char * )malloc(sizeof(char)*200);
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
      sprintf(aux,"%s",row[0]);
      desconectarBD();
      return atoi(aux);
   } else {
      desconectarBD();
      return 0;
   }
}

const char* consultarProductos(){
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
      return resultado;
}

const char* obtenerProducto(char *criteria){
   conectarBD();
   char query[500];
   char *header,*aux;
   char *resultado = (char *)malloc(sizeof(char)*BUFSIZ);
   header = "Id\tProducto\tPrecio\tExistencia\tDescripcion\n";
   aux = (char *)malloc(sizeof(char)*1024);

   sprintf(query,"select * from producto where nb_producto like '%%%s%%' or dx_descripcion like '%%%s%%'",criteria,criteria);
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
      return resultado;
}

char* agregarProducto(Producto *p){
      conectarBD();
   char query[500];
   char *header,*aux;
   char *resultado = (char *)malloc(sizeof(char)*BUFSIZ);
   header = "Id\tProducto\tPrecio\tExistencia\tDescripcion\tCateg\n";
   aux = (char *)malloc(sizeof(char)*1024);

   sprintf(query,"insert into producto (id_categoria, nb_producto, nu_precio, nu_existencia, dx_descripcion) values (%d,'%s',%f,%d,'%s')",p->idCategoria,p->producto, p->precio, p->existencia, p->descripcion);
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
   /* output table name */
   sprintf(resultado,"%s", header);
   if ((row = mysql_fetch_row(res)) != NULL) {
      resultado = "Insertado con éxito.";
   } else {
      resultado = "Error al insertar";
   }
   desconectarBD();
      return resultado;
}

main() {
   int opc, userType;
   char *criteria = malloc(sizeof(char)*200);
   Usuario* yo = malloc(sizeof(Usuario));
   Producto* p = malloc(sizeof(Producto));
   printf("Usuario: ");
   scanf("%15s",yo->login);
   printf("Contraseña: ");
   scanf("%15s",yo->pass);
   conectarBD();
   userType = iniciarSesion(yo);
   if(userType == 1){
      do{ 
      //Admin User
         printf("\nAdministrador \n1. Mostrar productos \n2. Buscar un producto \n3. Agregar productos \n4. Cerrar sesión y salir\nSeleccione una opción: ");
         scanf("%d",&opc);
         switch(opc){
            case 1:
               printf("%s",consultarProductos());
               break;
            case 2:
               printf("Busqueda: ");
               scanf("%s",criteria);
               printf("%s", obtenerProducto(criteria));
               break;
            case 3: //Add products
               printf("Introduce a continuación los datos del producto\n");
               printf("idCategoria: ");
               scanf("%d",&(p->idCategoria));
               printf("Nombre: ");
               scanf("%s",p->producto);
               printf("Precio: ");
               scanf("%f",&(p->precio));
               printf("Existencia: ");
               scanf("%d",&(p->existencia));
               printf("Descripción: ");
               scanf("%s",p->descripcion);
               printf("%s\n", agregarProducto(p));

               break;
            case 4:
               printf("Bye\n");
               break;
            default:
               break;
         }
      }while(opc!=4);
   }else if(userType > 0){
      do{ //Common User
         printf("\n1. Mostrar productos \n2. Buscar un producto \n3. Comprar productos \n4. Cerrar sesión y salir\nSeleccione una opción: ");
         scanf("%d",&opc);
         switch(opc){
            case 1:
               printf("%s",consultarProductos());
               break;
            case 2:
               printf("Busqueda: ");
               scanf("%s",criteria);
               printf("%s", obtenerProducto(criteria));
               break;
            case 3: //Buy products
               break;
            case 4:
               printf("Bye\n");
               break;
            default:
               break;
         }
      }while(opc!=4);
   } else {
      printf("No se encuentra el usuario\n");
   }
}

