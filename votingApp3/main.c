#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./VotersDb.h"
#include "./CandidatesDB.h"
#include "./votesDB.h"
#include "./appStates.h"

// ---------- Function Declarations ----------
void addVoter();
void listVoters();
void addCandidate();
void listCandidates();
void initDB();

// ---------- Main Menu ----------
int main()
{
    initDB();
    int choice;
    do
    {
        // system("cls");
        printf("\n==== Voting App ====\n");
        printf("1. Voters Menu\n");
        printf("2. Candidates Menu\n");
        printf("3. Vote Menu\n");
        if (appState.isVotingActive)
        {
            printf("4. cast Vote\n");
        }
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
        case 1:
        {
            int vChoice;
            system("cls");
            printf("\n-- Voters Menu --\n");
            printf("1. List Voters\n");
            printf("2. Add Voter\n");
            printf("0. Back\n");
            printf("Enter choice: ");
            scanf("%d", &vChoice);
            getchar();
            if (vChoice == 1)
                listVoters();
            else if (vChoice == 2)
                addVoter();
            break;
        }
        case 2:
        {
            int cChoice;
            system("cls");
            printf("\n-- Candidates Menu --\n");
            printf("1. List Candidates\n");
            printf("2. Add Candidate\n");
            printf("0. Back\n");
            printf("Enter choice: ");
            scanf("%d", &cChoice);
            getchar();
            if (cChoice == 1)
                listCandidates();
            else if (cChoice == 2)
                addCandidate();
            break;
        }
        case 3:
            // castVote();
            system("cls");
            printf("\n-- Vote Menu --\n");
            if (appState.isVotingActive)
            {
                printf("1. Stop Vote\n");
                printf("0. Back\n");
                printf("Enter choice: ");
                scanf("%d", &choice);
                getchar();
                if (choice == 1)
                {
                    stopCasting();
                }
            }
            else
            {
                printf("1. Initiate Vote\n");
                printf("2. Show Vote Results\n");
                printf("3. Erase All Votes\n");
                printf("0. Back\n");
                printf("Enter choice: ");
                scanf("%d", &choice);
                getchar();
                if (choice == 1)
                {
                    system("cls");
                    initiateVote();
                    printf("Voting has been initiated.\n");
                    getchar();
                }
                else if (choice == 2)
                {
                    system("cls");
                    showVoteResult();
                    getchar();
                }
                else if (choice == 3)
                {
                    system("cls");
                    EraseVotes();
                    printf("All votes have been erased.\n");
                    getchar();
                }
            }

            break;
        case 4:
            if (appState.isVotingActive)
            {
                system("cls");
                printf("---- Cast Your Vote ----\n");
                int voterId, candidateId;
                printf("Enter your Voter ID: ");
                scanf("%d", &voterId);
                Voter *v = getVoterById(voterId);
                if (v == NULL)
                {
                    printf("Invalid Voter ID.\n");
                    break;
                }
                
                printf("Welcome, %s!\n", (*v).name);
                if (checkIfVoterHasVoted(voterId)) {
                    printf("You have already voted. Thank you!\n");
                    break;
                }
                for (size_t i = 0; i < candidatesListSize; i++)
                {
                    Candidate c = candidatesList[i];
                    printf("Candidate ID: %d, Name: %s\n", c.id, c.name);
                }

                printf("Enter Candidate ID to vote for: ");
                scanf("%d", &candidateId);
                submitVote(voterId, candidateId);
                
            }
            break;
        case 0:
            system("cls");
            printf("Exiting...\n");
            break;
        default:
            system("cls");
            printf("Invalid choice!\n");
            getchar();
            break;
        }

    } while (choice != 0);

    return 0;
}

// ---------- Function Definitions ----------

// Ensure files exist
void initDB()
{
    votersInit();
    candidatesInit();
    printf("Candidates DB initialized.\n");
    initVoteStats();
    initializeAppState();
    printf("App State initialized.\n");
}

// Add voter
void addVoter()
{
    char vName[100];
    printf("Enter Voter Name: ");
    fgets(vName, 100, stdin);
    vName[strcspn(vName, "\n")] = 0;
    insertVoter(vName);
}

// List voters
void listVoters()
{
    system("cls");
    getVotersList();
    printf("\nID\tName\n");
    printf("------------------\n");
    for (size_t i = 0; i < votersListSize; i++)
    {
        Voter v = votersList[i];
        printf("%d\t%s\n", v.id, v.name);
    }
    getchar();
}

// Add candidate
void addCandidate()
{
    system("cls");
    listVoters();
    Candidate c;

    printf("Enter Voter ID for this candidate: ");
    scanf("%d", &c.voterId);
    getchar();

    insertCandidate(c.voterId);
    getchar();
}

// List candidates
void listCandidates()
{
    system("cls");
    getCandidatesList();
    Candidate c;
    printf("\nID\tName\tVoterID\n");
    printf("-------------------------\n");
    for (size_t i = 0; i < candidatesListSize; i++)
    {
        c = candidatesList[i];
        printf("%d\t%s\t%d\n", c.id, c.name, c.voterId);
    }
    getchar();
}
