#include <stdio.h>
#include <stdlib.h>

/*
en lugar de serun arreglo, son elementos ligados a traves de apuntadores
no tiene un limite de elementos, por lo cuala la funcion IsFull no es necesario

    tope en este caso es un apuntador
    si el tope apunta a Null, indica que la pila esta vacia

    tope->dato->apuntador->dato->apuntador->NULL
*/

typedef int tipodato;

typedef struct stack 
{
    tipodato data;
    struct stack *next;
}Stack;

struct stack* top = NULL;

struct stack *push(struct stack *top, int);
struct stack *display(struct stack *top);
struct stack *pop(struct stack* top);
int peek(struct stack *top);
int IsVoid(struct stack *top); 

int main(){
    tipodato op = 0;
    int val;
    printf("\nPILA DINAMICA\n");
    do
    {
        printf("\n\n|-------------------------------------|");
		printf("\n|            PILA DINAMICA            |");
		printf("\n|------------------|------------------|");
		printf("\n| 1. AGREGAR       | 4. PRIMERO       |");
		printf("\n| 2. ELIMINAR      | 5. SALIR         |");
		printf("\n| 3. DISPLAY       |                  |");
		printf("\n|------------------|------------------|");
		printf("\n\n Escoja una Opcion: ");
        scanf("%i",&op);
        switch (op)
        {
        case 1:
            printf("\n--------------------------------------\n");
            printf("\nIntroddusca el valor que desee agregar a la pila: ");
            scanf("%i",&val);
            top = push(top,val);
            printf("\n--------------------------------------\n");
            break;
        case 2:
            printf("\n--------------------------------------\n");
            printf("\nELIMINAR EL TOPE DE LA PILA ");
            top = pop(top);
             printf("\n--------------------------------------\n");
            break;
        case 3:
            top = display(top);
            break;
        case 4:
            printf("\n--------------------------------------\nMostrar el primer elemento de la pila\n");
            if (peek(top)==-1)
            {
                printf("\nLa pila esta vacia");
            }
            else
            {
                printf("El primer elemento de la pila es: %i",peek(top));
            }
             printf("\n--------------------------------------\n");
            break;
        case 5:
            printf("\nHasta luego");
            break;
        default:
            printf("\nValor no valido, introdusca uno correcto\n");
            break;
        }
    } while (op != 5);

    return 0;
}



int IsVoid(struct stack *top){
    return top == NULL;    
}

struct stack *push(struct stack *top, int val){
   
    struct stack *ptr;
    ptr = (struct stack*)malloc(sizeof(struct stack));
    ptr->data = val;
     if (ptr == NULL) {
    
        // Manejar error de asignación de memoria
        return top; // Devolver la pila original sin cambios
    }
    if (top==NULL)
    {
        ptr->next=NULL;
        top=ptr;
        /* code */
    }
    else
    {
        ptr->next=top;
        top=ptr;
    }
    
    return top;
}

struct stack *pop(struct stack* top){
    struct stack *ptr;
    ptr = top;
    if (top==NULL)
    {
        printf("pila vacia");

        /* code */
    }
    else{
        top=top->next;
        printf("el valor que fue eliminado es: %i",ptr->data);
        free(ptr);
    }
    return top;
}

int peek(struct stack *top){
    if (top==NULL)
    {
        /* code */
        return -1;
    }
    else
    {
        return top->data;
    }   
}

struct stack *display(struct stack *top){
    struct stack *ptr;
    ptr=top;
    if (top == NULL)
    {
        printf("pila vacia");
        /* code */
    }
    else
    {
        printf("\nelementos de la pila: ");
        while (ptr != NULL)
        {
            printf(" %i,",ptr->data);
            ptr = ptr ->next;
        }
        
    }
    return top;
    
}