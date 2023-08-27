#include "../headers/managerDB.h"
#include <iostream>
#include <string>
#include <vector>

SQLiteManager::SQLiteManager(const char* dbname) : db(nullptr) {
    openDataBase(dbname);
}

SQLiteManager::~SQLiteManager() {
    closeDataBase();
}

bool SQLiteManager::openDataBase(const std::string& nombreDB) {
    int rc = sqlite3_open(nombreDB.c_str(), &db);
    if (rc == SQLITE_OK) {
        std::cout << rc << " true" << std::endl;
        return true;
    } else {
        std::cerr << rc << " false" << std::endl;
        return false;
    }
}

void SQLiteManager::closeDataBase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}


void SQLiteManager::querryDataBase(const std::string& querry){
char* errorMessage = nullptr;
    int rc = sqlite3_exec(db, querry.c_str(), nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "Error executing query: " << errorMessage << std::endl;
        sqlite3_free(errorMessage); // Liberar memoria del mensaje de error
    }

}
std::vector<dataUser> SQLiteManager::obtenerRegistrosUsuarios(int id) {
        std::vector<dataUser> registros;

        std::string consulta = "SELECT nombres, apellidos, fechaNacimiento, edad, antiguedadEmpresa, correoElectronico, codigoVenta, puesto FROM usuarios where id ="+std::to_string(id)+";";
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, consulta.c_str(), -1, &stmt, nullptr);
        if (rc == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                dataUser usuario;
                usuario.nombre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                usuario.apellido = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                usuario.fechaNacimiento = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                usuario.edad = sqlite3_column_int(stmt, 3);
                usuario.antiguedadEmpresa = sqlite3_column_int(stmt, 4);
                usuario.correo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                usuario.codigoVenta = sqlite3_column_int(stmt, 6);
                usuario.idPuesto = sqlite3_column_int(stmt, 7);

                registros.push_back(usuario);
            }
            sqlite3_finalize(stmt);
        } else {
            std::cerr << "Error al ejecutar la consulta: " << sqlite3_errmsg(db) << std::endl;
        }

        return registros;
    }

std::string SQLiteManager::newUser( const dataUser& user) {
    std::string consulta = "INSERT INTO usuarios (nombres, apellidos, fechaNacimiento, edad, antiguedadEmpresa, correoElectronico, codigoVenta, Puesto) VALUES (";
    consulta += "'" + user.nombre + "', ";
    consulta += "'" + user.apellido + "', ";
    consulta += "'" + user.fechaNacimiento + "', ";
    consulta += std::to_string(user.edad) + ", ";
    consulta += std::to_string(user.antiguedadEmpresa) + ", ";
    consulta += "'" + user.correo + "', ";
    consulta += std::to_string(user.codigoVenta) + ", ";
    consulta += std::to_string(user.idPuesto) + ");";

    return consulta;
}