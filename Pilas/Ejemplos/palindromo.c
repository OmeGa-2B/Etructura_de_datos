#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char tipodato;

//programa que verifica si la cadena es un palindromo(se lee igual de izquierda a derecha que de derecha a izquierda)

//cracion de una estructura en el cual se guardaran los carcateres de la cadena para despues compararlo
typedef struct Cadena
{
    tipodato data;
    struct Cadena *next;
}cadena;

//inicializacion de una la pila
cadena *top = NULL;

//prototipos de las funciones que se crearan despues
cadena *push(cadena *top, char ca);
cadena *pop(cadena* top);
int empty(cadena* top); //verifica si la pila esta vacia
char *Nospace(char* cade); //funcion que elimina los espacios de la cadena para poder comparra sin problema

int main(){
    int flag = 1; //badera que se matendra igual si la palabra es un palindromo, si cambia a 0 no es un palindromo

    //creacion de la cadena
    char *cad;
    cad = (char*)malloc(sizeof(char)*100);  

    printf("\n---------------------------------\nPalindromo\n-----------------------------------\n");
    printf("Introdusca una frase o palabra: ");
    gets(cad);

    cad = Nospace(cad);//se manda la cadena a la funcion para eliminar los espacios, se sobreecribe
    puts(cad);

    int count = 0;

    //se agregan los carecteres a la pila para su posterior comparacion
    while (cad[count] != '\0')
    {
        top = push(top,cad[count]);
        count++;
    }

    count = 0;

    //recorre la cedena y saca los valores de la pila para comparar si la cadena de lee igual de izquierda a derecha que de derecha a izquierda
    while (cad[count] != '\0')
    {
        if(cad[count] != top->data){ //si un caracter es diferente, cambiara el valor de la badera a 0 
            printf("\ncomparacion %c",cad[count]);
            printf(" con %c", top->data);
            flag = 0;
            break;
        }else
        {
            top = pop(top);
        }
        count++;
    }
    
    if (flag == 1)
    {
        printf("\nla palabra es un palindromo\n");
    }
    else{
        printf("\nla palabra no es un palindromo\n");
    }
    
    return 0;
}

char *Nospace(char *cade){
    int i, j = 0;
    char *cadse;
    cadse = (char*)malloc(sizeof(char)*100);

    for (i = 0; i < strlen(cade); i++) {
        if (cade[i] != ' ') {
            cadse[j] = cade[i];
            j++;
        }
    }

    cadse[j] = '\0';

    return cadse;
}

int empty(cadena *top){
    return top == NULL;
}

cadena *push(cadena* top, char ca){
    cadena *ptr;
    ptr = (cadena*)malloc(sizeof(cadena));
    ptr->data = ca;

 if (ptr == NULL) {
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

cadena *pop(cadena* top){
    cadena *ptr;
    ptr = top;
    if (top==NULL)
    {
        printf("pila vacia");
    }
    else{
        top=top->next;
        free(ptr);
    }
    return top;
}