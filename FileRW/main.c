#include <stdio.h>
#include <string.h>
#include <conio.h>

void getPassword(char *password, size_t size) {
    int i = 0;
    char ch;

    printf("Enter password: ");
    while ((ch = getch()) != '\r' && i < size - 1) {
        if (ch == '\b' && i > 0) {  // handle backspace
            i--;
            printf("\b \b");
        } else {
            password[i++] = ch;
            printf("*"); // show * instead of character
        }
    }
    password[i] = '\0';
    printf("\n");
}

int main() {
    struct Users {
        int id;
        char email[250];
        char password[250];

    };

    // FILE *fpw = fopen("users.txt", "w");
    
    // struct Users newUser = { 1, "a@b.com", "a12345" };

    // fprintf(fpw, "%d %s %s", newUser.id, newUser.email, newUser.password);
    // fclose(fpw);

    FILE *fpr = fopen("users.txt", "r");

    struct Users theUser;

    char reqEmail[250], reqPassword[250];
    printf("Enter email: ");
    scanf("%s", reqEmail);
    // getPassword(reqPassword, sizeof(reqPassword));
    int found = 0;
    // printf("%s", reqEmail);

    while (fscanf(fpr, "%d %s %s", &theUser.id, theUser.email, theUser.password) == 3)
    {        
        // printf("%d %s %s\n", theUser.id, theUser.email, theUser.password);
        // printf("%s %s %d", theUser.email, reqEmail, strcmp(theUser.email, reqEmail));
        if (strcmp(theUser.email, reqEmail)==0)
        {
            printf("found");
            found = !found;
            break;
        }
        
    }

    if (!found)
    {
        printf("not found");
    }
    

    fclose(fpr);

    return 0;
}
