#include "VotersDb.h"

Voter votersList[100];
int votersListSize = 0;
const char *voterFile = "voters.txt";

void getVotersList() {
    Voter v;
    votersListSize = 0;
    FILE *fpr = fopen(voterFile, "r");
    int i = 0;
    while(fscanf(fpr, "%d | %[^\n]\n", &v.id, v.name) == 2) { 
        votersList[i] = v;
        votersListSize++;
        i++;
    }
    fclose(fpr);
}

void insertVoter(char* vName) {
    Voter v;
    if(votersListSize == 0) {
        v.id = 1;
    } else {
        v.id = votersList[votersListSize - 1].id + 1;
    }
    strcpy(v.name, vName);

    FILE *fp = fopen(voterFile, "a");
    fprintf(fp, "%d | %s \n", v.id, v.name);
    votersList[votersListSize] = v;
    votersListSize++;
    fclose(fp);

    printf("Voter added with ID: %d\n", v.id);
}

void votersInit() {
    FILE *fp = fopen(voterFile, "r");
    if (fp == NULL) {
        printf("Voters DB not found. Creating new one...\n");
        fp = fopen(voterFile, "w");
        fclose(fp);
        return;
    }
    fclose(fp);
    getVotersList();
     
}

Voter getVoterById(int id) {
    for (size_t i = 0; i < votersListSize; i++) {
        if (votersList[i].id == id) {
            return votersList[i];
        }
    }
    printf("Voter with ID=%d not found.\n", id);
}

