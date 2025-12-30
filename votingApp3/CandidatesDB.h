#ifndef CANDIDATESDB_H
#define CANDIDATESDB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VotersDb.h"


typedef struct {
    int id;
    char name[100];
    int voterId; // linked voter
} Candidate;

extern Candidate candidatesList[100];
extern int candidatesListSize;
extern const char *candidateFile;

void getCandidatesList();
void insertCandidate(int voterId) ;
void candidatesInit();
Candidate* getCandidateById(int id);



#endif
