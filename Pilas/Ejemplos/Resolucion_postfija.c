#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//evaluacion de una cadena postfija

//creacion de la estructura de operandos
typedef struct operandos
{
    int data;
    struct operandos *next;
}Operandos;

//inicializacion de la pila
Operandos *top = NULL;

Operandos *push(Operandos *top, char ca); //agregar un nuevo tope a la pila
Operandos *pop(Operandos* top); //eliminar el tope de la pila

int empty(Operandos* top); //determina si la pila esta vacia
int peek(Operandos *top); //muestra el tope de la pila

void evaluaciosn(char* cad); //funcion donde se llevaran a cabo las operaciones
int isOperator(char c); //funcion que determina si es un operador


int main(){
    //creacion de la cadena dondo se guardara la operacion postfija
    char *cad;
    cad =(char*)malloc(sizeof(char)*100);
    printf("\n--------------------------------------\nEvaluacvion postfija\n----------------------------------------------\n");
    printf("introdusca una operacion en su forma postfija: ");
    gets(cad);

    evaluaciosn(cad);//se envia la cadena a la funcion para resolverla
    return 0;
}


void evaluaciosn(char* cad){

    int z,op1,op2,num,count = 0;

    //while que recorrera toda la cadena
    while (cad[count] != '\0')
    {
        if (isOperator(cad[count]) == 0)//se determina si el caracter de la cadena es un operando o un operador
        {
            //en caso de que no sea un operador, tenemos que transformar el caracter a un entero primeramente
            // esto se hace simplemente restandole el caracter '0'
            num = cad[count]-'0';
            //se introduce la cadena
            top = push(top,num); 
        }
        else
        {
            /*
                en caso de que el caracter sea un operando se sacan los primero dos elementos de la pila en Op1 y Op2
                despues se eliminan los valores de la pila

                dependiendo del operador que sea se resuelve la opracion de la forma:
                    op2 + op1
                    op2-op1
                siempre la variable op2 como primer elemento de la operacion, el resultado se guarda en z y se agrega a la pila  
            */
            op1 = peek(top);
            top = pop(top);
            op2 = peek(top);
            top = pop(top);

            switch (cad[count])
            {
            case '+':
                z = op2 + op1;
                top = push(top,z);       
                break;
            case '-':
                z = op2 - op1;
                top = push(top,z);    
                break;
            case '*':
                z = op2 * op1;
                top = push(top,z);      
                break;
            case '/':
                z = op2 / op1;
                top = push(top,z);     
                break;
            case '^':
                z = pow(op2,op1);
                top = push(top,z);     
                break;
            
            default:
                break;
            }
        }
        
        count++;
        
    }

    //se imprime el resultado parea despues eliminarlo de la pila
    printf("\nEl resultado es: %i",peek(top));
    top = pop(top);
    
}


int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}


int empty(Operandos *top){
    return top == NULL;
}

Operandos *push(Operandos* top, char ca){
    Operandos*ptr;
    ptr = (Operandos*)malloc(sizeof(Operandos));
    ptr->data = ca;

 if (empty(top) == 1) {
        return top; 
    }
    if (top==NULL)
    {
        ptr->next=NULL;
        top=ptr;
    }
    else
    {
        ptr->next=top;
        top=ptr;
    }
    
    return top;
}

Operandos *pop(Operandos* top){
    Operandos *ptr;
    ptr = top;
    if (empty(top) == 1)
    {
        return 0;
    }
    else{
        top=top->next;
        free(ptr);
    }
    return top;
}

int peek(Operandos *top){
    if (empty(top) == 1)
    {
        /* code */
        return -1;
    }
    else
    {
        return top->data;
    }   
}