#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "args.h"
#include "procedure.h"
#include "dispatch_table.h"

typedef struct TableEntry {
    char *name;
    Procedure p;
    struct TableEntry *next;
} TableEntry;

struct DispatchTable {
    TableEntry **table;
    unsigned int capacity;
    unsigned int size;
};


DispatchTable create_dispatch_table(unsigned int capacity) {
    DispatchTable result = malloc(sizeof(struct DispatchTable));
    result->table = malloc(sizeof(TableEntry*) * capacity);
    result->capacity = capacity;
    result->size = 0;
    for (int i = 0; i < result->capacity; i++) {
        result->table[i] = NULL;
    }
    return result;
}

void destroy_dispatch_table(DispatchTable dt) {
    for (int i = 0; i < dt->capacity; i++) {
        TableEntry *current = dt->table[i];
        while (current != NULL) {
            TableEntry *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
    }
    free(dt->table);
    free(dt);
}

unsigned int get_size(DispatchTable dt) {
    return dt->size;
}

/**
 * Jenkins one_at_a_time hash function, taken from
 * https://en.wikipedia.org/wiki/Jenkins_hash_function#lookup2
 */
static unsigned int jenkins_hash(const char *key) {
    int length = strlen(key);
    unsigned int i = 0;
    unsigned int hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

void add_binding(DispatchTable *dt, const char *name, Procedure p) {
    if (get_size(*dt) == (*dt)->capacity) {
        DispatchTable new = create_dispatch_table((*dt)->capacity * 2);
        TableEntry **table = (*dt)->table;
        
        for (int i = 0; i < get_size(*dt); i++) {
            TableEntry *current = table[i];
            while (current != NULL) {
                add_binding(&new, current->name, current->p);
                current = current->next;
            }
        }
        
        DispatchTable temp = *dt;
        *dt = new;
        destroy_dispatch_table(temp);
    }

    int index = jenkins_hash(name) % (*dt)->capacity;
    TableEntry *new_entry = malloc(sizeof(struct TableEntry));
    char *copy_name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(copy_name, name);
    new_entry->name = copy_name;
    new_entry->p = p;
    new_entry->next = (*dt)->table[index];
    (*dt)->table[index] = new_entry;
    (*dt)->size++;
}

Procedure get_bound_procedure(DispatchTable dt, const char *name) {
    int index = jenkins_hash(name) % dt->capacity;
    TableEntry *current = dt->table[index];
    while (strcmp(current->name, name) != 0) {
        current = current->next;
    }
    return current->p;
}

bool has_binding(DispatchTable dt, const char *name) {
    int index = jenkins_hash(name) % dt->capacity;
    TableEntry *entry = dt->table[index];

    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            return true;
        }
        entry = entry->next;
    }
    return false;
}
