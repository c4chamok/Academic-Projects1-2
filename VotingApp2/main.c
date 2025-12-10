#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "Globals.h"
#include "Auth.h"
#include "menu.h"
#include "./Voters/votersPage.h"

MenuList mainMenuList = {NULL, 0, 0};
GlobalVars G = {0, 0};   // initially not logged in


void wrapperFunc(GlobalVars *states) {
    printf("This is a placeholder function.\n");
    getch();
}



void buildMenu(MenuList *menuList, GlobalVars *states) {
    clearMenu(menuList);

    if (states->isAuthenticated == 0) {
        addMenu(menuList, "Admin Login", login);
    } else {
        addMenu(menuList, "Enlist Candidates", adminPanel);
        addMenu(menuList, "View Candidates", adminPanel);
        addMenu(menuList, "Collect Voters Data", adminPanel);
        addMenu(menuList, "View Voters Data", renderVoterWindow);
        addMenu(menuList, "Logout", logout);
    }

    addMenu(menuList, "Exit", exitApp);
}


int main() {
    showMenu(&mainMenuList, &G, buildMenu);
    return 0;
}


