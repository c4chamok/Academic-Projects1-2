#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Globals.h"

int login(GlobalVars *states) {
    char pass[50];
    printf("Enter admin password: ");
    scanf("%s", pass);

    if (strcmp(pass, "123456") == 0) {
        states->isAuthenticated = 1;
        printf("\nLogin Successful!\n");
    } else {
        printf("\nWrong Password!\n");
    }
    getch();
    return 1;
}

int logout(GlobalVars *states) {
    states->isAuthenticated = 0;
    printf("\nLogged Out!\n");
    getch();
    return 1;
}

int adminPanel(GlobalVars *states) {
    printf("\nWelcome Admin! You can manage settings here.\n");
    getch();
    return 1;
}