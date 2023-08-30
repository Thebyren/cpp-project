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
    void nominaEmpleados(const ParametrosVentana& params);
    void ventas(const ParametrosVentana& params);
    void reportes(const ParametrosVentana& params);
    void sueldos(const ParametrosVentana& params);

};

#endif /* FUNCIONES_H */
