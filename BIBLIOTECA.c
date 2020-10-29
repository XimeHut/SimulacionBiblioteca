#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Variables Globales que introduce el usuario
char titulo[20];
char autor[20];
char editorial[20];
char cantidad[3];
char precio[10];

char datos[80];
char libro[80];
char lib[100];

char Tom [5];
char Res [5];
char Gan [10];


FILE *archivo;
FILE *venta;
FILE *devoluciones;


void obtenerDatos()
{
    printf("TITULO: ");
    gets(titulo);
    gets(titulo);
    
    printf("AUTOR: ");
    gets(autor);
    
    printf("EDITORIAL: ");
    gets(editorial);
    
    printf("CANTIDAD EN EXISTENCIA: ");
    gets(cantidad);
    
    printf("PRECIO: ");
    gets(precio);
    
    strcpy(datos,"");
    strcat(datos,titulo);
    strcat(datos,"_");
    strcat(datos,autor);
    strcat(datos,"_");
    strcat(datos,editorial);
    strcat(datos,"_");
    strcat(datos,cantidad);
    strcat(datos,"_");
    strcat(datos,precio);
    strcat(datos,"\n");
    
    printf("%s",datos);
}

void capturar()
{
    // 1. ABRIR EL ARCHIVO PARA ESCRIBIR
    archivo = fopen("Libros.txt","a");
    
    // 2. Escribir o guardar los datos en el archivo
    fputs(datos,archivo);
    
    // 3. Cerrar el archivo
    fclose(archivo);
}

void consultar()
{
    // 1. Abrir el archivo para leer los datos
    archivo = fopen("Libros.txt","r");
    
    // 2. Leer datos del archivo
    while(fgets(datos,80,archivo) > 0)
        printf("%s",datos);
    
    // 3. Cerrar el archivo
    fclose(archivo);
}

void consultarEditorial()
{
    char tit[20];
    char aut[20];
    char edit[20];
    char ed[20];
    int encontrado=0;
    
    // 1. Obtener la Editorial a consultar
    printf("Editorial a consultar: ");
    gets(editorial);
    gets(editorial);
    
    // 2. Abrir el archivo para leer los datos
    archivo = fopen("Libros.txt","r");
    
    printf("\nLibros de la Editorial: %s\n",editorial);
    
    // 3. Leer datos del archivo
    while(fgets(datos,80,archivo) > 0)
    {
        strcpy(libro,datos);
       
        strcpy(tit,strtok(datos,"_"));
        strcpy(aut,strtok(NULL,"_"));
        strcpy(edit,strtok(NULL,"_"));
        
        if(strcmp(editorial,edit) == 0)
        {
            printf("%s   %s   %s\n",tit,aut,edit);
            printf("Libro: %s\n",libro);
            
            encontrado = 1;
        }
    }
    
    // 4. Cerrar el archivo
    fclose(archivo);
    
    if(encontrado == 0)
        printf("\nNo existen Libros de la Editorial: %s\n",editorial);
}

int encontrarTitulo(char title[])
{
	char tit[20];
	char aut[20];
	char edit[20];
	char cant[5];
	char pre[10];
	
	int encontrado=0;
	char datosLibro[80];
	
	//1. Abrir el archivo para leer
	archivo = fopen("Libros.txt","r");
	
	//2. Procesar el archivo y buscar el titulo
	while((fgets(datosLibro,80,archivo) > 0) && (encontrado ==0))
	{
		strcpy(libro,datosLibro);
		
		strcpy(tit,strtok(datosLibro,"_"));
        strcpy(aut,strtok(NULL,"_"));
        strcpy(edit,strtok(NULL,"_"));
        strcpy(cant,strtok(NULL,"_"));
        strcpy(pre,strtok(NULL,"_"));
        
        if(strcmp(title,tit) == 0)
        {
            encontrado = 1;
            strcpy(titulo,tit);
            strcpy(autor,aut);
            strcpy(editorial,edit);
            strcpy(cantidad,cant);
            strcpy(precio,pre);
        }
	}
	
	//3. Cerrar el archivo
	fclose(archivo);
	//4. Entregar el resultado
	return encontrado;
}

void consultartitulo()
{
	char tit[20];
	int encontrado = 0;
	
	//1. Obtener titulo
	printf("Titulo del libro a buscar: ");
	gets (tit);
	gets (tit);
	
	//2. Buscar el titulo
	encontrado= encontrarTitulo(tit);
	//Si se encuentra el titulo
	if (encontrado ==1)
		//Desplegar datos
		printf("Datos del libro: %s\n", libro);
	//Sino
	else
		//Mensaje "No se localizo"
		printf("No se localizo el libro: %s \n", tit);
}

void procesoventa()
{
	int numeroLibros;
	int ncantidad;
	float fprecio;
	
	char strLibros[20];
	char strCantidad[20];
	char strPrecio[20];

	//1. Obtener el numero de libros
	printf ("Cantidad de libros de la venta: ");
	scanf ("%d", &numeroLibros);
	//2. Actualizar inventario y calcular total venta
	ncantidad = atoi(cantidad); // ALFANUMERICO A ENTERO - PASAR TODO A NUMERICO
	fprecio = atof(precio); // FLOTANTE 
	
	ncantidad = ncantidad - numeroLibros;
	fprecio = fprecio*numeroLibros;
	
	//3. Preparar datos de venta para guardar en el archio Ventas.txt
	sprintf(strLibros," NO. LIBROS: %d", numeroLibros); //CONVERTIR DE 
	sprintf(strCantidad,"SOBRAN: %d", ncantidad); 
	sprintf(strPrecio,"PRECIO TOTAL: %.2f", fprecio); 
	
	strcpy(lib,strtok(libro,"\n"));
	strcat(lib,"_");
	strcat(lib,strLibros);
	strcat(lib,"_");
	strcat(lib,strCantidad);
	strcat(lib,"_"); 
	strcat(lib,strPrecio);
	strcat(lib,"\n"); // PARA QUE BAJA DE RENGLON 
	
	printf("Datos de venta: \n %s", lib);
	
	//4. Almacenar los datos en el archivo Ventas.txt
	venta = fopen("Ventas.txt","a");
    
    // Escribir o guardar los datos en el archivo
    fputs(lib,venta);
    
    // Cerrar el archivo
    fclose(venta);
}

void ventalibros()
{
	char tit[20];
	int encontrado = 0; 
	
	//1. Obtener titulo
	printf("Titulo del libro a vender: ");
	gets (tit);
	gets (tit);
	
	
	//2. Buscar el titulo
	encontrado= encontrarTitulo(tit);
	//Si se encuentra el titulo
	if (encontrado ==1)
		//Desplegar datos
		//printf("Datos del libro: %s\n", libro);
		procesoventa();
	//Sino
	else
		//Mensaje "No se localizo"
		printf("No se localizo el libro: %s \n", tit);
}

void ventas()
{
	venta = fopen("Ventas.txt","r");
    
    // 2. Leer datos del archivo
    printf("Ventas: \n");
    while(fgets(lib,100,venta) > 0)
		printf("%s",lib);
    
    // 3. Cerrar el archivo
    fclose(venta);
}

int encontrarTituloD(char title[])
{
	char tit[20];
	char aut[20];
	char edit[20];
	char cant[5];
	char pre[10];
	char tom [5];
	char res [5];
	char gan [10];
	
	int encontrado=0;
	char datosLibro[80];
	
	//1. Abrir el archivo para leer
	archivo = fopen("Ventas.txt","r");
	
	//2. Procesar el archivo y buscar el titulo
	while((fgets(datosLibro,80,archivo) > 0) && (encontrado ==0))
	{
		strcpy(libro,datosLibro);
		
		strcpy(tit,strtok(datosLibro,"_"));
        strcpy(aut,strtok(NULL,"_"));
        strcpy(edit,strtok(NULL,"_"));
        strcpy(cant,strtok(NULL,"_"));
        strcpy(pre,strtok(NULL,"_"));
        strcpy(tom,strtok(NULL,"_"));
        strcpy(res,strtok(NULL,"_"));
        strcpy(gan,strtok(NULL,"_"));
        
        if(strcmp(title,tit) == 0)
        {
            encontrado = 1;
            strcpy(titulo,tit);
            strcpy(autor,aut);
            strcpy(editorial,edit);
            strcpy(cantidad,cant);
            strcpy(precio,pre);
            strcpy(Tom,tom);
            strcpy(Res,res);
            strcpy(Gan,gan);
         
            
            
        }
	}
	
	//3. Cerrar el archivo
	fclose(archivo);
	//4. Entregar el resultado
	return encontrado;
}

void procesodev ()
{
	int numeroLibros;
	int ncantidad;
	float fprecio;
	float Fprecio;
	
	char strLibros[20];
	char strCantidad[20];
	char strPrecio[20];
	char strTotal[20];

	//1. Obtener el numero de libros a devolver 
	printf ("Cantidad de libros a devolver: ");
	scanf ("%d", &numeroLibros);
	//2. Actualizar inventario y calcular total venta
	ncantidad = atoi(Tom); // ALFANUMERICO A ENTERO - PASAR TODO A NUMERICO
	fprecio = atof(precio); // FLOTANTE 
	Fprecio= atof(Gan);
	
	ncantidad = ncantidad + numeroLibros;
	Fprecio=Fprecio-(fprecio*numeroLibros);
	fprecio = fprecio*numeroLibros;

	//3. Preparar datos de venta para guardar en el archio Ventas.txt
	sprintf(strLibros," NO.DEV: %d", numeroLibros); //CONVERTIR DE 
	sprintf(strCantidad,"RESTAN: %d", ncantidad); 
	sprintf(strPrecio,"DINERO DEV: %.2f", fprecio); 
	sprintf(strTotal,"GANANCIA: %.2f", Fprecio);
	
	strcpy(lib,strtok(libro,"\n"));
	strcat(lib,"_");
	strcat(lib,strLibros);
	strcat(lib,"_");
	strcat(lib,strCantidad);
	strcat(lib,"_"); 
	strcat(lib,strPrecio);
	strcat(lib,"_");
	strcat(lib,strTotal);
	
	strcat(lib,"\n"); // PARA QUE BAJA DE RENGLON 
	
	printf("Datos de devoluciones: \n %s", lib);
	
	//4. Almacenar los datos en el archivo Ventas.txt
	devoluciones = fopen("Devoluciones.txt","a");
    
    // Escribir o guardar los datos en el archivo
    fputs(lib,devoluciones);
    
    // Cerrar el archivo
    fclose(devoluciones);
	

	
}

void dev()
{
	
	char tit [20];
	int encontrado = 0;
//ENCONTRAR TITULO 

	printf ("TITULO A DEVOLVER: ");
	gets (tit);
	gets (tit);
//	BUSCAR TITULO

encontrado = encontrarTituloD(tit);
	//Si se encuentra el titulo
	if (encontrado ==1)
		//Desplegar datos
		//printf("Datos del libro: %s\n", libro);
		procesodev();
	//Sino
	else
		//Mensaje "No se localizo"
		printf("No se ha vendido ese libro: %s \n", tit);
}	
	
void consulatadev ()
{
	devoluciones = fopen("Devoluciones.txt","r");
    
    // 2. Leer datos del archivo
    printf("Devoluciones: \n");
    while(fgets(lib,100,devoluciones) > 0)
		printf("%s",lib);
    
    // 3. Cerrar el archivo
    fclose(devoluciones);
}

void opciones()
{
    int opcion;
    
    do
    {
        // 1. Mostrar opciones al usuario
        printf("\n   BOOK STORE TEC\n");
        printf("1) Capturar datos\n");
        printf("2) Consultar datos\n");
        printf("3) Consultar por Editorial\n");
        printf("4) Consultar por TItulo\n");
        printf("5) Venta de libros\n");
        printf("6) Consulta DE ventas \n");
        printf("7) Devolucion de libros\n");
        printf("8) Consulta de devoluciones \n");
        printf("9) Exit\n");
        printf("   Opcion = ");
        
        // 2. Obtener la opcion
        scanf("%d",&opcion);
        
        // 3. Checar opciones y realizar transaccion correspondiente
        if(opcion == 1)
        {
            obtenerDatos();
            capturar();
        }
        
        if(opcion == 2)
            consultar();
        
        if(opcion == 3)
            consultarEditorial();
    
    	if(opcion == 4)
			consultartitulo();
        
        if (opcion == 5)
        	ventalibros();
        	
        if (opcion == 6)
        	ventas();
        	
         if (opcion== 7)
        	dev();
        	
        if (opcion == 8)	
        	consulatadev ();
        	
				
        system("pause");
		system("cls");
    }while(opcion = 9);
}

int main()
{
    opciones();
}
