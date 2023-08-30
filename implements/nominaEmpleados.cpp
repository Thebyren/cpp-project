#include "../headers/funciones.h"
#include "../headers/menu.h"
#include "../headers/managerDB.h"
#include "../headers/fecha.h"
#include <cctype>
#include <algorithm>

void funciones::nominaEmpleados(const ParametrosVentana &params)
{

    dataUser usuario;

    SQLiteManager manager("base.db");
    clear();
    refresh();
    WINDOW *win = newwin(params.yMAX, params.xMAX-1, 0, 0);
    box(win, 0, 0);
    wrefresh(win);
    usuario.id = 1;
    usuario.nombre = userInput(win, 2, 2, "ingresa tu nombre: ");
    usuario.apellido = userInput(win, 4, 2, "ingresa tu apellido: ");
    WINDOW *winAux = newwin(params.yMAX, params.xMAX / 2, 0, params.xMAX / 2);

    std::vector<puestos> puesto = manager.obtenerPuestos();
    int fila = 1;
    for (const puestos &puestos : puesto)
    {
        int idP = puestos.idPuesto;
        std::string n = puestos.nombre;
        std::string mensaje = "id " + std::to_string(idP) + " " + n;
        mvwprintw(winAux, fila, (params.xMAX / 4) - 30, mensaje.c_str());
        fila++;
        box(winAux, 0, 0);
        wrefresh(winAux);
    }
    usuario.idPuesto = std::stoi(userInput(win, 6, 2, "selecciona el id del puesto: "));
    wclear(winAux);
    std::vector<departamentos> departamento = manager.obtenerDepartamentos();
    fila = 1;
    for (const departamentos &departamentos : departamento)
    {
        int idDP = departamentos.id;
        std::string nP = departamentos.nombre;
        std::string mensaje = "id: " + std::to_string(idDP) + " " + nP;
        mvwprintw(winAux, fila, (params.xMAX / 4) - 30, mensaje.c_str());
        fila++;
        box(winAux, 0, 0);
        wrefresh(winAux);
    }
    int DP = std::stoi(userInput(win, 8, 2, "ingrese id del Departamento: "));
    std::vector<municipios> municipio = manager.obtenerMunicipios(DP);
    wclear(winAux);
    fila = 1;
    for (const municipios &municipios : municipio)
    {
        int idDP = municipios.id;
        std::string nP = municipios.nombre;
        std::string mensaje = "id: " + std::to_string(idDP) + " " + nP;
        mvwprintw(winAux, fila, (params.xMAX / 4) - 30, mensaje.c_str());
        fila++;
        box(winAux, 0, 0);
        wrefresh(winAux);
    }
    int MP = std::stoi(userInput(win, 10, 2, "ingrese el id del municipio: "));
    std::vector<aldeas> aldea = manager.obtenerAldeas(MP);
    wclear(winAux);
    fila = 1;
    for (const aldeas &aldeas : aldea)
    {
        int idDP = aldeas.id;
        std::string nP = aldeas.nombre;
        std::string mensaje = "id: " + std::to_string(idDP) + " " + nP;
        mvwprintw(winAux, fila, (params.xMAX / 4) - 30, mensaje.c_str());
        fila++;
        box(winAux, 0, 0);
        wrefresh(winAux);
    }
    int AD = std::stoi(userInput(win, 12, 2, "ingrese el id de aldea: "));
    wclear(winAux);
    wrefresh(winAux);
    usuario.ubicacion = manager.obtenerUbicacion(DP, MP, AD);
    usuario.correo = userInput(win, 14, 2, "ingrese su correo electronico: ");
    std::vector<telefonos> registros;
    for (int i = 0; i < 3; i++)
    {
        box(winAux, 0, 0);
        std::string tipos[3] = {
            "casa", "trabajo", "personal"};
        std::string temp;
        telefonos telefono;
        mvwprintw(winAux, 3, 4, "Es opcional rellenar todos los telefonos");
        temp = userInput(winAux, 4 + i * 2, 4, "ingrese el numero de " + tipos[i] + ": ");
        if (temp.empty())
        {
            continue;
        }
        try
        {
            temp.erase(std::remove_if(temp.begin(), temp.end(), [](char c)
                                      { return !std::isdigit(c); }),
                       temp.end());
            telefono.numero = std::stoi(temp); // Convertir la cadena a un número entero
        }
        catch (...)
        {
            wrefresh(winAux);
            i--;
            continue; // Continuar con la siguiente iteración
        }
        telefono.tipo = tipos[i];
        registros.push_back(telefono);
    }

    int row = 6;
    for (const telefonos &telefono : registros)
    {
        mvwprintw(winAux, row * 2, 4, "telefono: %d", telefono.numero); // Cambiar %d a %s si 'numero' es una cadena
        row++;
        wrefresh(winAux);
    }

    mvwprintw(winAux, 16, 4, "ingrese la fecha de nacimento en el formato \"1Enero2023\" ");
    usuario.fechaNacimiento = userInput(winAux, 17, 4, "ingrese la fecha: "); // Aquí reemplaza con la fecha real
    // Extraer los últimos 4 caracteres de la cadena para obtener el año
    std::string anioStr = usuario.fechaNacimiento.substr(usuario.fechaNacimiento.size() - 4);
    // Convertir el año a un valor numérico
    int anioNacimiento = std::stoi(anioStr);
    // Calcular la edad aproximada
    int anioActual = ObtenerAnioActual(); // Cambia esto con el año actual
    usuario.edad = anioActual - anioNacimiento;
    mvwprintw(winAux, 18,4,"la edad es: %d", usuario.edad);

    usuario.antiguedadEmpresa = std::stoi(userInput(winAux, 20, 4, "ingrese su antiguedad en la empresa: "));
    wgetch(winAux);

    
    manager.querryDataBase(manager.newPhone(registros, usuario.id));
    getch();
    wclear(winAux);
    wdeleteln(winAux);

    // finaliza la instancia general
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    std::string msg = " enter para salir ";
    start_color();
    wattron(win, A_REVERSE);
    mvwprintw(win, params.yMAX - 1, (params.xMAX / 2) - (msg.size() / 2), msg.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);

    getch();
};
