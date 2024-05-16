#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 25
typedef struct pair {
    unsigned char key[MAX_KEY_LENGTH];
    void (*value)(void);
    struct pair* next;
} pair;

typedef struct map { 
    unsigned int size;
    pair** items;
    unsigned int count; 
} map;

unsigned int hash(map* table, const char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; ++i)
        hash = 31 * hash + key[i];
    return hash % table->size;
}

void initmap(map* table, unsigned int size) {
    table->size = size;
    table->count = 0;
    table->items = (pair**)malloc(size * sizeof(pair*));
    for (int i = 0; i < table->size; ++i)
        table->items[i] = NULL;
}

void addto(map* table, const char* key, void (*value)(void)) {
    if (table->count >= table->size) { printf("Error: Array overflow\n"); return; }
    unsigned int index = hash(table, key);
    pair* item = (pair*)malloc(sizeof(pair));
    if (item == NULL) {
        printf("Error: An error occured while memory allocating\n");
        return;
    }
    strcpy(item->key, key);
    item->value = value;
    item->next = table->items[index];
    table->items[index] = item;
    table->count++;
}

void* findin(map* table, const char* key) {
    unsigned int index = hash(table, key);
    pair* current = table->items[index];
    while(current != NULL) {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

void executefrom(map* table, const char* key) {
    void* function = findin(table, key);
    if (function != NULL) 
        ((void(*)(void))function)();
    else { 
        printf("Error: The function wasn't found or doesn't exist\n");
        return;
    }
}

void freemap(map* table) {
    for (int i = 0; i < table->size; ++i) {
        pair* current = table->items[i];
        while (current != NULL) {
            pair* temp = current;
            current = current->next;
            free(temp);
        }
        table->items[i] = NULL;
    }
    free(table->items);
    free(table);
}
#endif