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
        while (getchar() != '\n');
        insertBook(rootBook, newBook);
    }
    
    return rootBook;
}

NodeUser *insertUser(NodeUser *rootUser, NodeUser *newUser){
    if (rootUser == NULL){
        printf("\nUsuário cadastrado.\n");
        return newUser;
    }

    if (strcmp(rootUser->info->email, newUser->info->email) > 0){
        rootUser->left = insertUser(rootUser->left, newUser);
    } else if (strcmp(rootUser->info->email, newUser->info->email) < 0){
        rootUser->right = insertUser(rootUser->right, newUser);
    } else{
        printf("Email já cadastrado!\n");
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
            free(rootBook->info);
            free(rootBook);
            printf("\nLivro deletado!");
            return aux;
        } else if (rootBook->right == NULL){
            NodeBook *aux = rootBook->left;
            free(rootBook->info);
            free(rootBook);
            printf("\nLivro deletado!");
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
            free(rootUser->info);
            free(rootUser);
            printf("\nUsuário deletado.");
            return aux;
        } else if (rootUser->right == NULL){
            NodeUser *aux = rootUser->left;
            free(rootUser->info);
            free(rootUser);
            printf("\nUsuário deletado.");
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
    printf("\n\t%s (%d) | ID: %d\n\tAutor: %s | Status: %s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->year, rootBook->info->id, rootBook->info->writer, rootBook->info->status, rootBook->info->whoBorrowed);
    rootBook->right = showBooksInOrder(rootBook->right);

    return rootBook;
}

NodeUser *showUserInOrder(NodeUser *rootUser){
    if (rootUser == NULL){
        return rootUser;
    }

    rootUser->left = showUserInOrder(rootUser->left);
    printf("\n\tUsuário: %s\n\tEmail: %s\n\tNúmero de livros em posse: %d\n", rootUser->info->name, rootUser->info->email, rootUser->info->numOfBooks);
    rootUser->right = showUserInOrder(rootUser->right);

    return rootUser;
}

NodeBook *findBookById(NodeBook *rootBook, int id){
    if (rootBook == NULL){
        printf("\nLivro não encontrado\n");
        return NULL;
    }

    if (rootBook->info->id > id){
        rootBook->left = findBookById(rootBook->left, id);
    } else if (rootBook->info->id < id){
        rootBook->right = findBookById(rootBook->right, id);
    } else {
        printf("\n\t%s (%d) | ID: %d\n\tAutor: %s | Status: %s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->year, rootBook->info->id, rootBook->info->writer, rootBook->info->status, rootBook->info->whoBorrowed);
        return rootBook;
    }
    return rootBook;
}

NodeBook *findBookByWriter(NodeBook *rootBook, char writer[], int *verify){
    if (rootBook == NULL){
        return NULL;
    }
    
    if (strcmp(rootBook->info->writer, writer) == 0){
        printf("\n\t%s (%d) | ID: %d\n\tAutor: %s | Status: %s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->year, rootBook->info->id, rootBook->info->writer, rootBook->info->status, rootBook->info->whoBorrowed);
        *verify = 1;
    }


    findBookByWriter(rootBook->left, writer, verify);
    findBookByWriter(rootBook->right, writer, verify);

    return rootBook;
}

NodeUser *findUserByEmail(NodeUser *rootUser, char email[]){
    if (rootUser == NULL){
        printf("\nUsuário não encontrado\n");
        return NULL;
    }

    if (strcmp(rootUser->info->email, email) > 0){
        rootUser->left = findUserByEmail(rootUser->left, email);
    } else if (strcmp(rootUser->info->email, email) < 0){
        rootUser->right = findUserByEmail(rootUser->right, email);
    } else{
        printf("\n\tUsuário: %s\n\tEmail: %s\n\tNúmero de livros em posse: %d\n", rootUser->info->name, rootUser->info->email, rootUser->info->numOfBooks);
        return rootUser;
    }
    
    return rootUser;
}

NodeUser *findUserByName(NodeUser *rootUser, char name[], int *verify){
    if (rootUser == NULL){
        return NULL;
    }

    if (strcmp(rootUser->info->name, name) == 0){
        printf("\n\tUsuário: %s\n\tEmail: %s\n\tNúmero de livros em posse: %d\n", rootUser->info->name, rootUser->info->email, rootUser->info->numOfBooks);
        *verify = 1;
    }

    findUserByName(rootUser->left, name, verify);
    findUserByName(rootUser->right, name, verify);
    
    return rootUser;
}

NodeBook *findLoansByEmail(NodeBook *rootBook, char email[], int *verify){
    if (rootBook == NULL){
        return NULL;
    }

    if (strcmp(rootBook->info->whoBorrowed, email) == 0){
       printf("\n\t%s (%d) | ID: %d\n\tAutor: %s | Status: %s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->year, rootBook->info->id, rootBook->info->writer, rootBook->info->status, rootBook->info->whoBorrowed);
        *verify = 1;
    }

    findLoansByEmail(rootBook->left, email, verify);
    findLoansByEmail(rootBook->right, email, verify);
    
    return rootBook;
}

NodeBook *updateBook(NodeBook *rootBook, int id){
    if (rootBook == NULL){
        printf("\nLivro não encontrado\n");
        return NULL;
    }

    if (rootBook->info->id > id){
        rootBook->left = updateBook(rootBook->left, id);
    } else if (rootBook->info->id < id){
        rootBook->right = updateBook(rootBook->right, id);
    } else {
        printf("\n\t%s (%d) | ID: %d\n\tAutor: %s | Status: %s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->year, rootBook->info->id, rootBook->info->writer, rootBook->info->status, rootBook->info->whoBorrowed);
        char newTitle[MAX_TITLE], newWriter[MAX_NAME];
        int newYear;
        printf("\nAltere as informações:\n");
        printf("Caso não queira alterar Título e Autor digite NÃO, e para o ano digite 0\n");
        printf("Título: ");
        fgets(newTitle, MAX_TITLE, stdin);
        newTitle[strcspn(newTitle, "\n")] = '\0';
        if (strcmp(newTitle, "NÃO") != 0){
            strcpy(rootBook->info->title, newTitle);
        }
        printf("Autor: ");
        fgets(newWriter, MAX_NAME, stdin);
        newWriter[strcspn(newWriter, "\n")] = '\0';
        if (strcmp(newWriter, "NÃO") != 0){
            strcpy(rootBook->info->writer, newWriter);
        }
        printf("Ano de publicação: ");
        scanf("%d", &newYear);
        while (getchar() != '\n');
        if (newYear != 0){
            rootBook->info->year = newYear;
        }
        printf("\n\t%s (%d) | ID: %d\n\tAutor: %s | Status: %s | Emprestado para: %s\n", rootBook->info->title, rootBook->info->year, rootBook->info->id, rootBook->info->writer, rootBook->info->status, rootBook->info->whoBorrowed);
        printf("\nInformações alteradas.\n");

        return rootBook;
    }
    return rootBook;
}

NodeUser *updateUser(NodeUser *rootUser, char email[]){
    if (rootUser == NULL){
        printf("\nUsuário não encontrado\n");
        return NULL;
    }

    if (strcmp(rootUser->info->email, email) > 0){
        rootUser->left = updateUser(rootUser->left, email);
    } else if (strcmp(rootUser->info->email, email) < 0){
        rootUser->right = updateUser(rootUser->right, email);
    } else{
        printf("\n\tUsuário: %s\n\tEmail: %s\n\tNúmero de livros em posse: %d\n", rootUser->info->name, rootUser->info->email, rootUser->info->numOfBooks);
        char newName[MAX_NAME];
        printf("\nAltere o nome:\n");
        printf("Caso queira manter digite NÃO\n");
        printf("Nome: ");
        fgets(newName, MAX_NAME, stdin);
        newName[strcspn(newName, "\n")] = '\0';
        if (strcmp(newName, "NÃO") != 0){
            strcpy(rootUser->info->name, newName);
            printf("\nInformações alteradas.\n");
        }
        printf("\n\tUsuário: %s\n\tEmail: %s\n\tNúmero de livros em posse: %d\n", rootUser->info->name, rootUser->info->email, rootUser->info->numOfBooks);
        

        return rootUser;
    }
    
    return rootUser;
}

NodeBook *bookLoan(NodeBook *rootBook, NodeUser *rootUser, int id, char email[]){
    if (rootBook == NULL){
        printf("\nLivro não encontrado.\n");
        return NULL;
    }
    if (rootUser == NULL){
        printf("\nUsuário não encontrado.\n");
        return NULL;
    }

    if (rootBook->info->id > id){
        rootBook->left = bookLoan(rootBook->left, rootUser, id, email);
    } else if (rootBook->info->id < id){
        rootBook->right = bookLoan(rootBook->right, rootUser, id, email);
    } else{
        if (strcmp(rootUser->info->email, email) > 0){
            rootBook = bookLoan(rootBook, rootUser->left, id, email);
        } else if (strcmp(rootUser->info->email, email) < 0){
            rootBook->right = bookLoan(rootBook, rootUser->right, id, email);
        } else{
            if (strcmp(rootBook->info->status, "Disponível") == 0){
                strcpy(rootBook->info->whoBorrowed, email);
                strcpy(rootBook->info->status, "Emprestado");
                rootBook->info->numOfLoans++;
                rootUser->info->numOfBooks++;
                printf("Empréstimo realizado.\n");
            } else{
                printf("Livro já emprestado\n");
            }
        }
    }
    return rootBook;
}

NodeBook *returnBook(NodeBook *rootBook, NodeUser *rootUser, int id){
    if (rootBook == NULL){
        printf("\nLivro não encontrado.\n");
        return NULL;
    }

    if (rootBook->info->id > id){
        rootBook->left = returnBook(rootBook->left, rootUser, id);
    } else if (rootBook->info->id < id){
        rootBook->right = returnBook(rootBook->right, rootUser, id);
    } else{
            if (strcmp(rootBook->info->status, "Emprestado") == 0){
                strcpy(rootBook->info->whoBorrowed, "Ninguém");
                strcpy(rootBook->info->status, "Disponível");
                rootUser->info->numOfBooks--;
                printf("Devolução realizada.\n");
            } else{
                printf("Livro já está disponível!\n");
            }
        }
    return rootBook;
}

void freeBooks(NodeBook *rootBook){
    if (rootBook == NULL){
        return;
    }

    freeBooks(rootBook->left);
    freeBooks(rootBook->right);

    free(rootBook->info);
    free(rootBook);
}

void freeUsers(NodeUser *rootUser){
    if (rootUser == NULL){
        return;
    }

    freeUsers(rootUser->left);
    freeUsers(rootUser->right);

    free(rootUser->info);
    free(rootUser);
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
        printf("7. Mostrar todos\n");
        printf("8. Estatísticas\n");
        printf("0. Sair\n");
        printf("------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
        while (getchar() != '\n');

        if (option < 0 || option > 7){
            printf("Opção inválida!\n");
        }

        if (option == 1){
            int optcad;

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
            }
        }

        if (option == 2){
            int optfnd;

            printf("\n1. Livros\n");
            printf("2. Usuários\n");
            printf("3. Empréstimos\n");
            printf("0. Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &optfnd);
            while (getchar() != '\n');

            if (optfnd < 0 || optfnd > 3){
                printf("Opção inválida!\n");
            }

            if (optfnd == 1){
                int optfndbook;

                printf("\n1. Por ID\n");
                printf("2. Por autor\n");
                printf("0. Voltar\n");
                printf("Escolha uma opção: ");
                scanf("%d", &optfndbook);
                while (getchar() != '\n');

                if (optfndbook < 0 || optfndbook > 2){
                    printf("\nOpção inválida!\n");
                }
                if (optfndbook == 1){
                    int idb;
                    printf("ID: ");
                    scanf("%d", &idb);
                    while (getchar() != '\n');
                    findBookById(rootBook, idb);
                }
                if (optfndbook == 2){
                    char writerb[MAX_NAME];
                    int verify = 0;
                    printf("Autor: ");
                    fgets(writerb, MAX_NAME, stdin);
                    writerb[strcspn(writerb, "\n")] = '\0';
                    findBookByWriter(rootBook, writerb, &verify);
                    if (verify == 0){
                        printf("\nLivro não encontrado.\n");
                    }
                }
            }

            if (optfnd == 2){
                int optfnduser;

                printf("\n1. Por nome\n");
                printf("2. Por email\n");
                printf("0. Voltar\n");
                printf("Escolha uma opção: ");
                scanf("%d", &optfnduser);
                while (getchar() != '\n');

                if (optfnduser < 0 || optfnduser > 2){
                    printf("\nOpção inválida!\n");
                }
                if (optfnduser == 1){
                    char name[MAX_NAME];
                    int verify = 0;
                    printf("Nome: ");
                    fgets(name, MAX_NAME, stdin);
                    name[strcspn(name, "\n")] = '\0';
                    findUserByName(rootUser, name, &verify);
                    if (verify == 0){
                        printf("\nUsuário não encontrado.\n");
                    }
                }
                if (optfnduser == 2){
                    char email[MAX_EMAIL];
                    printf("Email: ");
                    fgets(email, MAX_NAME, stdin);
                    email[strcspn(email, "\n")] = '\0';
                    findUserByEmail(rootUser, email);
                }
            }
            
            if (optfnd == 3){
                char email[MAX_EMAIL];
                    int verify = 0;
                    printf("Email: ");
                    fgets(email, MAX_NAME, stdin);
                    email[strcspn(email, "\n")] = '\0';
                    findLoansByEmail(rootBook, email, &verify);
                    if (verify == 0){
                        printf("\nNenhum empréstimo.\n");
                    }
            }
        }

        if (option == 3){
            int optupd;

            printf("\n1. Livros\n");
            printf("2. Usuários\n");
            printf("0. Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &optupd);
            while (getchar() != '\n');

            if (optupd < 0 || optupd > 2){
                    printf("\nOpção inválida!\n");
            }
            if (optupd == 1){
                int id;
                printf("ID: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                rootBook = updateBook(rootBook, id);
            }
            if (optupd == 2){
                char email[MAX_EMAIL];
                printf("Email: ");
                fgets(email, MAX_NAME, stdin);
                email[strcspn(email, "\n")] = '\0';
                rootUser = updateUser(rootUser, email);
            }
        }

        if (option == 4){
            int optdel;
            printf("\n1. Livro\n");
            printf("2. Usuário\n");
            printf("0. Voltar\n");
            printf("Escolha uma opção: ");
            scanf("%d", &optdel);               
            while (getchar() != '\n');

            if (optdel < 0 || optdel > 2){
                    printf("\nOpção inválida!\n");
            }

            if (optdel == 1){
                int id;
                printf("ID: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                rootBook = deleteBook(rootBook, id);
            }

            if (optdel == 2){
                char email[MAX_EMAIL];
                printf("Email: ");
                fgets(email, MAX_NAME, stdin);
                email[strcspn(email, "\n")] = '\0';
                rootUser = deleteUser(rootUser, email);
            }

        }

        if (option == 5){
            printf("\n5. Empréstimo\n");
            char email[MAX_EMAIL];
            int id;
            printf("\nID do livro: ");
            scanf("%d", &id);
            while (getchar() != '\n');
            printf("Email do usuário: ");
            scanf("%s", email);
            while (getchar() != '\n');
            bookLoan(rootBook, rootUser, id, email);
        }

        if (option == 6){
            int id;
            printf("ID: ");
            scanf("%d", &id);
            while (getchar() != '\n');
            returnBook(rootBook, rootUser, id);
        }
    }
    
    freeBooks(rootBook);
    freeUsers(rootUser);

    return 0;
}
