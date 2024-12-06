/**
 * @file app.c
 *
 * @author  Nitin Suryadevara (nitin.suryadevara@pdx.edu)
 * @version 1.0.0
 * @date    05-Dec-2024
 *
 * @brief Application for managing temperature and humidity data using a Binary Search Tree (BST).
 *
 * @details
 * This application populates a BST with temperature and humidity data, allows
 * users to search for specific timestamps, and displays the data in an ordered table.
 * The application also demonstrates the functionality of the BST ADT.
 *
 * Revision History
 * ----------------
 * 1.0.0   (05-Dec-2024)   Initial version.
 *
 * @note This implementation was created based on user requirements.
 */

#include "app.h"

#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/**
 * @brief Formats and prints a timestamp in the format "DD-MMM-YYYY".
 */
void format_and_print_date(time_t timestamp) {
    struct tm* tm_info = localtime(&timestamp);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%b-%Y", tm_info);
    printf("%s", buffer);
}

/**
 * @brief Runs the main application loop.
 */
void run_application() {
    // srand(time(NULL));  // Seed the random number generator

    bst_node_t* root = NULL;
    int num_records;

    // Display application banner and current working directory
    printf("BST Population with random dataset\n");
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

    // Get user input for the number of records to generate
    printf("Enter the starting month (1 to 12), day (1 to 31), and number of days (1 to 100): ");
    int start_month, start_day, num_days;
    scanf("%d,%d,%d", &start_month, &start_day, &num_days);
    getchar();  // Consume the newline character

    // Validate inputs
    if (start_month < 1 || start_month > 12 || start_day < 1 || start_day > 31 || num_days < 1 || num_days > 100) {
        printf("ERROR: Invalid input. Please ensure month is 1-12, day is 1-31, and days is 1-100.\n");
        return;
    }

    printf("User requested %d data items starting at %2d/%2d/%4d\n", num_days, start_month, start_day, 2023);

    // Generate timestamps and populate the BST
    struct tm start_date = {0};
    start_date.tm_year = 2023 - 1900;     // Year since 1900
    start_date.tm_mon = start_month - 1;  // Month (0-11)
    start_date.tm_mday = start_day;       // Day of the month

    time_t base_timestamp = mktime(&start_date);
    if (base_timestamp == -1) {
        printf("ERROR: Failed to generate base timestamp.\n");
        return;
    }

    root = populateBST(root, num_days, base_timestamp);

    /*
        for (int i = 0; i < num_days; i++) {
            temp_humid_data_t data;
            data.timestamp = base_timestamp + (i * 86400);  // Add one day per record
            data.temp = 60 + rand() % 40;                   // Random temperature (60F to 99F)
            data.humid = 30 + rand() % 50;                  // Random humidity (30% to 79%)
            root = insert_node(root, data);
            printf("INFO(main()): added timestamp %ld from data[%d] to BST\n", data.timestamp, i);

            // printf("DEBUG: Inserting timestamp %ld, Temp: %d, Humid: %d into BST\n", data.timestamp, data.temp, data.humid);
        }
    */

    // Search loop
    printf("\nEnter a search date (mm/dd/yyyy): ");
    char input[256];
    while (fgets(input, sizeof(input), stdin)) {
        if (strcmp(input, "\n") == 0) {
            break;  // Exit the search loop on an empty line
        }

        int month, day, year;
        if (sscanf(input, "%d/%d/%d", &month, &day, &year) != 3) {
            printf("ERROR: Invalid date format. Please use mm/dd/yyyy.\n");
            continue;
        }

        struct tm search_date = {0};
        search_date.tm_year = year - 1900;
        search_date.tm_mon = month - 1;
        search_date.tm_mday = day;

        time_t search_timestamp = mktime(&search_date);
        if (search_timestamp == -1) {
            printf("ERROR: Invalid date.\n");
            continue;
        }

        printf("INFO(search()): Starting search for timestamp %ld\n", search_timestamp);

        // Search the BST
        bst_node_t* result = search_node(root, search_timestamp);
        if (result) {
            printf("FOUND-> ");
            format_and_print_date(result->data.timestamp);
            printf("\t%4.1fF(%08X) %4.1f%%(%08X)\n",
                   (float)result->data.temp, result->data.temp,
                   (float)result->data.humid, result->data.humid);

            // printf("DEBUG: Preparing to display -> Timestamp: %ld, Temp: %d, Humid: %d\n",
            //      result->data.timestamp, result->data.temp, result->data.humid);

        } else {
            printf("Did not find data for ");
            format_and_print_date(search_timestamp);
            printf("\n");
        }

        printf("Enter a search date (mm/dd/yyyy): ");
    }

    // Inorder traversal and display of BST data
    printf("\nTemperature/Humidity table:\n");
    printf("---------------------------\n");
    printf("%-20s %-10s %-10s\n", "Date", "Temp (F)", "Humid (%)");
    inorder_traversal(root);

    // Cleanup
    delete_tree(root);
    printf("\nBST deleted and application terminated.\n");
}

int main() {
    run_application();
    return 0;
}
