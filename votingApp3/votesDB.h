#ifndef VOTES_DB_H
#define VOTES_DB_H
#include "candidatesDB.h"
#include "VotersDb.h"
#include "appStates.h"

typedef struct {
    int id;
    int candidateId;
    int voteCount;
} Vote;

extern Vote votesList[100];
extern int votesListSize;
extern const char *voteFile;

void initiateVote();
void initVoteStats();
void submitVote(int voterId, int candidateId);
int checkIfVoterHasVoted(int voterId);
void stopCasting();
void addtoVotedVotersIdsList(int voterId);
void showVoteResult();
void EraseVotes();


#endif