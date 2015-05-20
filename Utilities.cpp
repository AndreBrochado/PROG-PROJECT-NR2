//
// Created by up201403057 on 20-05-2015.
//

#include "Utilities.h"

void setColor(unsigned int color, unsigned int background_color) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (background_color == 0)
        SetConsoleTextAttribute(hCon, color);
    else
        SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
                                      BACKGROUND_RED);
}

void setColor(unsigned int color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

