//Define Structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//int i,j;
//for(i=1; i <= 5; i++) {
    //for(j=1; j <= i;j++) {
      //printf("*");  
    //}
    //printf("\n");
//}


#define MAX_BOOKS 100

struct Book {
    int id;
    char title[100];
    char author[100];
    int isBorrowed; // 0 for available, 1 for borrowed
};

struct Library {
    struct Book books[MAX_BOOKS];
    int bookCount;
};



//Function Prototypes

void addBook(struct Library *library);
void viewBooks(const struct Library *library);
void borrowBook(struct Library *library);
void returnBook(struct Library *library);
void saveToFile(const struct Library *library);
void loadFromFile(struct Library *library);

//Implement Functions

void addBook(struct Library *library) {
    if (library->bookCount >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    struct Book newBook;
    newBook.id = library->bookCount + 1; // Simple ID assignment
    printf("Enter book title: ");
    getchar(); // Clear newline from previous input
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove newline character
    printf("Enter author name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove newline character
    newBook.isBorrowed = 0; // Set as available

    library->books[library->bookCount] = newBook;
    library->bookCount++;
    printf("Book added successfully!\n");
}

//Viewing Books

void viewBooks(const struct Library *library) {
    if (library->bookCount == 0) {
        printf("No books available in the library.\n");
        return;
    }
    printf("Books in the library:\n");
    for (int i = 0; i < library->bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Status: %s\n",
               library->books[i].id,
               library->books[i].title,
               library->books[i].author,
               library->books[i].isBorrowed ? "Borrowed" : "Available");
    }
}

//Borrowing a Book

void borrowBook(struct Library *library) {
    int id;
    printf("Enter book ID to borrow: ");
    scanf("%d", &id);
    
    if (id < 1 || id > library->bookCount) {
        printf("Invalid book ID!\n");
        return;
    }

    if (library->books[id - 1].isBorrowed) {
        printf("The book is already borrowed!\n");
        return;
    }

    library->books[id - 1].isBorrowed = 1; // Mark as borrowed
    printf("You have borrowed the book: %s\n", library->books[id - 1].title);
}

//Returning a Book

void returnBook(struct Library *library) {
    int id;
    printf("Enter book ID to return: ");
    scanf("%d", &id);

    if (id < 1 || id > library->bookCount) {
        printf("Invalid book ID!\n");
        return;
    }

    if (!library->books[id - 1].isBorrowed) {
        printf("The book was not borrowed!\n");
        return;
    }

    library->books[id - 1].isBorrowed = 0; // Mark as available
    printf("You have returned the book: %s\n", library->books[id - 1].title);
}

//File Handling Functions

void saveToFile(const struct Library *library) {
    FILE *file = fopen("library.dat", "wb");
    
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    fwrite(library, sizeof(struct Library), 1, file);
    
    fclose(file);
}

void loadFromFile(struct Library *library) {
    FILE *file = fopen("library.dat", "rb");
    
    if (!file) {
        printf("No saved data found. Starting fresh.\n");
        return;
    }
    
    fread(library, sizeof(struct Library), 1, file);
    
    fclose(file);
}

//Main Function

int main() {
    struct Library library = { .bookCount = 0 };
    
    loadFromFile(&library); // Load existing data
    
    int choice;
    
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Save and Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(&library);
                break;
            case 2:
                viewBooks(&library);
                break;
            case 3:
                borrowBook(&library);
                break;
            case 4:
                returnBook(&library);
                break;
            case 5:
                saveToFile(&library);
                printf("Data saved successfully. Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
        
    } while (choice != 5);

   return 0;
}
