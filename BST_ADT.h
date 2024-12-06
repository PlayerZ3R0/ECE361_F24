
/**
 * @file BST_ADT.h
 *
 * @author  Nitin Suryadevara (nitin.suryadevara@pdx.edu)
 * @version 1.0.0
 * @date    05-Dec-2024
 *
 * @brief Header file for the Binary Search Tree Abstract Data Type (BST ADT)
 *
 * @details
 * This header file provides the API for managing a binary search tree (BST)
 * that stores temperature, humidity, and timestamp data. The BST supports
 * insertion, search, traversal, and deletion operations. The tree is organized
 * using timestamps as keys, ensuring ordered data retrieval.
 *
 * Revision History
 * ----------------
 * 1.0.0   (05-Dec-2024)   Initial version with API definitions
 *
 * @note This implementation was created based on user requirements.
 */

#ifndef _BST_ADT_H
#define _BST_ADT_H

#include <time.h>
#include <stdint.h>

/**
 * @struct temp_humid_data
 * @brief Structure to hold temperature, humidity, and timestamp data.
 * 
 * @details
 * - timestamp: The time associated with the measurement.
 * - temp: Temperature value (unsigned integer).
 * - humid: Humidity value (unsigned integer).
 */
typedef struct temp_humid_data {
    time_t timestamp;
    uint32_t temp;
    uint32_t humid;
} temp_humid_data_t;

/**
 * @struct bst_node
 * @brief Structure for a node in the binary search tree.
 * 
 * @details
 * Each node contains a data field, and pointers to its left and right children.
 */
typedef struct bst_node {
    temp_humid_data_t data;
    struct bst_node* left;
    struct bst_node* right;
} bst_node_t;

/**
 * @brief Create a new binary search tree node.
 * @param data The data to store in the node.
 * @return Pointer to the newly created node.
 * 
 * @details
 * Allocates memory for a new node and initializes its fields.
 */
bst_node_t* create_node(temp_humid_data_t data);

/**
 * @brief Insert a node into the binary search tree.
 * @param root Pointer to the root of the tree.
 * @param data The data to insert into the tree.
 * @return Pointer to the root of the tree after insertion.
 * 
 * @details
 * Inserts a new node into the BST while maintaining the tree's order property.
 */
bst_node_t* insert_node(bst_node_t* root, temp_humid_data_t data);

/**
 * @brief Search for a node in the tree by timestamp.
 * @param root Pointer to the root of the tree.
 * @param timestamp The timestamp to search for.
 * @return Pointer to the node containing the timestamp, or NULL if not found.
 * 
 * @details
 * Searches the BST recursively to find a node with the specified timestamp.
 */
bst_node_t* search_node(bst_node_t* root, time_t timestamp);

/**
 * @brief Perform an Inorder traversal of the tree and print the nodes.
 * @param root Pointer to the root of the tree.
 * 
 * @details
 * Traverses the tree in sorted order (left, root, right) and prints each node's data.
 */
void inorder_traversal(bst_node_t* root);

/**
 * @brief Delete the entire binary search tree.
 * @param root Pointer to the root of the tree.
 * 
 * @details
 * Frees all nodes in the BST, starting from the leaves up to the root.
 */
void delete_tree(bst_node_t* root);

#endif
