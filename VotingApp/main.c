#include <stdio.h>
#include <string.h>
#include <conio.h> // for getch()

#define MAX_CANDIDATES 50
#define MAX_NAME_LEN 100

int main()
{
    int numCandidates, numVoters;
    char candidates[MAX_CANDIDATES][MAX_NAME_LEN];
    int votes[MAX_CANDIDATES] = {0};

    printf("Enter number of candidates: ");
    scanf("%d", &numCandidates);
    getchar(); // consume newline

    for (int i = 0; i < numCandidates; i++)
    {
        printf("Enter name of candidate %d: ", i + 1);
        fgets(candidates[i], MAX_NAME_LEN, stdin);
        candidates[i][strcspn(candidates[i], "\n")] = 0; // remove newline
    }

    printf("\nEnter number of voters: ");
    scanf("%d", &numVoters);

    for (int i = 0; i < numVoters; i++)
    {
        int choice = -1;

        printf("\nVoter %d, please vote:\n", i + 1);
        for (int j = 0; j < numCandidates; j++)
        {
            printf("%d. %s\n", j + 1, candidates[j]);
        }
        printf("0. Skip / Not Voting\n");

        printf("Enter your choice (1-%d or 0): ", numCandidates);

        // hide input
        char ch;
        while (1)
        {
            ch = getch();
            if (ch < '0' || ch > '9')
            {
                printf("\nInvalid input. Please enter a digit (0-%d): ", numCandidates);
                continue;
            }
            int digit = ch - '0';
            if (digit < 0 || digit > numCandidates)
            {
                printf("\nInvalid candidate number. Please enter (0-%d): ", numCandidates);
                continue;
            }
            break;
        }
        choice = ch - '0';

        // Print * instead of number
        printf("*\n");

        if (choice == 0)
        {
            printf("Vote skipped.\n");
            continue;
        }

        if (choice >= 1 && choice <= numCandidates)
        {
            votes[choice - 1]++;
            printf("Vote recorded.\n");
        }
        else
        {
            printf("Invalid candidate number.\n");
        }
    }

    // show result
    printf("\n--- Voting Results ---\n");
    for (int i = 0; i < numCandidates; i++)
    {
        printf("%s: %d votes\n", candidates[i], votes[i]);
    }

    // find winner
    int maxVotes = 0, winnerIndex = -1;
    for (int i = 0; i < numCandidates; i++)
    {
        if (votes[i] > maxVotes)
        {
            maxVotes = votes[i];
            winnerIndex = i;
        }
    }

    if (winnerIndex != -1)
        printf("\nWinner: %s with %d votes!\n", candidates[winnerIndex], maxVotes);
    else
        printf("\nNo votes were cast.\n");

    return 0;
}
