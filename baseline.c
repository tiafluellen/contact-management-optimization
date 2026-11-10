#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LENGTH 50
#define PHONE_LENGTH 20
#define SEARCH_REPETITIONS 100000

typedef struct {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
} Contact;

int find_contact(Contact contacts[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_contacts>\n", argv[0]);
        return 1;
    }

    int num_contacts = atoi(argv[1]);

    if (num_contacts <= 0) {
        printf("Number of contacts must be greater than 0.\n");
        return 1;
    }

    Contact *contacts = malloc(num_contacts * sizeof(Contact));

    if (contacts == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < num_contacts; i++) {
        snprintf(contacts[i].name, NAME_LENGTH, "Contact%d", i);
        snprintf(contacts[i].phone, PHONE_LENGTH, "555-%04d", i);
    }

    char target[NAME_LENGTH];
    snprintf(target, NAME_LENGTH, "Contact%d", num_contacts - 1);

    int index = -1;

    clock_t start = clock();

    for (int i = 0; i < SEARCH_REPETITIONS; i++) {
        index = find_contact(contacts, num_contacts, target);
    }

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    if (index != -1) {
        printf("Found: %s\n", contacts[index].name);
        printf("Phone: %s\n", contacts[index].phone);
    } else {
        printf("Contact not found.\n");
    }

    printf("Contacts: %d\n", num_contacts);
    printf("Search repetitions: %d\n", SEARCH_REPETITIONS);
    printf("Total search time: %.9f seconds\n", elapsed);
    printf("Average search time: %.12f seconds\n",
           elapsed / SEARCH_REPETITIONS);

    free(contacts);

    return 0;
}