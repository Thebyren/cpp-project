#ifndef MANAGERDB_H
#define MANAGERDB_H
#include <sqlite3.h>
#include <string>
#include <vector>

struct departamentos
{
    int id;
    std::string nombre;
};
struct municipios
{
    int id;
    std::string nombre;
    int idDP;
};
struct aldeas
{
    int id;
    std::string nombre;
    int idMP;
};
struct telefonos
{
    int id;
    int numero;
    std::string tipo;
};
struct ventasUser
{
    int idVenta;
    int idVendedor;
    std::string detalles;
    int monto;
};

struct puestos
{
    std::string nombre;
    float salario;
    float bonificacion;
    int idPuesto;
};
struct prestaciones
{
    int rango;
    float comision;
    float isr;
    float irtra;
    float boletoOrnato;
};
struct nominaGeneralEmpleado
{
    float sueldoLiquido;
    float comision;
    float igss;
    float isr;
    float irtra;
    float boletoOrnato;
};
struct dataUser
{
    int id;
    std::string nombre;
    std::string apellido;
    std::string fechaNacimiento;
    std::string ubicacion;
    std::string correo;
    int edad;
    int antiguedadEmpresa;
    int idPuesto; // Un identificador que representa la relación con el puesto en otra tabla
};
class SQLiteManager
{
    sqlite3 *db; // puntero a la base de datos
public:
    SQLiteManager(const char *dbname);
    ~SQLiteManager();
    // funciones
    bool openDataBase(const std::string &nombreDB);

    void closeDataBase();

    void querryDataBase(const std::string &texto);
    std::string newUser(const dataUser &user);
    std::string newPhone(std::vector<telefonos> telefonos, int id);
    std::string newVenta(const ventasUser &);

    std::vector<dataUser> obtenerRegistrosUsuarios();
    std::vector<puestos> obtenerPuestos();
    std::vector<departamentos> obtenerDepartamentos();
    std::vector<municipios> obtenerMunicipios(int id);
    std::vector<aldeas> obtenerAldeas(int id);
    std::string obtenerUbicacion(int DP, int MP, int AD);
    int obtenerId();
    int obtenerIdVenta();
    dataUser obtenerDatosEmpleado(int id);
    double obtenerTotalVentas(int id);
    prestaciones obtenerPrestaciones(double sueldo);
    // variables globales

private:
};
#endif /* MANAGERDB_H */
