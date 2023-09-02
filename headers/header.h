#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ncurses.h>
#include <string>
#include "managerDB.h"
#include "menu.h"
#include "funciones.h"

// void (opciones[3]() = {nominaEmpleados, ventas, Sueldos, reportes})

const std::vector<std::string> principalMenu = {
    " registro de empleados ",
    " ventas ",
    " nomina de sueldos ",
    " reportes ",
    " salir "};
int xMAX, yMAX;
funciones objetofuncion;
bool(funciones::*lista[4])(const ParametrosVentana &params) = {
    &funciones::nominaEmpleados,
    &funciones::ventas,
    &funciones::sueldos,
    &funciones::reportes};

void inicio()
{
    initscr();
    start_color();
    noecho();
    getmaxyx(stdscr, yMAX, xMAX);
    keypad(stdscr, true);
    refresh();
    wrefresh(stdscr);
}

void fin()
{
    refresh();
    clear();
    endwin();
    printf(" finalizo el programa ");
}

#endif /* HEADER_H */
