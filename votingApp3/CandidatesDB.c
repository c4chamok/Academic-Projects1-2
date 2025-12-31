#include "CandidatesDB.h"

Candidate candidatesList[100];
int candidatesListSize = 0;
const char *candidateFile = "candidates.txt";

void getCandidatesList() {
    Candidate v;
    candidatesListSize = 0;
    FILE *fpr = fopen(candidateFile, "r");
    int i = 0;
    while(fscanf(fpr, "%d | %[^|] | %d\n", &v.id, v.name, &v.voterId) == 3) { 
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
    Voter *v = getVoterById(voterId);
    if (v == NULL) {
        printf("\tError: Voter ID %d not found. Cannot add candidate.\n", voterId);
        return;
    }
    Candidate *existedCand = getCandidateById(voterId);
    if (existedCand != NULL) {
        printf("\tError: Voter ID %d is already a candidate. Cannot add again.\n", voterId);
        return;
    }
    strcpy(c.name, (*v).name);

    FILE *fp = fopen(candidateFile, "a");
    fprintf(fp, "%d | %s | %d \n", c.id, c.name, voterId);
    candidatesList[candidatesListSize] = c;
    candidatesListSize++;
    fclose(fp);

    printf("\tcandidate added with ID: %d\n", c.id);
}

void candidatesInit() {
    FILE *fp = fopen(candidateFile, "r");
    if (fp == NULL) {
        printf("\tcandidates DB not found. Creating new one...\n");
        fp = fopen(candidateFile, "w");
        fclose(fp);
        return;
    }
    fclose(fp);
    getCandidatesList();
}

Candidate *getCandidateById(int id) {
    for (size_t i = 0; i < candidatesListSize; i++) {
        if (candidatesList[i].id == id) {
            return &candidatesList[i];  // return address
        }
    }
    return NULL;  // NOT FOUND
}
