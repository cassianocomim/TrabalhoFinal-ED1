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
    char status[12];
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

    if (rootBook->info->id > newBook->info->id){
        rootBook->left = insertBook(rootBook->left, newBook);
    } else if (rootBook->info->id < newBook->info->id){
        rootBook->right = insertBook(rootBook->right, newBook);
    } else{
        printf("ID já existente, escolha outro id.\n");
        printf("ID: ");
        scanf("%d", &newBook->info->id);
        insertBook(rootBook, newBook);
    }
    
    return rootBook;
}

NodeUser *insertUser(NodeUser *rootUser, NodeUser *newUser){
    if (rootUser == NULL){
        return newUser;
    }

    if (strcmp(rootUser->info->email, newUser->info->email) >= 0){
        rootUser->left = insertUser(rootUser->left, newUser);
    } else{
        rootUser->right = insertUser(rootUser->right, newUser);
    }
    
    return rootUser;
}

NodeBook *deleteBook(NodeBook *rootBook, int id){
    if (rootBook == NULL){
        printf("Livro não encontrado.\n");
        return rootBook;
    }
    
    if (rootBook->info->id > id){
        rootBook->left = deleteBook(rootBook->left, id);
    } else if (rootBook->info->id < id){
        rootBook->right = deleteBook(rootBook->right, id);
    } else {
        //Caso com 0 ou 1 filho
        if (rootBook->left == NULL){
            NodeBook *aux = rootBook->right;
            free(rootBook);
            return aux;
        } else if (rootBook->right == NULL){
            NodeBook *aux = rootBook->left;
            free(rootBook);
            return aux;
        }

        //Caso com 2 filhos
        NodeBook *aux = rootBook->right;
        while (aux->left != NULL){
            aux = aux->left;
        }
        rootBook->info->id = aux->info->id;

        rootBook->right = deleteBook(rootBook->right, aux->info->id);
    }
    return rootBook;
}

NodeUser *deleteUser(NodeUser *rootUser, char email[]){
    if (rootUser == NULL){
        printf("Usuário não encontrado.\n");
        return rootUser;
    }
    
    
    if (strcmp(rootUser->info->email, email) > 0){
        rootUser->left = deleteUser(rootUser->left, email);
    } else if (strcmp(rootUser->info->email, email) < 0){
        rootUser->right = deleteUser(rootUser->right, email);
    } else {
        //Caso com 0 ou 1 filho
        if (rootUser->left == NULL){
            NodeUser *aux = rootUser->right;
            free(rootUser);
            return aux;
        } else if (rootUser->right == NULL){
            NodeUser *aux = rootUser->left;
            free(rootUser);
            return aux;
        }

        //Caso com 2 filhos
        NodeUser *aux = rootUser->right;
        while (aux->left != NULL){
            aux = aux->left;
        }
        strcpy(rootUser->info->email, aux->info->email);

        rootUser->right = deleteUser(rootUser->right, aux->info->email);
    }
    return rootUser;
}

NodeBook *showBooksInOrder(NodeBook *rootBook){
    if (rootBook == NULL){
        return rootBook;
    }

    rootBook->left = showBooksInOrder(rootBook->left);
    printf("\t %s | %s | %d | ID: %d \n\t%s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->writer, rootBook->info->year, rootBook->info->id, rootBook->info->status, rootBook->info->whoBorrowed);
    rootBook->right = showBooksInOrder(rootBook->right);

    return rootBook;
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
    showBooksInOrder(rootBook);
    //necessário para delete
    // char email[MAX_EMAIL];
    // printf("Email: ");
    // scanf("%s", email);
    // while (getchar() != '\n');
    // int id;
    // printf("ID: ");
    // scanf("%d", &id);
    // while (getchar() != '\n');
    

    return 0;
}
