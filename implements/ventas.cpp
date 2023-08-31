#include"../headers/funciones.h"
#include "../headers/managerDB.h"
#include"../headers/menu.h"

void funciones::ventas(const ParametrosVentana& params){
    SQLiteManager manager("base.db");
    ventasUser venta;
    wclear(params.ventana);
    WINDOW*win = newwin(params.yMAX,params.xMAX,0,0);
    box(win,0,0);
    venta.idVenta = manager.obtenerIdVenta()+1;
    venta.idVendedor = std::stoi(userInput(win, 2,3,"ingrese el id del vendedor: "));
    venta.detalles= userInput(win, 4, 3, "ingrese los detalles de la compra:  ");
    venta.monto = std::stoi(userInput(win,6,3,"ingrese el monto de la venta: "));
    manager.querryDataBase(manager.newVenta(venta));
    manager.closeDataBase();
    wgetch(win);
    wdeleteln(win);
};
