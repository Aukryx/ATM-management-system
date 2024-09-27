#include <stdio.h>
#include <string.h>
#include <termios.h>
#include "header.h"

const char *USERS = "/home/student/C/atm-management-system/data/users.txt";

void initUser(struct User *u, const char *name, const char *password)
{
    strcpy(u->name, name);
    strcpy(u->password, password);
}

int loginMenu(struct User *u)
{
    char enteredUsername[50];
    char enteredPassword[50];
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", enteredUsername);

    // Check if user exists and get user data
    FILE *fp = fopen(USERS, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int userFound = 0;
    while (fscanf(fp, "%d %s %s", &u->id, u->name, u->password) != EOF) {
        if (strcmp(u->name, enteredUsername) == 0) {
            userFound = 1;
            break;
        }
    }

    fclose(fp);

    if (!userFound) {
        printf("\nUser does not exist!\n");
        return 0;
    }

    // Disable echo for password input
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
        perror("tcsetattr");
        return 0;
    }

    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", enteredPassword);

    // Restore terminal settings
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
        perror("tcsetattr");
        return 0;
    }

    // Check password
    if (strcmp(enteredPassword, u->password) != 0) {
        printf("\nIncorrect password!\n");
        return 0;
    }

    printf("\nLogin successful!\n");
    return 1;
}

const char *getPassword(struct User u)
{
    static char password[50];  // Make this static
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%s %s", userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            strcpy(password, userChecker.password);  // Copy to static buffer
            return password;
        }
    }

    fclose(fp);
    return "no user found";
}

int registerUser() {
    char username[50];
    char password[50];
    int userId = 0;
    FILE *fp;
    struct User newUser;

    system("clear");
    printf("\n\n\t\t======= User Registration =======\n");

    int usernameExists;
    do {
        usernameExists = 0;
        printf("\nEnter username: ");
        scanf("%s", username);

        // Check if username already exists and find the highest user ID
        fp = fopen(USERS, "r");
        if (fp != NULL) {
            char existingUser[50];
            int existingId;
            while (fscanf(fp, "%d %s %*s", &existingId, existingUser) != EOF) {
                if (strcmp(existingUser, username) == 0) {
                    printf("Username already exists. Please choose a different one.\n");
                    usernameExists = 1;
                    break;
                }
                if (existingId > userId) {
                    userId = existingId;
                }
            }
            fclose(fp);
        }
    } while (usernameExists);

    userId++;  // Increment for the new user

    printf("Enter password: ");
    scanf("%s", password);

    // Add new user to file
    fp = fopen(USERS, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    fprintf(fp, "%d %s %s\n", userId, username, password);
    fclose(fp);

    printf("Registration successful! Your user ID is: %d\n", userId);

    // Initialize the newUser struct with the registered user's information
    newUser.id = userId;
    strcpy(newUser.name, username);
    strcpy(newUser.password, password);

    // Call the success function with the new user
    success(newUser);

    return 1;
}