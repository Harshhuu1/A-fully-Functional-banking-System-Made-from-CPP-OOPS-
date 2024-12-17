# Banking System Project

## Overview
This is a simple Banking System project written in C++. The system allows users to create bank accounts, deposit and withdraw money, view account details, modify account information, and delete accounts. It uses file handling for persistent storage of account data.

## Features
1. **Create New Account**: Allows users to create new bank accounts with account number, name, account type, and an initial deposit.
2. **Deposit Money**: Add funds to an existing account.
3. **Withdraw Money**: Withdraw funds from an account (if sufficient balance is available).
4. **Balance Inquiry**: View details of a specific account.
5. **Display All Accounts**: List details of all existing accounts.
6. **Modify Account**: Edit account holder information and update balance.
7. **Delete Account**: Remove an account from the system permanently.

## Requirements
- C++ compiler (e.g., GCC, Clang, or MSVC)
- Basic knowledge of C++ programming and file handling

## How to Run
1. Copy the source code into a `.cpp` file (e.g., `banking_system.cpp`).
2. Compile the file using a C++ compiler. For example, using GCC:
   ```bash
   g++ -o banking_system banking_system.cpp
   ```
3. Run the compiled program:
   ```bash
   ./banking_system
   ```

## Usage
- Follow the on-screen menu to select desired operations.
- Input the required details when prompted.

### Menu Options
1. **Create New Account**: Enter account number, holder's name, account type (`C` for Current, `S` for Savings), and initial deposit (minimum balance requirements apply).
2. **Deposit Money**: Provide the account number and deposit amount.
3. **Withdraw Money**: Provide the account number and withdrawal amount. Ensure sufficient balance.
4. **Balance Inquiry**: Enter the account number to view details.
5. **Display All Accounts**: View a list of all accounts with their details.
6. **Close an Account**: Enter the account number to delete it.
7. **Modify an Account**: Enter the account number and update the details.
8. **Exit**: Quit the program.

## File Handling
- The program uses a binary file named `accounts.dat` to store account data.
- Each account is serialized and saved, ensuring data persistence between runs.
- Temporary files are used during account modification and deletion to avoid data corruption.

## Code Highlights
- **Class-Based Design**:
  - `BankAccount` class encapsulates account details and operations.
- **Serialization and Deserialization**:
  - File handling is implemented using binary I/O for efficient storage and retrieval.
- **Input Validation**:
  - Ensures valid inputs for account operations.
- **Modular Functions**:
  - Separate functions handle specific operations, ensuring clean and maintainable code.

## Example Run
```
		Bank Management System
	1. Create New Account
	2. Deposit Money
	3. Withdraw Money
	4. Balance Inquiry
	5. Display All Accounts
	6. Close an Account
	7. Modify an Account
	8. Exit

Enter Your Choice (1-8): 1

Enter the Account Number: 1001
Enter the Account Holder's Name: John Doe
Enter Account Type (C/S): S
Enter Initial Deposit (>=500 for Savings and >=1000 for Current): 1000

Account Created Successfully!
```

## Limitations
- The program assumes proper user input; advanced input validation is limited.
- Only basic account operations are supported.

## Future Improvements
- Implement a graphical user interface (GUI).
- Use a relational database for better data management.
- Add advanced features like transaction history, interest calculation, and multi-user support.

## License
This project is free to use and modify for educational purposes.

