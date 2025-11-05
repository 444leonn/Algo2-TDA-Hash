<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Leon Acosta - 113246 - leacosta@fi.uba.ar

- Para la compilacion y ejecucion del programa se provee un **makefile**.

  - Compilar:

    ```bash
    # compilar el programa
    make hash
    # compilar las pruebas
    make pruebas_alumno
    ```

  - Ejecutar:

    ```bash
    # correr el programa
    make ejecutar PARAMETROS="<parametros>"
    # correr con el programa valgrind
    make valgrind PARAMETROS="<parametros>"
    # correr las pruebas
    make valgrind-alumno
    ```

> [!IMPORTANT]
> Los parametros que se deben pasar entre "" corresponden al nombre de un archivo con pokemones, y tres parametros extra los cuales son busqueda, nombre o id, nombre del pokemon buscado o ID del pokemon buscado.
>
> Ejemplo: `make ejecutar PARAMETROS="./ejemplos/normal.csv buscar nombre Pikachu"` O `make ejecutar PARAMETROS="./ejemplos/normal.csv buscar id 1"`

--- 

##  Funcionamiento

El programa funciona recibiendo por parámetro el nombre de un archivo el cual contiene datos de pokemones, se encarga de hacer las verificaciones necesarias.  
Luego se encarga de leerlo línea por línea, y parseando cada línea en una estructura de _pokemon_, cada pokemon es almacenado luego en una estructura `tp1_t`.  
A partir de esa estructura es que se utiliza la implementación del **TDA Hash**. En donde se crea una Tabla de Hash **(revisar esto)** dependiendo si la opción de búsqueda era por número de ID, o por Nombre de Pokemon, permitiendo diferenciar la manera en que se organizara la jerarquía de nuestro Diccionario en la Tabla de Hash.

## Implementación

Para la implementación de la estructura de Hash decidí utilizar las siguientes estructuras auxiliares:

- **`struct nodo`**: en el que se guarda el par de clave y valor y una referencia al siguiente nodo.
- **`struct par`**: se guarda la clave y una referencia al valor que se quiere almacenar.

Luego la estructura de hash contiene un vector dinámico de nodos el cual va a ser precisamente la _Tabla de Hash_, y tres variables que almacenan, la cantidad de elementos almacenados, la capacidad total que se puede almacenar, y el factor de carga total de la tabla.

### Creación

A la hora de crear una Tabla de Hash, es necesario indicar el tamaño con el que va a contar inicialmente.  
Si este tamaño es menor a una capacidad mí	nima de 3, se crea la tabla de hash con esa capacidad mínima.  
Se utiliza la funcion `calloc()` de la biblioteca estandard para reservar la memoria e inicializar en 0 tanto para la estructura como la tabla.

#### Complejidad Temporal

La complejidad temporal de la creación podemos decir que es _O(1)_, ya que aunque utiliza `calloc()` que incializa en `NULL` o `0` las variables, siempre realizamos la misma cantidad de operaciones, modficando unicamente la cantidad de memoria que debe reservar `calloc()` para la `tabla`.

### Inserción

La inserción me resulto personalmente una de las operaciones mas difíciles de realizar ya que se debe tener cuidado con el _factor de carga_ de nuestra Tabla.  
Para ello lo primero que se verifica es que el mismo no supere el _0.75_ si lo supera se redimiensiona la tabla con la funcion de _rehash_.  
Luego se utiliza la _función de hash_ para transformar la clave en un numero que utilizaremos como indice para insertar en nuestra tabla.  
Finalmente se inserta la clave y el valor de manera recursiva en nuestra tabla, actualizando la cantidad y el factor de carga.

#### Rehash

Esta función se encarga del redimiensionamiento de la tabla.  
Para ello guarda la referencia a la tabla anterior, y crea una nueva con el doble de capacidad.  
Luego se encarga de reubicar cada uno de los nodos de la tabla anterior en la nueva, de manera tal que se vuelve a aplicar a cada clave la función de hash.  
Finalmente se recalcula el factor de carga, para la nueva capacidad de la tabla.

#### Función de Hash

Este módulo se encarga de transformar una string en un número asociado.  
Lo hace a partir del algoritmo _DJB2_ y con el método de la división.  
Este algoritmo se encarga de acumular el valor como entero de cada caracter (`c`), y luego acumularlo en la variable `hash` multiplicandola y luego sumandole el valor de `c`.  
Finalemente la funcion retorna el resultado de la operacion modulo entre lo acumulado y la capacidad total de la tabla.  
En el caso de que la clave pasada sea `NULL` o que la capacidad de la tabla sea menor a la minima, devuelve un valor negativo.

#### Complejidad Temporal

La complejidad temporal de esta operación posee gran complejidad ya que el caso en el que se _rehashea_ la tabla debemos copiar todos los elementos de la tabla, por lo que en ese caso la complejidad sería de _O(n)_.  
Sin embargo, al utilizar una buena función de hash, en el sentido de bajar la posibilidad de las colisiones, y suponiendo que el tamaño con el que se inicializa la tabla tiene consideración el asunto de las colisiones.  
En este caso podemos decir que la complejidad va a tender a ser de _O(n)_.	

### Ver Cantidad

Esta operación devuelve lo almacenado dentro de la variable de `cantidad` de la estructura.

#### Complejidad Temporal

Podemos decir que la complejidad para esta implementación de la estructura es de _O(1)_, ya que accede a una variable almacenada en la estructura.

### Búsqueda

Tanto para la función de búsqueda, como para la función que verifica si un valor está contenido dentro de nuestra Tabla de Hash, utilizo el mismo módulo recursivo.  
La diferencia está en que la función de búsqueda retorna el una referencia al valor buscado si es que lo encuentra. Y la otra función retorna un booleano que se vuelve `true` cuando encuentra la clave buscada.  
La función de búsqueda recursiva recorre los nodos enlazados que se encuentran en el índice de la tabla obtenido por la `función de hash`.

#### Complejidad Temporal

Esta operación mantiene la misma idea que la inserción, por lo que podemos decir que tendera a _O(1)_.

### Quitar

Esta función se encarga de eliminar el valor y la clave asociado al pasado por parámetro.  
Para ello utiliza un módulo recursivo el cual recibe un puntero auxiliar, en el cual se guarda la referencia al valor eliminado.  
Este módulo realiza una búsqueda avanzando sobre los nodos, hasta encontrar la clave a eliminar, liberando la memoria utilizada para ese nodo.  

#### Complejidad Temporal

Esta operación al igual que insertar podemos decir que tiende a _O(1)_ ya que recorremos unicamente la lista de nodos enlazados que se encuentra en el indice de nuestra tabla de Hash.

### Iterador

El iterador nos permite aplicarle una función a cada uno de los pares clave y valor, además de permitir utilizar una variable extra para utilizar en la función si es deseado.  
Continua iterando y aplicando la función siempre y cuando la función que se desea aplicar devuelva `true`, en caso de devolver `false` se frena con la iteración.

#### Complejidad Temporal

Al iterar los elementos almacenados dentro de la lista podemos decir que la complejidad sera de _O(n)_.

### Destrucción

Nos permite liberar la memoria utiliza para nuestra estructura de hash.  
También tenemos un modulo que destruye los valores almacenados a través de un puntero a una función de destructor.  
Lo hace iterando toda la tabla y recorriendo los nodos de cada índice de manera recursiva.

#### Complejidad Temporal

Al tener que liberar la memoria para cada uno de los registros almacenados, podemos decir que la complejidad sera _O(n)_ para _n_ registros a liberar.

---

## Respuestas a las preguntas teóricas

### Diccionarios

Un _diccionario_ es un tipo de dato abstracto (TDA) el cual nos permite almacenar información, esta información denominada _valores_ la almacenamos en conjunto con identificadores únicos llamados _claves_, este conjunto de claves y valores nos permiten construir la estructura de un Diccionario.

- _Ejemplo_: Un ejemplo de utilización de un Diccionario podría ser el almacenamiento de la informacion de los Alumnos, en donde podriamos establecer un diccionario en el que almacenar, Nombre, Apellido, Datos de Contacto, y demas informacion como los **valores** asociados a cada alumno y luego utilizar el Numero de Padron de cada alumno como este identificador unico _clave_.

En base a esto podemos encontrar diferentes formas de implementarlo.

#### Formas de Implementación

Una implementacion sencilla sería la de utilizar un **vector** (puede ser dinamico o estatico), en donde se almacenen punteros/direcciones de memoria, sobre los cuales almacenamos los pares de _clave_, _valor_ que deseamos almacenar.

<div align="center">
<img src="img/diagrama-diccionario-vector.svg">
</div>

Otra manera de implementar sería a partir de la implementación de alguno de los TDA, realizado en los TPs anteriores, como lo podrían ser por ejemplo utilizando una **Lista de Nodos Enlazados**, o un **Arbol Binario de Busqueda** (ABB).  
En particular si utilizamos un Arbol Binario de Busqueda, en donde cada Nodo del arbol almacenaria una referencia al par clave y valor del diccionario.

<div align="center">
<img src="img/diagrama-diccionario-abb.svg">
</div>

**Tabla de Hash**

También podemos implementar un Diccionario a partir de una Tabla de Hash.  
La Tabla de Hash es una estructura la cual almacena valores, y podemos acceder a esos valores de manera mas directa dentro de la estructura.  
Utiliza una **Función de Hash** para establecer los índices dentro de la estructura a los que se correponde cada clave.  
- La _función de Hash_ se encarga de transformar la clave que buscamos en un valor asociado a la misma (puede ser una cadena de caracteres o un numero) asociado a la misma, lo cual permite ubicarlo de manera simplificada dentro de la Tabla de Hash.
En nuestro problema en particular, la funcion de Hash convierte un string en un numero asociado, ese numero se correponde a un indice dentro de la Tabla.

Sin embargo, pueden haber Claves que luego de aplicarles esta función de Hash devuelvan el mismo valor, esto resulta en que, al querer acceder a ese valor, obtenegamos resultado erroneos.  
A este resultado de que mas de una Clave se corresponda con el mismo índice dentro de la Tabla de Hash se lo conoce como **"Colisiones"**, y dependiendo del tipo Tabla de Hash que se este tratando es que tenemos distintas maneras de solucionarlas. 

**Tipos de Hash**

- **Hash Abierto**: Se caracteriza por tener un _Direccionamiento Cerrado_, lo cual implica que mas alla de las colisiones generadas, la clave se va a encontrar dentro de la tabla siempre en la posición obtenida de la funcion de Hash. Se lo denomina _"Hash Abierto"_ ya que se utiliza una estructura de soporte para almacenar los pares clave y valor en la tabla, y no directamente dentro de la misma.  
Para la resolución de las colisiones se suele almacenar el par clave valor, a continuación del valor que ya se encontraba previamente en la Tabla de Hash, a este metodo se lo llama de _Encadenamiento_, ya que vamos enlazando pares de claves y valores, dentro de un mismo indice de la Tabla.

<div align="center">
<img src="img/diagrama-hash-abierto.svg">
</div>

- **Hash Cerrado**: En este otro tipo de Hash el _Direccionamiento_ decimos que es _Abierto_, esto se da ya que los valores son almacenados directamente en la tabla de hash, en el indice resultante de aplicar la funcion de hash a la clave.  
En este tipo de Tabla se establece que su _tamaño_ debe ser mayor o igual que el numero claves.  
Las colisiones en este tipo de Hash se resuelven recorriendo la tabla hasta encontrar el proximo espacio disponible en el que almacenar el valor, (aunque esta manera de recorrer puede variar).  
Esta metodologia a la hora de resolver colisiones genera que al buscar una clave dentro de la Tabla de Hash, el indice que accedamos obtenido de la funcion de Hash no contenga el valor que buscamos, sino que el mismo haya sido desplazado dentro de la tabla.

<div align="center">
<img src="img/diagrama-hash-cerrado.svg">
</div>

**Tipos de Métodos de Búsqueda**

Estos metodos se aplican a la hora de Acceder a un valor dentro de un _Hash Cerrado_, ya que existe la posibilidad de que dentro de la tabla no se encuentre almacenado en la posicion dada por la _funcion de hash_ que tenemos establecida. 

- **"Probing Lineal"**: consiste en buscar el siguiente espacio libre inmediato.
- **"Probing Cuadratico"**: (intentos falidos)^2 para intentar insertar.
- **Hash Doble**: aplicar una segunda función de hash a la clave cuando hay colision.

**Importancia del Tamaño del Hash**

Si bien podemos utilizar un _Hash Abierto_, junto con una estructura de apoyo, o un _Hash Cerrado_ resolviendo las colisiones con los métodos anteriores, es importante tener noción de la _importancia del tamaño_ de nuestro Hash, ya que el mismo _indica la posibilidad_ de que haya una colisión dentro de nuestra tabla.  
Para ello, se utiliza un valor llamado *Factor de Carga*, el cual nos indica esta posibilidad, y podemos establecer un valor máximo permitido o aceptado y poder así _redimensionar_ nuestra Tabla para disminuir su valor.

**Factor de Carga**

Consiste en el valor resultante de la división entre el _número total de claves almacenadas (n)_ y la _capacidad total de la Tabla (m)_.  
_α = n / m_

**Redimensionamiento / Rehash**

Podemos establecer _α = 0.75_ como el valor máximo aceptado dentro de nuestra tabla, y si se llega a este valor o se supera, debemos redimensionar la tabla.  
Por ejemplo, aumentar su capacidad _(m)_ al doble.
