#include "../headers/reportes.h"
#include "../headers/managerDB.h"
#include "../headers/menu.h"
void colores(){
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
}
void printCustom(WINDOW *win, int y, int x, const char *format, ...)
{
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
void reportes::NominaGeneral(const ParametrosVentana &params)
{
    clear();
    SQLiteManager manager("base.db");
    wclear(params.ventana);
    WINDOW *win = newwin(params.yMAX, params.xMAX, 0, 0);
    box(win, 0, 0);
    prestaciones prestaciones;
    std::vector<dataUser> registros = manager.obtenerRegistrosUsuarios();
    int row = 1;
    colores();
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 3, 6, " id ");
    wattroff(win, COLOR_PAIR(1));
    
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 11, " nombre ");
    wattroff(win, COLOR_PAIR(2));
    
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 3, 28, " puesto ");
    wattroff(win, COLOR_PAIR(3));
    
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 3, 49, " sueldo liquido ");
    wattroff(win, COLOR_PAIR(4));
    
    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 3, 66, " comision ");
    wattroff(win, COLOR_PAIR(5));
    
    wattron(win, COLOR_PAIR(6));
    mvwprintw(win, 3, 78, " igss ");
    wattroff(win, COLOR_PAIR(6));
    
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 3, 86, " Boleto de ornato ");
    wattroff(win, COLOR_PAIR(1));
    for (dataUser user : registros)
    {
        nominaGeneralEmpleado nge;
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
        float total = manager.obtenerTotalVentas(user.id);
        prestaciones = manager.obtenerPrestaciones(total);
        float comision = prestaciones.comision * total;
        float igss = puesto.salario * 0.0483;
        float isr = prestaciones.isr * total;
        std::string idstr = std::to_string(user.id);
        std::string nomstr = user.nombre;
        float Bostr = prestaciones.boletoOrnato;
        float SLstr = (puesto.salario + puesto.bonificacion + comision) - (igss + isr + prestaciones.boletoOrnato);
        mvwprintw(win, 4 + row, 6, idstr.c_str());
        mvwprintw(win, 4 + row, 11, nomstr.c_str());
        mvwprintw(win, 4 + row, 28, puesto.nombre.c_str());
        mvwprintw(win, 4 + row, 49, "%.2f", SLstr);
        mvwprintw(win, 4 + row, 66, "%.2f", comision);
        mvwprintw(win, 4 + row, 78, "%.2f", igss);
        mvwprintw(win, 4 + row, 86, "%.2f", Bostr);

        row+=2;
    }

    std::string msg = " enter para salir ";
    wattron(win, A_REVERSE);
    mvwprintw(win, params.yMAX - 1, (params.xMAX / 2) - (msg.size() / 2), msg.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);
    wgetch(win);
    wdeleteln(win);
}

void reportes::DatosGenerales(const ParametrosVentana &params)
{
    clear();
    SQLiteManager manager("base.db");
    start_color();
    wclear(params.ventana);
    WINDOW *win = newwin(params.yMAX, params.xMAX, 0, 0);
    box(win, 0, 0);
    prestaciones prestaciones;
    std::vector<dataUser> registros = manager.obtenerRegistrosUsuarios();
    int row = 1;

    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 3, 6, "id");
    wattroff(win, COLOR_PAIR(1));
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 11, "nombre");
    wattroff(win, COLOR_PAIR(2));
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 3, 28, "apellidos");
    wattroff(win, COLOR_PAIR(3));
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, 3, 43, "puesto");
    wattroff(win, COLOR_PAIR(4));
    wattron(win, COLOR_PAIR(5));
    mvwprintw(win, 3, 65, "sueldo");
    wattroff(win, COLOR_PAIR(5));
    wattron(win, COLOR_PAIR(6));
    mvwprintw(win, 3, 75, "edad");
    wattroff(win, COLOR_PAIR(6));
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 3, 85, "fecha de nacimiento");
    wattroff(win, COLOR_PAIR(1));
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 105, "correo");
    wattroff(win, COLOR_PAIR(2));
    std::vector<puestos> puestoRef = manager.obtenerPuestos();
    puestos puesto;
    for (dataUser user : registros)
    {
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
        mvwprintw(win, 4 + row, 6, "%d", user.id);
        mvwprintw(win, 4 + row, 11, user.nombre.c_str());
        mvwprintw(win, 4 + row, 28, user.apellido.c_str());
        mvwprintw(win, 4 + row, 43, puesto.nombre.c_str());
        mvwprintw(win, 4 + row, 65, "%.f", puesto.salario);
        mvwprintw(win, 4 + row, 75, "%d", user.edad);
        mvwprintw(win, 4 + row, 85, user.fechaNacimiento.c_str());
        mvwprintw(win, 4 + row, 105, user.correo.c_str());

        std::vector<telefonos> registrosTelefonos = manager.obtenerTelefonos(user.id);
        mvwprintw(win, 4 + row + 1, 6, "Ubicacion: %s", user.ubicacion.c_str());
        /*
        int c = 0;
        for (const telefonos &telefono : registrosTelefonos)
        {
            std::string datatelefonos = "telefono de " + telefono.tipo + ": " + std::to_string(telefono.numero);
            printCustom(win, 6 + row, 6 + c, datatelefonos.c_str());
            c += 35;
        }*/
        row += 4; // Aumentar la fila para la siguiente entrada de usuario
    }

    // termina la ventana
    std::string msg = " enter para salir ";
    wattron(win, A_REVERSE);
    mvwprintw(win, params.yMAX - 1, (params.xMAX / 2) - (msg.size() / 2), msg.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);
    wgetch(win);
    wdeleteln(win);
}
void reportes::Salarios(const ParametrosVentana &params)
{
    clear();
    SQLiteManager manager("base.db");
    wclear(params.ventana);
    WINDOW *win = newwin(params.yMAX, params.xMAX, 0, 0);
    box(win, 0, 0);
    prestaciones prestaciones;
    std::vector<dataUser> registros = manager.obtenerRegistrosUsuarios();
    int row = 1;
    mvwprintw(win, 3, 6, "id");
    mvwprintw(win, 3, 11, "nombre");
    mvwprintw(win, 3, 28, "puesto");
    mvwprintw(win, 3, 49, "sueldo liquido");
    mvwprintw(win, 3, 66, "comision");
    mvwprintw(win, 3, 78, "igss");
    mvwprintw(win, 3, 86, "salario base");
    mvwprintw(win, 3, 100, "total ventas");
    for (dataUser user : registros)
    {
        nominaGeneralEmpleado nge;
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
        float total = manager.obtenerTotalVentas(user.id);
        prestaciones = manager.obtenerPrestaciones(total);
        float comision = prestaciones.comision * total;
        float igss = puesto.salario * 0.0483;
        float isr = prestaciones.isr * total;
        std::string idstr = std::to_string(user.id);
        std::string nomstr = user.nombre;
        float Bostr = prestaciones.boletoOrnato;
        float SLstr = (puesto.salario + puesto.bonificacion + comision) - (igss + isr + prestaciones.boletoOrnato);
        mvwprintw(win, 4 + row, 6, idstr.c_str());
        mvwprintw(win, 4 + row, 11, nomstr.c_str());
        mvwprintw(win, 4 + row, 28, puesto.nombre.c_str());
        mvwprintw(win, 4 + row, 49, "%.2f", SLstr);
        mvwprintw(win, 4 + row, 66, "%.2f", comision);
        mvwprintw(win, 4 + row, 78, "%.2f", igss);
        mvwprintw(win, 4 + row, 86, "%.2f", puesto.salario);
        mvwprintw(win, 4 + row, 100, "%.2f", total);

        row+=2;
    }

    std::string msg = " enter para salir ";
    wattron(win, A_REVERSE);
    mvwprintw(win, params.yMAX - 1, (params.xMAX / 2) - (msg.size() / 2), msg.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);
    wgetch(win);
    wdeleteln(win);
};
