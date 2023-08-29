#ifndef HEADER_H
#define HEADER_H

#include<iostream>
#include<ncurses.h>
#include <string>
#include "managerDB.h"
#include "menu.h"
#include"funciones.h"

//void (opciones[3]() = {nominaEmpleados, ventas, Sueldos, reportes})

const std::vector<std::string> principalMenu={
    "registro de empleados",
    "ventas",
    "nomina de sueldos",
    "reportes",
    "  salir "
};
int xMAX, yMAX;
funciones objetofuncion;
void (funciones::*lista[4])() = {
            &funciones::nominaEmpleados,
            &funciones::ventas,
            &funciones::sueldos,
            &funciones::reportes
};

void inicio(){
    initscr();
    start_color();
    noecho();
    getmaxyx(stdscr,yMAX,xMAX);
    keypad(stdscr, true);
    mvprintw(-yMAX,-xMAX,"use las flechas del teclado para seleccionar");
}

void fin(){
    refresh();
    clear();
    printf("finalizo el programa");
    endwin();
}

#endif /* HEADER_H */
