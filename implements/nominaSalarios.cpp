#include "../headers/funciones.h"
#include "../headers/managerDB.h"
#include "../headers/menu.h"
#include <cstdarg>
#include<string.h>
void msgCustom(WINDOW* win, int y, int x, const char* format, ...) {
    va_list args;
    va_start(args, format);
    wmove(win, y, x);
    int bufferSize = 1024; // Tamaño del búfer para almacenar la cadena formateada
    char buffer[bufferSize];
    vsnprintf(buffer, bufferSize, format, args);
    wprintw(win, buffer);
    va_end(args);
    // Dibuja la línea horizontal para simular el campo de entrada
    wattron(win, COLOR_PAIR(8));
    mvwhline(win, y + 1, x, ACS_S1, strlen(buffer));
    wattroff(win, COLOR_PAIR(8));
}
void funciones::sueldos(const ParametrosVentana &params)
{
    WINDOW *win = newwin(params.yMAX, params.xMAX, 0, 0);
    SQLiteManager manager("base.db");
    dataUser user;
    prestaciones prestaciones;
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(1));
    wrefresh(win);
    int id = std::stoi(userInput(win, 5, 5, "ingrese el id del empleado: "));
    user = manager.obtenerDatosEmpleado(id);
    float total = manager.obtenerTotalVentas(id);
    prestaciones = manager.obtenerPrestaciones(total);

    std::vector<puestos> puestoRef = manager.obtenerPuestos();
    puestos puesto;
    for (const puestos &puestos : puestoRef)
    {
        if (puestos.idPuesto == user.idPuesto)
        {
            puesto.idPuesto = puestos.idPuesto;
            puesto.nombre = puestos.nombre;
            puesto.salario = puestos.salario;
            puesto.bonificacion = puestos.bonificacion;
        }
    }

    std::string resumen = "id: " + std::to_string(user.id) + " nombre: " + user.nombre + " " + user.apellido;
    mvwprintw(win, 8, 5, resumen.c_str());
    msgCustom(win, 9, 5, "puesto: %s", puesto.nombre.c_str());
    msgCustom(win, 11, 5, "salario: %.2f", puesto.salario);
    msgCustom(win, 13, 5, "monto total de ventas: %.2f", total);
    float igss = puesto.salario * 0.0483;
    msgCustom(win, 15, 5, "IGSS:  %.2f", igss);
    float comision = prestaciones.comision * total;
    msgCustom(win, 17, 5, "su comision es de %.2f", comision);
    float isr = prestaciones.isr * total;
    msgCustom(win, 19, 5, "su ISR es de %.2f", isr);
    msgCustom(win, 21, 5, "su boleto de ornato debe ser de: %.2f", prestaciones.boletoOrnato);
    float sueldoLiquido = (puesto.salario + puesto.bonificacion + comision) - (igss + isr + prestaciones.boletoOrnato);
    msgCustom(win, 23, 5, "su sueldo liquido es de: %.2f", sueldoLiquido);

    std::string msg = " enter para salir ";
    wattron(win, A_REVERSE);
    mvwprintw(win, params.yMAX - 1, (params.xMAX / 2) - (msg.size() / 2), msg.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);

    wgetch(win);
    wdeleteln(win);
};
