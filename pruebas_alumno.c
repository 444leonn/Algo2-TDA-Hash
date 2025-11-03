#include "pa2m.h"
#include "src/constantes.h"
#include "src/hash.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);

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

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);
	hash_quitar(hash, CLAVE_1);
	hash_quitar(hash, CLAVE_4);

	size_t cantidad = hash_cantidad(hash);
	pa2m_afirmar(
		cantidad == 4,
		"Hash Cantidad devuelve la cantidad correcta, luego de eliminar elementos. (devolvio: %d)",
		cantidad);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_insertar_devuelve_false_para_hash_invalido()
{
	char *p_VALOR_1 = VALOR_1;

	bool resultado = hash_insertar(NULL, CLAVE_1, p_VALOR_1, NULL);

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
	char *p_VALOR_1 = VALOR_1;

	bool resultado = hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	pa2m_afirmar(
		resultado == true,
		"Insertar en un Hash válido, inserta el valor y devuelve true.");

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_insertar_devuelve_true_si_logra_insertar_y_almacena_referencia_del_valor_reemplazado()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_7 = VALOR_7;
	char *p_VALOR_8 = VALOR_8;

	hash_insertar(hash, CLAVE_7, p_VALOR_7, NULL);
	void *reemplazado = NULL;
	hash_insertar(hash, CLAVE_7, p_VALOR_8, &reemplazado);

	bool almacenado = strcmp((char*)reemplazado, VALOR_7) == 0;

	pa2m_afirmar(reemplazado != NULL && almacenado == true, "Insertar en un Hash valido, reemplaza un elemento anterior y devuelve referencia.");

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_buscar_devuelve_null_para_hash_invalido()
{
	void *resultado = hash_buscar(NULL, CLAVE_1);
	pa2m_afirmar(resultado == NULL, "Intentar buscar en un Hash Invalido devuelve NULL. (devolvio: %p)", resultado);
}

void hash_buscar_devuelve_null_para_clave_no_encontrada()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;
	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);

	void *resultado = hash_buscar(hash, CLAVE_7);

	pa2m_afirmar(resultado == NULL, "Intentar buscar una clave inexistente en Hash devuelve NULL. (devolvio: %p)", resultado);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_buscar_devuelve_referencia_al_valor_encontrado()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);

	void *resultado = hash_buscar(hash, CLAVE_4);
	bool son_iguales = strcmp(p_VALOR_4, (char *)resultado) == 0;

	pa2m_afirmar(
		resultado != NULL && son_iguales,
		"Buscar una clave en el Hash la encuentra y devuelve el valor almacenado. (devolvio: %p, esperado: %p)",
		resultado, p_VALOR_4);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_contiene_devuelve_false_para_hash_invalido()
{
	bool resultado = hash_contiene(NULL, CLAVE_1);
	pa2m_afirmar(resultado == false, "Verificar si un valor esta dentro del Hash devuelve FALSE para Hash Invalido.");
}

void hash_contiene_devuelve_false_si_no_contiene_la_clave()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);

	bool resultado = hash_contiene(hash, CLAVE_7);

	pa2m_afirmar(resultado == false, "Verificar si un valor esta dentro del Hash devuelve FALSE si la clave no existe.");

	if (hash != NULL)
		hash_destruir(hash);

}

void hash_contiene_devuelve_true_si_contiene_la_clave()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);

	bool resultado = hash_contiene(hash, CLAVE_4);

	pa2m_afirmar(resultado == true,
		"Verificar si un valor esta dentro del Hash devuelve TRUE si la clave existe");

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_quitar_devuelve_null_para_hash_invalido()
{
	void *resultado = hash_quitar(NULL, CLAVE_1);
	pa2m_afirmar(resultado == NULL, "Intentar quitar clave en Hash Invalido devuelve NULL. (devolvio: %p)", resultado);
}

void hash_quitar_devuelve_null_para_clave_inexistente()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	void *resultado = hash_quitar(hash, CLAVE_1);
	pa2m_afirmar(
		resultado == NULL,
		"Intentar quitar clave Inexistente del Hash devuelve NULL. (devolvio: %p)",
		resultado);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_quitar_quita_el_elemento_y_devuelve_referencia_al_valor_almacenado()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);

	void *resultado = hash_quitar(hash, CLAVE_4);
	bool son_iguales = strcmp(p_VALOR_4, (char*)resultado) == 0;

	pa2m_afirmar(resultado != NULL && son_iguales,
		"Quitar una clave de un Hash, devuelve referencia al elemento que almacenaba. (devolvio: %d, esperado: %d)", resultado, p_VALOR_4);

	if (hash != NULL)
		hash_destruir(hash);
}

void hash_quitar_quita_varios_elementos_y_devuelve_sus_referencias()
{
	hash_t *hash = hash_crear(CAPACIDAD_INICIAL);

	char *p_VALOR_1 = VALOR_1;
	char *p_VALOR_2 = VALOR_2;
	char *p_VALOR_3 = VALOR_3;
	char *p_VALOR_4 = VALOR_4;
	char *p_VALOR_5 = VALOR_5;
	char *p_VALOR_6 = VALOR_6;

	hash_insertar(hash, CLAVE_1, p_VALOR_1, NULL);
	hash_insertar(hash, CLAVE_2, p_VALOR_2, NULL);
	hash_insertar(hash, CLAVE_3, p_VALOR_3, NULL);
	hash_insertar(hash, CLAVE_4, p_VALOR_4, NULL);
	hash_insertar(hash, CLAVE_5, p_VALOR_5, NULL);
	hash_insertar(hash, CLAVE_6, p_VALOR_6, NULL);

	void *resultado_1 = hash_quitar(hash, CLAVE_4);
	bool son_iguales_1 = strcmp(p_VALOR_4, (char*)resultado_1) == 0;

	void *resultado_2 = hash_quitar(hash, CLAVE_1);
	bool son_iguales_2 = strcmp(p_VALOR_1, (char*)resultado_2) == 0;

	pa2m_afirmar(resultado_1 != NULL && resultado_2 != NULL && son_iguales_1 && son_iguales_2,
		"Quitar varias claves de un Hash, devuelve referencia a los elementos que almacenaba. (devolvio: %d y %d, esperado: %d y %d)", resultado_1, resultado_2, p_VALOR_4, p_VALOR_1);

	if (hash != NULL)
		hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("============== Pruebas TDA Hash ===============");
	pa2m_nuevo_grupo("Pruebas de Creación:");
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

	pa2m_nuevo_grupo("Pruebas de Búsqueda:");
	hash_buscar_devuelve_null_para_hash_invalido();
	hash_buscar_devuelve_null_para_clave_no_encontrada();
	hash_buscar_devuelve_referencia_al_valor_encontrado();
	hash_contiene_devuelve_false_para_hash_invalido();
	hash_contiene_devuelve_false_si_no_contiene_la_clave();
	hash_contiene_devuelve_true_si_contiene_la_clave();

	pa2m_nuevo_grupo("Pruebas de Quitar:");
	hash_quitar_devuelve_null_para_hash_invalido();
	hash_quitar_devuelve_null_para_clave_inexistente();
	hash_quitar_quita_el_elemento_y_devuelve_referencia_al_valor_almacenado();
	hash_quitar_quita_varios_elementos_y_devuelve_sus_referencias();

	pa2m_nuevo_grupo("Pruebas de Iterador:");

	return pa2m_mostrar_reporte();
}
