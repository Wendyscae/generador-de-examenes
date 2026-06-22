//Proyecto: Generador de Ex·menes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Reactivo{
    char pregunta[500];
    char op1[200];
    char op2[200];
    char op3[200];
    char op4[200];
    int correcta;
    float puntos;
    int respuestaUsuario;
    struct Reactivo *ant;
    struct Reactivo *sig;
}Reactivo;

Reactivo* crearReactivo(){
    Reactivo *nuevo = (Reactivo*)malloc(sizeof(Reactivo));
    if(nuevo == NULL){
        printf("Error de memoria.\n");
        exit(1);
    }
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    nuevo->respuestaUsuario = 0;
    nuevo->correcta = 0;
    nuevo->puntos = 0;
    return nuevo;
}

void insertarFinal(Reactivo **inicio, Reactivo *nuevo){
    if(*inicio == NULL){
        *inicio = nuevo;
        return;
    }
    Reactivo *aux = *inicio;
    while(aux->sig){
        aux = aux->sig;
    }
    aux->sig = nuevo;
    nuevo->ant = aux;
}

void limpiarCadena(char *cad){
    cad[strcspn(cad,"\n")] = 0;
}

void agregarReactivo(Reactivo **inicio){
    Reactivo *nuevo = crearReactivo();
    getchar();
    printf("\nPregunta: ");
    fgets(nuevo->pregunta,500,stdin);
    limpiarCadena(nuevo->pregunta);

    printf("Opcion 1: ");
    fgets(nuevo->op1,200,stdin);
    limpiarCadena(nuevo->op1);

    printf("Opcion 2: ");
    fgets(nuevo->op2,200,stdin);
    limpiarCadena(nuevo->op2);

    printf("Opcion 3: ");
    fgets(nuevo->op3,200,stdin);
    limpiarCadena(nuevo->op3);

    printf("Opcion 4: ");
    fgets(nuevo->op4,200,stdin);
    limpiarCadena(nuevo->op4);

    do{
        printf("Respuesta correcta (1-4): ");
        scanf("%d",&nuevo->correcta);
    }while(nuevo->correcta < 1 || nuevo->correcta > 4);
    printf("Puntos: ");
    scanf("%f",&nuevo->puntos);
    insertarFinal(inicio,nuevo);
    printf("\nReactivo agregado.\n");
}

void guardarExamen(char *archivo, Reactivo *inicio){
    FILE *f = fopen(archivo,"w");
    if(f == NULL){
        printf("Error al guardar.\n");
        return;
    }
    Reactivo *aux = inicio;
    while(aux){
        fprintf(f,":p;%s\n",aux->pregunta);
        fprintf(f,":op1;%s\n",aux->op1);
        fprintf(f,":op2;%s\n",aux->op2);
        fprintf(f,":op3;%s\n",aux->op3);
        fprintf(f,":op4;%s\n",aux->op4);
        fprintf(f,":r;op%d\n",aux->correcta);
        fprintf(f,"%.2f\n\n",aux->puntos);
        aux = aux->sig;
    }
    fclose(f);
    printf("\nExamen guardado correctamente.\n");
}

Reactivo* cargarExamen(char *archivo){
    FILE *f = fopen(archivo,"r");
    if(f == NULL){
        return NULL;
    }
    Reactivo *inicio = NULL;
    char linea[600];
    while(fgets(linea,sizeof(linea),f)){
        if(strncmp(linea,":p;",3)==0){
            Reactivo *nuevo = crearReactivo();
            strcpy(nuevo->pregunta,linea+3);
            limpiarCadena(nuevo->pregunta);

            fgets(linea,sizeof(linea),f);
            strcpy(nuevo->op1,linea+5);
            limpiarCadena(nuevo->op1);

            fgets(linea,sizeof(linea),f);
            strcpy(nuevo->op2,linea+5);
            limpiarCadena(nuevo->op2);

            fgets(linea,sizeof(linea),f);
            strcpy(nuevo->op3,linea+5);
            limpiarCadena(nuevo->op3);

            fgets(linea,sizeof(linea),f);
            strcpy(nuevo->op4,linea+5);
            limpiarCadena(nuevo->op4);

            fgets(linea,sizeof(linea),f);

            if(strstr(linea,"op1")){
                nuevo->correcta = 1;
            }else{
            	if(strstr(linea,"op2")){
                    nuevo->correcta = 2;
                }else{
				    if(strstr(linea,"op3")){
                        nuevo->correcta = 3;
			        }else{
                        nuevo->correcta = 4;
                    }
                }
            }
            fgets(linea,sizeof(linea),f);
            nuevo->puntos = atof(linea);
            insertarFinal(&inicio,nuevo);
        }
    }
    fclose(f);
    return inicio;
}

void mostrarReactivo(Reactivo *r){
    printf("\nPregunta:\n%s\n\n",r->pregunta);
    printf("1) %s\n",r->op1);
    printf("2) %s\n",r->op2);
    printf("3) %s\n",r->op3);
    printf("4) %s\n",r->op4);
    printf("\nCorrecta: %d",r->correcta);
    printf("\nPuntos: %.2f\n",r->puntos);
}

void modificarExamen(Reactivo **inicio){
    if(*inicio == NULL){
        printf("\nNo hay examen cargado.\n");
        return;
    }
    Reactivo *actual = *inicio;
    int op;
    do{
        printf("\n === REACTIVO ACTUAL ===");

        printf("\nPregunta:\n%s\n", actual->pregunta);

        printf("\n1) %s", actual->op1);
        printf("\n2) %s", actual->op2);
        printf("\n3) %s", actual->op3);
        printf("\n4) %s", actual->op4);

        printf("\n\nRespuesta correcta: %d", actual->correcta);
        printf("\nPuntos: %.2f\n", actual->puntos);

        printf("\nAnterior.....................1");
        printf("\nSiguiente....................2");
        printf("\nModificar reactivo...........3");
        printf("\nAgregar reactivo.............4");
        printf("\nGuardar y salir..............5");

        printf("\n\nOpcion: ");
        scanf("%d",&op);
        switch(op){
            case 1: if(actual->ant != NULL){
                        actual = actual->ant;
                    }else{
                        printf("\nYa estas en el primer reactivo.\n");
                    }
                    break;
            case 2: if(actual->sig != NULL){
                        actual = actual->sig;
                    }else{
                        printf("\nYa estas en el ultimo reactivo.\n");
                    }
                    break;
            case 3: getchar();
                    printf("\nNueva pregunta: ");
                    fgets(actual->pregunta,500,stdin);
                    limpiarCadena(actual->pregunta);

                    printf("Nueva opcion 1: ");
                    fgets(actual->op1,200,stdin);
                    limpiarCadena(actual->op1);
                      
				    printf("Nueva opcion 2: ");
                    fgets(actual->op2,200,stdin);
                    limpiarCadena(actual->op2);

                    printf("Nueva opcion 3: ");
                    fgets(actual->op3,200,stdin);
                    limpiarCadena(actual->op3);

                    printf("Nueva opcion 4: ");
                    fgets(actual->op4,200,stdin);
                    limpiarCadena(actual->op4);
                    do{
                        printf("Respuesta correcta (1-4): ");
                        scanf("%d",&actual->correcta);
                    }while(actual->correcta < 1 || actual->correcta > 4);
                    printf("Puntos: ");
                    scanf("%f",&actual->puntos);
                    printf("\nReactivo actualizado correctamente.\n");
                    break;
            case 4: agregarReactivo(inicio);
                    printf("\nReactivo agregado al final del examen.\n");
                    break;
        }
    }while(op!=5);
}

void aplicarExamen(Reactivo *inicio){
    if(inicio == NULL){
        printf("\nNo existe examen.\n");
        return;
    }
    Reactivo *actual = inicio;
    char nav;
    while(1){
        printf("\n%s\n\n",actual->pregunta);

        printf("1) %s\n",actual->op1);
        printf("2) %s\n",actual->op2);
        printf("3) %s\n",actual->op3);
        printf("4) %s\n",actual->op4);

        do{
            printf("\nRespuesta (1-4): ");
            scanf("%d",&actual->respuestaUsuario);
        }while(actual->respuestaUsuario < 1 || actual->respuestaUsuario > 4);
        printf("\n[a] ... Anterior");
        printf("\n[d] ... Siguiente");
        printf("\n[f] ... Finalizar");
        printf("\nOpcion: ");
        scanf(" %c",&nav);

        if(nav=='a' && actual->ant)
            actual = actual->ant;
        else if(nav=='d' && actual->sig)
            actual = actual->sig;
        else if(nav=='f')
            break;
    }
    float total = 0;
    float obtenidos = 0;
    Reactivo *aux = inicio;
    while(aux){
        total += aux->puntos;
        if(aux->respuestaUsuario == aux->correcta){
            obtenidos += aux->puntos;
        }
        aux = aux->sig;
    }
    printf("\n === RESULTADO FINAL === \n");
    printf("\nPuntos obtenidos: %.2f",obtenidos);
    printf("\nPuntos totales: %.2f",total);
    if(total > 0){
        printf("\nPorcentaje: %.2f%%\n",(obtenidos*100)/total);
    }else{
        printf("\nPorcentaje: 0.00%%\n");
    }
}

void liberarLista(Reactivo *inicio){
    Reactivo *aux;
    while(inicio){
        aux = inicio;
        inicio = inicio->sig;
        free(aux);
    }
}

int main(){
    Reactivo *examen = NULL;
    int opc;
    char archivo[100];
	do{
        printf("\n === SISTEMA DE EXAMENES === \n");
        printf("Generar examen.................1\n");
        printf("Modificar examen...............2\n");
        printf("Aplicar examen.................3\n");
        printf("Salir..........................4\n");
        printf("\n\nOpcion: ");
        scanf("%d",&opc);
        switch(opc){
            case 1: printf("\nNombre archivo: ");
                    scanf("%s",archivo);
                    if(examen!=NULL){
                        liberarLista(examen);
                    }
                    examen = NULL;
                    int cantidad;
                    printf("Cantidad de reactivos: ");
                    scanf("%d",&cantidad);
					for(int i=0;i<cantidad;i++){
                        printf("\nReactivo %d\n",i+1);
                        agregarReactivo(&examen);
                    }
                    guardarExamen(archivo,examen);
                    break;

            case 2: printf("\nArchivo a cargar: ");
                    scanf("%s",archivo);
                    if(examen!=NULL){
                        liberarLista(examen);
                        examen = NULL;
                    }
                    examen = cargarExamen(archivo);
                    if(examen!=NULL){
                        modificarExamen(&examen);
                        guardarExamen(archivo, examen);
                    }else{
                        printf("\nNo existe el archivo.\n");
                    }
                    break;

            case 3: printf("\nArchivo a aplicar: ");
                    scanf("%s",archivo);
                    if(examen != NULL){
                        liberarLista(examen);
                        examen = NULL;
                    }
                    examen = cargarExamen(archivo);
                    if(examen){
                        aplicarExamen(examen);
                    }else{
                        printf("\nNo existe archivo.\n");
                    }
					break;
			default: printf("\nOpcion no valida.\n"); break;		
        }
    }while(opc!=4);
    liberarLista(examen);
    return 0;
}
