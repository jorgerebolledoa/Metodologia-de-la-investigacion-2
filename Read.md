# Implementación de Métodos para el Cálculo del Coeficiente Binomial en C

## 1. Descripción General

Este programa presenta una colección de **ocho algoritmos distintos** para el cálculo del coeficiente binomial:

$$
C(n,k) = \binom{n}{k} = \frac{n!}{k!(n-k)!}
$$

El objetivo es comparar diferentes enfoques computacionales, tanto en términos de eficiencia como de uso de memoria, mostrando alternativas clásicas, recursivas, de programación dinámica y basadas en factorización prima.

---

## 2. Métodos Implementados

1. **Factoriales iterativos**
   Implementación directa a partir de la definición clásica.

2. **Recursión de Pascal**
   Utiliza la identidad de Pascal:

   $$
   C(n,k) = C(n-1,k-1) + C(n-1,k), \quad C(n,0)=C(n,n)=1
   $$

3. **Método multiplicativo**
   Calcula paso a paso el cociente:

   $$
   C(n,k) = \prod_{i=1}^{k} \frac{n-i+1}{i}
   $$

4. **Programación dinámica con memoria estática**
   Construcción iterativa de la tabla de combinaciones hasta $n$, con límite predefinido `MAXN`.

5. **Programación dinámica con memoria dinámica**
   Construcción de la tabla con memoria reservada mediante `malloc`, liberada posteriormente.

6. **Programación dinámica optimizada en espacio**
   Se emplea un arreglo unidimensional de tamaño $k+1$, reduciendo significativamente el uso de memoria.

7. **Factoriales recursivos**
   Variante recursiva de la definición factorial aplicada al cálculo de combinaciones.

8. **Descomposición en primos**
   Se basa en la factorización prima de $n!$, utilizando el exponente de cada primo en el numerador y denominador para obtener el resultado exacto.

---

## 3. Compilación

El código debe compilarse utilizando el compilador `gcc`:

```bash
gcc binomial.c -o binomial -lm
```

La opción `-lm` es necesaria debido al uso de la biblioteca matemática (`math.h`) en el método de descomposición en primos.

---

## 4. Ejecución

La sintaxis de ejecución es la siguiente:

```bash
./binomial metodo n k
```

* `metodo`: entero entre 1 y 8, que selecciona el algoritmo a utilizar.
* `n`: entero que representa el número total de elementos.
* `k`: entero que representa el tamaño de la combinación.

Ejemplo:

```bash
./binomial 3 10 4
```

Salida esperada:

```
C(10, 4) = 210
Tiempo de ejecución: 0.000002 segundos
```

---

## 5. Consideraciones de Eficiencia

* **Métodos 1 y 7**: simples conceptualmente, pero propensos a desbordamiento numérico en factoriales grandes.
* **Método 2**: la recursión de Pascal crece exponencialmente, siendo ineficiente para valores grandes de $n$.
* **Métodos 4, 5 y 6**: los enfoques de programación dinámica son los más eficientes para un rango amplio de valores, siendo el método 6 el más óptimo en memoria.
* **Método 3**: ofrece un buen balance entre simplicidad y eficiencia, evitando factoriales completos.
* **Método 8**: aunque más complejo, proporciona un cálculo exacto basado en propiedades aritméticas fundamentales.

---

## 6. Estructura del Código

* **Funciones auxiliares**: factorial iterativo y recursivo, generación de primos, cálculo de exponentes primos.
* **Funciones principales**: cada método se encuentra encapsulado en una función independiente.
* **Función `main`**: recibe los parámetros de entrada, selecciona el algoritmo, ejecuta el cálculo y mide el tiempo de ejecución con `clock()`.
