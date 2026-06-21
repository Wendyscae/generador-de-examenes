# Generador de Exámenes - Sistema de Gestión Académica

## 1. Descripción del Proyecto
Este sistema es una aplicación desarrollada en lenguaje C que permite la creación, edición y aplicación de exámenes de manera estructurada. El proyecto implementa **estructuras de datos dinámicas** para gestionar el flujo de reactivos, garantizando un uso eficiente de la memoria y una experiencia de navegación intuitiva para el usuario. 

## 2. Tecnologías y Estructuras Utilizadas
* **Lenguaje:** C (Estándar ISO).
* **Gestión de Memoria:** Uso de punteros y asignación dinámica (`malloc`, `free`) para manejar un número indeterminado de preguntas. 
* **Estructura de Datos:** Lista Doblemente Enlazada. Esta estructura fue elegida porque permite al usuario moverse libremente entre preguntas (adelante y atrás) durante la aplicación del examen. 
* **Persistencia:** Manejo de archivos de texto (`FILE *`) con un formato de etiquetas específico (`:p;`, `:opN;`, `:r;`, puntaje) para asegurar que los datos no se pierdan al cerrar el programa. 

---

## 3. Explicación del Código
El código está diseñado de forma modular para facilitar su mantenimiento.

### Estructura del Nodo (`Reactivo`)
Representa la unidad básica de información. Contiene el texto de la pregunta, las 4 opciones de respuesta, la respuesta correcta, el puntaje y dos punteros (`ant`, `sig`) que crean la cadena de la lista doblemente enlazada.

### Funciones Principales
* `crearReactivo()`: Reserva memoria dinámica para una nueva pregunta y prepara los punteros de la lista.
* `insertarFinal()`: Gestiona la lógica de enlace, asegurándose de que cada nuevo reactivo se conecte con el anterior y el siguiente.
* `guardarExamen()`: Recorre la lista en memoria y escribe cada nodo en un archivo de texto siguiendo el formato estricto exigido (etiquetas `:p;`, `:opN;`, etc.).
* `cargarExamen()`: Realiza el proceso inverso. Lee el archivo línea por línea, identifica las etiquetas y reconstruye la lista doblemente enlazada en la memoria RAM.
* `modificarExamen()`: Implementa la navegación mediante los punteros `ant` y `sig`, permitiendo al usuario editar reactivos existentes. 
* `aplicarExamen()`: Distribuye el examen en pantalla. Compara la respuesta del usuario con la clave correcta y acumula el puntaje en tiempo real.

### Función `main()`
Es el cerebro del programa. Implementa un menú interactivo (`switch`) que controla el flujo principal:
1. **Generar**: Llama a `agregarReactivo` repetidamente.
2. **Modificar**: Carga el archivo a memoria y abre la interfaz de edición.
3. **Aplicar**: Carga el archivo y ejecuta la lógica de evaluación.
4. **Salir**: Libera toda la memoria utilizada mediante `liberarLista` para evitar fugas.

---

