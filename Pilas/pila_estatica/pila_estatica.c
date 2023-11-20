#include <stdio.h>
#include <stdlib.h>


/*
Stack en ingles

estructura tipo UEPS (ultimo en etrar primero en salir)

LIFO

tiene una longitud determinada, si se llena no se pueden agregar mas elemntos


defimicion de una pila

    pila estatica

    typedef int tipodato;

    typedef struct Pila{
        tipodato array_pila[n];
        int top;
    }pila;

declaracion
    Pila S1;

inicializacion:
    S1.top = 0;    
*/

/*
    OPERACIONES
        unarias:
            -Agregar elemento(push)
                pila a donde se agrega
                elemento a agregar

                generalidad push(S,x)

            -pila llena
                regresa un 0 o 1 dependiendo si la pila esta llena o no
                se ejecuta antes del push para verificar qeu aun se encuentre un espacio libre

                cuando la pila ya esta llena se dice que hay un desbordamiento o un overflow

            -pila vacio
                regresa 0 o 1 dependiendo si la pila esta vaicia
                se ejecuta antes del pop paar verifiar que la pila no este vacia

                cuando la pila esta viacia se dice que hay subdesbordamiento o underflow

            -sacar elemento(pop(s))
                no es necesario dar de parametro del elemnto ya que solo se puede acceder al ultimo elemento introducido
                el valor de debe conservar 

                de froma directa se puede hacer y=pop(S)

            -StackTop(s)
                consulta el elemento que esta en el tope pero sin sacar el dato de ella
                es el quivalente a realizar un pop y un push

                cuando el tope tiene un valor de -1, lapila esta vacia(primero se mueve e tope y despues de guada el valor)
                se puede poner el ultimo tope como 0 en lugar de -1(primero se guarda el valor y despues se mueve el top)


                y = pop(S)
                push(S,y)

        binarias

        deben ser dos pilas del mismo tipo de datos
*/

typedef int tipoDato;

#define MaxTamaPila 100

//pila
typedef struct pila
{
    tipoDato A[MaxTamaPila];
    int cima;// indicador tope
}Pila;

void VoidP(Pila* P);
void BorarrP(Pila* P);
tipoDato Primero(Pila P);
int IsVoid(Pila P);
int isFull(Pila P);
int Push(Pila*P,tipoDato elemento);
tipoDato pop(Pila *P);
int salir();

int main(){

    Pila S1;//declaracion de la pila
    VoidP(&S1);

    int op, flag = 0;
    tipoDato elemento, aux;

    do
    {
        printf("\n--------------------------------------------------\n");
        printf("\nPILA ESTATICA\n");
        printf("\nMenu: \n1)Consultar primer elento\n2)Consultar si la pila esta vacia\n3)Consultar sin la pila esta llea\n4)Agregar elemnro\n5)Eliminar elemento\nopcion: ");
        scanf("%i",&op);
        switch (op)
        {
        case 1:
            printf("\n--------------------------------------------------");
            printf("\nPrimer elemto de la Pila(elemento en el tope)\n");
            if (Primero(S1) != 0)
            {
                printf("El primer elemento de la pila es: %i",Primero(S1));
            }
            printf("\n--------------------------------------------------\n");
            flag = salir();
            break;
        case 2:
            printf("\n--------------------------------------------------");
            printf("\nLista Vacia\n");
            if (IsVoid(S1) == 1)
            {
                printf("La pila esta vacia");
            }
            else{
                printf("La pila no esta vacia");
            }
            printf("\n--------------------------------------------------\n");
            flag = salir();
            break;
        case 3:
            printf("\n--------------------------------------------------");
            printf("\nLista Llena\n");
            if (isFull(S1) == 1)
            {
                printf("La pila esta Llena");
            }
            else{
                printf("La pila no esta Llena");
            }
            printf("\n--------------------------------------------------\n");
            flag = salir();
            break;
        case 4:
            printf("\n--------------------------------------------------");
            printf("\nAgregar elemento\n");
            printf("\nIngrese un numero entero: ");
            scanf("%i",&elemento);
            if (Push(&S1, elemento) != 0)
            {
                printf("\nElemento agregado con exito");
            }
            printf("\n--------------------------------------------------\n");
            flag = salir();
            break;
        case 5:
            printf("\n--------------------------------------------------");
            printf("\nEliminar/Utilizar elemento\n");
            aux = pop(&S1);
            if (aux != 0)
            {
                printf("El elemento eliminado es: %i",aux);
            }
            printf("\n--------------------------------------------------\n");
            flag = salir();
            break;
    
        default:
            break;
        }
    } while (flag == 0);
    
  

    return 0;
}

int salir(){
    int op, flag = 0;

    while (flag == 0)
    {
        printf("Desea salir del programa?\n1)Si\n2)No\nopcion: ");
        scanf("%i",&op);
        switch (op)
        {
        case 1:
            flag = 1;
            return 1;
            break;
        case 2:
            flag = 1;
            return 0;
            break;
        default:
            printf("\nopcion no valida\n");
            break;
        }
    }
    
}

//Inicializacion de la pila
void VoidP(Pila*P){
    P->cima=-1;
}

int Push(Pila*P,tipoDato elemento){
    if (isFull(*P))
    {
        puts("Desbordamiento Pila");
        return 0;
    }

    P->cima++;
    P->A[P->cima] = elemento;
}

tipoDato pop(Pila *P){
    tipoDato Aux;
    if (IsVoid(*P))
    {
        puts("La pila esta vacia");
        return 0;
    }
    Aux = P->A[P->cima];//se accede al elemento pila 
    P->cima--;//decrementa el tope, el valor se queda guardado en Aux pero ya no pertenece a la pila
    return Aux;
}



tipoDato Primero(Pila P){//StackTop
    if (IsVoid(P))
    {
        puts("La pila esta vacia");
        return 0;
    }

    return P.A[P.cima];//Accede al primer elemento de la pila sin eliminar el elemento de la pila
}

int IsVoid(Pila P){
    return P.cima == -1;
}

int isFull(Pila P){
    return P.cima == MaxTamaPila-1;
}
