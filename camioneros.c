#include <stdlib.h>
#include <libpq-fe.h>
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>
// gcc -o conex conexion.c -I /usr/include/postgresql/ -lpq
//gcc conexion.c -lpq -o cliente
char tab[50], cad[100];
int opc=0;
int i=0,j=0,fila,columna;
PGconn *conn;
PGresult *resultado;
// void menu();
// void consultar_datos();
// void insertar_datos();
// void Modificar();
// void Eliminar();
// void Reporte();


void main(){
	conexion();
	menu();		
}

void menu(){//Empieza men�?- principal
	do{
		printf("***************************** \n");
		printf("***********HOLA************** \n");
		printf("***************************** \n");
		printf("1.-Consultar datos \n");
		printf("2.-Insertar datos \n");
		printf("3.-Modificar datos \n");
		printf("4.-Eliminar datos \n");
		printf("5.-Reporte \n");
		printf("6.-Salir \n");
		printf("Selecciona una opcion: \n");
		scanf("%d",&opc);
		switch(opc){
			case 1: menuconsulta(); break;
			case 2:	menu_insertar_actualizar("INSERTAR");  break;
			case 3: menu_insertar_actualizar("ACTUALIZAR"); break;
			case 4: menueliminar(); break;
			case 5: reporte(); break;
        	default: break;
		}
	}while(opc!=6);
}

void conexion(){//Empieza conexion A BASE DE DATOS
	conn = PQsetdbLogin("localhost","5432",NULL,NULL,"camioneros","postgres","VictorDL");
	if(PQstatus(conn) != CONNECTION_BAD){
		printf("Hola Estamos conectados\n");	
	}else{
	 	printf("error al conectar a la base de datos");
	}		
 }//Termina conexion A BASE DE DATOS
void menuconsulta(){//Empieza men�?- principal
	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");
	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");
	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);
	switch(opc){
		case 1://código que consulta a camiones 
			sprintf(cad,"select * from camiones;");
			resultado = PQexec(conn, cad);
		    if(resultado != NULL){
				fila=PQntuples(resultado);
            	columna=PQnfields(resultado);
			    for (i = 0; i < fila ; i++){
            		for (j = 0; j < columna; j++){
            	    	printf("%s\t",PQgetvalue(resultado,i,j));
					}
					printf("\n");			   				
            	}			     				
            }		
		break;
		case 2: //código que consulta a viajes break;
		case 3: //código que consulta a almacen 
			sprintf(cad,"select * from almacen;");
			resultado = PQexec(conn, cad);
		    if(resultado != NULL){
				fila=PQntuples(resultado);
            	columna=PQnfields(resultado);
			    for (i = 0; i < fila ; i++){
            		for (j = 0; j < columna; j++){
            	    	printf("%s\t",PQgetvalue(resultado,i,j));
					}
					printf("\n");			   				
            	}			     				
            }		
		
		break;
		case 4: //código que consulta a envío break;
		case 5: //código que consulta a tienda break;		
        default: 
            printf("PONGASE LISTO");            
        break;
    }
}
void menu_insertar_actualizar(char operacion[30]){//Empieza insertar 
    char placa[20];
    float cp_peso;
    //----CAMION--------
    int num_via;
    //----VIAJE--------
    int id_envio;
    char origen[30];
    char destino[30];
    int cantidad;
    //----ENVIO----
    int id_t;
    char nom_tienda[30];
    char dir[30];//         <--       
    char tel[15];//         <--
    //----TIENDA---           |
    int id_al;//              |
    char almacen[30];//       |
    //                 --------
    //----ALMACEN--           
	printf("***************************** \n");
	printf("****OPERACION***%s***\n",operacion);
	printf("***************************** \n");
	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");
    printf("Selecciona una opcion: \n");
	scanf("%d",&opc);
	switch(opc){
		case 1: //código que inserta a camiones 
            printf("INGRESE  EL NUMERO DE PLACA: \n");
            scanf("%s",&placa);
            printf("INGRESE LA CAPACIDAD DE PESO DEL CAMION:\n");
            scanf("%f",&cp_peso);            
		break;

		case 2: //código que inserta a viajes 
            printf("INGRESE EL NUMERO DE VIAJE: \n");
            scanf("%s",&num_via);            
		break;

		case 3://código que inserta a almacen 
            printf("INGRESE EL ID DEL ALMACEN:\n");
            scanf("%d",&id_al);
            printf("INGRESE EL ALMACEN:\n");
            scanf("%s",&almacen);
            printf("INGRESE LA DIRECCION DEL ALMACEN %s\n",almacen);
            scanf("%s",&dir);	
			//fflush();		
            printf("INGRESE EL TELEFONO DEL ALMACEN %s\n",almacen);
            scanf("%s",&tel);	
			//fflush();
			//id |    nom_almacen    |    dir    | telefono 
			sprintf(cad,"insert into almacen values(%d,'%s','%s','%s');",id_al,almacen,dir,tel);					
			PQexec(conn, cad);
		break;

		case 4: //código que inserta a envío 
            printf("INGRESE EL ID ENVIO:\n");
            scanf("%d",&id_envio);
            printf("INGRESE EL ORIGEN DEL ENVIO %d\n",id_envio);
            scanf("%s",&origen);				
            printf("INGRESE EL DESTINO DEL ENVIO %d",id_envio);
            scanf("%s",&destino);							
            printf("INGRESE LA CANTIDAD QUE LLEVARÁ EL ENVIO %d\n",id_envio);
            scanf("%d",&cantidad);						
		break;

		case 5: //código que inserta a tienda 
            printf("INGRESE EL ID DE LA TIENDA\n");
            scanf("%d",&id_t);			
            printf("INGRESE EL NOMBRE DE LA TIENDA\n");
            scanf("%s",&nom_tienda);			
            printf("INGRESE LA DIRECCION DE LA TIENDA\n");
            scanf("%s",&dir);								
            printf("INGRESE EL TELEFONO DE LA TIENDA\n");
            scanf("%s",&tel);																							
			//printf("DESEA GUARDAR LOS DATOS INGRESADOS \nID TIENDA %s | NOMBRE %s |DIRECCION %s| ")
		break;
		
        default: 
			printf("ERROR!!! \nPRUEBE INEGRESAR UNA OPCION VALIDA.");
		break;
	}

}//termina insertar 

void menueliminar(){//Empieza menu eliminar
	char d_del[30];
	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");
	printf("1.-Camiones \n");
	printf("2.-Viajes \n");
	printf("3.-Almacen\n \n");
	printf("4.-Envío \n \n");
	printf("5.-Tienda \n \n");
	printf("Selecciona una opcion: \n");
	scanf("%d",&opc);
	switch(opc){
		case 1: //código que elimina a camiones 
			printf("INGRESE LA PLACA DEL CAMION QUE QUIERE ELIMINAR:\n");
			scanf("%s",&d_del);
		break;
		case 2: //código que elimina a viajes 
			printf("INGRESE EL NUMERO DEL VIAJE QUE QUIERE ELIMINAR:\n");
			scanf("%s",&d_del);			
		break;
		case 3: //código que elimina a almacen 
			printf("INGRESE EL ID DEL ALMACEN QUE QUIERE ELIMINAR:\n");
			scanf("%s",&d_del);					
		break;
		case 4: //código que elimina a envío 
			printf("INGRESE EL ID DEL ENVIO QUE DESEA ELIMINAR:\n");
			scanf("%s",&d_del);					
		break;
		case 5: //código que elimina a tienda 
			printf("INGRESE EL ID DE LA TIENDA QUE QUIERE ELIMINAR:\n");
			scanf("%s",&d_del);				
		break;		
        default: //ERROR
			printf("ERROR!!!\n");
		break;
	}
}//termina menu eliminar 
void reporte(){//Empieza reporte

	printf("***************************** \n");
	printf("***********HOLA************** \n");
	printf("***************************** \n");

	

}//termina reporte