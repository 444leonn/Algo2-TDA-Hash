#include "hash.h"
#include "constantes.h"

#include <stdlib.h>
#include <string.h>

typedef struct par {
    char *clave;
	void *valor;
} par_t;

typedef struct nodo
{
	struct par par;
	struct nodo *siguiente;
} nodo_t;

struct hash {
	struct nodo **tabla;
	size_t capacidad;
	size_t cantidad;
	float factor_carga;
};

hash_t *hash_crear(size_t capacidad_inicial)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (hash == NULL)
		return NULL;

	if (capacidad_inicial < CAPACIDAD_MINIMA) {
		hash->tabla = calloc(CAPACIDAD_MINIMA, sizeof(nodo_t*));
		hash->capacidad = CAPACIDAD_MINIMA;
	} else {
		hash->tabla = calloc(capacidad_inicial, sizeof(nodo_t*));
		hash->capacidad = capacidad_inicial;
	}

	return hash;
}

size_t hash_cantidad(hash_t *hash)
{
	if (hash == NULL)
		return 0;

	return hash->cantidad;
}

// FIXME: Esta funcion esta mal, muchas colision (ver de usar djb2 o quizas acumular los valores ascii de la clave y despues dividirlo)
int funcion_hash(char *clave, size_t capacidad)
{
	if (clave == NULL)
		return ERROR;

	size_t largo = strlen(clave);
	return largo % capacidad;
}

void rehash(hash_t *hash)
{
	if (hash == NULL)
		return;

	hash_t *aux = realloc(hash, 2 * (hash->capacidad));
	if (aux == NULL)
		return;
	hash = aux;
	hash->capacidad = 2 * hash->capacidad;
	hash->factor_carga = (float) hash->cantidad / hash->capacidad;
}

char *copiar_clave(char *clave)
{
	size_t largo = strlen(clave) + 1;
	char *aux = malloc(largo * sizeof(char));
	if (aux == NULL)
		return NULL;

	return strcpy(aux, clave);
}

nodo_t *hash_insertar_recursivo(nodo_t *nodo, char *clave, void *valor,
			void **encontrado, bool *insertado, bool *reemplazado)
{
	if (nodo == NULL) {
		nodo = malloc(sizeof(nodo_t));
		if (nodo == NULL)
			return NULL;

		nodo->par.valor = valor;
		nodo->par.clave = copiar_clave(clave);
		*insertado = true;
		return nodo;
	} else if (strcmp(nodo->par.clave, clave) == 0 && *encontrado != NULL) {
		*encontrado = nodo->par.valor;
		nodo->par.valor = valor;
		*reemplazado = true;
		return nodo;
	}

	return hash_insertar_recursivo(nodo->siguiente, clave, valor, encontrado, insertado, reemplazado);
}


bool hash_insertar(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	if (hash == NULL || clave == NULL)
		return false;

	if (hash->factor_carga >= 0.75)
		rehash(hash);

	int clave_hasheada = funcion_hash(clave, hash->capacidad);
	if (clave_hasheada == ERROR)
		return false;
	if (clave_hasheada > hash->capacidad)
		clave_hasheada = hash->capacidad - 1;

	bool insertado = false, reemplazado = false;
	hash->tabla[clave_hasheada] = hash_insertar_recursivo(hash->tabla[clave_hasheada], clave, valor, encontrado, &insertado, &reemplazado);
	if (insertado == true) {
		hash->cantidad++;
		hash->factor_carga = (float)hash->cantidad / hash->capacidad;
	}

	return insertado || reemplazado;
}

void *hash_buscar(hash_t *hash, char *clave);

bool hash_contiene(hash_t *hash, char *clave);

void *hash_quitar(hash_t *hash, char *clave);

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx);

void hash_destruir(hash_t *hash);

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *));
