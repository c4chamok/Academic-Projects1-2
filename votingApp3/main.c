#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./VotersDb.h"
#include "./CandidatesDB.h"
#include "./votesDB.h"
#include "./appStates.h"
#include "./UIBuilder.h"

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
    Menu menus[20];
    int currentMenuCount = 0;
    do
    {
        system("cls");
        printf("\n\t ==== Voting App ====\n");
        currentMenuCount = 0;
        menus[currentMenuCount++] = (Menu){"Voters Menu"};
        menus[currentMenuCount++] = (Menu){"Candidates Menu"};
        menus[currentMenuCount++] = (Menu){"Vote Menu"};
        if (appState.isVotingActive)
        {
            menus[currentMenuCount] = (Menu){"Cast Vote"};
            currentMenuCount++;
        }
        
        renderMenus(menus, currentMenuCount);
        printf("\t0. Exit\n");
        printf("\tEnter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
        case 1:
        {
            int vChoice;
            system("cls");
            printf("\n\t-- Voters Menu --\n");
            currentMenuCount = 0;
            menus[currentMenuCount++] = (Menu){"List Voters"};
            menus[currentMenuCount++] = (Menu){"Add Voter"};
            renderMenus(menus, currentMenuCount);
            printf("\t0. Back\n");
            printf("\tEnter choice: ");
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
            printf("\n\t-- Candidates Menu --\n");
            currentMenuCount = 0;
            menus[currentMenuCount++] = (Menu){"List Candidates"};
            menus[currentMenuCount++] = (Menu){"Add Candidate"};
            renderMenus(menus, currentMenuCount);
            printf("\t0. Back\n");
            printf("\tEnter choice: ");
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
            int tempChoice;
            system("cls");
            printf("\n\t-- Vote Menu --\n");
            if (appState.isVotingActive)
            {
                currentMenuCount = 0;
                menus[currentMenuCount++] = (Menu){"Stop Vote"};
                renderMenus(menus, currentMenuCount);
                printf("\t0. Back\n");
                printf("\tEnter choice: ");
                scanf("%d", &tempChoice);
                getchar();
                if (tempChoice == 1)
                {
                    stopCasting();
                }
            }
            else
            {
                currentMenuCount = 0;
                menus[currentMenuCount++] = (Menu){"Initiate Vote"};
                menus[currentMenuCount++] = (Menu){"Show Vote Results"};
                menus[currentMenuCount++] = (Menu){"Erase All Votes"};
                renderMenus(menus, currentMenuCount);
                printf("\t0. Back\n");
                printf("\tEnter choice: ");
                scanf("%d", &tempChoice);
                getchar();
                if (tempChoice == 1)
                {
                    system("cls");
                    initiateVote();
                    printf("\tVoting has been initiated.\n");
                    getchar();
                }
                else if (tempChoice == 2)
                {
                    system("cls");
                    showVoteResult();
                    getchar();
                }
                else if (tempChoice == 3)
                {
                    system("cls");
                    EraseVotes();
                    printf("\tAll votes have been erased.\n");
                    getchar();
                }
            }

            break;
        case 4:
            if (appState.isVotingActive)
            {
                system("cls");
                printf("\t---- Cast Your Vote ----\n");
                int voterId, candidateId;
                printf("\tEnter your Voter ID: ");
                scanf("%d", &voterId);
                getchar();
                Voter *v = getVoterById(voterId);
                if (v == NULL)
                {
                    printf("\tInvalid Voter ID.\n");
                    getchar();
                    break;
                }
                
                printf("\tWelcome, %s!\n", (*v).name);
                if (checkIfVoterHasVoted(voterId)) {
                    printf("\tYou have already voted. Thank you!\n");
                    getchar();
                    break;
                }
                for (size_t i = 0; i < candidatesListSize; i++)
                {
                    Candidate c = candidatesList[i];
                    printf("\tCandidate ID: %d, Name: %s\n", c.id, c.name);
                }

                printf("\tEnter Candidate ID to vote for: ");
                scanf("%d", &candidateId);
                getchar();
                submitVote(voterId, candidateId);
                
            }
            break;
        case 0:
            system("cls");
            printf("\tExiting...\n");
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

void initDB()
{
    votersInit();
    candidatesInit();
    printf("\tCandidates DB initialized.\n");
    initVoteStats();
    initializeAppState();
    printf("\tApp State initialized.\n");
}

// Add voter
void addVoter()
{
    system("cls");
    Voter v;
    printf("\tEnter Voter Name: ");
    fgets(v.name, 100, stdin);
    v.name[strcspn(v.name, "\n")] = 0;
    printf("\tEnter Fathers Name: ");
    fgets(v.fathersName, 100, stdin);
    v.fathersName[strcspn(v.fathersName, "\n")] = 0;
    printf("\tEnter Mothers Name: ");
    fgets(v.mothersName, 100, stdin);
    v.mothersName[strcspn(v.mothersName, "\n")] = 0;
    printf("\tEnter Birth Date(dd/mm/yyyy): ");
    fgets(v.birthDate, 100, stdin);
    v.birthDate[strcspn(v.birthDate, "\n")] = 0;
    printf("\tEnter Address: ");
    fgets(v.address, 100, stdin);
    v.address[strcspn(v.address, "\n")] = 0;
    printf("\tEnter Phone Number: ");
    fgets(v.phoneNumber, 100, stdin);
    v.phoneNumber[strcspn(v.phoneNumber, "\n")] = 0;
    insertVoter(&v);
}

// List voters
void listVoters()
{
    system("cls");
    getVotersList();
    printf("\n\tID\tName\tFathers Name\tMothers Name\tBirth Date\tAddress Phone Number\n");
    printf("\t--------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < votersListSize; i++)
    {
        Voter v = votersList[i];
        printf("\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n", v.id, v.name, v.fathersName, v.mothersName, v.birthDate, v.address, v.phoneNumber);
    }
    printf("\t1. Update Voter\n");
    printf("\t0. Exit\n");
    printf("\tEnter a choise: ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("\tEnter the Id of the voter to Update: \n");
        int id;
        scanf("%d", &id);
        getchar();
        Voter *v = getVoterById(id), tempVoter;
        tempVoter = *v;
        if (v == NULL)
        {
            printf("\tVoter not found!\n");
            getchar();
            return;
        }
        printf("\t1. to update Name: %s\n", (*v).name);
        printf("\t2. to update Fathers Name: %s\n", (*v).fathersName);
        printf("\t3. to update Mothers Name: %s\n", (*v).mothersName);
        printf("\t4. to update Birth Date: %s\n", (*v).birthDate);
        printf("\t5. to update Address: %s\n", (*v).address);
        printf("\t6. to update Phone Number: %s\n", (*v).phoneNumber);
        printf("\tEnter your choice: ");
        int uChoice;
        scanf("%d", &uChoice);
        getchar();
        switch (uChoice)
        {
        case 1:
            printf("\tEnter new Name: ");
            fgets(tempVoter.name, 100, stdin);
            tempVoter.name[strcspn(tempVoter.name, "\n")] = 0;
            strcpy((*v).name, tempVoter.name);
            break;
        case 2:
            printf("\tEnter new Fathers Name: ");
            fgets(tempVoter.fathersName, 100, stdin);
            tempVoter.fathersName[strcspn(tempVoter.fathersName, "\n")] = 0;
            strcpy((*v).fathersName, tempVoter.fathersName);
            break;
        case 3:
            printf("\tEnter new Mothers Name: ");
            fgets(tempVoter.mothersName, 100, stdin);
            tempVoter.mothersName[strcspn(tempVoter.mothersName, "\n")] = 0;
            strcpy((*v).mothersName, tempVoter.mothersName);
            break;
        case 4:
            printf("\tEnter new Birth Date: ");
            fgets(tempVoter.birthDate, 100, stdin);
            tempVoter.birthDate[strcspn(tempVoter.birthDate, "\n")] = 0;
            strcpy((*v).birthDate, tempVoter.birthDate);
            break;
        case 5:
            printf("\tEnter new Address: ");
            fgets(tempVoter.address, 100, stdin);
            tempVoter.address[strcspn(tempVoter.address, "\n")] = 0;
            strcpy((*v).address, tempVoter.address);
            break;
        case 6:
            printf("\tEnter new Phone Number: ");
            fgets(tempVoter.phoneNumber, 100, stdin);
            tempVoter.phoneNumber[strcspn(tempVoter.phoneNumber, "\n")] = 0;
            strcpy((*v).phoneNumber, tempVoter.phoneNumber);
            break;
        default:
            printf("\tInvalid choice!\n");
            getchar();
            return;
        }
        printf("%d | %s | %s | %s | %s | %s | %s\n", 
            tempVoter.id, tempVoter.name, tempVoter.fathersName, 
            tempVoter.mothersName, tempVoter.birthDate, 
            tempVoter.address, tempVoter.phoneNumber);
        updateVoter(&tempVoter);
        printf("\tVoter updated successfully!\n");

    } else if (choice == 0){
        return;
    }
    
    getchar();
}

// Add candidate
void addCandidate()
{
    system("cls");
    Candidate c;

    printf("\n\tID\tName\tFathers Name\tMothers Name\tBirth Date\tAddress Phone Number\n");
    printf("\t--------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < votersListSize; i++)
    {
        Voter v = votersList[i];
        printf("\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n", v.id, v.name, v.fathersName, v.mothersName, v.birthDate, v.address, v.phoneNumber);
    }

    printf("\tEnter Voter ID for this candidate: ");
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
    printf("\n\tID\tName\tVoterID\n");
    printf("\t-------------------------\n");
    for (size_t i = 0; i < candidatesListSize; i++)
    {
        c = candidatesList[i];
        printf("\t%d\t%s\t%d\n", c.id, c.name, c.voterId);
    }
    getchar();
}
