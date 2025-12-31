#include "UIBuilder.h"


/* Get maximum menu name width */
int getMaxMenuWidth(Menu menus[], int count) {
    int maxWidth = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(menus[i].name);
        if (len > maxWidth) {
            maxWidth = len;
        }
    }
    return maxWidth;
}

/* Render menus */
void renderMenus(Menu menus[], int count) {
    int maxWidth = getMaxMenuWidth(menus, count) + 7;

    /* Top border */
    printf("\t");
    for (int i = 0; i < maxWidth; i++) {
        printf("#");
    }
    printf("\n");

    /* Menu items */
    for (int i = 0; i < count; i++) {
        int nameLen = strlen(menus[i].name);
        int indexLen = (i + 1 < 10) ? 1 : 2;  // digits in menu index

        printf("\t| %d. %s", i + 1, menus[i].name);

        int spaces = maxWidth - nameLen - 5 - indexLen;
        for (int s = 0; s < spaces; s++) {
            printf(" ");
        }

        printf("|\n");
    }

    /* Bottom border */
    printf("\t");
    for (int i = 0; i < maxWidth; i++) {
        printf("#");
    }
    printf("\n");
}

// int main() {
//     Menu menus[] = {
//         {"Start Voting Session"},
//         {"Stop Voting Session"},
//         {"Show Vote Results"},
//         {"Add Voter"},
//         {"Exit"}
//     };

//     int menuCount = sizeof(menus) / sizeof(menus[0]);

//     renderMenus(menus, menuCount);

//     return 0;
// }
