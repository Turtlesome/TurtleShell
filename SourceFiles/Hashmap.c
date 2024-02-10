#include "Hashmap.h"


void free_hashmap(hashmap_char* head)
{
    hashmap_char* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void printHashMap(hashmap_char* head)
{
    hashmap_char* current = head;
    while (current != NULL)
    {
        printf("Key: %s, Value: %s\n", current->key ? current->key : "NULL", current->value ? current->value : "NULL");
        current = current->next;
    }
}