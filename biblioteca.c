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

struct _nd{
    Book *info;
    struct _nd *left;
    struct _nd *right;
};
typedef struct _nd NodeBook;

NodeBook *createNodeBook(){
    NodeBook *new = malloc(sizeof(NodeBook));

    Book *book = malloc(sizeof(Book));

    printf("Título: ");
    fgets(book->title, MAX_TITLE, stdin);
    book->title[strcspn(new->info->title, "\n")] = '\0';

    printf("Autor: ");
    fgets(book->writer, MAX_NAME, stdin);
    book->writer[strcspn(new->info->writer, "\n")] = '\0';

    printf("Ano de publicação: ");
    scanf("%d", &book->year);

    printf("ID: ");
    scanf("%d", &book->id);

    strcpy("Disponível", book->status);

    strcpy("Ninguém", book->whoBorrowed);

    book->numOfLoans = 0;

    new->info = book;

    return new;
}

int main(){

    return 0;
}