#ifndef MENU_H
#define MENU_H
#include "Globals.h"

typedef struct {
    char title[100];
    int (*fn)(GlobalVars *states);
} MenuItem;

typedef struct
{
    MenuItem *items;
    int count;
    int capacity;
} MenuList;

enum MenuResult {
    MENU_CONTINUE = 1,
    MENU_EXIT = 0,
    MENU_BACK = -1
};


void addMenu(MenuList *menuList, const char *title, int (*fn)(GlobalVars *states)) {
    if (menuList->count == menuList->capacity) {
        menuList->capacity = (menuList->capacity == 0) ? 4 : menuList->capacity * 2;
        menuList->items = realloc(menuList->items, sizeof(MenuItem) * menuList->capacity);
    }

    strcpy(menuList->items[menuList->count].title, title);
    menuList->items[menuList->count].fn = fn;
    menuList->count++;
}

void clearMenu(MenuList *menuList) {
    menuList->count = 0;  // Do NOT free, re-use memory
}

int exitApp(GlobalVars *states) {
    printf("Exiting...\n");
    return 0;
}



void showMenu(MenuList *menuList, GlobalVars *states, void (*buildMenu)(MenuList *, GlobalVars *)) {
    int selected = 0;

    while (1) {
        buildMenu(menuList, states);  // dynamic build

        system("cls");
        printf("=== Dynamic Menu ===\n\n");

        for (int i = 0; i < menuList->count; i++) {
            if (i == selected)
                printf(" --> %s\n", menuList->items[i].title);
            else
                printf("     %s\n", menuList->items[i].title);
        }

        int key = getch();
        int sequence = 1;
        if (key == 0 || key == 224) {
            key = getch();
            if (key == 72) selected = (selected - 1 + menuList->count) % menuList->count;
            if (key == 80) selected = (selected + 1) % menuList->count;
        }
        else if (key == 13) {
            system("cls");
            sequence = menuList->items[selected].fn(states);  
        }
        if (sequence == MENU_CONTINUE) continue;
        else if (sequence == MENU_EXIT) exit(0);
        else if (sequence == MENU_BACK) break;
        
        
        
        //free(menuList)  // rebuild menu next loop
    }
}
#endif

