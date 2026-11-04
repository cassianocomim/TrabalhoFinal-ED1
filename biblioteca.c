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

    strcpy("Disponível", book->status);

    strcpy("Ninguém", book->whoBorrowed);

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

    return 0;
}
