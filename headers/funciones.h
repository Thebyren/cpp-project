#ifndef FUNCIONES_H
#define FUNCIONES_H
#include<vector>
#include<ncurses.h>
struct ParametrosVentana {
    WINDOW* ventana;
    int yMAX;
    int xMAX;
};
class funciones {
public:
    bool nominaEmpleados(const ParametrosVentana& params);
    bool ventas(const ParametrosVentana& params);
    bool reportes(const ParametrosVentana& params);
    bool sueldos(const ParametrosVentana& params);
};
class reportes{
public:
    void DatosGenerales(const ParametrosVentana& params);
    void NominaGeneral(const ParametrosVentana& params);
    void Salarios(const ParametrosVentana& params);
};


#endif /* FUNCIONES_H */
