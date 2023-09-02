#include "../headers/funciones.h"
#include "../headers/managerDB.h"
#include "../headers/menu.h"

bool funciones::ventas(const ParametrosVentana &params)
{
    SQLiteManager manager("base.db");
    ventasUser venta;
    wclear(params.ventana);
    WINDOW *win = newwin(params.yMAX, params.xMAX, 0, 0);
    box(win, 0, 0);
    venta.idVenta = manager.obtenerIdVenta() + 1;
    venta.idVendedor = std::stoi(userInput(win, 2, 3, "ingrese el id del vendedor: "));
    venta.detalles = userInput(win, 4, 3, "ingrese los detalles de la compra:  ");
    venta.monto = std::stoi(userInput(win, 6, 3, "ingrese el monto de la venta: "));
    manager.querryDataBase(manager.newVenta(venta));
    manager.closeDataBase();

    std::string msg = " enter para salir ";
    wattron(win, A_REVERSE);
    mvwprintw(win, params.yMAX - 1, (params.xMAX / 2) - (msg.size() / 2), msg.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);
    wgetch(win);
    wdeleteln(win);
    return false;
};
