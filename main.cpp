#include "headers/header.h"
using namespace std;

int xMAX, yMAX;

void inicio(){
    initscr();
    start_color();
    noecho();
    getmaxyx(stdscr,yMAX,xMAX);
    keypad(stdscr, true);
}

void fin(){
    refresh();
    clear();
    printf("finalizo el programa");
    endwin();
}
int main() {
    inicio();
    WINDOW* ventana = newwin(yMAX, xMAX, 0,0);
    printMenu menu(ventana, principalMenu, yMAX, xMAX);
    int n = menu.getSelected();
    fin();
    cout<<"su seleccion fue: "<<principalMenu[n];
    return 0;
}