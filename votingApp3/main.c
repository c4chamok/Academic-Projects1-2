#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

typedef struct {
    int id;
    char name[MAX_NAME];
} Voter;

typedef struct {
    int id;
    char name[MAX_NAME];
    int voterId; // linked voter
} Candidate;

typedef struct {
    int candidateId;
    char candidateName[MAX_NAME];
    int voteCount;
} Vote;

// ---------- File Paths ----------
const char *voterFile = "voters.txt";
const char *candidateFile = "candidates.txt";
const char *voteFile = "votes.txt";

// ---------- Function Declarations ----------
void addVoter();
void listVoters();
void addCandidate();
void listCandidates();
void castVote();
int getNextVoterId();
int getNextCandidateId();
int voterExists(int id);
int candidateExists(int id);
void initFiles();

// ---------- Main Menu ----------
int main() {
    initFiles();
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
void initFiles() {
    FILE *fp;
    fp = fopen(voterFile, "a"); if(fp) fclose(fp);
    fp = fopen(candidateFile, "a"); if(fp) fclose(fp);
    fp = fopen(voteFile, "a"); if(fp) fclose(fp);
}

// Add voter
void addVoter() {
    Voter v;
    v.id = getNextVoterId();
    printf("Enter Voter Name: ");
    fgets(v.name, MAX_NAME, stdin);
    v.name[strcspn(v.name, "\n")] = 0; // remove newline

    FILE *fp = fopen(voterFile, "a");
    fprintf(fp, "%d|%s\n", v.id, v.name);
    fclose(fp);

    printf("Voter added with ID: %d\n", v.id);
}

// List voters
void listVoters() {
    Voter v;
    FILE *fp = fopen(voterFile, "r");
    if(!fp) { printf("No voters found!\n"); return; }
    printf("\nID\tName\n");
    printf("------------------\n");
    while(fscanf(fp, "%d|%[^\n]\n", &v.id, v.name) == 2) {
        printf("%d\t%s\n", v.id, v.name);
    }
    fclose(fp);
}

// Add candidate
void addCandidate() {
    listVoters();
    Candidate c;
    c.id = getNextCandidateId();
    printf("Enter Candidate Name: ");
    fgets(c.name, MAX_NAME, stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("Enter Voter ID for this candidate: ");
    scanf("%d", &c.voterId);
    getchar();

    if(!voterExists(c.voterId)) {
        printf("Voter ID not found!\n");
        return;
    }

    FILE *fp = fopen(candidateFile, "a");
    fprintf(fp, "%d|%s|%d\n", c.id, c.name, c.voterId);
    fclose(fp);

    // Add candidate to votes file
    FILE *vfp = fopen(voteFile, "a");
    fprintf(vfp, "%d|%s|0\n", c.id, c.name);
    fclose(vfp);

    printf("Candidate added with ID: %d\n", c.id);
}

// List candidates
void listCandidates() {
    Candidate c;
    FILE *fp = fopen(candidateFile, "r");
    if(!fp) { printf("No candidates found!\n"); return; }
    printf("\nID\tName\tVoterID\n");
    printf("-------------------------\n");
    while(fscanf(fp, "%d|%[^|]|%d\n", &c.id, c.name, &c.voterId) == 3) {
        printf("%d\t%s\t%d\n", c.id, c.name, c.voterId);
    }
    fclose(fp);
}

// Cast vote
void castVote() {
    listCandidates();
    int cid;
    printf("Enter Candidate ID to vote: ");
    scanf("%d", &cid);
    getchar();

    if(!candidateExists(cid)) {
        printf("Candidate not found!\n");
        return;
    }

    FILE *fp = fopen(voteFile, "r+");
    if(!fp) { printf("Votes file missing!\n"); return; }

    Vote v;
    long pos;
    while((pos = ftell(fp)) , fscanf(fp, "%d|%[^|]|%d\n", &v.candidateId, v.candidateName, &v.voteCount) == 3) {
        if(v.candidateId == cid) {
            v.voteCount++;
            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%d|%s|%d\n", v.candidateId, v.candidateName, v.voteCount);
            printf("Vote casted for %s!\n", v.candidateName);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("Something went wrong!\n");
}

// Get next voter ID
int getNextVoterId() {
    Voter v;
    int maxId = 0;
    FILE *fp = fopen(voterFile, "r");
    if(!fp) return 1;
    while(fscanf(fp, "%d|%[^\n]\n", &v.id, v.name) == 2) {
        if(v.id > maxId) maxId = v.id;
    }
    fclose(fp);
    return maxId + 1;
}

// Get next candidate ID
int getNextCandidateId() {
    Candidate c;
    int maxId = 0;
    FILE *fp = fopen(candidateFile, "r");
    if(!fp) return 1;
    while(fscanf(fp, "%d|%[^|]|%d\n", &c.id, c.name, &c.voterId) == 3) {
        if(c.id > maxId) maxId = c.id;
    }
    fclose(fp);
    return maxId + 1;
}

// Check if voter exists
int voterExists(int id) {
    Voter v;
    FILE *fp = fopen(voterFile, "r");
    if(!fp) return 0;
    while(fscanf(fp, "%d|%[^\n]\n", &v.id, v.name) == 2) {
        if(v.id == id) { fclose(fp); return 1; }
    }
    fclose(fp);
    return 0;
}

// Check if candidate exists
int candidateExists(int id) {
    Candidate c;
    FILE *fp = fopen(candidateFile, "r");
    if(!fp) return 0;
    while(fscanf(fp, "%d|%[^|]|%d\n", &c.id, c.name, &c.voterId) == 3) {
        if(c.id == id) { fclose(fp); return 1; }
    }
    fclose(fp);
    return 0;
}
