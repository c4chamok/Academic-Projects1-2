#include "appStates.h"


AppState appState, tempAppState;

void initializeAppState() {
    printf("App State - isVotingActive: %d\n", appState.isVotingActive);
    FILE *fp = fopen("appState.txt", "r");
    if (fp == NULL) {
        // File doesn't exist, create it with default values
        fp = fopen("appState.txt", "w");
        fprintf(fp, "VOTE_ACTIVE=0\n");
        fclose(fp);
        appState.isVotingActive = 0;
    } else {
        char line[50];
        if (fscanf(fp, "VOTE_ACTIVE=%d", &tempAppState.isVotingActive) == 1) {    
                appState.isVotingActive = tempAppState.isVotingActive;   
        }   
    }
    
    fclose(fp);
}

void setIsVotingActive(int status) {
    appState.isVotingActive = status;
    FILE *fp = fopen("appState.txt", "r");
    FILE *tempFp = fopen("tempAppState.txt", "w");
    char line[50];
    int value;
    while (fscanf(fp, "%s=%d", line, &value) != EOF) {
        if (strncmp(line, "VOTE_ACTIVE", 11) == 0) {
            fprintf(tempFp, "VOTE_ACTIVE=%d\n", status);
        } else {
            fprintf(tempFp, "%s=%d\n", line, value);
        }
    }
    fclose(fp);
    fclose(tempFp);
    remove("appState.txt");
    rename("tempAppState.txt", "appState.txt");
}





