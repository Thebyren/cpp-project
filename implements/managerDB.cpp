#include "../headers/managerDB.h"
#include <iostream>
#include <string>
#include <vector>

SQLiteManager::SQLiteManager(const char *dbname) : db(nullptr)
{
    openDataBase(dbname);
}

SQLiteManager::~SQLiteManager()
{
    closeDataBase();
}

bool SQLiteManager::openDataBase(const std::string &nombreDB)
{
    int rc = sqlite3_open(nombreDB.c_str(), &db);
    if (rc == SQLITE_OK)
    {
        std::cout << rc << " true" << std::endl;
        return true;
    }
    else
    {
        std::cerr << rc << " false" << std::endl;
        return false;
    }
}

void SQLiteManager::closeDataBase()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

void SQLiteManager::querryDataBase(const std::string &querry)
{
    char *errorMessage = nullptr;
    int rc = sqlite3_exec(db, querry.c_str(), nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Error executing query: " << errorMessage << std::endl;
        sqlite3_free(errorMessage); // Liberar memoria del mensaje de error
    }
}
std::vector<dataUser> SQLiteManager::obtenerRegistrosUsuarios()
{
    std::vector<dataUser> registros;

    std::string consulta = "SELECT nombres, apellidos, fechaNacimiento, edad, antiguedadEmpresa, correoElectronico, puesto FROM usuarios ;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            dataUser usuario;
            usuario.nombre = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            usuario.apellido = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            usuario.fechaNacimiento = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            usuario.edad = sqlite3_column_int(stmt, 3);
            usuario.antiguedadEmpresa = sqlite3_column_int(stmt, 4);
            usuario.correo = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
            usuario.idPuesto = sqlite3_column_int(stmt, 6);

            registros.push_back(usuario);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return registros;
}
// se obtienen los datos de los puestos
std::vector<puestos> SQLiteManager::obtenerPuestos()
{
    std::vector<puestos> registros;

    std::string consulta = "SELECT nombre, salario, bonificacion, idPuesto FROM puestos ;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            puestos puesto;
            puesto.nombre = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            puesto.salario = sqlite3_column_double(stmt, 1);
            puesto.bonificacion = sqlite3_column_double(stmt, 2);
            puesto.idPuesto = sqlite3_column_int(stmt, 3);

            registros.push_back(puesto);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return registros;
}
// se obtienen los datos de los departementos
std::vector<departamentos> SQLiteManager::obtenerDepartamentos()
{
    std::vector<departamentos> registros;

    std::string consulta = "SELECT id, nombre FROM  departamentos;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            departamentos departamento;
            departamento.id = sqlite3_column_double(stmt, 0);
            departamento.nombre = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            registros.push_back(departamento);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return registros;
}
// se obtienen los datos de los municipios
std::vector<municipios> SQLiteManager::obtenerMunicipios(int id)
{
    std::vector<municipios> registros;

    std::string consulta = "SELECT id, nombre, departamento_id FROM  municipios where departamento_id = " + std::to_string(id) + ";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            municipios municipio;
            municipio.id = sqlite3_column_double(stmt, 0);
            municipio.nombre = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            municipio.idDP = sqlite3_column_double(stmt, 2);
            registros.push_back(municipio);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return registros;
}
// se obtienen los datos de aldeas
std::vector<aldeas> SQLiteManager::obtenerAldeas(int id)
{
    std::vector<aldeas> registros;

    std::string consulta = "SELECT id, nombre, municipio_id FROM  aldeas where municipio_id = " + std::to_string(id) + ";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            aldeas aldea;
            aldea.id = sqlite3_column_double(stmt, 0);
            aldea.nombre = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            aldea.idMP = sqlite3_column_double(stmt, 2);
            registros.push_back(aldea);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return registros;
}

double SQLiteManager::obtenerTotalVentas(int id)
{
    std::string consulta = "SELECT monto FROM ventas WHERE idVendedor = " + std::to_string(id) + ";";
    sqlite3_stmt *stmt;

    double totalMonto = 0.0; // Cambio en el nombre y tipo de dato
    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            totalMonto += sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return totalMonto;
}
int SQLiteManager::obtenerId()
{
    std::string consulta = "SELECT id FROM usuarios ORDER BY id DESC LIMIT 1";
    sqlite3_stmt *stmt;
    int lastid;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            lastid = sqlite3_column_int(stmt, 0);
        }
        else
        {
            lastid = 0; // No se encontraron registros, asignar valor predeterminado
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
    return lastid;
}

int SQLiteManager::obtenerIdVenta()
{
    std::string consulta = "SELECT idventa FROM ventas ORDER BY idventa DESC LIMIT 1";
    sqlite3_stmt *stmt;
    int lastid;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            lastid = sqlite3_column_int(stmt, 0);
        }
        else
        {
            lastid = 0; // No se encontraron registros, asignar valor predeterminado
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
    return lastid;
}

dataUser SQLiteManager::obtenerDatosEmpleado(int id)
{
    dataUser user;
    std::string consulta = "SELECT id, nombres, apellidos, puesto, fechaNacimiento, edad, antiguedadEmpresa, correoElectronico FROM usuarios WHERE id = "+std::to_string(id)+";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            user.id= sqlite3_column_int(stmt, 0);
            user.nombre= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            user.apellido = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            user.idPuesto = sqlite3_column_int(stmt, 3);
            user.fechaNacimiento = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
            user.edad = sqlite3_column_int(stmt, 5);
            user.antiguedadEmpresa = sqlite3_column_int(stmt, 6);
            user.correo= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));

        }
        else
        {
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
    return user;
}
std::string SQLiteManager::obtenerUbicacion(int DP, int MP, int AD)
{
    std::string ubicacion, departamento, municipio, aldea;
    std::string consulta = "SELECT d.nombre AS nombre_departamento, m.nombre AS nombre_municipio, a.nombre AS nombre_aldea FROM departamentos d JOIN municipios m ON d.id = m.departamento_id JOIN aldeas a ON m.id = a.municipio_id WHERE d.id = " + std::to_string(DP) + " AND m.id = " + std::to_string(MP) + " AND a.id = " + std::to_string(AD) + ";";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            departamento = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            municipio = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            aldea = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }
    ubicacion = departamento + ", " + municipio + ", " + aldea;

    return ubicacion;
}
prestaciones SQLiteManager::obtenerPrestaciones(double sueldo)
{
    prestaciones datos;
    std::string consulta = "SELECT rangoVentas, comision, isr, irtra, boletoOrnato FROM prestaciones;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            double rangoMin = sqlite3_column_double(stmt, 0);
            double comision = sqlite3_column_double(stmt, 1);
            double isr = sqlite3_column_double(stmt, 2);
            double irtra = sqlite3_column_double(stmt, 3);
            double boletoOrnato = sqlite3_column_double(stmt, 4);

            if (sueldo <= rangoMin)
            {
                datos.rango = rangoMin;
                datos.comision = comision;
                datos.isr = isr;
                datos.irtra = irtra;
                datos.boletoOrnato = boletoOrnato;
                break; // Ya encontramos el rango adecuado, salimos del ciclo
            }
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
    }

    return datos;
}

std::string SQLiteManager::newPhone(std::vector<telefonos> registros, int id)
{
    std::string consulta = "INSERT INTO telefonos (userId, numero, tipo) VALUES ";
    for (const telefonos &telefono : registros)
    {
        consulta += "(" + std::to_string(id) + ", ";        // Se corrigió el cierre de comillas simples
        consulta += std::to_string(telefono.numero) + ", "; // Convertir el número a cadena
        consulta += "'" + telefono.tipo + "'),";
    }

    // Eliminar la coma y el espacio extra al final
    consulta = consulta.substr(0, consulta.size() - 1); // Se cambió de -2 a -1 para quitar solo la coma
    consulta += ";";

    return consulta;
}

std::string SQLiteManager::newVenta(const ventasUser &venta)
{
    std::string consulta = "INSERT INTO ventas (idVenta, idvendedor, detalles, monto) VALUES (";
    consulta += std::to_string(venta.idVenta) + ", ";
    consulta += std::to_string(venta.idVendedor) + ", ";
    consulta += " ' " + venta.detalles + "', ";
    consulta += std::to_string(venta.monto) + ");";
    return consulta;
}
std::string SQLiteManager::newUser(const dataUser &user)
{
    std::string consulta = "INSERT INTO usuarios (nombres, apellidos, fechaNacimiento, edad, antiguedadEmpresa, correoElectronico, Puesto) VALUES (";
    consulta += "'" + user.nombre + "', ";
    consulta += "'" + user.apellido + "', ";
    consulta += "'" + user.fechaNacimiento + "', ";
    consulta += std::to_string(user.edad) + ", ";
    consulta += std::to_string(user.antiguedadEmpresa) + ", ";
    consulta += "'" + user.correo + "', ";
    consulta += std::to_string(user.idPuesto) + ");";

    return consulta;
}