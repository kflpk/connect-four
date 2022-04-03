#pragma once
#include <ncurses.h>

void wfill(WINDOW* win, char c); 
/* ncurses-like function to fill a window with a char
   (space usually) */