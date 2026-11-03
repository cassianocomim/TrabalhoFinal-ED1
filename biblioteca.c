#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_EMAIL 200
#define MAX_TITLE 100

typedef struct{
    char name[MAX_NAME];
    char email[MAX_EMAIL];
} User;

typedef struct{
    char title[MAX_TITLE];
    char writer[MAX_NAME];
    int year;
    int id;
    char status[10];
    char whoborrowed[MAX_EMAIL];
} Book;

