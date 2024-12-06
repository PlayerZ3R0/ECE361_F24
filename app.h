/**
 * @file app.h
 *
 * @author  Nitin Suryadevara (nitin.suryadevara@pdx.edu)
 * @version 1.0.0
 * @date    05-Dec-2024
 *
 * @brief Header file for the application that interacts with the BST.
 *
 * @details
 * This file provides the `run_application` function declaration for the application
 * and includes the implementation of `populateBST` to populate the Binary Search Tree (BST).
 */

#ifndef APP_H
#define APP_H

#include "BST_ADT.h"
#include "iom361_r2.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * @brief Populate the BST with random sensor data.
 * 
 * @param root Pointer to the root of the BST.
 * @param num_records The number of records to generate.
 * @return Pointer to the populated BST root.
 *
 * @details
 * Generates random temperature and humidity data using the 
 * _iom361_setSensor1_rndm() function and populates the BST. The data
 * records are shuffled before insertion to ensure balanced BST performance.
 */
static bst_node_t* populateBST(bst_node_t* root, int num_records, time_t base_timestamp) {
    if (num_records <= 0) {
        printf("ERROR: Number of records must be greater than 0\n");
        return root;
    }

    // Initialize the I/O module
    int rtn_code;
    uint32_t* io_base = iom361_initialize(0, 0, &rtn_code);
    if (io_base == NULL || rtn_code != 0) {
        printf("ERROR: Failed to initialize I/O module\n");
        return root;
    }

    // Create an array of data records
    temp_humid_data_t* records = malloc(num_records * sizeof(temp_humid_data_t));
    if (!records) {
        perror("Failed to allocate memory for records");
        return root;
    }

    // Generate random sensor data with timestamps based on base_timestamp
    srand(time(NULL)); // Seed for randomness
    for (int i = 0; i < num_records; i++) {
        float temp = (float)(rand() % 101);  // Random temperature (0-100 °C)
        float humid = (float)(rand() % 100); // Random humidity (0-99% RH)
        _iom361_setSensor1(temp, humid);

        // Read sensor data from the I/O registers
        int temp_code, humid_code;
        uint32_t temp_reg = iom361_readReg(io_base, TEMP_REG, &temp_code);
        uint32_t humid_reg = iom361_readReg(io_base, HUMID_REG, &humid_code);

        if (temp_code != 0 || humid_code != 0) {
            printf("ERROR: Failed to read sensor data\n");
            free(records);
            return root;
        }

        // Store data in the records array
        records[i].timestamp = base_timestamp + (i * 86400);  // Add one day per record
        records[i].temp = (temp_reg * 200 / (1 << 20)) - 50;  // Convert temperature
        records[i].humid = (humid_reg * 100 / (1 << 20));     // Convert humidity
    }

    // Shuffle the records array
    for (int i = num_records - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        temp_humid_data_t temp = records[i];
        records[i] = records[j];
        records[j] = temp;
    }

    // Insert shuffled records into the BST
    for (int i = 0; i < num_records; i++) {
        root = insert_node(root, records[i]);
    }

    printf("BST populated with %d records.\n", num_records);

    // Free allocated memory
    free(records);
    return root;
}


/**
 * @brief Runs the application.
 *
 * @details
 * This function manages the BST operations, such as populating the tree,
 * searching by timestamps, and displaying the temperature/humidity table.
 */
void run_application();

#endif
