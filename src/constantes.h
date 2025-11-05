#ifndef CONSTANTES_H_
#define CONSTANTES_H_

// CODIGOS DE ESCAPE PARA COLORES
#define TROJO "\x1b[31m"
#define TNORMAL "\x1b[0m"

// MODOS DE APERTURA DE ARCHIVO
#define MODO_LECTURA "r"
#define MODO_ESCRITURA "w"

// VALORES PARA INICIALIZACIONES
#define TAMAÑO_INICIAL 15
#define CAPACIDAD_INICIAL 4
#define CAPACIDAD_MINIMA 3

#define CANT_INVALIDA 1
#define ERROR -1
#define TIPO_INVALIDO -1
#define POSICION_INVALIDA -1

// PARA VALIDAR PARAMETROS
#define OPCION_ID "idIDIdiD"
#define OPCION_NOMBRE "nombrenombrEnombREnomBREnoMBREnOMBRENOMBRE"

// MENSAJES DE ERROR
#define CANT_PARAMETROS \
	"Error, debe ingresar una cantidad de parametros valida."
#define PARAMETRO_INVALIDO "Error, parametro ingresado invalido."
#define FALLO_LECTURA_ARCHIVO "Error, ha falla la lectura del archivo."
#define FALLO_CREACION_ABB "Error, ha fallado creacion de ABB."
#define FALLO_CREACION_HASH "Error, ha fallado creacion de HASH."
#define NO_ENCONTRADO "El Pokemon no ha sido encontrado."
#define OPCION_INVALIDA "Error, opcion de busqueda invalida."

// CONSTANTES PARA PRUEBAS DE HASH
#define CLAVE_1 "papa"
#define VALOR_1 "blanca"

#define CLAVE_2 "tomate"
#define VALOR_2 "rojo"

#define CLAVE_3 "lechuga"
#define VALOR_3 "verde"

#define CLAVE_4 "zanahoria"
#define VALOR_4 "naranja"

#define CLAVE_5 "banana"
#define VALOR_5 "amarilla"

#define CLAVE_6 "berenjena"
#define VALOR_6 "violeta"

#define CLAVE_7 "aceituna"
#define VALOR_7 "negra"
#define VALOR_8 "verde"

#endif // CONSTANTES_H_
