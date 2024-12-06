# ECE 361 Homework 5 Application

This repository contains the source code and supporting files for the **ECE 361 Homework 5 Application**, which demonstrates the use of a Binary Search Tree (BST) to store and process temperature and humidity data based on user inputs. The program includes randomized data generation, I/O emulation, and a structured approach to application development in C.

---

## Features

- **Binary Search Tree (BST) Implementation**:
  - Stores temperature, humidity, and timestamp data.
  - Supports insertion, searching, and traversal operations.
  - Ensures ordered data retrieval based on timestamps.

- **Random Data Generation**:
  - Generates random temperature (°F) and humidity (%) values.
  - Uses timestamps for unique identification of data points.

- **Interactive User Input**:
  - Allows users to specify a starting date, duration, and number of records.
  - Supports searching for specific dates and outputs matching records.

- **I/O Module Emulation**:
  - Simulates memory-mapped I/O operations for temperature and humidity sensors.

- **Makefile Support**:
  - Automates the build process, including compilation and linking.
  - Includes a `make clean` target to remove executable and object files.

---

## Files in the Repository

| File                 | Description                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| `app.c`              | Main application code for interacting with the BST and handling user inputs. |
| `app.h`              | Header file for the application, including the `populateBST` function.       |
| `BST_ADT.c`          | Implementation of the Binary Search Tree Abstract Data Type (BST ADT).      |
| `BST_ADT.h`          | Header file for the BST ADT.                                                |
| `float_rndm.c`       | Provides random floating-point number generation within a specified range.   |
| `float_rndm.h`       | Header file for the random float generator.                                 |
| `iom361_r2.c`        | Emulates I/O module functionality for temperature and humidity sensors.     |
| `iom361_r2.h`        | Header file for the I/O module emulation.                                   |
| `makefile`           | Makefile for automating the build process, including object file cleanup.   |
| `test_BST_ADT.c`     | Test code for the BST ADT implementation.                                   |
| `test_app.txt`       | Sample transcript of the program's input and output for testing purposes.   |

---

## Usage Instructions

### Prerequisites

Ensure you have a working C compiler (e.g., GCC) and `make` utility installed on your system.

### Building the Application

1. Build the application using the `make` command:
   ```bash
   make
   ```

2. Run the application:
   ```bash
   ./app.exe
   ```

### Cleaning Up

To remove all object files (`.o`) and the executable (`app.exe`):
```bash
make clean
```

---

## How It Works

1. **User Input**:
   - The program prompts the user to enter:
     - Starting month and day.
     - Number of days to generate data for.

2. **Data Generation**:
   - The program populates a BST with random temperature and humidity data using shuffled timestamps.

3. **Searching the BST**:
   - Users can search for specific dates to retrieve matching temperature and humidity data.

4. **Display**:
   - The program outputs all stored data in an ordered table (sorted by timestamp) using an in-order traversal of the BST.

---

## Example Interaction

```plaintext
BST Population with random dataset
Current working directory: G:\Other computers\SurfacePro7+\PSU\ECE 361\Homework\HW 5\work

Enter the starting month (1 to 12), day (1 to 31), and number of days (1 to 100): 8,1,30
User requested 30 data items starting at  8/ 1/2023
BST populated with 30 records.

Enter a search date (mm/dd/yyyy): 8/15/2023
INFO(search()): Starting search for timestamp 1692086400
FOUND-> 15-Aug-2023     Temp: 87°F   Humid: 66%

Temperature/Humidity Table:
---------------------------
Date                 Temp (F)   Humid (%)
Timestamp: 1690876800, Temp: 72, Humid: 37
Timestamp: 1690963200, Temp: 95, Humid: 53
...
BST deleted and application terminated.
```

---

## Contributions

Contributions are welcome! If you'd like to improve the project or add new features, feel free to fork the repository and submit a pull request.

---

## Acknowledgments

- I/O emulation inspired by work from **Roy Kravitz**.
- Random floating-point generator adapted from code by **Thang Nguyen**.
