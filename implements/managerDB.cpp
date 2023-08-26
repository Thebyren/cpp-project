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
