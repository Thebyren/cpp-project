#ifndef _JUGADOR_H_
#define _JUGADOR_H_
#include<curses.h>
class Jugador{
    public:
    Jugador(WINDOW * win, int y, int x, char c);
        void mvUp();
        void mvDown();
        void mvRight();
        void mvLeft();

        int getmv();
        void display();
    private:
        int xloc,yloc, xMAX, yMAX;
        char personaje;
        WINDOW *curwin;
};

Jugador::Jugador(WINDOW * win, int y, int x, char c){
    curwin = win;
    yloc = y;
    xloc = x;
    getmaxyx(curwin, yMAX, xMAX);
    keypad(curwin, true);
    personaje = c;

};
void Jugador::mvUp(){
    mvwaddch(curwin, yloc, xloc, ' ');
    yloc--;
    if(yloc <1){
        yloc = 1;
    }
}
void Jugador::mvDown(){
    mvwaddch(curwin, yloc, xloc, ' ');
        yloc++;
    if(yloc > yMAX-2){
        yloc = yMAX -2;
    }
}
void Jugador::mvLeft(){
    mvwaddch(curwin, yloc, xloc, ' ');
        xloc--;
    if(xloc <1){
        xloc = 1;
    }
}
void Jugador::mvRight(){
    mvwaddch(curwin, yloc, xloc, ' ');
        xloc++;
    if(xloc > xMAX -2){
        xloc = xMAX-2;
    }
}
int Jugador::getmv(){
    int choice = wgetch(curwin);
    switch (choice)
    {
    case KEY_UP:
        mvUp();
        break;
    case KEY_DOWN:
        mvDown();
        break;
    case KEY_LEFT:
        mvLeft();
        break;
    case KEY_RIGHT:
        mvRight();
        break;
    
    default:
        break;
    }
    return choice;
}
void Jugador::display(){
    mvwaddch(curwin, yloc, xloc, personaje);
}

#endif 