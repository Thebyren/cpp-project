#include "../headers/menu.h"
printMenu::printMenu(WINDOW *win, const std::vector<std::string> &choices, int yMAX, int xMAX)
{
    selected = 0;
    int choice;
    WINDOW *titulo = newwin(yMAX / 3, xMAX - 10, 1, 5);
    keypad(win, true);
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    init_pair(7, COLOR_WHITE, COLOR_RED);
    init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(10, COLOR_YELLOW, COLOR_BLACK);
    const std::string aviso = " use las flechas del teclado para desplazarse, use enter para seleccionar";
    while (1)
    {
        werase(win); // Borrar el contenido de la ventana
        box(win, 0, 0);
        box(titulo, 0, 0);
        for (int i = 1; i < 1 + choices.size(); i++)
        {

            box(titulo, 0, 0);
            if (i - 1 == selected)
                wattron(win, COLOR_PAIR(i));
            box(win, 0, 0);
            mvwprintw(win, ((yMAX / 2) - choices.size()) + i, (xMAX / 2) - (choices[i - 1].length() / 2), choices[i - 1].c_str());
            wattroff(win, COLOR_PAIR(i));

            wattron(win, COLOR_PAIR(7));

            mvwprintw(win, yMAX - 1, (xMAX / 2) - (aviso.length() / 2), aviso.c_str());
            wattroff(win, COLOR_PAIR(7));
        }

        box(titulo, 0, 0);
        wrefresh(win);
        wattron(titulo, COLOR_PAIR(10));
        std::string ascii1 = "  _             \t _  _                        \t _   _ _  _  _   ";
        std::string ascii2 = " | _| _ _ _ _  _ \t| \\| |_  _ _   _ _ _ _  \t| | | | \\| |/ _ \\ ";
        std::string ascii3 = " | _/ _` | ' \\(_-<\t| .` | || | '  \\/ -_) '_/ _ \\ \t| |_| | .` | (_) |";
        std::string ascii4 = " |_|\\__,_|_||_/__/\t|_|\\_|\\_,_|_|_|_\\___|_| \\___/\t \\___/|_|\\_|\\___/ ";
        std::string mensaje2 = "fans numero UNO, control de procesos super importantes";
        mvwprintw(titulo, 2, (xMAX / 2) - (5 + ascii4.length() / 2), ascii1.c_str());
        mvwprintw(titulo, 3, (xMAX / 2) - (5 + ascii4.length() / 2), ascii2.c_str());
        mvwprintw(titulo, 4, (xMAX / 2) - (5 + ascii4.length() / 2), ascii3.c_str());
        mvwprintw(titulo, 5, (xMAX / 2) - (5 + ascii4.length() / 2), ascii4.c_str());
        wattroff(titulo, COLOR_PAIR(10));
        mvwprintw(titulo, 7, (xMAX / 2) - (4 + mensaje2.length() / 2), mensaje2.c_str());
        wrefresh(titulo);

        choice = wgetch(win);
        switch (choice)
        {
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
    box(titulo, 0, 0);
    wdeleteln(titulo);
}
int printMenu::getSelected()
{
    return selected;
}
std::string userInput(WINDOW *win, int y, int x, const std::string &message)
{
    echo();
    wmove(win, y, x);
    wprintw(win, message.c_str());
    // Dibuja la línea horizontal para simular el campo de entrada
    wattron(win, COLOR_PAIR(8));
    mvwhline(win, y + 1, x + message.length(), ACS_S1, message.length());
    wattroff(win, COLOR_PAIR(8));
    wrefresh(win);

    std::string input;
    int ch;
    int col = x + message.length();

    while ((ch = mvwgetch(win, y, col)) != KEY_F(2))
    {
        if (ch == '\n')
        {
            break;
        }
        else if (ch == KEY_BACKSPACE || ch == 127)
        { // Tecla retroceso
            if (!input.empty())
            {
                input.pop_back();
                col--;
                // mvwaddch(win, y, col, ' '); // Borra el caracter en la pantalla
                mvwaddstr(win, y, col, "    ");
                wrefresh(win);
            }
        }
        else
        {
            input += static_cast<char>(ch);
            col++;
            wrefresh(win);
        }
    }
    noecho();
    return input;
}
