#include "headers/header.h"
int main() {
    while(1){
    inicio();

    WINDOW* ventana = newwin(yMAX, xMAX, 0,0);
    int n ;

    ParametrosVentana paramsWin ;
    paramsWin.ventana = ventana;
    paramsWin.xMAX = xMAX;
    paramsWin.yMAX = yMAX;
    
    while(1){
        printMenu menu(ventana, principalMenu, yMAX, xMAX);
        
        n= menu.getSelected();
        (objetofuncion.*lista[n])(paramsWin);
     if(n == 4 ){
            break;
        }
    }
    
    fin();
    std::cout<<"su seleccion fue: "<<principalMenu[n];
    return 0;
    }
}