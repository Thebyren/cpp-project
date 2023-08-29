#include "headers/header.h"
int main() {
    inicio();

    WINDOW* ventana = newwin(yMAX, xMAX, 0,0);
    int n ;
    while(1){
        printMenu menu(ventana, principalMenu, yMAX, xMAX);
        n= menu.getSelected();
        (objetofuncion.*lista[n])();   
        if(n == 4){
            break;
        }
    }

    fin();
    std::cout<<"su seleccion fue: "<<principalMenu[n];
    return 0;
}