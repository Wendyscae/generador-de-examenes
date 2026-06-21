# Generador de Exámenes - Estructura de Datos I

Proyecto final desarrollado para la materia de **Estructura de Datos I** en la **Universidad Autónoma de Aguascalientes**.

## Descripción del Proyecto
El sistema es una aplicación en lenguaje C diseñada para gestionar la creación, modificación y aplicación de exámenes.El programa utiliza **listas doblemente enlazadas** como estructura de datos principal para permitir la navegación bidireccional entre los reactivos del examen.

## Funcionalidades Principales
* **Generar examen:** Crea un nuevo archivo de examen con preguntas, opciones, respuesta correcta y puntaje.
* **Modificar examen:** Permite editar reactivos existentes de manera dinámica.
* **Aplicar examen:** Distribuye los reactivos en memoria, permite la navegación durante la prueba y calcula el puntaje final.

## Formato de los Archivos
El programa lee y escribe archivos de texto siguiendo estrictamente este formato:

```text
:p; Pregunta
:op1; Opción 1
:op2; Opción 2
:op3; Opción 3
:op4; Opción 4
:r; opN
Puntaje
