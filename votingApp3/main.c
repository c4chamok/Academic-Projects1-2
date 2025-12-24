#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./VotersDb.h"
#include "./CandidatesDB.h"

#define MAX_NAME 100

typedef struct {
    int candidateId;
    char candidateName[MAX_NAME];
    int voteCount;
} Vote;

// ---------- File Paths ----------
const char *voteFile = "votes.txt";

// ---------- Function Declarations ----------
void addVoter();
void listVoters();
void addCandidate();
void listCandidates();
void castVote();
void initDB();

// ---------- Main Menu ----------
int main() {
    initDB();
    int choice;
    do {
        printf("\n==== Voting App ====\n");
        printf("1. Voters Menu\n");
        printf("2. Candidates Menu\n");
        printf("3. Cast Vote\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1: {
                int vChoice;
                printf("\n-- Voters Menu --\n");
                printf("1. List Voters\n");
                printf("2. Add Voter\n");
                printf("0. Back\n");
                printf("Enter choice: ");
                scanf("%d", &vChoice);
                getchar();
                if(vChoice == 1) listVoters();
                else if(vChoice == 2) addVoter();
                break;
            }
            case 2: {
                int cChoice;
                printf("\n-- Candidates Menu --\n");
                printf("1. List Candidates\n");
                printf("2. Add Candidate\n");
                printf("0. Back\n");
                printf("Enter choice: ");
                scanf("%d", &cChoice);
                getchar();
                if(cChoice == 1) listCandidates();
                else if(cChoice == 2) addCandidate();
                break;
            }
            case 3:
                castVote();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}

// ---------- Function Definitions ----------

// Ensure files exist
void initDB() {
    votersInit();
    candidatesInit();
}

// Add voter
void addVoter() {
    char vName[MAX_NAME];
    printf("Enter Voter Name: ");
    fgets(vName, MAX_NAME, stdin);
    vName[strcspn(vName, "\n")] = 0;
    insertVoter(vName);
}

// List voters
void listVoters() {
    getVotersList();
    printf("\nID\tName\n");
    printf("------------------\n");
    for (size_t i = 0; i < votersListSize; i++) {
        Voter v = votersList[i];
        printf("%d\t%s\n", v.id, v.name);
    }
}

// Add candidate
void addCandidate() {
    listVoters();
    Candidate c;
    
    printf("Enter Voter ID for this candidate: ");
    scanf("%d", &c.voterId);
    getchar();

    insertCandidate(c.voterId);

    printf("Candidate added with ID: %d\n", c.id);
}

// List candidates
void listCandidates() {
    getCandidatesList();
    Candidate c;
    printf("\nID\tName\tVoterID\n");
    printf("-------------------------\n");
    for (size_t i = 0; i < candidatesListSize; i++) {
        c = candidatesList[i];
        printf("%d\t%s\t%d\n", c.id, c.name, c.voterId);
    }
}

// Cast vote
void castVote() {
    listCandidates();
    
}









