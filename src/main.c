#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        // here
        updateAccount(u);
        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        // here
        checkAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        makeTransactions(u);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        deleteAccount(u);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        transferOwner(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int option;
    do {
        system("clear");
        printf("\n\n\t\t======= ATM =======\n");
        printf("\n\t\t-->> Feel free to login / register :\n");
        printf("\n\t\t[1]- Login\n");
        printf("\n\t\t[2]- Register\n");
        printf("\n\t\t[3]- Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (loginMenu(u)) {
                    printf("\nLogin successful!\n");
                    return; // Proceed to main menu
                }
                break;
            case 2:
                if (registerUser()) {
                    printf("Please login with your new account.\n");
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (1);
}

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
