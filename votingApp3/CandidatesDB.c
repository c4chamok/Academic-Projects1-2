#include "CandidatesDB.h"

Candidate candidatesList[100];
int candidatesListSize = 0;
const char *candidateFile = "candidates.txt";

void getCandidatesList() {
    Candidate v;
    candidatesListSize = 0;
    FILE *fpr = fopen(candidateFile, "r");
    int i = 0;
    while(fscanf(fpr, "%d | %[^\n]\n", &v.id, v.name) == 2) { 
        candidatesList[i] = v;
        candidatesListSize++;
        i++;
    }
    fclose(fpr);
}

void insertCandidate(int voterId) {
    Candidate c;
    if(candidatesListSize == 0) {
        c.id = 1;
    } else {
        c.id = candidatesList[candidatesListSize - 1].id + 1;
    }
    Voter v = getVoterById(voterId);
    strcpy(c.name, v.name);

    FILE *fp = fopen(candidateFile, "a");
    fprintf(fp, "%d | %s | %s \n", c.id, c.name, voterId);
    candidatesList[candidatesListSize] = c;
    candidatesListSize++;
    fclose(fp);

    printf("candidate added with ID: %d\n", c.id);
}

void candidatesInit() {
    FILE *fp = fopen(candidateFile, "r");
    if (fp == NULL) {
        printf("candidates DB not found. Creating new one...\n");
        fp = fopen(candidateFile, "w");
        fclose(fp);
        return;
    }
    fclose(fp);
    getCandidatesList();
}
