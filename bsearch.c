/* Purpose: Binary Search Tree
 * Author: Ian Morrison
 * Date: November 20/2022
 * References: https://www.algolist.net/Data_structures/Binary_search_tree/Removal
 */

#include "bsearch.h"


// *** BST property ***
// 1) The left subtree of a node must only contain nodes with keys
// 	    that come before the parent in alphabetical order.
// 2) The right subtree of a node must only contain nodes with keys
// 		that come after the parent in alphabetical order.
// 3) Every subtree is also a BST.
// 4) You may assume all nodes have different keys.


// The following function creates a BST by initializing a root node with the specified string.
// 1) Parameters: 
//      char *string: The string to be copied to the root node.
// 2) Returns a pointer to the root node.
// 3) The key of the node MUST be malloc-ed.
// 4) Set left and right to NULL, indicating there's no left or right child at the start.
struct bst_node *create_BST(char *string) {
    struct bst_node *root = malloc(sizeof(struct bst_node));
    root->key = malloc(strlen(string) + 1);
    strcpy(root->key, string);
    root->count= 1;
    root->left = NULL;
    root->right = NULL;
    return root;
}


// The following function inserts a node with the specified string into the proper position of the BST.
// 1) Parameters: 
//      char *string: The string to be copied to the new node
//      struct bst_node *root: A pointer to the root node of the BST
// 2) The new node should be inserted as a LEAF NODE of the tree.
//      After insertion, the BST property should be maintained.
//      You can find the definition of the BST property at the top of this file.
// 3) The key of the node MUST be malloc-ed.
void insert_node(char *string, struct bst_node *root) {

    if (string == NULL || strlen(string) == 0 || root == NULL) {
        return;
    }

    // Checks to see if our string should be insterted on the left
    if (strcmp(root->key, string) > 0) {
        // If the left of the root is NULL, we have reached a leaf node and can now insert
        if (root->left == NULL) {
            root->left = create_BST(string);

        }
        else {
            // Recursive call to insert_node() to find a leaf node
            insert_node(string, root->left);     
        }
    }

    // Finds max count for appearance of root->key string
    else if (strcmp(root->key, string) == 0) {
        root->count++;
        if (max_count < root->count) {
            max_count = root->count;
        }
        return;
    }


    // Checks to see if our string should ne inserted on the right
    else if(strcmp(root->key, string) < 0) {
        // If the right of the root is NULL, we have reached a leaf node and can now insert
        if (root->right == NULL) {
            root->right = create_BST(string);

        }
        else {
            // Recursive call to insert_node() to find a leaf node
            insert_node(string, root->right);
        }
    }
    return;
}

void in_order_print(struct bst_node *root, char descriptor[]) {

    // This is our base case 
    if (root == NULL) {
        return;
    }

    in_order_print(root->left, descriptor);


    // This block removes the plural (s) from our descriptor if the count is less than 2
    char label[6] = {'\0'};
    if (root->count < 2) {
        strncpy(label, descriptor, 4);
    }
    else {
        strcpy(label, descriptor);
    }
    printf("%s: %d %s\n", root->key, root->count, label);


    in_order_print(root->right, descriptor);
    return;
}

void in_order_numerical(struct bst_node *root, char descriptor[], int repeat_count) {

    // This is our base case 
    if (root == NULL) {
        return;
    }
    in_order_numerical(root->left, descriptor, repeat_count);

    if (root->count == repeat_count) {
        
        // This block removes the plural (s) from our descriptor if the count is less than 2
        char label[6] = {'\0'};
        if (root->count < 2) {
            strncpy(label, descriptor, 4);
        }
        else {
            strcpy(label, descriptor);
        }

        printf("%s: %d %s\n", root->key, root->count, label);
    }

    in_order_numerical(root->right, descriptor, repeat_count);
}

// The following function validates a BST.
// 1) Parameters:
//      struct bst_node *root: A pointer to the root node of the BST
// 2) Returns true if the tree rooted at `root` is a BST; false otherwise
//      Returns true if there's <= 1 node in the tree.
// 3) You can find the definition of a BST at the top of this file.
bool validate_BST(struct bst_node *root) {

    // If we successfully reach a leaf node, this line is validated
    if (root->left == NULL) {
        return true;
    }
    // If our root and it's left node follow our parameters, validate right node and it's nodes, if any
    else if ((root->left != NULL) && (strcmp(root->key, root->left->key) > 0)) {
        //printf("root: %s, left: %s\n", root->key, root->left->key);
        return validate_BST(root->left);
    }
    // If the leftt node is NOT NULL and it does NOT satisfy our parameters, return false.
    else {
        return false;
    }


    // If we successfully reach a leaf node, this line is validated
    if (root->right == NULL) {
        return true;
    }
    // If our root and it's right node follow our parameters, validate right node and it's nodes, if any
    else if ((root->right != NULL) && (strcmp(root->key, root->right->key) < 0)) {
        //printf("root: %s, right: %s\n", root->key, root->right->key);
        return validate_BST(root->right);
    }
    // If the right node is NOT NULL and it does NOT satisfy our parameters, return false.
    else {
        return false;
    }

}


// The following function finds the node with the maximum key in the BST.
// 1) Parameters:
//      struct bst_node *root: A pointer to the root node of the BST
// 2) Returns a pointer to the node with the maximum key in the BST rooted at `root`.
struct bst_node *find_max(struct bst_node *root) {
// Our maximum value will be located at the right-most node

    // If the right node isn't NULL, call find_max() with right node as the root
    if (root->right != NULL) {
        return find_max(root->right);
    }
    // If it is NULL, it is our maximum value
    else {
        return root;
    }
}


// The following function finds the node with the minimum key in the BST.
// 1) Parameters:
//      struct bst_node *root: A pointer to the root node of the BST
// 2) Returns a pointer to the node with the minimum key in the BST rooted at `root`.
struct bst_node *find_min(struct bst_node *root) {
// Our minimum value will be located at the left-most node
    
    // If the left node isn't NULL, call find_min() with left node as the root
    if (root->left != NULL) {
        return find_min(root->left);
    }
    // If it is NULL, this is our minimum value
    else {
        return root;
    }
}


// The following function deletes the node with the specified string from the BST if it exists.  
// 1) Parameters:
//      char *string: The string to be deleted
//      struct bst_node *root: A pointer to the root node of the BST
// 2) Returns a pointer to the (new) root node of the BST.
//      Returns NULL if the tree if empty after deletion.
// 3) The BST property must be maintained after deletion.
// 4) You may use the above functions directly if needed.
struct bst_node *delete_node(char *string, struct bst_node *root) {

    // If our root is NULL, return it
    if (root == NULL) {
        return root;
    }

    // This block checks if the node to delete would be to the left of root
    if (strcmp(root->key, string) > 0) {
        if (root->left == NULL) {
           return root;
        }
        // root->left will be set to the returned node
        root->left = delete_node(string, root->left);
    }

    // This block checks if the node to delete would be to the right of root
    else if (strcmp(root->key, string) < 0) {
        if (root->right == NULL) {
            return root;
        }
        // root->right will be set to the returned node
        root->right = delete_node(string, root->right);
    }

    // If root is equal to the string to delete, enter
    else if (strcmp(root->key, string) == 0) {

        // If both left and right of root are NULL, it is a leaf. We can free root and return NULL to maintain BST
        if ((root->left == NULL) && (root->right == NULL)) {
            free(root);
            return NULL;
        }
        // If right is NULL and left is not, free root and return the node to the left of the deleted node to maintain BST
        else if ((root->left != NULL) && (root->right == NULL)) {
            struct bst_node *temp = root->left;
            free(root);
            return temp;
        }
        // If right is not NULL but left is, free root and return the node to the right of the deleted node to maintain BST
        else if ((root->right != NULL) && (root->left == NULL)) {
            struct bst_node *temp = root->right;
            free(root);
            return temp;
        }

        // When the deleted node has nodes to the left and the right, we need to fill in the deleted node's location with the smallest value to the right to maintain BST
        else {
            struct bst_node *temp = find_min(root->right);
            root->key = temp->key;
            // Since the deleted node has been filled in with temp->key, there are two copies of temp->key in our BST, so we need to delete it to maintain BST
            root->right = delete_node(temp->key, root->right);
        }
        
    }
    return root;

}

void free_btree(struct bst_node *root) {

    // Base case. If our node is null, it has no memory
    if (root == NULL) {
        return;
    }

    free_btree(root->left);
    free_btree(root->right);
    free(root->key);
    free(root);

}
