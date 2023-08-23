#include <iostream>
#include <curses.h>
#include <string>

using namespace std;

int main() {
    initscr();
    start_color();
    noecho();
    curs_set(0);
    cbreak();

    init_pair(1, COLOR_RED, COLOR_BLACK);

    int xMAX, yMAX;
    getmaxyx(stdscr, xMAX, yMAX);

    WINDOW *win = newwin(xMAX / 2, yMAX / 2, xMAX / 4, yMAX / 4);

    refresh();
    wrefresh(win);

    keypad(win, true);

    string choices[3] = {"primario", "secundario", "terciario"};
    int choice, highlight = 0;

    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, 2 + i, 2, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        wrefresh(win);

        choice = wgetch(win);
        switch (choice) {
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
        }
        
        // Ensure the highlight stays within valid range
        if (highlight >= 3) {
            highlight = 0;
        } else if (highlight < 0) {
            highlight = 2;
        }

        // Handle ENTER key press to select an option
        if (choice == 10) {
            break; // Exit the loop when Enter is pressed
        }
    }
    printw("tu eleccion fue  %s",choices[highlight].c_str());

    getch();
    endwin();
    return 0;
}
