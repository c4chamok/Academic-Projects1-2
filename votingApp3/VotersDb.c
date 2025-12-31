#include "VotersDb.h"

Voter votersList[100];
int votersListSize = 0;
const char *voterFile = "voters.txt";

void getVotersList() {
    Voter v;
    votersListSize = 0;
    FILE *fpr = fopen(voterFile, "r");
    int i = 0;
    while(fscanf(fpr, "%d | %[^|] | %[^|] | %[^|] | %[^|] | %[^|] | %[^|\n]\n", 
        &v.id, v.name, v.fathersName, v.mothersName, v.birthDate, v.address, v.phoneNumber) == 7) { 
        votersList[i] = v;
        votersListSize++;
        i++;
    }
    fclose(fpr);
}

void insertVoter(Voter *voter) {
    Voter v = *voter;
    if(votersListSize == 0) {
        v.id = 1;
    } else {
        v.id = votersList[votersListSize - 1].id + 1;
    }

    FILE *fp = fopen(voterFile, "a");
    fprintf(fp, "%d | %s | %s | %s | %s | %s | %s\n", 
            v.id, v.name, v.fathersName, 
            v.mothersName, v.birthDate, 
            v.address, v.phoneNumber);
    votersList[votersListSize] = v;
    votersListSize++;
    fclose(fp);

    printf("\tVoter added with ID: %d\n", v.id);
}

void updateVoter(Voter *voter) {
    Voter v = *voter;

    FILE *fp = fopen(voterFile, "w");
    for (size_t i = 0; i < votersListSize; i++) {
        if(votersList[i].id == v.id) {
            votersList[i] = v;
        }
        fprintf(fp, "%d | %s | %s | %s | %s | %s | %s\n", 
            votersList[i].id, votersList[i].name, votersList[i].fathersName, 
            votersList[i].mothersName, votersList[i].birthDate, 
            votersList[i].address, votersList[i].phoneNumber);
    }
    fclose(fp);
}

void votersInit() {
    FILE *fp = fopen(voterFile, "r");
    if (fp == NULL) {
        printf("\tVoters DB not found. Creating new one...\n");
        fp = fopen(voterFile, "w");
        fclose(fp);
        return;
    }
    fclose(fp);
    getVotersList();
     
}

Voter *getVoterById(int id) {
    for (size_t i = 0; i < votersListSize; i++) {
        if (votersList[i].id == id) {
            return &votersList[i];  // return address
        }
    }
    return NULL;  // NOT FOUND
}

