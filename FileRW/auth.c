#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char email[250] = "a@b.com";
    char reqEmail[250];
    printf("Enter email: ");
    scanf("%s", reqEmail);

    if (strcmp(email, reqEmail)==0)
    {
        printf("matched");
    } else
    {
        printf("not matched");
    }
    
    
    return 0;
}
