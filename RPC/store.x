struct Usuario{
	char login[15];
	char pass[15];
};

struct Producto
{
   int idCategoria;
   char producto[80];
   float precio;
   int existencia;
   char descripcion[255];
};

program ONLINE_STORE {
    version VERSION_1 {
    	int iniciarSesion(Usuario) = 1;
    	string consultarProductos(string) = 2;
        string obtenerProducto(string) = 3;
        int comprarProducto(int) = 4;
        int quitarProducto(int) = 5;
        int agregarProducto(Producto) = 6;
    } = 1;
} = 0x20000001; 