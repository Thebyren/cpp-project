#include<iostream>
#include<curses.h>
#include<cmath>
using namespace std;

string userInput(WINDOW *win, int y, int x, const std::string &message) {
    echo();
    wmove(win, y, x);
    wprintw(win, message.c_str());

    // Dibuja la línea horizontal para simular el campo de entrada
    mvwhline(win, y + 1, x + message.length(), ACS_S1, message.length());

    wrefresh(win);

    std::string input;
    int ch;
    int col = x + message.length();

    while ((ch = mvwgetch(win, y, col)) != KEY_F(2)) {
        if (ch == '\n') {
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127) { // Tecla retroceso
            if (!input.empty()) {
                input.pop_back();
                col--;
                //mvwaddch(win, y, col, ' '); // Borra el caracter en la pantalla
                mvwaddstr(win, y, col, "    ");
                wrefresh(win);
            }
        } else {
            input += static_cast<char>(ch);
            col++;
            wrefresh(win);
        }
    }
    noecho();
    return input;
}

int main(){
    int yMAXIMO, xMAXIMO;
    cbreak();
    initscr();
    noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
    attron(COLOR_PAIR(1));
    box(stdscr,0,0);
    attroff(COLOR_PAIR(1));
    getmaxyx(stdscr, yMAXIMO, xMAXIMO);
    refresh();

    WINDOW * ventana = newwin(yMAXIMO/2,xMAXIMO/2,yMAXIMO/4,xMAXIMO/4);
    box(ventana, 0,0);
    
    
    // y eso es como un cin
    string sueldo = userInput(ventana, 6,5, "ingrese su sueldo: "); 

    
    int sueldoINT = stoi(sueldo);
    float sueldoFLOAT = stof(sueldo);
    
    string resultado = to_string(round(sueldoFLOAT/2));
    mvwprintw(ventana, 8,6, "la mitad de su sueldo es %s" , resultado.c_str());// muy importante el %s y c_str, 
                                                                    //asi pueden agregar la variable
    string nombre = userInput(ventana, 9,6, "ingrese su nombre: ");
    mvwprintw(ventana, 11,6,"su nombre es: %s" , nombre.c_str());

    wrefresh(ventana);
    getch();
    wclear(ventana);
    box(ventana,0,0);
    wrefresh(ventana);
    getch();
    
    return 0;
}