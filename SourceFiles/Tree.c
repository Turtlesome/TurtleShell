#include "Tree.h"

Node* newNode(char* command, void (*command_function)(hashmap_char*)) 
{
    Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) 
    {
		printf("Memory allocation error\n");
		return NULL;
	}

    node->command = command;
    node->command_function = command_function;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return(node);
}

int max_value(int a, int b) 
{
    return (a > b)? a : b;
}

// A utility function to get the height of the tree
int height(Node* node) 
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

// Function to right rotate subtree rooted with y
Node *rightRotate(Node *y) 
{
    Node *x = y->left;
    Node *z = x->right;

    // Perform rotation
    x->right = y;
    y->left = z;

    // Update heights
    y->height = max_value(height(y->left), height(y->right))+1;
    x->height = max_value(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
Node *leftRotate(Node *x) 
{
    Node *y = x->right;
    Node *z = y->left;

    // Perform rotation
    y->left = x;
    x->right = z;

    //  Update heights
    x->height = max_value(height(x->left), height(x->right))+1;
    y->height = max_value(height(y->left), height(y->right))+1;

    return y;
}

// Get Balance factor of node N
int getBalance(Node *N) 
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, char* command, void (*command_function)(hashmap_char*))
{
    // Check if command is NULL
    if (command == NULL)
    {
        printf("Error: command is NULL\n");
        return node;
    }

    if (node == NULL)
    {
        return(newNode(command, command_function));
    }

    // Check if node->command is NULL
    if (node->command == NULL)
    {
        printf("Error: node->command is NULL\n");
        return node;
    }

    if (strcmp(command, node->command) < 0)
    {
        node->left = insert(node->left, command, command_function);
    }
    else if (strcmp(command, node->command) > 0)
    {
        node->right = insert(node->right, command, command_function);
    }
    // Equal keys not allowed
    else
    {
        return node;
    }

    // Check if node is NULL after recursive calls
    if (node == NULL)
    {
        printf("Error: node is NULL after recursive calls\n");
        return NULL;
    }

    node->height = 1 + max_value(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && node->left != NULL && strcmp(command, node->left->command) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && node->right != NULL && strcmp(command, node->right->command) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && node->left != NULL && strcmp(command, node->left->command) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && node->right != NULL && strcmp(command, node->right->command) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

Node* search(Node* root, char* command)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || strcmp(root->command, command) == 0)
        return root;

    // Key is greater than root's key
    if (strcmp(root->command, command) < 0)
        return search(root->right, command);

    // Key is smaller than root's key
    return search(root->left, command);
}
