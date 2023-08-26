#ifndef MANAGERDB_H
#define MANAGERDB_H
#include <sqlite3.h>
#include <string>
#include <vector>


struct dataUser{
    int id;
    std::string nombre;
    std::string apellido;
    std::string fechaNacimiento;
    std::vector<std::string> telefonos;
    std::string ubicacion;
    int edad;
    int antiguedadEmpresa;
    std::string correo;
    int codigoVenta; // representa la clave foranea en idVenta de la tabla ventas
    int idPuesto;  // Un identificador que representa la relación con el puesto en otra tabla
};
class SQLiteManager{
public:
    SQLiteManager(const char* dbname);
    ~SQLiteManager();
//funciones
    bool openDataBase(const std::string& nombreDB);

    void closeDataBase();

    void querryDataBase(const std::string& texto);
    std::string newUser(const dataUser& user);
//variables globales

private:
    sqlite3* db; //puntero a la base de datos
};


#endif /* MANAGERDB_H */
