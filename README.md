# Bank Account System

## Overview

The **Bank Account System** is a C programming project that demonstrates core concepts of data structures and file input/output (I/O) management. The system provides a simple interface for creating bank accounts, managing transactions, and persisting data across sessions using file storage.

This project is designed for learning purposes, focusing on:
- **C Programming**: Understanding and applying C language fundamentals.
- **Data Structures**: Implementing hash tables and linked lists.
- **File I/O**: Reading from and writing to files for data persistence.

## Features

- **Account Management**:
    - Create a new account with a unique identifier.
    - Deposit and withdraw funds.
    - Check the account balance.

- **File Operations**:
    - Save account data to a file.
    - Load account data from a file.
    - Automatically create the data file if it does not exist.

## Project Structure

- `include/`: Contains header files with declarations for the project.
    - `account.h`: Defines account-related functions and data structures.
    - `uuid4.h`: Provides UUID generation functionality.

- `src/`: Contains source files with implementations.
    - `account.c`: Implements account management functions.
    - `uuid4.c`: Implements UUID generation.

- `main.c`: The main application file that interacts with users and manages account operations.

## Usage

1. **Compile the Project**:
   ```bash
   make
   ```
2. **Run the Application**:
    ```bash
    ./bank_system
    ```
3. **Menu Options**:
   - `1. Create Account`: Generates a new account with a unique UUID.
   - `2. Deposit`: Adds funds to an existing account.
   - `3. Withdraw`: Removes funds from an existing account.
   - `4. Check Balance`: Displays the current balance of an account.
   - `5. Save Accounts`: Saves current account data to a file.
   - `6. Load Accounts`: Loads account data from a file.
   - `7. Exit`: Exits the application.

## Development
- Language: C
- Dependencies: Standard C libraries, custom UUID generation [library](https://github.com/gpakosz/uuid4).
   
## License
This project is provided for educational purposes and personal use only. No license is provided for commercial use.

## Contact
For questions or feedback, please contact me [here](mailto:alvarodiagoaguilar@gmail.com?subject=C%20Banking%20System).
