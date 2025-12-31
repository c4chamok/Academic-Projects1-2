#ifndef VOTERS_DB_H
#define VOTERS_DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { 
    int id; 
    char name[100]; 
    char phoneNumber[50]; 
    char fathersName[100]; 
    char mothersName[100]; 
    char address[100]; 
    char birthDate[100]; 
} Voter;

extern Voter votersList[100];
extern int votersListSize;
extern const char *voterFile;

void getVotersList();
Voter* getVoterById(int id);

void insertVoter(Voter *voter); 
void updateVoter(Voter *voter);

void votersInit();
#endif