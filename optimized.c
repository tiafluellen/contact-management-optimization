#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LENGTH 50
#define PHONE_LENGTH 20
#define SEARCH_REPETITIONS 100000

typedef struct Contact {
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    struct Contact *next;
} Contact;

typedef struct {
    Contact **buckets;
    int size;
} HashTable;

unsigned int hash_function(const char *name, int size) {
    unsigned int hash = 5381;

    while (*name) {
        hash = ((hash << 5) + hash) + (unsigned char)*name;
        name++;
    }

    return hash % size;
}

HashTable *create_table(int size) {
    HashTable *table = malloc(sizeof(HashTable));

    if (table == NULL) {
        return NULL;
    }

    table->size = size;
    table->buckets = calloc(size, sizeof(Contact *));

    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

void insert_contact(HashTable *table, const char *name, const char *phone) {
    unsigned int index = hash_function(name, table->size);

    Contact *new_contact = malloc(sizeof(Contact));

    if (new_contact == NULL) {
        return;
    }

    strcpy(new_contact->name, name);
    strcpy(new_contact->phone, phone);

    new_contact->next = table->buckets[index];
    table->buckets[index] = new_contact;
}

Contact *find_contact(HashTable *table, const char *name) {
    unsigned int index = hash_function(name, table->size);

    Contact *current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void free_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        Contact *current = table->buckets[i];

        while (current != NULL) {
            Contact *next = current->next;
            free(current);
            current = next;
        }
    }

    free(table->buckets);
    free(table);
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

    HashTable *table = create_table(num_contacts * 2);

    if (table == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < num_contacts; i++) {
        char name[NAME_LENGTH];
        char phone[PHONE_LENGTH];

        snprintf(name, NAME_LENGTH, "Contact%d", i);
        snprintf(phone, PHONE_LENGTH, "555-%04d", i);

        insert_contact(table, name, phone);
    }

    char target[NAME_LENGTH];
    snprintf(target, NAME_LENGTH, "Contact%d", num_contacts - 1);

    Contact *result = NULL;

    clock_t start = clock();

    for (int i = 0; i < SEARCH_REPETITIONS; i++) {
        result = find_contact(table, target);
    }

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    if (result != NULL) {
        printf("Found: %s\n", result->name);
        printf("Phone: %s\n", result->phone);
    } else {
        printf("Contact not found.\n");
    }

    printf("Contacts: %d\n", num_contacts);
    printf("Search repetitions: %d\n", SEARCH_REPETITIONS);
    printf("Total search time: %.9f seconds\n", elapsed);
    printf("Average search time: %.12f seconds\n",
           elapsed / SEARCH_REPETITIONS);

    free_table(table);

    return 0;
}