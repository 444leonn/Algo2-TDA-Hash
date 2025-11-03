#include "hash.h"
#include "constantes.h"

#include <stdio.h>
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

float calcular_factor_carga(size_t cantidad, size_t capacidad)
{
	return (float)(cantidad % capacidad);
}

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

int funcion_hash(char *clave, size_t capacidad)
{
	if (clave == NULL)
		return ERROR;

	unsigned long hash = 5381;
    int c;

    while ((c = *clave++)) {
        hash = ((hash << 5) + hash) + (unsigned long) c;
    }

	return (int)(hash % capacidad);
}

void rehash(hash_t *hash)
{
	if (hash == NULL)
		return;

	size_t capacidad_anterior = hash->capacidad;
	nodo_t **tabla_anterior = hash->tabla;

	hash->capacidad = 2 * capacidad_anterior;
	hash->tabla = calloc(hash->capacidad, sizeof(nodo_t*));
	if (hash->tabla == NULL) {
		hash->tabla = tabla_anterior;
		hash->capacidad = capacidad_anterior;
		return;
	}

	hash->cantidad = 0;

	for (size_t i = 0; i < capacidad_anterior; i++) {
		nodo_t *actual = tabla_anterior[i];
		while (actual != NULL) {
			nodo_t *siguiente = actual->siguiente;

			int nuevo_indice = funcion_hash(actual->par.clave, hash->capacidad);

			actual->siguiente = hash->tabla[nuevo_indice];
			hash->tabla[nuevo_indice] = actual;
			hash->cantidad++;

			actual = siguiente;
		}
	}

	free(tabla_anterior);

	hash->factor_carga = calcular_factor_carga(hash->cantidad, hash->capacidad);
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
		nodo = calloc(1, sizeof(nodo_t));
		if (nodo == NULL)
			return NULL;

		nodo->par.valor = valor;
		nodo->par.clave = copiar_clave(clave);
		*insertado = true;
		return nodo;
	} else if (strcmp(nodo->par.clave, clave) == 0) {
		if (*encontrado != NULL)
			*encontrado = nodo->par.valor;
		nodo->par.valor = valor;
		*reemplazado = true;
		return nodo;
	}

	nodo->siguiente = hash_insertar_recursivo(nodo->siguiente, clave, valor, encontrado, insertado, reemplazado);

	return nodo;
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

	bool insertado = false, reemplazado = false;
	hash->tabla[clave_hasheada] = hash_insertar_recursivo(hash->tabla[clave_hasheada], clave, valor, encontrado, &insertado, &reemplazado);
	if (insertado == true) {
		hash->cantidad++;
		hash->factor_carga = calcular_factor_carga(hash->cantidad, hash->capacidad);
	}

	return insertado || reemplazado;
}

void *hash_buscar_recursivo(nodo_t *nodo, char *clave)
{
	if (nodo == NULL)
		return NULL;

	if (strcmp(nodo->par.clave, clave) == 0)
		return nodo->par.valor;

	return hash_buscar_recursivo(nodo->siguiente, clave);
}

void *hash_buscar(hash_t *hash, char *clave)
{
	int clave_hasheada = funcion_hash(clave, hash->capacidad);
	if (clave_hasheada == ERROR)
		return NULL;

	return hash_buscar_recursivo(hash->tabla[clave_hasheada], clave);
}

bool hash_contiene(hash_t *hash, char *clave);

nodo_t *hash_quitar_recursivo(nodo_t *nodo, char *clave, void **aux)
{
	if (nodo == NULL)
		return NULL;

	if (strcmp(nodo->par.clave, clave) == 0) {
		*aux = nodo->par.valor;
		nodo_t *siguiente = nodo->siguiente;
		free(nodo->par.clave);
		free(nodo);

		return siguiente;
	}
	nodo->siguiente = hash_quitar_recursivo(nodo->siguiente, clave, aux);

	return nodo;
}

void *hash_quitar(hash_t *hash, char *clave)
{
	int clave_hasheada = funcion_hash(clave, hash->capacidad);
	if (clave_hasheada == ERROR)
		return NULL;

	void *resultado = NULL;
	hash->tabla[clave_hasheada] = hash_quitar_recursivo(
		hash->tabla[clave_hasheada], clave, &resultado);

	if (resultado != NULL) {
		hash->cantidad--;
		hash->factor_carga = calcular_factor_carga(hash->cantidad, hash->capacidad);
	}

	return resultado;
}

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx);

void eliminar_recursivo(nodo_t *nodo, void (*destructor)(void *))
{
	if (nodo == NULL)
		return;

	eliminar_recursivo(nodo->siguiente, destructor);

	if (nodo != NULL) {
		if (destructor != NULL && nodo->par.valor != NULL)
			destructor(nodo->par.valor);
		if (nodo->par.clave != NULL)
			free(nodo->par.clave);
		free(nodo);
	}
}

void hash_destruir(hash_t *hash)
{
	for (size_t i = 0; i < hash->capacidad; i++)
		eliminar_recursivo(hash->tabla[i], NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	for (size_t i = 0; i < hash->capacidad; i++)
		eliminar_recursivo(hash->tabla[i], destructor);
}
