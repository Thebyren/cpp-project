#include "../headers/menu.h"
#include "../headers/reportes.h"
#include "../headers/funciones.h"
#include<iostream>
const std::vector<std::string> opciones = {
    " Reporte datos generales de los empleados  ",
    " Reporte de nomina general de los empleados ",
    " Reporte de salarios ",
    " salir "

};
reportes objetoreportes;
void (reportes::*listaReportes[3])(const ParametrosVentana &params) = {
    &reportes::DatosGenerales,
    &reportes::NominaGeneral,
    &reportes::Salarios};

bool funciones::reportes(const ParametrosVentana &params)
{

    int n;
    WINDOW *win = newwin(params.yMAX, params.xMAX, 0, 0);
    while (1)
    {
        printMenu menu(win, opciones, params.yMAX, params.xMAX);
        
        n = menu.getSelected();

        if (n >= 0 && n < 3)
        {
            (objetoreportes.*listaReportes[n])(params);
        }
        else{
            std::cout<<"hola";
        }
        mvwprintw(win, 4, 4, "el la eleccion es: %d", n);
        if (n == 3)
        {
            return true;
            continue;

        }
    }
    return false;
};
