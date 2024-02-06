#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "palabras.h"

// Estructura para el árbol de búsqueda
struct TreeNode
{
    char letter;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Estructura para la lista de jugadores
struct Node
{
    char Nickname[50];
    int number;
    struct Node *next;
};

// Prototipos de funciones
void menu();
//   funciones para la obtencion de palabras al azar
const char *banco_palabras(int op);
const char *palabra_elegir(const char **categoria, int count);
//     funciones ABB
struct TreeNode *createNode(char letter);
struct TreeNode *insertNode(struct TreeNode *root, char letter);
struct TreeNode *saveLettersToBST(const char *word);
int buscarLetraEnArbol(struct TreeNode *root, char letra);
void imprimirArbol(struct TreeNode *root);
void liberarArbol(struct TreeNode *root);
// funciones Lista de jugadores
struct Node *createPlayerNode(char *name, int number);
struct Node *insertPlayerNode(struct Node *head, struct Node *newNode);
void freePlayerList(struct Node *head);
void list_players(int puntos);
struct Node *buscarJugador(struct Node *head, const char *nombre);
// funciones de interfaz y funcionamiento del juego
void dibujarahorcado(int intentos, int puntos, struct Node *headPlayerList);
void interfas(const char* palabra, int categoria, struct TreeNode *bstRoot, int intentos, char* palabra_oculta, int puntos);
int comprobacionpalabra(char* palabra_oculta);

struct Node *headPlayerList = NULL;
struct TreeNode *RaizLetras = NULL;

int main()
{
    srand(time(NULL));

    printf("\nPROYECTO FINAL DE ESTRUCTURA Y ALGORITMO DE DATOS\n");
    printf("\n-------------------------------------------------------------------\n");
    printf("\t\tJUEGO DE AHORCADO\n\n");
    //insertar valores a la lista para tener un visualizacion de como funciona
    headPlayerList = createPlayerNode("SoEasy",400);
    headPlayerList =  createPlayerNode("Omega",700);
    headPlayerList = createPlayerNode("Juan",550);
    menu();
    system("PAUSE");
    freePlayerList(headPlayerList);//liberar memoria de la lista de usuraio
    return 0;
}

void menu()
{
    int op;
    char nickname[50];
    printf("\t\nMenu de categorias");
    printf("\n1)Paises\n2)Animales\n3)Comidas\n4)Generos de musica\n5)Nombres de juegos\n6)Deportes\n7)salir\nopcion: ");
    scanf("%i", &op);
    if (op < 1 || op > 7)//verificacion de que la opcion este dentro del rango de opciones, si esta fuera del rango se lo indicara al usuario
    {
        system("cls"); // Cambié "clear" por "cls" para sistemas Windows
        printf("\n-------------------------------------------------------------------\n");
        printf("\nOpcion elegida no valida, intentelo de nuevo");
        printf("\n-------------------------------------------------------------------\n");
        printf("\t\tJUEGO DE AHORCADO\n\n");
        menu();
    }
    else
    {
        if (op == 7)//si op(referente a opcion) es 7 el programa terminara
        {
            system("cls");
            printf("\n\nGracias por jugar\n\n");
            return 0;
        }
        system("cls");//limpia la pantalla
        const char *palabra = banco_palabras(op); //obtine una pala al azar de "palabras.h" dependiendo de la categoria
        struct TreeNode *bstRoot = saveLettersToBST(palabra);//ingresa la palabra dento de un ABB

        int longitud = strlen(palabra); // obtiene la longitud de la palabra
        char* palabra_oculta;//cadena deonde se guardara la palabra en forma de "------------"
        palabra_oculta = (char*)malloc(sizeof(char)*longitud);

        for (int i = 0; i < longitud; i++) {
            palabra_oculta[i] = '_';
        }

        palabra_oculta[longitud] = '\0';
        interfas(palabra,op,bstRoot,0,palabra_oculta, 0);//palabra,categoria,raiz del arbol,intentos,palabra en forma oculta, puntos
    }
}

const char *banco_palabras(int op)
{
    //retorna una palabra al azar de palabras.h dependiendo de la categoria
    switch (op)
    {
    case 1:
        return palabra_elegir(PAISES, PAISES_COUNT);
    case 2:
        return palabra_elegir(ANIMALES, ANIMALES_COUNT);
    case 3:
        return palabra_elegir(COMIDA, COMIDA_COUNT);
    case 4:
        return palabra_elegir(MUSICA, MUSICA_COUNT);
    case 5:
        return palabra_elegir(GAMES, GAMES_COUNT);
    case 6:
        return palabra_elegir(SPORTS, SPORTS_COUNT);
    default:
        return NULL;
    }
}

//retorna un indice aleatorio dependiendo
const char *palabra_elegir(const char **categoria, int count)
{
    int indice = rand() % count;
    return categoria[indice];
}

// Funciones del árbol binario de búsqueda

// Función para crear un nodo
struct TreeNode *createNode(char letter)
{
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (newNode == NULL)
    {
        fprintf(stderr, "Fallo en la asignacion de memoria\n");
        exit(EXIT_FAILURE);
    }
    newNode->letter = letter;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Función para insertar una letra en el árbol
struct TreeNode *insertNode(struct TreeNode *root, char letter)
{
    if (root == NULL)
    {
        return createNode(letter);
    }

    if (letter < root->letter)
    {
        root->left = insertNode(root->left, letter);
    }
    else if (letter > root->letter)
    {
        root->right = insertNode(root->right, letter);
    }

    return root;
}

// Función para guardar la palabra en el árbol
struct TreeNode *saveLettersToBST(const char *word)
{
    struct TreeNode *root = NULL;
    int i, len = strlen(word);

    for (i = 0; i < len; i++)
    {
        root = insertNode(root, word[i]);
    }

    return root;
}

//funcion para buscar una letra en el arbol
int buscarLetraEnArbol(struct TreeNode *root, char letra)
{
    if (root == NULL)
    {
        return 0; // La letra no se encontró en el árbol
    }

    if (letra == root->letter)
    {
        return 1; // La letra se encontró en el árbol
    }
    else if (letra < root->letter)
    {
        return buscarLetraEnArbol(root->left, letra);
    }
    else
    {
        return buscarLetraEnArbol(root->right, letra);
    }
}

//funcion para imprimir los valores del arbol
void imprimirArbol(struct TreeNode *root)
{
    if (root != NULL)
    {
        imprimirArbol(root->left);
        printf("%c ", root->letter);
        imprimirArbol(root->right);
    }
}

//liberar un arbol;
void liberarArbol(struct TreeNode *root) {
    if (root != NULL) {
        liberarArbol(root->left);
        liberarArbol(root->right);
        free(root);  // Liberar el nodo actual
    }
}
// Funciones para la lista de jugadores

// Función para crear un nuevo nodo para la lista
struct Node *createPlayerNode(char *name, int number)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Fallo en la asignacion de memoria\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->Nickname, name, sizeof(newNode->Nickname) - 1);
    newNode->Nickname[strcspn(newNode->Nickname, "\n")] = '\0';
    newNode->number = number;
    newNode->next = NULL;
    insertPlayerNode(headPlayerList,newNode);
}

// Función para insertar un nodo en la lista (ordenando de mayor a menor)
struct Node *insertPlayerNode(struct Node *headPlayerList, struct Node *newNode)
{
    // Verificar si el jugador ya existe en la lista
    struct Node *existingPlayer = buscarJugador(headPlayerList, newNode->Nickname);

    if (existingPlayer != NULL)
    {
        // El jugador ya existe, actualizar los puntos
        existingPlayer->number += newNode->number;
        free(newNode);  // Liberar memoria del nuevo nodo, ya que no se usará
    }
    else
    {
        // El jugador no existe, insertar un nuevo nodo
        if (headPlayerList == NULL || newNode->number > headPlayerList->number)
        {
            newNode->next = headPlayerList;
            return newNode;
        }

        struct Node *current = headPlayerList;
        while (current->next != NULL && newNode->number <= current->next->number)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    return headPlayerList;
}


// Función para liberar la memoria de la lista
void freePlayerList(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}

//funcion para crear un nuevo perfil de jugador a base de un nickname y unos puntos
void list_players(int puntos){
    char nickName[50];
    system("cls");
    printf("\t\tJUEGO DE AHORCADO\n\n");
    printf("\n-------------------------------------------------------------------\n");
    printf("\ningrese su nickname: ");
    fflush(stdin);
    fgets(nickName,sizeof(nickName),stdin);
    struct Node *jugadorencontrado = buscarJugador(headPlayerList,nickName);//regresa un puntero, el puntero sera NULL si no existe el nickname
    if (jugadorencontrado != NULL)                                          //osea que el jugador no existe
    {
        jugadorencontrado->number += puntos;
    }
    else{
        headPlayerList = createPlayerNode(nickName,puntos);
    }
    system("PAUSE");
    menu();//regresa al menu
}

struct Node *buscarJugador(struct Node *head, const char *nombre) {
    struct Node *current = head;

    while (current != NULL) {
        if (strcmp(current->Nickname, nombre) == 0) {
            // El jugador se encontró, devuelve el puntero al nodo
            return current;
        }
        current = current->next;
    }

    // El jugador no se encontró en la lista
    return NULL;
}


//funciones principales para la interfaz

//verificacion si el usuario ya encontro todas las letras o no
//si hay algun guion significa que aun faltan letras
int comprobacionpalabra(char* palabra_oculta){
    for (int i = 0; palabra_oculta[i] != '\0'; i++)
    {
        if (palabra_oculta[i] == '_')
        {
            return 0;
        }
    }

    return 1;
}

//interfaz principal
void interfas(const char* palabra, int categoria,struct TreeNode *bstRoot, int intentos,char* palabra_oculta, int puntos){
    char letra;
    system("cls");//limpia la pantall
    switch (categoria)//lo unico que hace esto es seguir imprimiendo la categoria a la cual pertenece la palabra
    {
    case 1:
        printf("\n\t\t\t\t\t\tPAISES\n");
        printf("\n\t\t-------------------------------------------------------------------\n\n");
        break;
    case 2:
        printf("\n\t\t\t\t\t\tANIMALES\n");
        printf("\n\t\t-------------------------------------------------------------------\n\n");
        break;
    case 3:
        printf("\n\t\t\t\t\t\tCOMIDA\n\n");
        printf("\n\t\t-------------------------------------------------------------------\n\n");
        break;
    case 4:
        printf("\n\t\t\t\t\t\tGENEROS MUSICALES\n\n");
        printf("\n\t\t-------------------------------------------------------------------\n\n");
        break;
    case 5:
        printf("\n\t\t\t\t\t\tNOMBRE DE VIDEOJUEGOS\n\n");
        printf("\n\t\t-------------------------------------------------------------------\n\n");
        break;
    case 6:
        printf("\n\t\t\t\t\t\tDEPORTES\n\n");
        printf("\n\t\t-------------------------------------------------------------------\n\n");
        break;
    default:
        break;
    }

    if (intentos < 6)
    {

        //imprime la palabra de forma oculata "--------"
        printf("palabra a adivinar: ");
        for (int i = 0; palabra_oculta[i] != '\0'; i++)
        {
            printf("%c",palabra_oculta[i]);
        }
        printf("\n\n\n");

        dibujarahorcado(intentos, puntos,headPlayerList);

        printf("\n\n\nLetras que ya fueron utilizadas: ");
        imprimirArbol(RaizLetras);
        printf("\n");

        printf("\nIngrese alguna letra: ");
        scanf(" %c",&letra);

        //verifica si la letra que introdujo el usuario ya la habia introducido antes a treavs de un ABB
        if (buscarLetraEnArbol(RaizLetras,letra) == 1){
            printf("\nla letra ya a sido intoducida anteriormente, introdusca otra letra\n");
            system("PAUSE");
            interfas(palabra,categoria,bstRoot,intentos,palabra_oculta, puntos);
        }
        else
        {
            RaizLetras =insertNode(RaizLetras, letra);
        }

        if (buscarLetraEnArbol(bstRoot,letra) == 1)
        {
            //si la letra coicide con alguna letra de la palabra, los guines sons sustituidos por la letra
            //se suma 100 puntos por cada letra correcta
            for (int i = 0; palabra[i] != '\0'; ++i)
            {
                if (palabra[i] == letra)
                {
                    palabra_oculta[i] = letra;
                    puntos += 100;
                }
            }
            //se comprueba si el usuario ya encontro todas las letras
            if (comprobacionpalabra(palabra_oculta) == 1)
            {
                system("cls");
                dibujarahorcado(intentos,puntos,headPlayerList);
                printf("\nFelicidaes encontraste la palabra correcta: %s\n",palabra);
                system("PAUSE");
                liberarArbol(RaizLetras);//libera al arbol
                RaizLetras = NULL;
                free(palabra_oculta);
                list_players(puntos);
            }
            else
            {
                interfas(palabra,categoria,bstRoot,intentos,palabra_oculta, puntos);
            }
        }
        else
        {
            //si el ususuario falla con una letra, se le restas 50 puntos
            puntos -= 50;
            if (puntos < 0)
            {
                puntos = 0;
            }
            interfas(palabra,categoria,bstRoot,intentos+1,palabra_oculta, puntos);
        }
    }
    else
    {
        printf("\nNo has conseguido adivinar la palabra :(, la palabra era: %s",palabra);
        system("PAUSE");
        liberarArbol(RaizLetras);//libera al arbol
        RaizLetras = NULL;
        free(palabra_oculta);
        list_players(puntos);
    }
}

//funcion para dibujar cada error del usuario
void dibujarahorcado(int intentos, int puntos, struct Node *headPlayerList) {
    switch(intentos) {
        case 0:
            //imprime la figura del ahorcado, los puntos del jugador y los tres jugadores con mayor puntaje
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t      | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t      | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t      | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
        case 1:
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t O    | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t      | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t      | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
        case 2:
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t O    | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t |    | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t      | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
        case 3:
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t O    | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t/|    | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t      | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
        case 4:
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t O    | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t/|\\   | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t      | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
        case 5:
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t O    | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t/|\\   | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t/     | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
        case 6:
            printf("\t\t -----| \t\t\t\t\t\t TOP 3: \n");
            printf("\t\t |    | \t tus puntos: %i \n",puntos);
            printf("\t\t O    | \t\t\t\t\t\t 1.- %s: %i\n",headPlayerList->Nickname,headPlayerList->number);
            printf("\t\t/|\\   | \t\t\t\t\t\t 2.- %s: %i \n",headPlayerList->next->Nickname,headPlayerList->next->number);
            printf("\t\t/ \\   | \t\t\t\t\t\t 3.- %s: %i \n",headPlayerList->next->next->Nickname,headPlayerList->next->next->number);
            printf("\t\t      |\n");
            break;
    }
}
