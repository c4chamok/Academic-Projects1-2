#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact
{
    int id;
    char phoneNumber[12];
    char contactName[100];
};


int main()
{
    // char numbers[5][12] = {"01874464640", "01874464641", "01874464640"};
    // char names[5][100] = {"Mr. Abdul", "B", "C"};
    struct Contact contacts[50] = {{ 1, "01874464640", "Mr. Abdul" }};
    int currentNumContacts = 1;

    while (1)
    {
        printf("1. view contacts\n");
        printf("2. create new\n");
        printf("3. exit\n");

        int choise;
        printf("choose an option : ");
        scanf("%d", &choise);

        if (choise == 1)
        {
            for (int i = 0; i < currentNumContacts; i++)
            {
                // printf("%d %d", strlen(numbers[i]), strlen(names[i]));
                if (strlen(contacts[i].phoneNumber) != 0 && strlen(contacts[i].contactName) != 0)
                {
                    printf("%s : %s\n", contacts[i].contactName, contacts[i].phoneNumber);
                }
            }
            
            printf("\n0. Home\n");
            printf("1. exit\n");
            printf("choise : ");
            scanf("%d", &choise);

            if (choise == 0)
            {
                continue;
            } else if (choise == 1)
            {
                break;
            } else {
                continue;
            }
            
        }
        else if (choise == 2)
        {

            printf("Enter number : ");
            scanf("%s", contacts[currentNumContacts].phoneNumber);
            printf("Enter contact name : ");
            scanf("%s", contacts[currentNumContacts].contactName);
            printf("Contact Saved named %s", contacts[currentNumContacts].contactName);
            currentNumContacts++;
            printf("\n0. Home\n");
            printf("1. exit\n");
            printf("choise : ");
            scanf("%d", &choise);

            if (choise == 0)
            {
                continue;
            } else if (choise == 1)
            {
                break;
            } else {
                continue;
            }
            
        }
        else if (choise == 3)
        {
            break;
        }
        else
        {
            continue;
        }
    }

    return 0;
}
