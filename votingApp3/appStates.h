#ifndef APP_STATES_H
#define APP_STATES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int isVotingActive;
} AppState;

extern AppState appState;

void initializeAppState();
void setIsVotingActive(int status);

#endif