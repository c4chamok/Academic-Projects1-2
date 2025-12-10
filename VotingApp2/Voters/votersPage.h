#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "../Globals.h"
#include "../menu.h"
// #include "../menu.h"

MenuList vMenuList = {NULL, 0, 0};

typedef struct {
    int id;
    char voterName[200];
    char nidNo[30];
} Voter;

int rowCount;
int finalId;

void initDBv() {
    FILE *fpr = fopen("./voters.txt", "r");

    if (fpr == NULL) {
        // create empty file
        printf("Voters DB not found. Creating new one...\n");
        FILE *fpw = fopen("./voters.txt", "w");
        fclose(fpw);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(Voter), fpr) != NULL) {
        rowCount++;
    }

    int id = 0;
    char name[200] = "";
    char phone[200] = "";

    fclose(fpr);
}

int addVoter(GlobalVars *states){
    FILE *fpw = fopen("./voters.txt", "a");
    Voter newVoter;
    getchar(); // <-- clear leftover newline before fgets

    printf("Enter name: ");
    fgets(newVoter.voterName, sizeof(newVoter.voterName), stdin);

    // remove newline from fgets
    newVoter.voterName[strcspn(newVoter.voterName, "\n")] = 0;

    printf("Enter NID No. : ");
    scanf("%s", newVoter.nidNo);

    newVoter.id = rowCount + 1;

    fprintf(fpw, "%d | %s | %s\n",
            newVoter.id,
            newVoter.voterName,
            newVoter.nidNo);
    printf("Voter added with ID: %d, name: %s, NID: %s \n", newVoter.id, newVoter.voterName, newVoter.nidNo);
    fclose(fpw);
    rowCount++;
    return 1;
}

Voter voters[50];
void getVoters() {
    FILE *fpr = fopen("./voters.txt", "r");
    int i = 0;
    while (fscanf(fpr, "%d | %[^|] | %[^|\n]", &voters[i].id, voters[i].voterName, voters[i].nidNo) == 3) {
        // printf("%s : %s\n", voters[i].voterName, voters[i].nidNo);
        i++;
    }
    
}

int editVoter(GlobalVars *states) {
    return 1;
}

// int back(GlobalVars *states) {
//     return MENU_BACK;
// }

void vBuildMenu(MenuList *menuList, GlobalVars *states) {
    clearMenu(menuList);
    getVoters();
    addMenu(menuList, "Add voters", addVoter);
    for (size_t i = 0; i < rowCount; i++)
    {
        char title[200];
        sprintf(title, "id: %d, name: %s", voters[i].id, voters[i].voterName);
        addMenu(menuList, title, editVoter);
    }

    addMenu(menuList, "Exit", exitApp);
}

int renderVoterWindow(GlobalVars *states) {
    printf("Voters Data:\n");
    initDBv(); 
    showMenu(&vMenuList, states, vBuildMenu);
    return 1;
}

