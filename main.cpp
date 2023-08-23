#include <iostream>
#include <curses.h>
#include <string>
#include <ctime>
#include "jugador.h"
using namespace std;

int main() {
    initscr();
    noecho();
    cbreak();


    //obtener datos de la pantalla
    int yMAX, xMAX;
    getmaxyx(stdscr, yMAX,xMAX);

    // crear la ventana
    WINDOW * mainwin = newwin(20,50,(yMAX/2)-10,10);
    box(mainwin,0,0);
    refresh();
    wrefresh(mainwin);

    Jugador * p = new Jugador(mainwin, 1,1 ,'@');
    do{
        p->display();
        wrefresh(mainwin);
    }while(p-> getmv()!='x');


    //cerrar todo
    endwin();
    return 0;
}
