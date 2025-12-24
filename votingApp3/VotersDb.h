#ifndef VOTERS_DB_H
#define VOTERS_DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
} Voter;

extern Voter votersList[100];
extern int votersListSize;
extern const char *voterFile;

void getVotersList();
Voter getVoterById(int id);

void insertVoter(char* vName) ;

void votersInit();
#endif