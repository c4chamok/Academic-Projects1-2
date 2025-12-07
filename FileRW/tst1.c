#include <stdio.h>
#include <string.h>

struct Contact
{
    int id;
    char phoneNumber[12];
    char contactName[100];
};

int main()
{
    // char numbers[5][12] = {"01584365740", "01584365741", "01584365742"};
    // char names[5][100] = {"Mr. Abdul", "B", "C"};
    // int currentNumContacts = 3;
    // struct Contact contacts[50] = {{ 1, "01874464640", "Mr. Abdul" }, { 2, "01584365741", "B" }};
    FILE *fpr = fopen("./Contacts.txt", "r");
    if (fpr == NULL)
    {
        printf("no file found");
    }
    printf("file found\n");

    struct Contact newCont;

    while (fscanf(fpr, "%d | %[^|] | %[^|\n]", &newCont.id, newCont.contactName, newCont.phoneNumber) == 3)
    {
        printf("%s : %s\n", newCont.contactName, newCont.phoneNumber);
        /* code */
    }
    

    return 0;
}
