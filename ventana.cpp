#include<iostream>
#include<curses.h>
#include<cmath>
using namespace std;

string userInput(WINDOW *win, int x, int y, const std::string &message) {
    wmove(win, y, x);
    wprintw(win, message.c_str());
    wrefresh(win);

    std::string input;
    int ch;
    int col = x + message.length();

    while ((ch = mvwgetch(win, y, col)) != KEY_F(2)) {
    if (ch == '\n') {
        break;
    } else {
        input += static_cast<char>(ch);
        col++;
        wrefresh(win);
    }
}

    return input;
}


int main(){
    int yMAXIMO, xMAXIMO;
    initscr();
    cbreak();
    getmaxyx(stdscr, yMAXIMO, xMAXIMO);

    refresh();
    WINDOW * ventana = newwin(yMAXIMO,xMAXIMO,0,0);
    box(ventana, 0,0);
    
    
    // y eso es como un cin
    string sueldo = userInput(ventana, 6,5, "ingrese su sueldo: "); 

    
    int sueldoINT = stoi(sueldo);
    float sueldoFLOAT = stof(sueldo);
    
    string resultado = to_string(round(sueldoFLOAT/2));
    mvwprintw(ventana, 7,5, "la mitad de su sueldo es %s" , resultado.c_str());// muy importante el %s y c_str, 
                                                                    //asi pueden agregar la variable
    wrefresh(ventana);
    getch();
    return 0;
}