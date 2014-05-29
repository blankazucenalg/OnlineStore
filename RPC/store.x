struct Producto{
	long id;
	char producto[80];
	double precio;
	int existencia;
	char descripcion[255];
};

struct Usuario{
	char login[15];
	char pass[15];
};

program ONLINE_STORE {
    version VERSION_1 {
        Producto obtenerProducto(char*) = 1;
        int comprarProducto(Producto) = 2;
        int quitarProducto(Producto) = 3;
        int iniciarSesion(Usuario) = 4;

    } = 1;
} = 0x20000001; 