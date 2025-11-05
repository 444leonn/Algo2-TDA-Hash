#include "src/hash.h"
#include "src/tp1.h"
#include "src/aux_tp1.h"
#include "src/constantes.h"

#include <stdio.h>
#include <string.h>

bool validar_opcion_id(char *opcion)
{
	return strstr(OPCION_ID, opcion) != NULL;
}

bool validar_opcion_nombre(char *opcion)
{
	return strstr(OPCION_NOMBRE, opcion) != NULL;
}

bool insertar_pokemon_hash_id(struct pokemon *un_pokemon, void *hash)
{
	if (hash == NULL)
		return false;
	struct hash *_hash = hash;

	char clave_id[50];
	sprintf(clave_id, "%d", un_pokemon->id);

	return hash_insertar(_hash, clave_id, un_pokemon, NULL);
}

bool insertar_pokemon_hash_nombre(struct pokemon *un_pokemon, void *hash)
{
	if (hash == NULL)
		return false;
	struct hash *_hash = hash;

	return hash_insertar(_hash, un_pokemon->nombre, un_pokemon, NULL);
}

void realizar_busqueda_id(tp1_t *tp1, char *id_buscado)
{
	size_t capacidad_hash = tp1_cantidad(tp1) * 2;

	hash_t *hash_pokemones_id = hash_crear(capacidad_hash);
	if (hash_pokemones_id == NULL) {
		printf(TROJO FALLO_CREACION_HASH TNORMAL "\n");
		return;
	}
	tp1_con_cada_pokemon(tp1, insertar_pokemon_hash_id, hash_pokemones_id);

	struct pokemon *resultado_busqueda =
		hash_buscar(hash_pokemones_id, id_buscado);
	if (resultado_busqueda != NULL)
		mostrar_pokemon(resultado_busqueda, NULL);
	else
		printf(TROJO NO_ENCONTRADO TNORMAL "\n");

	hash_destruir(hash_pokemones_id);
}

void realizar_busqueda_nombre(tp1_t *tp1, char *nombre)
{
	size_t capacidad_hash = tp1_cantidad(tp1) * 2;

	hash_t *hash_pokemones_nombre = hash_crear(capacidad_hash);
	if (hash_pokemones_nombre == NULL) {
		printf(TROJO FALLO_CREACION_HASH TNORMAL "\n");
		return;
	}
	tp1_con_cada_pokemon(tp1, insertar_pokemon_hash_nombre,
			     hash_pokemones_nombre);

	struct pokemon *resultado_busqueda =
		hash_buscar(hash_pokemones_nombre, nombre);
	if (resultado_busqueda != NULL)
		mostrar_pokemon(resultado_busqueda, NULL);
	else
		printf(TROJO NO_ENCONTRADO TNORMAL "\n");

	hash_destruir(hash_pokemones_nombre);
}

int main(int argc, char *argv[])
{
	if (argc < 4) {
		printf(TROJO CANT_PARAMETROS TNORMAL "\n");
		return 1;
	}
	if (strcmp(argv[2], "buscar") != 0) {
		printf(TROJO PARAMETRO_INVALIDO TNORMAL "\n");
		return 1;
	}

	tp1_t *tp = tp1_leer_archivo(argv[1]);
	if (tp == NULL) {
		printf(TROJO FALLO_LECTURA_ARCHIVO TNORMAL "\n");
		return 1;
	}

	if (validar_opcion_id(argv[3]))
		realizar_busqueda_id(tp, argv[4]);
	else if (validar_opcion_nombre(argv[3]))
		realizar_busqueda_nombre(tp, argv[4]);
	else
		printf(TROJO OPCION_INVALIDA TNORMAL "\n");

	tp1_destruir(tp);

	return 0;
}
