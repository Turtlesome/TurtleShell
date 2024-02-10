#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct hashmap_char
{
    char* key;
    char* value;
    struct hashmap_char* next;
} hashmap_char;

void free_hashmap(hashmap_char* head);
void printHashMap(hashmap_char* head);