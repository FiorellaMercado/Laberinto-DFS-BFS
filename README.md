# Laberinto-DFS-BFS

## ¿Cómo generé el laberinto?

Generé el laberinto utilizando el algoritmo **DFS (Depth-First Search)**.
Comencé con una matriz completamente llena de muros (#) y, mediante DFS recursivo, fui rompiendo paredes para crear caminos.
Recorrí las direcciones en orden aleatorio utilizando un generador de números aleatorios, lo que permite obtener laberintos distintos en cada ejecución.

De esa forma me aseguro que siempre exista un camino válido desde la entrada (E) hasta la salida (S).

## ¿Qué algoritmo usé para resolverlo?

Para resolver el laberinto utilicé el algoritmo **BFS (Breadth-First Search)**.
Este algoritmo explora el tablero por niveles utilizando una cola y me permite encontrar el camino más corto entre la entrada y la salida.
Durante la exploración registré el nodo padre de cada posición para luego reconstruir el camino final.

## ¿Qué descubrí al medir tiempos y qué haría distinto la próxima vez?

Al medir los tiempos de generación y resolución observé que, aunque las diferencias pueden parecer pequeñas en tableros de tamaño reducido, la diferencia aumenta a medida que crecen las dimensiones del laberinto.

En una próxima ocasión, buscaría alternativas más eficientes o mejoras en la implementación para reducir el tiempo de ejecución tratando de mantener el mismo resultado.

