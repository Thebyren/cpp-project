#ifndef MENU_H
#define MENU_H
#include <ncurses.h>
#include<vector>
#include<string>
std::string userInput(WINDOW *win, int y, int x, const std::string &message);
class printMenu{

    private:
    
    
    public:
    printMenu(WINDOW *win, const std::vector<std::string> &choices, int yMAX, int xMAX);
    int getSelected();
    int selected;
};

#endif /* MENU_H
 */
