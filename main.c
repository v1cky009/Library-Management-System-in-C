#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_PATRONS 100

typedef struct {
    int id;
    char title[100];
    char author[100];
    int available;
} Book;

typedef struct {
    int id;
    char name[100];
    char email[100];
    int borrowedBooks;
} Patron;

Book books[MAX_BOOKS];
Patron patrons[MAX_PATRONS];
int numBooks = 0;
int numPatrons = 0;

void addBook(Book *books, int *numBooks) {
    if (*numBooks >= MAX_BOOKS) {
        printf("Book list is full.\n");
        return;
    }
    printf("Enter book ID: ");
    scanf("%d", &books[*numBooks].id);
    printf("Enter book title: ");
    scanf("%s", books[*numBooks].title);
    printf("Enter book author: ");
    scanf("%s", books[*numBooks].author);
    books[*numBooks].available = 1;
    (*numBooks)++;
}

void removeBook(Book *books, int *numBooks) {
    int id;
    printf("Enter book ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < *numBooks; i++) {
        if (books[i].id == id) {
            for (int j = i; j < *numBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            (*numBooks)--;
            printf("Book removed.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void listBooks(Book *books, int numBooks) {
    printf("ID\tTitle\t\tAuthor\tAvailable\n");
    for (int i = 0; i < numBooks; i++) {
        printf("%d\t%s\t%s\t%s\n", books[i].id, books[i].title, books[i].author, books[i].available ? "Yes" : "No");
    }
}

void addPatron(Patron *patrons, int *numPatrons) {
    if (*numPatrons >= MAX_PATRONS) {
        printf("Patron list is full.\n");
        return;
    }
    printf("Enter patron ID: ");
    scanf("%d", &patrons[*numPatrons].id);
    printf("Enter patron name: ");
    scanf("%s", patrons[*numPatrons].name);
    printf("Enter patron email: ");
    scanf("%s", patrons[*numPatrons].email);
    patrons[*numPatrons].borrowedBooks = 0;
    (*numPatrons)++;
}

void removePatron(Patron *patrons, int *numPatrons) {
    int id;
    printf("Enter patron ID to remove: ");
    scanf("%d", &id);
    for (int i = 0; i < *numPatrons; i++) {
        if (patrons[i].id == id) {
            for (int j = i; j < *numPatrons - 1; j++) {
                patrons[j] = patrons[j + 1];
            }
            (*numPatrons)--;
            printf("Patron removed.\n");
            return;
        }
    }
    printf("Patron not found.\n");
}

void listPatrons(Patron *patrons, int numPatrons) {
    printf("ID\tName\t\tEmail\tBorrowed Books\n");
    for (int i = 0; i < numPatrons; i++) {
        printf("%d\t%s\t%s\t%d\n", patrons[i].id, patrons[i].name, patrons[i].email, patrons[i].borrowedBooks);
    }
}

void checkOutBook(Book *books, int numBooks, Patron *patrons, int numPatrons) {
    int bookId, patronId;
    printf("Enter book ID to check out: ");
    scanf("%d", &bookId);
    printf("Enter patron ID: ");
    scanf("%d", &patronId);
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookId && books[i].available) {
            books[i].available = 0;
            for (int j = 0; j < numPatrons; j++) {
                if (patrons[j].id == patronId) {
                    patrons[j].borrowedBooks++;
                    printf("Book checked out.\n");
                    return;
                }
            }
            printf("Patron not found.\n");
            return;
        }
    }
    printf("Book not found or not available.\n");
}

void returnBook(Book *books, int numBooks, Patron *patrons, int numPatrons) {
    int bookId, patronId;
    printf("Enter book ID to return: ");
    scanf("%d", &bookId);
    printf("Enter patron ID: ");
    scanf("%d", &patronId);
    for (int i = 0; i < numBooks; i++) {
        if (books[i].id == bookId && !books[i].available) {
            books[i].available = 1;
            for (int j = 0; j < numPatrons; j++) {
                if (patrons[j].id == patronId) {
                    patrons[j].borrowedBooks--;
                    printf("Book returned.\n");
                    return;
                }
            }
            printf("Patron not found.\n");
            return;
        }
    }
    printf("Book not found or already available.\n");
}

void menu() {
    int choice;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Remove Book\n");
        printf("3. List Books\n");
        printf("4. Add Patron\n");
        printf("5. Remove Patron\n");
        printf("6. List Patrons\n");
        printf("7. Check Out Book\n");
        printf("8. Return Book\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addBook(books, &numBooks); break;
            case 2: removeBook(books, &numBooks); break;
            case 3: listBooks(books, numBooks); break;
            case 4: addPatron(patrons, &numPatrons); break;
            case 5: removePatron(patrons, &numPatrons); break;
            case 6: listPatrons(patrons, numPatrons); break;
            case 7: checkOutBook(books, numBooks, patrons, numPatrons); break;
            case 8: returnBook(books, numBooks, patrons, numPatrons); break;
            case 9: return;
            default: printf("Invalid choice.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
