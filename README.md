# Generador de Exámenes - Estructura de Datos I

[cite_start]Proyecto final desarrollado para la materia de **Estructura de Datos I** en la **Universidad Autónoma de Aguascalientes**[cite: 1, 2, 3].

## Descripción del Proyecto
[cite_start]El sistema es una aplicación en lenguaje C diseñada para gestionar la creación, modificación y aplicación de exámenes. [cite_start]El programa utiliza **listas doblemente enlazadas** como estructura de datos principal para permitir la navegación bidireccional entre los reactivos del examen.

## Funcionalidades Principales
* [cite_start]**Generar examen:** Crea un nuevo archivo de examen con preguntas, opciones, respuesta correcta y puntaje[cite: 37, 40].
* [cite_start]**Modificar examen:** Permite editar reactivos existentes de manera dinámica[cite: 38, 55].
* [cite_start]**Aplicar examen:** Distribuye los reactivos en memoria, permite la navegación durante la prueba y calcula el puntaje final[cite: 39, 56, 57].

## Formato de los Archivos
[cite_start]El programa lee y escribe archivos de texto siguiendo estrictamente este formato[cite: 41]:

```text
:p; Pregunta
:op1; Opción 1
:op2; Opción 2
:op3; Opción 3
:op4; Opción 4
:r; opN
Puntaje
