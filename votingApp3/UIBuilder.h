#ifndef MENU_BUILDER_H
#define MENU_BUILDER_H

#include <stdio.h>
#include <string.h>
typedef struct {
    const char *name;
} Menu;

int getMaxMenuWidth(Menu menus[], int count);
void renderMenus(Menu menus[], int count);

#endif