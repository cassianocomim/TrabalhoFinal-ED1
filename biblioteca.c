#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_EMAIL 200
#define MAX_TITLE 100

typedef struct{
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    int numOfBooks;
} User;

typedef struct{
    char title[MAX_TITLE];
    char writer[MAX_NAME];
    int year;
    int id;
    char status[10];
    char whoBorrowed[MAX_EMAIL];
    int numOfLoans;
} Book;

struct _nu{
    User *info;
    struct _nu *left;
    struct _nu *right;
};
typedef struct _nu NodeUser;

struct _nb{
    Book *info;
    struct _nb *left;
    struct _nb *right;
};
typedef struct _nb NodeBook;

NodeUser *createNodeUser(){
    NodeUser *new = malloc(sizeof(NodeUser));
    
    User *user = malloc(sizeof(User));

    printf("Nome de usuário: ");
    fgets(user->name, MAX_NAME, stdin);
    user->name[strcspn(user->name, "\n")] = '\0';

    printf("Email: ");
    fgets(user->email, MAX_EMAIL, stdin);
    user->email[strcspn(user->email, "\n")] = '\0';

    user->numOfBooks = 0;
    
    new->info = user;
    new->left = NULL;
    new->right = NULL;
    
    return new;
}

NodeBook *createNodeBook(){
    NodeBook *new = malloc(sizeof(NodeBook));

    Book *book = malloc(sizeof(Book));

    printf("Título: ");
    fgets(book->title, MAX_TITLE, stdin);
    book->title[strcspn(book->title, "\n")] = '\0';

    printf("Autor: ");
    fgets(book->writer, MAX_NAME, stdin);
    book->writer[strcspn(book->writer, "\n")] = '\0';

    printf("Ano de publicação: ");
    scanf("%d", &book->year);

    printf("ID: ");
    scanf("%d", &book->id);

    while (getchar() != '\n'); //Ajuda de LLM para limpar o buffer do \n após o scanf e não prejudiar o fgets.

    strcpy(book->status, "Disponível");

    strcpy(book->whoBorrowed, "Ninguém");

    book->numOfLoans = 0;

    new->info = book;
    new->left = NULL;
    new->right = NULL;

    return new;
}

NodeBook *insertBook(NodeBook *rootBook, NodeBook *newBook){
    if (rootBook == NULL){
        return newBook;
    }

    if (rootBook->info->id >= newBook->info->id){
        rootBook->left = insertBook(rootBook->left, newBook);
    } else{
        rootBook->right = insertBook(rootBook->right, newBook);
    }
    
    return rootBook;
}

NodeUser *insertUser(NodeUser *rootUser, NodeUser *newUser){
    if (rootUser == NULL){
        return newUser;
    }

    if (strcmp(rootUser->info->name, newUser->info->name) >= 0){
        rootUser->left = insertUser(rootUser->left, newUser);
    } else{
        rootUser->right = insertUser(rootUser->right, newUser);
    }
    
    return rootUser;
}



int main(){
    int option= -1;
    NodeBook *rootBook = NULL;
    NodeUser *rootUser = NULL;

    while (option != 0){
        printf("\n----------Biblioteca----------\n");
        printf("1. Cadastro\n");
        printf("2. Consulta\n");
        printf("3. Atualização\n");
        printf("4. Exclusão\n");
        printf("5. Empréstimo\n");
        printf("6. Devolução\n");
        printf("7. Estatísticas\n");
        printf("0. Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        while (getchar() != '\n');

        if (option < 0 || option > 7){
            printf("Opção inválida!\n");
        }

        if (option == 0){
            break;
        }

        if (option == 1){
            int optcad = -1;

            printf("\n1. Livros\n");
            printf("2. Usuários\n");
            printf("0. Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &optcad);
            while (getchar() != '\n');

            if (optcad < 0 || optcad > 2){
                printf("Opção inválida!\n");
            }

            if (optcad == 1){
                rootBook = insertBook(rootBook, createNodeBook());
                printf("\nLivro cadastrado.\n");
            }

            if (optcad == 2){
                rootUser = insertUser(rootUser, createNodeUser());
                printf("\nUsuário cadastrado.\n");
            }
        }
    }


    return 0;
}
