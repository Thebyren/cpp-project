#include<ncurses.h>
#include<string>
#include<vector>

std::vector<std::string> choices={
    "nomina de empleados",
    "ventas",
    "nomina de ventas por empleado",
    "  salir "
};
void printMenu(WINDOW *win, const std::vector<std::string> &choices, int yMAX, int xMAX){
    int selected = 0;
    int choice;
    init_pair(1,COLOR_BLACK,COLOR_BLUE);
    init_pair(2,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(3,COLOR_BLACK,COLOR_YELLOW);
    init_pair(4,COLOR_BLACK,COLOR_BLUE);
    init_pair(5,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(6,COLOR_BLACK,COLOR_YELLOW);
    while (1) {
        werase(win); // Borrar el contenido de la ventana
        box(win, 0, 0);

        for (int i = 1; i < 1+choices.size(); i++) {
            
            if (i-1 == selected)
                wattron(win, COLOR_PAIR(i));
            
            mvwprintw(win, ((yMAX/2)-choices.size())+i, (xMAX/2)-(choices[i-1].length()/2), choices[i-1].c_str());
            wattroff(win, COLOR_PAIR(i));

        }

        wrefresh(win);

        choice = wgetch(win);
        switch (choice) {
            case KEY_UP:
                selected--;
                if (selected < 0)
                    selected = 0;
                break;
            case KEY_DOWN:
                selected++;
                if (selected >= choices.size())
                    selected = choices.size() - 1;
                break;
            default:
                break;
        }

        if (choice == 10) // Enter key
            break;
    }
}
int main(){
    initscr();
    noecho();
    start_color();
    int yMAX,xMAX;
    getmaxyx(stdscr, yMAX,xMAX);
    box(stdscr,0,0);
    wrefresh(stdscr);
    WINDOW*win = newwin(yMAX/2,xMAX/2,yMAX/4,xMAX/4);
    box(win,0,0);
    keypad(win, true);
    printMenu(win, choices, yMAX/2,xMAX/2);
    getch();
    endwin();
    return 0 ;    
}
