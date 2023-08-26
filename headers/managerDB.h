#ifndef MANAGERDB_H
#define MANAGERDB_H
#include <sqlite3.h>
#include <string>
#include <vector>

class SQLiteManager{
public:
    SQLiteManager(const char* dbname);
    ~SQLiteManager();
//funciones
    bool openDataBase(const std::string& nombreDB);

    void closeDataBase();

    void querryDataBase(const std::string& texto);
//variables globales
    
struct fila_resultado {
    int id;
    std::string nombre;
};
struct dataUser{
    int id;
    std::string nombre;
    std::string apellido;
    std::string fechaNacimiento;
    std::vector<std::string> telefonos;
    int edad;
    int antiguedadEmpresa;
    std::string correo;
    int codigoVenta; // representa la clave foranea en idVenta de la tabla ventas
    int idPuesto;  // Un identificador que representa la relación con el puesto en otra tabla
};
private:
    sqlite3* db; //puntero a la base de datos
    static int callback(void* data, int argc, char** argv, char** azColName);

};


#endif /* MANAGERDB_H */
