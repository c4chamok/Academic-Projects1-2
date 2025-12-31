#include "votesDB.h"


Vote votesList[100];
int votesListSize = 0;
int hasVottedVotersIdsList[100];
int hasVottedVotersIdsListSize = 0;
const char *voteFile = "votes.txt";
const char *votedVotersIdsFile = "votedVotersIds.txt";

void initVoteStats(){
    FILE *fp = fopen(votedVotersIdsFile, "r");
    if (fp == NULL) {
        // File doesn't exist, create it
        fp = fopen(votedVotersIdsFile, "w");
        fclose(fp);
        return;
    }
    int voterId;
    hasVottedVotersIdsListSize = 0;
    while (fscanf(fp, "%d\n", &voterId) == 1) {
        hasVottedVotersIdsList[hasVottedVotersIdsListSize] = voterId;
        hasVottedVotersIdsListSize++;
    }
    fclose(fp);
    fp = fopen(voteFile, "r");
    if (fp == NULL) {
        // File doesn't exist, create it
        fp = fopen(voteFile, "w");
        fclose(fp);
        return;
    }
    Vote v;
    votesListSize = 0;
    while (fscanf(fp, "%d | %d | %d\n", &v.id, &v.candidateId, &v.voteCount) == 3) {
        votesList[votesListSize] = v;
        votesListSize++;
    }

    fclose(fp);
}

void initiateVote() {
    // --forEach candidate in CandidatesDB,
    // --make a votes Entry with default voteCount 0,
    // --append votesList,
    // --set global voteStatus to true,
    EraseVotes();
    for (size_t i = 0; i < candidatesListSize; i++)
    {
        Vote v;
        v.id = i + 1; // simple incremental ID
        v.candidateId = candidatesList[i].id;
        v.voteCount = 0;

        // Append to votes file
        FILE *file = fopen(voteFile, "a");
        if (file == NULL) {
            perror("Failed to open votes file");
            exit(EXIT_FAILURE);
        }
        fprintf(file, "%d | %d | %d\n", v.id, v.candidateId, v.voteCount);
        votesList[i] = v;
        votesListSize++;
        fclose(file);
    }
    setIsVotingActive(1);
}

void submitVote(int voterId, int candidateId) {
    // --validate voting is active,
    // --validate candidateId,
    // --find vote entry by candidateId,
    // --increment voteCount,
    // --update votes file,
    
    if (!appState.isVotingActive) {
        printf("\tVoting is not active.\n");
        return;
    }
    Candidate *c = getCandidateById(candidateId);
    if (c == NULL) {
        printf("\tInvalid Candidate ID.\n");
        return;
    }

    for (size_t i = 0; i < votesListSize; i++)
    {
        if (votesList[i].candidateId == candidateId) {
            votesList[i].voteCount += 1;

            // Update votes file
            FILE *file = fopen(voteFile, "w");
            if (file == NULL) {
                perror("Failed to open votes file");
                exit(EXIT_FAILURE);
            }
            for (size_t j = 0; j < votesListSize; j++) {
                fprintf(file, "%d | %d | %d\n", votesList[j].id, votesList[j].candidateId, votesList[j].voteCount);
            }
            fclose(file);
            addtoVotedVotersIdsList(voterId);
            printf("\tVote submitted successfully.\n");
            getchar();
            return;
        }
    }
    printf("\tVote entry for Candidate ID %d not found.\n", candidateId);

}

int checkIfVoterHasVoted(int voterId) {
    for (size_t i = 0; i < hasVottedVotersIdsListSize; i++)
    {
        if (hasVottedVotersIdsList[i] == voterId) {
            return 1; // has voted
        }
    }
    return 0; // has not voted
}

void stopCasting() {
    // --set global voteStatus to false,
    setIsVotingActive(0);
}

void showVoteResult(){
        // --Check if the global voteStatus is False,
        // --show all the data of VotesDB,
        // --show the maximum voteCount winner,
        // --show how many people votted,
    if (appState.isVotingActive) {
        printf("\tVoting is still active. Cannot show results.\n");
        return;
    }
    printf("\n\tVote Results:\n");
    printf("\tCandidate ID\tCandidate Name\tVote Count\n");
    printf("\t--------------------------------------------------\n");
    int totalVotes = 0;
    int maxVotes = 0;
    Vote consideredWinners[100];
    int winnersCount = 0;
    for (size_t i = 0; i < votesListSize; i++) {
        Vote v = votesList[i];
        Candidate *c = getCandidateById(v.candidateId);
        printf("\t%d\t\t%s\t\t%d\n", v.candidateId, c->name, v.voteCount);
        totalVotes += v.voteCount;
        if (v.voteCount == maxVotes)
        {
            consideredWinners[winnersCount] = v;
            winnersCount++;
        } else if (v.voteCount > maxVotes)
        {
            maxVotes = v.voteCount;
            winnersCount = 0;
            consideredWinners[winnersCount] = v;
            winnersCount = 1;
        }
    }
    printf("\t-------------------------\n");
    printf("\tTotal Votes Cast: %d\n", totalVotes);
    printf("\tWinner(s):\n");
    if (winnersCount == 0 && maxVotes == 0) {
        printf("\tNo votes cast.\n");
    } else if (winnersCount == 1) {
        Candidate *winner = getCandidateById(consideredWinners[0].candidateId);
        printf("\tCandidate ID: %d, Name: %s with %d votes\n", winner->id, winner->name, consideredWinners[0].voteCount);
    } else {
        for (size_t i = 0; i < winnersCount; i++) {
            Candidate *winner = getCandidateById(consideredWinners[i].candidateId);
            printf("\tCandidate ID: %d, Name: %s with %d votes\n", winner->id, winner->name, consideredWinners[i].voteCount);
        }
        printf("\tIt's a tie!\n");
    }
}

void addtoVotedVotersIdsList(int voterId) {
    FILE *file = fopen(votedVotersIdsFile, "a");
    if (file == NULL) {
        perror("Failed to open voted voters IDs file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d\n", voterId);
    fclose(file);
    hasVottedVotersIdsList[hasVottedVotersIdsListSize] = voterId;
    hasVottedVotersIdsListSize++;
}

void EraseVotes() {
    FILE *fp = fopen(voteFile, "w");
    fclose(fp);
    votesListSize = 0;
    fp = fopen(votedVotersIdsFile, "w");
    fclose(fp);
    hasVottedVotersIdsListSize = 0;
}

