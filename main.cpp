#include <ncurses.h>
#include <string>
#include <form.h>
using namespace std;
void winmain(){
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    attron(COLOR_PAIR(1));
    box(stdscr,0,0);
    attroff(COLOR_PAIR(1));
}
int main() {
    initscr();  // Inicializa NCurses
    cbreak();   // Deshabilita el búfer de línea (actuación inmediata de teclas)
    echo();   // No muestres las teclas presionadas en la pantalla
    keypad(stdscr, TRUE);  // Habilita el uso de teclas especiales
    start_color(); // habilita el uso de colores por la terminal.

    winmain();
    int xMAX, yMAX;

    getmaxyx(stdscr, yMAX, xMAX);
    WINDOW * win1 = newwin(yMAX/2, xMAX/2, yMAX/4,xMAX/4);
    box(win1, 0,0);

    mvwprintw(win1, 4,4,"eleccion");

    refresh();
    wrefresh(win1);
    getch();
    endwin();   // Finaliza NCurses
    return 0;
}