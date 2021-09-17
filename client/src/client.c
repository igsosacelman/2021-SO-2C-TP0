#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	config = iniciar_config();

	log_info(logger, "Hola! Soy un log");
	log_info(logger, "Hola! Soy otro log");

	char* log = "Soy un tercer log";
	log_info(logger, log);

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor
	config_set_value(config,"IP","1234");
	config_save_in_file(config, config->path);

	log_info(logger, string_itoa(config_keys_amount(config)));
	log_info(logger, config_get_string_value(config,"IP"));


	//Loggear valor de config

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void) {
	return log_create("logger_tp0","TP0", true, LOG_LEVEL_INFO );
}

t_config* iniciar_config(void) {
	return config_create("tp0.config");
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	// Acá la idea es que imprimas por el log lo que recibis de la consola.


}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete;


}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
