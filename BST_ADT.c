
/**
 * @file BST_ADT.c
 *
 * @author  Nitin Suryadevara (nitin.suryadevara@pdx.edu)
 * @version 1.0.0
 * @date    05-Dec-2024
 *
 * @brief Implementation of the Binary Search Tree Abstract Data Type (BST ADT)
 *
 * @details
 * This file contains the implementation of a binary search tree (BST)
 * that stores temperature, humidity, and timestamp data. The BST supports
 * insertion, search, traversal, and deletion operations. The tree is organized
 * using timestamps as keys, ensuring ordered data retrieval.
 *
 * Revision History
 * ----------------
 * 1.0.0   (05-Dec-2024)   Initial version with function implementations
 *
 * @note This implementation was created based on user requirements.
 */

#include "BST_ADT.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Create a new binary search tree node.
 * @param data The data to store in the node.
 * @return Pointer to the newly created node.
 * 
 * @details
 * Allocates memory for a new node, initializes its fields with the given data,
 * and sets its left and right pointers to NULL.
 */
bst_node_t* create_node(temp_humid_data_t data) {
    bst_node_t* new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    if (!new_node) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * @brief Insert a node into the binary search tree.
 * @param root Pointer to the root of the tree.
 * @param data The data to insert into the tree.
 * @return Pointer to the root of the tree after insertion.
 * 
 * @details
 * Recursively inserts a new node into the BST. If the tree is empty, a new root node is created.
 * Nodes are placed based on their timestamp values.
 */
bst_node_t* insert_node(bst_node_t* root, temp_humid_data_t data) {
    if (root == NULL) {
        return create_node(data);
    }
    if (data.timestamp < root->data.timestamp) {
        root->left = insert_node(root->left, data);
    } else if (data.timestamp > root->data.timestamp) {
        root->right = insert_node(root->right, data);
    }
    return root;
}

/**
 * @brief Search for a node in the tree by timestamp.
 * @param root Pointer to the root of the tree.
 * @param timestamp The timestamp to search for.
 * @return Pointer to the node containing the timestamp, or NULL if not found.
 * 
 * @details
 * Recursively searches the BST for a node with the given timestamp. If the node
 * is found, a pointer to it is returned; otherwise, NULL is returned.
 */
bst_node_t* search_node(bst_node_t* root, time_t timestamp) {
    if (root == NULL || root->data.timestamp == timestamp) {
        return root;
    }
    if (timestamp < root->data.timestamp) {
        return search_node(root->left, timestamp);
    }
    return search_node(root->right, timestamp);
}

/**
 * @brief Perform an Inorder traversal of the tree and print the nodes.
 * @param root Pointer to the root of the tree.
 * 
 * @details
 * Recursively traverses the BST in sorted order (left subtree, root, right subtree).
 * Each node's timestamp, temperature, and humidity are printed to the console.
 */
void inorder_traversal(bst_node_t* root) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left);
    printf("Timestamp: %ld, Temp: %u, Humid: %u\n", 
           root->data.timestamp, root->data.temp, root->data.humid);
    inorder_traversal(root->right);
}

/**
 * @brief Delete the entire binary search tree.
 * @param root Pointer to the root of the tree.
 * 
 * @details
 * Recursively deletes all nodes in the BST, starting from the leaves and moving upwards.
 * Frees the memory allocated for each node.
 */
void delete_tree(bst_node_t* root) {
    if (root == NULL) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}
