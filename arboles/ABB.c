#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototipos de funciones
int IsVoid(int arbol[], int nodos);
int busqueda(int arbol[], int nodos, int padre, int raiz);
void menu(int arbol[], int nodos);
int* inicializacion_arbol(int arbol[], int nodos);

void insertarRaiz(int arbol[]);
void insertarHijoIzq(int arbol[], int nodos);
void insertarHijoDer(int arbol[], int nodos);
int ObtenerPadre(int raiz);
int HijoIzq(int raiz);
int HijoDer(int raiz);

int main(){
    printf("\n---------------------------------------\n");
    printf("\nArbol binario\n");
    printf("\n---------------------------------------\n");

    int NiMax_arbol;
    printf("\nIntroduce el numero de niveles del arbol: ");
    scanf("%i", &NiMax_arbol);

    NiMax_arbol = pow(2, NiMax_arbol + 1) - 1;

    int *arbol;
    arbol = (int*)malloc(sizeof(int) * NiMax_arbol);
    arbol = inicializacion_arbol(arbol, NiMax_arbol);
    menu(arbol, NiMax_arbol);

    // Liberar la memoria asignada dinámicamente
    free(arbol);

    system("PAUSE");
    return 0;
}

int* inicializacion_arbol(int arbol[], int nodos){
    for (int i = 0; i < nodos; i++) {
        arbol[i] = -1;
    }
    return arbol;
}

int ObtenerPadre(int raiz){
    return raiz / 2;
}

int HijoIzq(int raiz){
    return (2 * raiz) + 1;
}

int HijoDer(int raiz){
    return (2 * raiz) + 2;
}

// RECORRIDO DE ÁRBOL RID
int busqueda(int arbol[], int nodos, int padre, int raiz){
    if (raiz >= nodos) {
        return -1; // Índice fuera de rango
    }

    if (arbol[raiz] == padre){
        return raiz;
    } else {
        int izquierda = HijoIzq(raiz);
        int derecha = HijoDer(raiz);

        int resultado_izquierda = busqueda(arbol, nodos, padre, izquierda);
        if (resultado_izquierda != -1) {
            return resultado_izquierda;
        }

        return busqueda(arbol, nodos, padre, derecha);
    }
}

void insertarHijoIzq(int arbol[], int nodos){
    int padre, nodo, dato;
    printf("\nIntroduce el nodo padre: ");
    scanf("%i", &padre);

    nodo = busqueda(arbol, nodos, padre, 0);
    if (nodo != -1){
        printf("\nIntroduce el dato del nodo hijo izquierdo de %i: ", arbol[nodo]);
        scanf("%i", &dato);
        nodo = HijoIzq(nodo);
        arbol[nodo] = dato;
    } else {
        printf("\nPadre no encontrado dentro del arbol");
    }
}

void insertarHijoDer(int arbol[], int nodos){
    int padre, nodo, dato;
    printf("\nIntroduce el nodo padre: ");
    scanf("%i", &padre);

    nodo = busqueda(arbol, nodos, padre, 0);
    if (nodo != -1){
        printf("\nIntroduce el dato del nodo hijo derecho de %i: ", arbol[nodo]);
        scanf("%i", &dato);
        nodo = HijoDer(nodo);
        arbol[nodo] = dato;
    } else {
        printf("\nPadre no encontrado dentro del arbol");
    }
}

void menu(int arbol[], int nodos){
    int op, flag = 0, flag2 = 0, dato, nodo, raiz;

    do {
        printf("\n---------------------------------------\n");
        printf("\nMenu\n");
        printf("\n---------------------------------------\n");
        printf("1) Insertar nodo\n2) Buscar nodo\n3) Salir\nOpcion: ");
        scanf("%i", &op);

        switch (op) {
            case 1:
                if (IsVoid(arbol, nodos) == 1) {
                    insertarRaiz(arbol);
                } else {
                    do {
                        printf("\n1) Insertar hijo izquierdo\n2) Insertar hijo derecho\nOpcion: ");
                        scanf("%i", &op);
                        switch (op) {
                            case 1:
                                insertarHijoIzq(arbol, nodos);
                                flag2 = 1;
                                break;
                            case 2:
                                insertarHijoDer(arbol, nodos);
                                flag2 = 1;
                                break;
                            default:
                                printf("\nOpcion no valida, intentelo de nuevo");
                                break;
                        }
                    } while (flag2 == 0);
                }
                break;

            case 2:
                do {
                    if (IsVoid(arbol, nodos) == 1) {
                        printf("\nEl arbol esta vacio, no hay nodos que buscar");
                    } else {
                        do {
                            printf("\nElija una de las siguientes opciones:\n1) Buscar hijo izquierdo\n2) Buscar hijo derecho\n3) Buscar padre\nOpcion: ");
                            scanf("%i", &op);
                            switch (op) {
                                case 1:
                                    printf("\nIntroduce el dato del cual desea conocer el hijo izquierdo: ");
                                    scanf("%i", &dato);
                                    raiz = busqueda(arbol, nodos, dato, 0);
                                    if (raiz == -1) {
                                        printf("\nDato no encontrado");
                                    } else {
                                        nodo = HijoIzq(raiz);
                                        if (arbol[nodo] == -1) {
                                            printf("\nEl nodo no tiene un hijo izquierdo");
                                        } else {
                                            printf("\nEl hijo izquierdo del nodo es: %i", arbol[nodo]);
                                        }
                                    }
                                    break;

                                case 2:
                                    printf("\nIntroduce el dato del cual desea conocer el hijo derecho: ");
                                    scanf("%i", &dato);
                                    raiz = busqueda(arbol, nodos, dato, 0);
                                    if (raiz == -1) {
                                        printf("\nDato no encontrado");
                                    } else {
                                        nodo = HijoDer(raiz);
                                        if (arbol[nodo] == -1) {
                                            printf("\nEl nodo no tiene un hijo derecho");
                                        } else {
                                            printf("\nEl hijo derecho del nodo es: %i", arbol[nodo]);
                                        }
                                    }
                                    break;

                                case 3:
                                    printf("\nIntroduce el dato del cual desea conocer el padre: ");
                                    scanf("%i", &dato);
                                    raiz = busqueda(arbol, nodos, dato, 0);
                                    if (raiz == -1) {
                                        printf("\nDato no encontrado");
                                    } else {
                                        nodo = ObtenerPadre(raiz);
                                        if (arbol[nodo] == -1) {
                                            printf("\nEl nodo no tiene padre");
                                        } else {
                                            printf("\nEl padre del nodo es: %i", arbol[nodo]);
                                        }
                                    }
                                    break;
                                default:
                                    printf("\nOpcion no valida");
                                    break;
                            }
                        } while (flag2 == 0);
                    }
                } while (flag2 == 0);
                break;
            case 3:
                flag == 1;
                break;
            default:
                break;
        }
    } while (flag != 1 );
}

void insertarRaiz(int arbol[]){
    int dato;
    printf("\nIntroduce el dato que desea guardar en el nodo raiz: ");
    scanf("%i", &dato);
    arbol[0] = dato;
}

int IsVoid(int arbol[], int nodos){
    return arbol[0] == -1;
}
