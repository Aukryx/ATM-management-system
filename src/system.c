#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, struct Record *r)
{
    if (ptr == NULL || r == NULL) {
        printf("File pointer or record pointer is NULL in getAccountFromFile\n");
        return 0;
    }

    int result = fscanf(ptr, "%d %d %99s %d %d/%d/%d %99s %d %lf %9s",
                  &r->id,
                  &r->userId,
                  r->name,
                  &r->accountNbr,
                  &r->date.month,
                  &r->date.day,
                  &r->date.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType);

    if (result == EOF) {
        return 0;
    } else if (result != 11) {
        printf("Incorrect number of values read in getAccountFromFile: %d\n", result);
        return 0;
    }
    return 1;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    if (ptr == NULL) {
        printf("Error: File pointer is NULL in saveAccountToFile\n");
        return;
    }

    int result = fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
            r.id,
            u.id,
            r.name,
            r.accountNbr,
            r.date.month,
            r.date.day,
            r.date.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);

    if (result < 0) {
        printf("Error: Unable to write to file in saveAccountToFile\n");
    }
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    if (option == 1) {
        mainMenu(u);
    } else if (option == 0) {
        exit(0);
    } else {
        printf("Invalid option. Returning to main menu.\n");
        mainMenu(u);
    }
}

void createNewAcc(struct User u) {
    struct Record r;
    struct Record cr;
    int id = 0;
    FILE *pf = fopen(RECORDS, "a+");
    
    if (pf == NULL) {
        perror("Error opening file");
        return;
    }

    // Find the highest existing ID
    rewind(pf);
    while (getAccountFromFile(pf, &cr)) {
        if (cr.id > id) {
            id = cr.id;
        }
    }
    r.id = id + 1;  // Set the new ID
    r.userId = u.id;  // Use the user ID from the logged-in user
    strcpy(r.name, u.name);  // Use the name from the logged-in user

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    // Date validation
    while (1) {
        printf("\nEnter today's date(mm/dd/yyyy): ");
        if (scanf("%d/%d/%d", &r.date.month, &r.date.day, &r.date.year) != 3 ||
            r.date.month < 1 || r.date.month > 12 ||
            r.date.day < 1 || r.date.day > 31 ||
            r.date.year < 2000 || r.date.year > 9999) {
            printf("Please provide a valid date in the format mm/dd/yyyy\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    }

    // Account number validation
    while (1) {
        printf("\nEnter the account number: ");
        if (scanf("%d", &r.accountNbr) != 1 || r.accountNbr < 0) {
            printf("Please provide a valid positive account number\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    }

    // Check for existing account
    rewind(pf);
    while (getAccountFromFile(pf, &cr)) {
        if (strcmp(cr.name, r.name) == 0 && cr.accountNbr == r.accountNbr) {
            printf("✖ This Account already exists for this user\n\n");
            printf("Enter 1 to return to the main menu: ");
            int choice;
            scanf("%d", &choice);
            if (choice == 1) {
                fclose(pf);
                mainMenu(u);
                return;
            } else {
                goto noAccount;
            }
        }
    }

    // Country validation
    while (1) {
        printf("\nEnter the country: ");
        scanf("%s", r.country);
        if (strspn(r.country, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") == strlen(r.country)) {
            break;
        } else {
            printf("Country must contain only letters or dashes\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }

    // Phone number validation
    while (1) {
        printf("\nEnter the phone number (10 digits starting with 0): ");
        if (scanf("%d", &r.phone) != 1 || r.phone < 0 || r.phone > 999999999 || r.phone < 99999999 ) {
            printf("Please provide a valid 10-digit phone number starting with 0\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    }

    // Amount validation
    while (1) {
        printf("\nEnter amount to deposit: $");
        if (scanf("%lf", &r.amount) != 1 || r.amount < 0) {
            printf("Please provide a valid positive amount\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
    }
}

    // Account type validation
    while (1) {
        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");
        scanf("%s", r.accountType);
        if (strcmp(r.accountType, "saving") == 0 || strcmp(r.accountType, "current") == 0 ||
            strcmp(r.accountType, "fixed01") == 0 || strcmp(r.accountType, "fixed02") == 0 ||
            strcmp(r.accountType, "fixed03") == 0) {
            break;
        } else {
            printf("Please choose a valid account type\n");
        }
    }

    saveAccountToFile(pf, u, r);
    
    fclose(pf);
    success(u);
}


void updateAccount(struct User u) {
    int accountNumber;
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");
    FILE *tempFile = fopen("temp_records.txt", "w");
    
    if (pf == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    system("clear");
    printf("\t\t====== Update Account =====\n\n");
    printf("Enter the account number you wish to update: ");
    scanf("%d", &accountNumber);

    int found = 0;
    while (getAccountFromFile(pf, &r)) {
        if (r.userId == u.id && r.accountNbr == accountNumber) {
            found = 1;
            printf("\nCurrent account details:\n");
            printf("Account number: %d\n", r.accountNbr);
            printf("Country: %s\n", r.country);
            printf("Phone: %d\n", r.phone);

            int choice;
            do {
                printf("\nWhich field do you want to update?\n");
                printf("1. Country\n");
                printf("2. Phone number\n");
                printf("3. Done updating\n");
                printf("Enter your choice (1-3): ");
                scanf("%d", &choice);

                switch(choice) {
                    case 1:
                        // Update country
                        while (1) {
                            printf("\nEnter new country: ");
                            char newCountry[100];
                            getchar(); // Clear input buffer
                            fgets(newCountry, sizeof(newCountry), stdin);
                            newCountry[strcspn(newCountry, "\n")] = 0; // Remove newline
                            if (strspn(newCountry, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-") == strlen(newCountry)) {
                                strcpy(r.country, newCountry);
                                break;
                            } else {
                                printf("Country must contain only letters. Please try again.\n");
                                while (getchar() != '\n'); // Clear input buffer
                            }
                        }
                        break;
                    case 2:
                        // Update phone number
                        while (1) {
                            printf("\nEnter new phone number (10 digits starting with 0): ");
                            int newPhone;
                            scanf("%d", &newPhone);
                            if (newPhone >= 100000000 && newPhone <= 999999999) {
                                r.phone = newPhone;
                                break;
                            } else {
                                printf("Please provide a valid 10-digit phone number starting with 0\n");
                                while (getchar() != '\n'); // Clear input buffer
                            }
                        }
                        break;
                    case 3:
                        printf("Finished updating account.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 3);
        }
        // Save the record (updated or not) using the record's own user information
        struct User recordUser = {r.userId, "", ""}; // Create a minimal User struct with just the ID
        saveAccountToFile(tempFile, recordUser, r);
    }

    fclose(pf);
    fclose(tempFile);

    if (found) {
        remove(RECORDS);
        rename("temp_records.txt", RECORDS);
        printf("\nAccount updated successfully!\n");
    } else {
        remove("temp_records.txt");
        printf("Account not found or you don't have permission to update it.\n");
    }

    success(u);
}

void checkAccount(struct User u)
{
    int accountNumber;
    struct Record r;
    int found = 0;

    FILE *pf = fopen(RECORDS, "r");
    if (pf == NULL) {
        printf("Error opening file!\n");
        return;
    }

    system("clear");
    printf("\t\t====== Check Account Details =====\n\n");
    printf("Enter the account number you wish to check: ");
    scanf("%d", &accountNumber);

    while (getAccountFromFile(pf, &r))
    {
        if (r.userId == u.id && r.accountNbr == accountNumber)
        {
            found = 1;
            printf("\nAccount Details:\n");
            printf("Account number: %d\n", r.accountNbr);
            printf("Creation Date: %d/%d/%d\n", r.date.month, r.date.day, r.date.year);
            printf("Country: %s\n", r.country);
            printf("Phone number: %d\n", r.phone);
            printf("Amount deposited: $%.2f\n", r.amount);
            printf("Type of Account: %s\n", r.accountType);

            // Calculate and display interest
            if (strcmp(r.accountType, "current") == 0) {
                printf("You will not get interests because the account is of type current\n");
            } else {
                double interestRate;
                if (strcmp(r.accountType, "saving") == 0) {
                    interestRate = 0.07;
                    double monthlyInterest = r.amount * interestRate / 12;
                    printf("You will get $%.2f as interest on day %d of every month\n", 
                    monthlyInterest, r.date.day);
                } else if (strcmp(r.accountType, "fixed01") == 0) {
                    double interestFixed01;
                    int yearInterestFixed01;
                    interestRate = 0.04;
                    yearInterestFixed01 = r.date.year + 1;
                    interestFixed01 = r.amount * interestRate;
                    printf("You will get $%.2f as interest on %d/%d/%d", interestFixed01, r.date.day, r.date.month, yearInterestFixed01);
                } else if (strcmp(r.accountType, "fixed02") == 0) {
                    double interestFixed02;
                    int yearInterestFixed02;
                    interestRate = 0.05;
                    yearInterestFixed02 = r.date.year + 2;
                    interestFixed02 = r.amount * interestRate * 2;
                    printf("You will get $%.2f as interest on %d/%d/%d", interestFixed02, r.date.day, r.date.month, yearInterestFixed02);
                } else if (strcmp(r.accountType, "fixed03") == 0) {
                    double interestFixed03;
                    int yearInterestFixed03;
                    interestRate = 0.08;
                    yearInterestFixed03 = r.date.year + 3;
                    interestFixed03 = r.amount * interestRate * 3;
                    printf("You will get $%.2f as interest on %d/%d/%d", interestFixed03, r.date.day, r.date.month, yearInterestFixed03);
                } else {
                    printf("Unknown account type. Unable to calculate interest.\n");
                    break;
                }
            }
            break;
        }
    }

    fclose(pf);

    if (!found) {
        printf("Account not found or you don't have permission to access it.\n");
    }

    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, &r))
    {
        if (strcmp(r.name, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nCreation Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.date.day,
                   r.date.month,
                   r.date.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void makeTransactions(struct User u) {
    struct Record r;
    int accountChosen;
    double amountToWithdraw, amountToDeposit;
    int accountFound = 0;

    FILE *pf = fopen(RECORDS, "r");
    FILE *tempFile = fopen("temp_records.txt", "w");
    if (pf == NULL || tempFile == NULL) {
        printf("Error opening file(s)!\n");
        if (pf) fclose(pf);
        if (tempFile) fclose(tempFile);
        return;
    }

    system("clear");
    printf("\t\t====== Make Transactions =====\n\n");
    printf("Enter the account number for the transaction: ");
    if (scanf("%d", &accountChosen) != 1) {
        printf("Invalid input. Please enter a valid account number.\n");
        fclose(pf);
        fclose(tempFile);
        remove("temp_records.txt");
        return;
    }

    while (getAccountFromFile(pf, &r)) {
        if (r.userId == u.id && r.accountNbr == accountChosen) {
            accountFound = 1;
            if (strcmp(r.accountType, "fixed01") == 0 || 
                strcmp(r.accountType, "fixed02") == 0 || 
                strcmp(r.accountType, "fixed03") == 0) {
                printf("Transactions are not allowed for fixed accounts.\n");
                success(u);
            }

            int choice;
            printf("Current balance: $%.2f\n", r.amount);
            printf("Do you want to:\n1. Withdraw\n2. Deposit\n3. Exit\n");
            printf("Enter your choice (1-3): ");
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Exiting transaction menu.\n");
                break;
            }

            switch (choice) {
                case 1:
                    printf("Enter the amount to withdraw: $");
                    if (scanf("%lf", &amountToWithdraw) != 1 || amountToWithdraw <= 0) {
                        printf("Invalid amount. Withdrawal cancelled.\n");
                        break;
                    }
                    if (amountToWithdraw > r.amount) {
                        printf("Insufficient funds. Withdrawal cancelled.\n");
                    } else {
                        r.amount -= amountToWithdraw;
                        printf("Withdrawal successful. New balance: $%.2f\n", r.amount);
                    }
                    break;
                case 2:
                    printf("Enter the amount to deposit: $");
                    if (scanf("%lf", &amountToDeposit) != 1 || amountToDeposit <= 0) {
                        printf("Invalid amount. Deposit cancelled.\n");
                        break;
                    }
                    r.amount += amountToDeposit;
                    printf("Deposit successful. New balance: $%.2f\n", r.amount);
                    break;
                case 3:
                    printf("Exiting transaction menu.\n");
                    break;
                default:
                    printf("Invalid choice. Transaction cancelled.\n");
            }
        }
        
        struct User recordUser = {r.userId, "", ""};
        saveAccountToFile(tempFile, recordUser, r);
    }

    fclose(pf);
    fclose(tempFile);

    if (accountFound) {
        remove(RECORDS);
        rename("temp_records.txt", RECORDS);
        printf("\nTransaction process completed.\n");
    } else {
        remove("temp_records.txt");
        printf("Account number %d does not exist or you don't have permission to access it.\n", accountChosen);
    }

    success(u);
}

void deleteAccount(struct User u) {
    int accountNumber;
    struct Record r;
    int found = 0;

    FILE *pf = fopen(RECORDS, "r");
    FILE *tempFile = fopen("temp_records.txt", "w");
    if (pf == NULL || tempFile == NULL) {
        printf("Error opening file(s)!\n");
        return;
    }

    system("clear");
    printf("\t\t====== Delete Account =====\n\n");
    printf("Enter the account number you wish to delete: ");
    scanf("%d", &accountNumber);

    while (getAccountFromFile(pf, &r)) {
        if (r.userId == u.id && r.accountNbr == accountNumber) {
            found = 1;
            printf("\nAccount Details:\n");
            printf("Account number: %d\n", r.accountNbr);
            printf("Deposit Date: %d/%d/%d\n", r.date.month, r.date.day, r.date.year);
            printf("Country: %s\n", r.country);
            printf("Phone number: %d\n", r.phone);
            printf("Amount deposited: $%.2f\n", r.amount);
            printf("Type of Account: %s\n", r.accountType);

            int choice;
            printf("\nAre you sure you want to delete this account? (1 for yes, 0 for no): ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Account deleted successfully.\n");
            } else {
                printf("Deletion canceled.\n");
                // Save the record (unchanged) to the temporary file
                struct User recordUser = {r.userId, "", ""}; // Create a minimal User struct with just the ID
                saveAccountToFile(tempFile, recordUser, r);
                continue;
            }
        } else {
            // Save the record (unchanged) to the temporary file
            struct User recordUser = {r.userId, "", ""}; // Create a minimal User struct with just the ID
            saveAccountToFile(tempFile, recordUser, r);
        }
    }

    fclose(pf);
    fclose(tempFile);

    if (found) {
        remove(RECORDS);
        rename("temp_records.txt", RECORDS);
    } else {
        remove("temp_records.txt");
        printf("Account not found or you don't have permission to delete it.\n");
    }

    success(u);
}

void transferOwner(struct User u) {
    const char *USERS = "./data/users.txt";
    int accountNumber;
    char newUsername[100];
    struct Record r, checkRecord;
    int found = 0;
    struct User newUser;
    int newUserId = -1;

    FILE *pf = fopen(RECORDS, "r");
    FILE *uf = fopen(USERS, "r");
    FILE *tempFile = fopen("temp_records.txt", "w");
    if (pf == NULL || uf == NULL || tempFile == NULL) {
        printf("Error opening file(s)!\n");
        return;
    }

    system("clear");
    printf("\t\t====== Transfer Account Ownership =====\n\n");
    printf("Enter the account number you wish to transfer: ");
    scanf("%d", &accountNumber);
    printf("Enter the username of the new owner: ");
    scanf("%s", newUsername);

    // Find the user ID of the new owner
    rewind(uf);
    while (fscanf(uf, "%d %s %s", &newUser.id, newUser.name, newUser.password) != EOF) {
        if (strcmp(newUser.name, newUsername) == 0) {
            newUserId = newUser.id;
            break;
        }
    }

    if (newUserId == -1) {
        printf("User not found.\n");
        fclose(pf);
        fclose(uf);
        fclose(tempFile);
        remove("temp_records.txt");
        success(u);
        return;
    }

    // Check if the account number is already used by the new owner
    rewind(pf);
    while (getAccountFromFile(pf, &checkRecord)) {
        if (checkRecord.userId == newUserId && checkRecord.accountNbr == accountNumber) {
            printf("Error: This account number is already in use by the new owner. Operation cancelled.\n");
            fclose(pf);
            fclose(uf);
            fclose(tempFile);
            remove("temp_records.txt");
            success(u);
            return;
        }
    }

    rewind(pf);
    while (getAccountFromFile(pf, &r)) {
        if (r.userId == u.id && r.accountNbr == accountNumber) {
            found = 1;
            printf("\nAccount Details:\n");
            printf("Account number: %d\n", r.accountNbr);
            printf("Deposit Date: %d/%d/%d\n", r.date.month, r.date.day, r.date.year);
            printf("Country: %s\n", r.country);
            printf("Phone number: %d\n", r.phone);
            printf("Amount deposited: $%.2f\n", r.amount);
            printf("Type of Account: %s\n", r.accountType);

            int choice;
            printf("\nAre you sure you want to transfer this account to user '%s'? (1 for yes, 0 for no): ", newUsername);
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Account ownership transferred successfully.\n");
                r.userId = newUserId;
                strncpy(r.name, newUsername, sizeof(r.name) - 1);
                r.name[sizeof(r.name) - 1] = '\0'; // Ensure null-termination
            } else {
                printf("Transfer canceled.\n");
            }
        }
        // Save the record (updated or not) to the temporary file
        struct User recordUser = {r.userId, "", ""}; // Create a minimal User struct with just the ID
        saveAccountToFile(tempFile, recordUser, r);
    }

    fclose(pf);
    fclose(uf);
    fclose(tempFile);

    if (found) {
        remove(RECORDS);
        rename("temp_records.txt", RECORDS);
    } else {
        remove("temp_records.txt");
        printf("Account not found or you don't have permission to transfer it.\n");
    }

    success(u);
}