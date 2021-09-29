#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip = string_new();
	char* puerto = string_new();
	char* valor = string_new();

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger,"Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	if(config == NULL)
	{

		log_error(logger,"No se pudo abrir el archivo de configuracion.");
		return -1;

	}

	string_append(&ip, config_get_string_value(config, "IP"));
	string_append(&puerto, config_get_string_value(config, "PUERTO"));
	string_append(&valor, config_get_string_value(config, "CLAVE"));

	// Loggeamos el valor de config

	log_info(logger, ip);
	log_info(logger, puerto);
	log_info(logger, valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	if(conexion == -1) // Error de conexion
	{
		log_error(logger, "Error al realizar conexion con el servidor");
		return 0;
	}

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);

	// enviar_mensaje_por_consola(logger, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	return log_create("tp0.log","TP0",true,LOG_LEVEL_DEBUG);
}

t_config* iniciar_config(void)
{
	return config_create("../cliente.config");
}

void leer_consola(t_log* logger)
{
	char* leido;

	leido = readline("> ");

	while(!string_is_empty(leido)) {
		log_info(logger,leido);
		free(leido);
		leido = readline("> ");
	}

	free(leido);
}

void enviar_mensaje_por_consola(t_log* logger, int conexion)
{
	char* leido;

	leido = readline("> ");

	while(!string_is_empty(leido)) {
		log_info(logger,leido);
		enviar_mensaje(leido, conexion);
		free(leido);
		leido = readline("> ");
	}

	free(leido);
}

void paquete(int conexion)
{
	// Leemos y esta vez agregamos las lineas al paquete

	char* leido;
	t_paquete* paquete = crear_paquete();

	leido = readline("> ");

	while(!string_is_empty(leido)) {
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
		leido = readline("> ");
	}

	enviar_paquete(paquete, conexion);
	
	eliminar_paquete(paquete);
	free(leido);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
