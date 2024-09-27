#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    int accountNbr;
    char country[100];
    int phone;
    char accountType[10];
    double amount;
    struct Date date;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};
extern const char *USERS;

// authentication functions
int loginMenu(struct User *u);
int registerUser();
void success(struct User u);
void initUser(struct User *u, const char *name, const char *password);
const char *getPassword(struct User u);

// system function
void mainMenu(struct User u);
void createNewAcc(struct User u);
void updateAccount(struct User u);
void checkAccount(struct User u);
void checkAllAccounts(struct User u);
void makeTransactions(struct User u);
void deleteAccount(struct User u);
void transferOwner(struct User u);