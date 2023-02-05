#ifndef BSEARCH_H
#define BSEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#endif // BSEARCH_H

int max_count;

struct bst_node {
    char *key; //the string stored in the BST node - storage MUST be dynamically allocated
    int count;
    struct bst_node *left; // pointer to left child; NULL if there is no left child.
    struct bst_node *right; // pointer to right child; NULL if there is no right child.
};


// Insert your function declarations for ex11q2.c below:
struct bst_node *create_BST(char *string);
bool validate_BST(struct bst_node *root);
void insert_node(char *string, struct bst_node *root);
void in_order_print(struct bst_node *root, char descriptor[]);
void in_order_numerical(struct bst_node *root, char descriptor[], int repeat_count);
struct bst_node *find_max(struct bst_node *root);
struct bst_node *find_min(struct bst_node *root);
struct bst_node *delete_node(char *string, struct bst_node *root);
void free_btree(struct bst_node *root);
// end of insertion