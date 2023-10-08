#include <stdio.h>
#include <stdlib.h>

//conversion de una operacion infija a postfija


//estructa que guardara los datos de los operadores
typedef struct operandos
{
    char data;
    struct operandos *next;
}operandos;

operandos *top = NULL; //inicializacion  de la pila

operandos *push(operandos *top, char ca);
operandos *pop(operandos* top);

int empty(operandos* top);
int peek(operandos *top);

//funcion que recibe el caracter para determinar si es un operador o no
int isOperator(char c);
//funcion que recibe el operando y determina su nivel de jerarquia
int ComOperator(char c);


void conversion(char* cad);

int main(){
    char *cad;
    cad =(char*)malloc(sizeof(char)*200);
    printf("introdusca una operacion en su forma infija: ");
    gets(cad);

    conversion(cad);
    //+-*^()/

    return 0;
}


void conversion(char* cad){
    int count = 0, v1,v2;
    char oper, caracter;
    while (cad[count] != '\0')
    {
        //si el caracter es un operando, se imprimira de forma inmediata
        if (isOperator(cad[count]) == 0)
        {
            printf("%c",cad[count]);
        }
        else
        {
            /*
                si el caracter es un operando, se deben considerar las siguientes dos cosas

                si la prioridad del operador es mayor que la proridad del operador de la cima de la pila -> se mete a la pila
                si es menor o igual -> se saca el operador del la cinma y se imprime

            */

            if (cad[count] != ')')
            {
                //si la pila esta vacia, se agrega el operador a la pila
                if (empty(top) == 1)
                {
                    top = push(top, cad[count]);
                }
                else{
                    //si es operador es un parentesis de apertura, se agregara a la pila
                    if (cad[count] == '(')
                    {
                        top = push(top, cad[count]);
                    }
                    else{
                            //en caso contrario, se tendra que hacer la comparcion de operadores
                            oper = peek(top); // se guarda el operador que tiene la pila en el tope
                            v1 = ComOperator(oper); //se mandan a la funcion ComOperator para determinar sus jerarquias
                            v2 = ComOperator(cad[count]);

                            if (v2 > v1) //si el operador de la cadena en la posicion count es mayor en jerarquia al del tope de la pila, se agrega a la pila 
                            {
                                top = push(top,cad[count]);
                            }
                            //en caos contrario, se imprime el valor del tope y se elimina de la pila, despues se agrega el operador de cad[count]
                            else
                            {
                                top = pop(top);
                                top = push(top,cad[count]);
                            }
                    }
                }   
            } 
            //en caso de que el caracter en cad[count] se un parentesis de cierre, se sacan los operadores de la pila hasta encontar el parentesis de apertura
            else{
                while (top ->data != '(')
                {
                    top = pop(top);
                }
            }  
        }
        

        count++;
    }

    //se imprime el ultimo valor que queda en la pila
    while (top != NULL)
    {
        if(top->data == '('){
        top = pop(top);
        }
        top = pop(top);
    }
    
    
}

//recibe un caracter correspondiente a un operador y regresa la jerarquia
int ComOperator(char c){
    if (c == '-'||c == '+')
    {
        return 1;
    }
    
    if (c == '*'||c == '/')
    {
        return 2;
    }

    if (c == '^')
    {
        return 3;
    }
    return 0;
}

//determina si es un oiperador o no
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
}


int empty(operandos *top){
    return top == NULL;
}

operandos *push(operandos* top, char ca){
    operandos*ptr;
    ptr = (operandos*)malloc(sizeof(operandos));
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

operandos *pop(operandos* top){
    operandos *ptr;
    ptr = top;
    if (empty(top) == 1)
    {
        return 0;
    }
    else{
        top=top->next;
        if (ptr->data != '(')
        {
            printf("%c",ptr->data);
        }
        free(ptr);
    }
    return top;
}

int peek(operandos *top){
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