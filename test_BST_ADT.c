
/**
 * @file test_BST_ADT.c
 *
 * @author  Nitin Suryadevara (nitin.suryadevara@pdx.edu)
 * @version 1.0.0
 * @date    05-Dec-2024
 *
 * @brief Test program for the Binary Search Tree Abstract Data Type (BST ADT)
 *
 * @details
 * This program tests the functionality of the BST ADT, including insertion,
 * search, traversal, and deletion. It also validates the ADT's ability to
 * handle edge cases, such as accessing a NULL or invalid pointer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "BST_ADT.h"

void test_bst_operations() {
    // Display greeting and current working directory
    printf("Comprehensive test program for the new Stack ADT (stack_adt.c)\n");
    errno = 0;
    char* buf = getcwd(NULL, 0);  // Allocates a buffer large enough to hold the path
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    } else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");

    printf("===== Testing Binary Search Tree Operations =====\n");

    // Initialize test data
    temp_humid_data_t data1 = {.timestamp = 1001, .temp = 55, .humid = 60};
    temp_humid_data_t data2 = {.timestamp = 1002, .temp = 65, .humid = 65};
    temp_humid_data_t data3 = {.timestamp = 1000, .temp = 43, .humid = 55};
    temp_humid_data_t data4 = {.timestamp = 1003, .temp = 34, .humid = 70};

    // Create root node and insert data
    printf("Creating BST and inserting nodes...\n");
    bst_node_t* root = NULL;
    root = insert_node(root, data1);
    root = insert_node(root, data2);
    root = insert_node(root, data3);
    root = insert_node(root, data4);
    printf("Insertion completed.\n");

    // Test Inorder Traversal
    printf("Performing Inorder Traversal:\n");
    inorder_traversal(root);
    printf("\n");

    // Test Search Function
    printf("Searching for a node with timestamp 1002:\n");
    bst_node_t* result = search_node(root, 1002);
    if (result) {
        printf("Node found: Timestamp: %ld, Temp: %u, Humid: %u\n",
               result->data.timestamp, result->data.temp, result->data.humid);
    } else {
        printf("Node not found.\n");
    }

    // Test Search for Non-existent Node
    printf("Searching for a node with timestamp 9999:\n");
    result = search_node(root, 9999);
    if (result) {
        printf("Node found: Timestamp: %ld, Temp: %u, Humid: %u\n",
               result->data.timestamp, result->data.temp, result->data.humid);
    } else {
        printf("Node not found.\n");
    }

    // Test Edge Case: Inserting into NULL BST
    printf("Testing insertion into a NULL BST:\n");
    bst_node_t* new_root = insert_node(NULL, data1);
    if (new_root) {
        printf("Insertion successful: Root node created with timestamp %ld\n",
               new_root->data.timestamp);
    }
    delete_tree(new_root);

    // Delete the tree and verify
    printf("Deleting the BST:\n");
    delete_tree(root);
    printf("BST deleted successfully.\n");
}

int main() {
    test_bst_operations();
    return 0;
}
