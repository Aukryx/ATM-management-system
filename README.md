# ATM System in C

This is an implementation of an ATM (Automated Teller Machine) system written in C. It allows users to perform various banking operations such as creating new accounts, updating account information, checking account details, making transactions, deleting accounts, and transferring account ownership.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Code Explanation](#code-explanation)
- [Makefile](#makefile)
- [Contributing](#contributing)
- [License](#license)

## Features
- User authentication (login and registration)
- Create a new account
- Update account information
- Check account details
- Check the list of owned accounts
- Make transactions (withdraw or deposit)
- Remove an existing account
- Transfer account ownership
- Validation for user input

## Getting Started

### Prerequisites
- C compiler (e.g., GCC)

### Installation
1. Clone the repository:
```bash
git clone https://github.com/your-username/atm-system.git
```
2. Navigate to the project directory:
```bash
cd atm-system
```

## Usage
1. Compile the program using the provided Makefile:
```bash
make
```
2. Run the compiled program:
```bash
./atm
```
3. The program will display the initial menu, allowing you to log in or register a new account.
4. Once logged in, you can navigate the main menu and perform the desired banking operations.

## File Structure
- `src/main.c`: The main entry point of the program.
- `src/system.c`: Implements the main menu and various account management functions.
- `src/auth.c`: Handles user authentication (login and registration).
- `src/header.h`: Contains the necessary structs and function prototypes.

## Code Explanation
The code is divided into several files, each responsible for a specific aspect of the ATM system:

1. `main.c`: This file is the entry point of the program. It initializes the user and calls the `initMenu()` and `mainMenu()` functions.
2. `system.c`: This file contains the implementation of the main menu and the various account management functions, such as `createNewAcc()`, `updateAccount()`, `checkAccount()`, `checkAllAccounts()`, `makeTransactions()`, `deleteAccount()`, and `transferOwner()`.
3. `auth.c`: This file handles the user authentication, including the `loginMenu()` and `registerUser()` functions.
4. `header.h`: This file defines the necessary structs and function prototypes used throughout the program.

## Makefile
The provided Makefile simplifies the build process. Here's a breakdown of the Makefile:

```makefile
objects = src/main.o src/system.o src/auth.o

atm : $(objects)
    cc -o atm $(objects)

main.o : src/header.h
kbd.o : src/header.h
command.o : src/header.h
display.o : src/header.h
insert.o : src/header.h
search.o : src/header.h
files.o : src/header.h
utils.o : src/header.h

clean :
    rm -f $(objects)
    rm atm
```

- The `objects` variable lists the object files that need to be compiled.
- The `atm` target compiles the object files and links them to create the final executable.
- The object file dependencies ensure that the necessary header files are included.
- The `clean` target removes the compiled object files and the executable.

To build the program, simply run `make` in the project directory. To clean up the compiled files, run `make clean`.

## Contributing
If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License
This project is licensed under the [MIT License](LICENSE).