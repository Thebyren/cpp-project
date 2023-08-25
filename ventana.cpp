#include<iostream>
#include<curses.h>
using namespace std;

int main(){
    int yMAXIMO, xMAXIMO;
    initscr();
    cbreak();
    getmaxyx(stdscr, yMAXIMO, xMAXIMO);

    refresh();
    WINDOW * ventana = newwin(yMAXIMO,xMAXIMO,0,0);
    box(ventana, 0,0);
    mvwprintw(ventana, 5,5,"ingrese su sueldo");
    string sueldo;


    mvwprintw(ventana, 7,5, sueldo.c_str());
    wrefresh(ventana);

    getch();
    return 0;
}