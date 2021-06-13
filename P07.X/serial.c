/** @brief: Este programa muestra el uso del UART
*/
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define N  4096
#define EVER 1
#define RESET_COLOR		"\x1b[0m"
#define AMARILLO_TEXTO	"\x1b[33m"
#define MAGENTA_TEXTO	"\x1b[35m"
#define CYAN_TEXTO		"\x1b[36m"

int config_serial ( char *, speed_t );
void guardaDatos( unsigned char datos[] );

int main()
{
	register int i;
	int fd_serie, tam_Cad;
	unsigned char dato;
	unsigned char cad[16];
	unsigned char cad2[]=" ";

	fd_serie = config_serial( "/dev/ttyUSB0", B9600 );
	printf(AMARILLO_TEXTO"\n\t  *******    Practica 7: UART    ******* \n"RESET_COLOR);
	printf(MAGENTA_TEXTO"\n  serial abierto con descriptor: %d  \n"RESET_COLOR, fd_serie);

	do{
		printf(CYAN_TEXTO"\n  Ingrese una cadena > "RESET_COLOR);
		fgets(cad,16,stdin); fflush(stdin);
		tam_Cad = strlen(cad) - 1;

		for(i=0;cad[i]!='\n';i++){
			dato = cad[i];
		    write( fd_serie, &dato, 1 );		
		}

		for(i=0;i<(80-tam_Cad);i++){
			dato = cad2[0];
		    write( fd_serie, &dato, 1 );
		}
	}while(strcmp(cad,"exit\n")!=0);

	//Leemos N datos del UART
	/*
	dato = 0;
	for( i = 0; i < N; i++ )
	{
		read( fd_serie, &dato, 1 );
		printf("%c \n", dato );
	}
	*/

	close( fd_serie );

	return 0;
}

void guardaDatos( unsigned char datos[] )
{
        FILE *apArch;
        register int n;

        apArch = fopen("pulso.dat", "w");
        if( apArch == NULL )
        {
                perror("Error al abrir el archivo");
                exit(EXIT_FAILURE);
        }
        for( n = 0; n < N; n++ )
        {
                fprintf(apArch, "%d \n",datos[n]);
        }
        fclose(apArch);
}


/** @brief: Esta funcion Configura la interfaz serie
 *  @param: dispositivo_serial, Nombre el dispositivo serial a usar: ttyUSB0, ttyUSB1, etc
 *  @param: baudios, Velocidad de comunicacion. Se usa la constante Bxxxx, donde xxxx  es la
 *          velocidad. Estan definidas en termios.h. Ejemplo: B9600, B19200, B115200 ...
 *  @return: fd, Descriptor del serial
 *******************************************************************************************
 */
int config_serial( char *dispositivo_serial, speed_t baudios )
{
	struct termios newtermios;
  	int fd;
/*
 * Se abre un descriptor de archivo para manejar la interfaz serie
 * O_RDWR - Se abre el descriptor para lectura y escritura
 * O_NOCTTY - El dispositivo terminal no se convertira en el terminal del proceso
 * ~O_NONBLOCK - Se hace bloqueante la lectura de datos
 */
  	fd = open( dispositivo_serial, (O_RDWR | O_NOCTTY) & ~O_NONBLOCK );
	if( fd == -1 )
	{
		printf("Error al abrir el dispositivo tty \n");
		exit( EXIT_FAILURE );
  	}
/*
 * cflag - Proporciona los indicadores de modo de control
 *	CBAUD	- Velocidad de transmision en baudios.
 * 	CS8	- Especifica los bits por dato, en este caso 8
 * 	CLOCAL 	- Ignora las lineas de control del modem: CTS y RTS
 * 	CREAD  	- Habilita el receptor del UART
 * iflag - proporciona los indicadores de modo de entrada
 * 	IGNPAR 	- Ingnora errores de paridad, es decir, comunicación sin paridad
 * oflag - Proporciona los indicadores de modo de salida
 * lflag - Proporciona indicadores de modo local
 * 	TCIOFLUSH - Elimina datos recibidos pero no leidos, como los escritos pero no transmitidos
 * 	~ICANON - Establece modo no canonico, en este modo la entrada esta disponible inmediatamente
 * cc[]	 - Arreglo que define caracteres especiales de control
 *	VMIN > 0, VTIME = 0 - Bloquea la lectura hasta que el numero de bytes (1) esta disponible
 */
	newtermios.c_cflag 	= CBAUD | CS8 | CLOCAL | CREAD;
  	newtermios.c_iflag 	= IGNPAR;
  	newtermios.c_oflag	= 0;
  	newtermios.c_lflag 	= TCIOFLUSH | ~ICANON;
  	newtermios.c_cc[VMIN]	= 1;
  	newtermios.c_cc[VTIME]	= 0;

// Configura la velocidad de salida del UART
  	if( cfsetospeed( &newtermios, baudios ) == -1 )
	{
		printf("Error al establecer velocidad de salida \n");
		exit( EXIT_FAILURE );
  	}
// Configura la velocidad de entrada del UART
	if( cfsetispeed( &newtermios, baudios ) == -1 )
	{
		printf("Error al establecer velocidad de entrada \n" );
		exit( EXIT_FAILURE );
	}
// Limpia el buffer de entrada
	if( tcflush( fd, TCIFLUSH ) == -1 )
	{
		printf("Error al limpiar el buffer de entrada \n" );
		exit( EXIT_FAILURE );
	}
// Limpia el buffer de salida
	if( tcflush( fd, TCOFLUSH ) == -1 )
	{
		printf("Error al limpiar el buffer de salida \n" );
		exit( EXIT_FAILURE );
	}
/*
 * Se establece los parametros de terminal asociados con el
 * descriptor de archivo fd utilizando la estructura termios
 * TCSANOW - Cambia los valores inmediatamente
 */
	if( tcsetattr( fd, TCSANOW, &newtermios ) == -1 )
	{
		printf("Error al establecer los parametros de la terminal \n" );
		exit( EXIT_FAILURE );
	}
//Retorna el descriptor de archivo
	return fd;
}
