#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashmap.h"


typedef struct Node {
    char* command;
    void (*command_function)(hashmap_char*);
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* newNode(char*, void (*command_function)(hashmap_char*));
int max_value(int, int);
int height(Node*);
Node* rightRotate(Node*);
Node* leftRotate(Node*);
int getBalance(Node*);
Node* insert(Node* , char* , void (*command_function)(hashmap_char*));
Node* search(Node*, char*);
