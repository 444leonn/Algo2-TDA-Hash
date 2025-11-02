#include "pa2m.h"
#include "src/constantes.h"
#include "src/hash.h"
#include <stdbool.h>
#include <string.h>

void hash_crear_lo_crea_correctamente_para_cantidad_menor()
{
	hash_t *hash = hash_crear(CANT_INVALIDA);

	pa2m_afirmar(hash != NULL, "Crear un Hash con Cantidad Invalida, lo crea con cantidad minima.");

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_crear_lo_crea_correctamente_para_cantidad_esperada()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	pa2m_afirmar(hash != NULL,
		     "Crear un Hash con Cantidad Valida lo crea.");

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_cantidad_devuelve_0_para_hash_invalido()
{
	size_t cantidad = hash_cantidad(NULL);
	pa2m_afirmar(
		cantidad == 0,
		"Cantidad del Hash es igual a 0 para Hash invalido. (devolvio: %d)",
		cantidad);
}

void hash_cantidad_devuelve_0_para_hash_vacio()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	size_t cantidad = hash_cantidad(hash);
	pa2m_afirmar(
		cantidad == 0,
		"Cantidad del Hash es igual a 0 para un Hash vacio. (devolvio: %d)", cantidad);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_cantidad_devuelve_cantidad_correcta()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);
	hash_insertar(hash, CLAVE_1, (void*)VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, (void*)VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, (void*)VALOR_3, NULL);

	size_t cantidad = hash_cantidad(hash);
	pa2m_afirmar(
		cantidad == 3,
		"Hash Cantidad devuelve la cantidad correcta. (devolvio: %d)",
		cantidad);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_cantidad_devuelve_cantidad_correcta_luego_de_insertar_y_eliminar()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);
	hash_insertar(hash, CLAVE_1, (void*)VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, (void*)VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, (void*)VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, (void*)VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, (void*)VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, (void*)VALOR_6, NULL);
	hash_quitar(hash, CLAVE_1);
	hash_quitar(hash, CLAVE_4);

	size_t cantidad = hash_cantidad(hash);
	pa2m_afirmar(
		cantidad == 4,
		"Hash Cantidad devuelve la cantidad correcta. (devolvio: %d)",
		cantidad);

	if (hash != NULL)
		hash_destruir(hash);
}


void hash_insertar_devuelve_false_para_hash_invalido()
{
	bool resultado = hash_insertar(NULL, CLAVE_1, (void *)VALOR_1, NULL);

	pa2m_afirmar(resultado == false, "Insertar en un Hash inválido, no lo inserta y devuelve false.");
}

void hash_insertar_devuelve_false_para_clave_invalida()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	bool resultado = hash_insertar(hash, NULL, NULL, NULL);
	pa2m_afirmar(
		resultado == false,
		"Insertar una clave inválida en Hash, no lo inserta y devuelve false.");

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_insertar_devuelve_true_si_logra_insertar()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	bool resultado = hash_insertar(hash, CLAVE_1, (void *)VALOR_1, NULL);
	pa2m_afirmar(resultado == true, "Insertar en un Hash válido, inserta el valor y devuelve true.");
}

void hash_insertar_devuelve_true_si_logra_insertar_y_almacena_referencia_del_valor_reemplazado()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);
	hash_insertar(hash, CLAVE_7, (void*)VALOR_7, NULL);
	void *reemplazado;
	hash_insertar(hash, CLAVE_7, (void*)VALOR_8, &reemplazado);

	bool almacenado = strcmp((char*)reemplazado, VALOR_7);

	pa2m_afirmar(reemplazado != NULL && almacenado == true, "Insertar en un Hash valido, reemplaza un elemento anterior y devuelve referencia.");

	if (hash != NULL)
		hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas TDA Hash. ===============");
	pa2m_nuevo_grupo("Pruebas de Creacion:");
	hash_crear_lo_crea_correctamente_para_cantidad_menor();
	hash_crear_lo_crea_correctamente_para_cantidad_esperada();

	pa2m_nuevo_grupo("Pruebas de Cantidad:");
	hash_cantidad_devuelve_0_para_hash_invalido();
	hash_cantidad_devuelve_0_para_hash_vacio();
	hash_cantidad_devuelve_cantidad_correcta();
	hash_cantidad_devuelve_cantidad_correcta_luego_de_insertar_y_eliminar();

	pa2m_nuevo_grupo("Pruebas de Insertar:");
	hash_insertar_devuelve_false_para_hash_invalido();
	hash_insertar_devuelve_false_para_clave_invalida();
	hash_insertar_devuelve_true_si_logra_insertar();
	hash_insertar_devuelve_true_si_logra_insertar_y_almacena_referencia_del_valor_reemplazado();

	return pa2m_mostrar_reporte();
}
